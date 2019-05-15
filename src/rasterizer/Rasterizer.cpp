#include "Rasterizer.hpp"

#include <algorithm>

namespace conrast { namespace  rast {

Rasterizer::Rasterizer()
{}


Rasterizer::Rasterizer(Rasterizer::Options options)
    : m_options(options)
{}


void Rasterizer::setOptions(Rasterizer::Options options) {
    m_options = options;
}


void Rasterizer::render(surface::RenderTarget& renderTarget, const mesh::Mesh& mesh) const {
    switch(m_options.vertexStruct) {
        case Options::VertexStruct::Points: {
            for(const auto& index : mesh.indexes) {
                const auto& vertex = mesh.vertices[index];
                if(vertex.position.z >= 1.0f) {
                    auto posScreen = transformToScreen(vertex.position);
                    if(posScreen.position.x >= -1.0f && posScreen.position.x <= 1.0f
                        && posScreen.position.y >= -1.0f && posScreen.position.y <= 1.0f) {
                        auto rasterPos = renderTarget.convertScreenToRaster(posScreen.position);
                        renderTarget.drawPixel(rasterPos, posScreen.depth, vertex.color);
                    }
                }
            }
            break;
        }
        case Options::VertexStruct::Lines: {
            if(mesh.indexes.size() < 2 || mesh.indexes.size() % 2 != 0) {
                return;
            }
            for(auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
                drawLine(renderTarget, { mesh.vertices[*it++], mesh.vertices[*it++] });
            }
            break;
        }
        case Options::VertexStruct::LineStrip: {
            if(mesh.indexes.size() < 2) {
                return;
            }
            for(auto it = mesh.indexes.begin() + 1; it != mesh.indexes.cend(); it++) {
                drawLine(renderTarget, { mesh.vertices[*(it-1)], mesh.vertices[*it] });
            }
            break;
        }
        case Options::VertexStruct::Triangles: {
            if(mesh.indexes.size() < 3 || mesh.indexes.size() % 3 != 0) {
                return;
            }
            if(m_options.fillType == Options::FillType::Fill) {
                for(auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
                    drawTriangleFilled(renderTarget, { mesh.vertices[*it++], mesh.vertices[*it++], mesh.vertices[*it++] });
                }
            }
            else if(m_options.fillType == Options::FillType::Line) {
                for(auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
                    drawTriangleLines(renderTarget, { mesh.vertices[*it++], mesh.vertices[*it++], mesh.vertices[*it++] });
                }
            }
            break;
        }
        case Options::VertexStruct::TriangleStrip: {
            if(mesh.indexes.size() < 3) {
                return;
            }
            mesh::Triangle triangle = {
                mesh.vertices[mesh.indexes[0]],
                mesh.vertices[mesh.indexes[1]],
                mesh.vertices[mesh.indexes[2]]
            };
            if(m_options.fillType == Options::FillType::Fill) {
                for(auto it = mesh.indexes.begin() + 3; it != mesh.indexes.cend(); it++) {
                    drawTriangleFilled(renderTarget, triangle);
                    triangle.vertices[0] = triangle.vertices[1];
                    triangle.vertices[1] = triangle.vertices[2];
                    triangle.vertices[2] = mesh.vertices[*it];
                }
            }
            else if(m_options.fillType == Options::FillType::Line) {
                for(auto it = mesh.indexes.begin() + 3; it != mesh.indexes.cend(); it++) {
                    drawTriangleLines(renderTarget, triangle);
                    triangle.vertices[0] = triangle.vertices[1];
                    triangle.vertices[1] = triangle.vertices[2];
                    triangle.vertices[2] = mesh.vertices[*it];
                }
            }
            break;
        }
    }

}


Rasterizer::ScreenPixel Rasterizer::transformToScreen(utils::Vec3f position) const {
    return { { position.x / position.z, -position.y / position.z }, position.z - 1.0f };
}


utils::Vec3f Rasterizer::transformToWorld(utils::Vec3f screenPos) const {
    return { screenPos.x * screenPos.z, -screenPos.x * screenPos.z, screenPos.z + 1.0f};
}


color::Color Rasterizer::getInterpolatedColor(utils::Vec3f screenPos, const std::vector<mesh::Vertex> triangle) const {
    // TODO implement
    return triangle[0].color;
}

void Rasterizer::drawLine(surface::RenderTarget& renderTarget, const mesh::Line& line) const {
    auto startScreen = transformToScreen(line.start.position);
    auto endScreen = transformToScreen(line.end.position);
    auto startRaster = renderTarget.convertScreenToRaster(startScreen.position);
    auto endRaster = renderTarget.convertScreenToRaster(endScreen.position);
    auto startToEnd = endRaster - startRaster;
    float length = startToEnd.length();
    utils::Vec2f dir = utils::Vec2f{ static_cast<float>(startToEnd.x), static_cast<float>(startToEnd.y) } / length;
    auto startRasterFloat = utils::Vec2f{ static_cast<float>(startRaster.x), static_cast<float>(startRaster.y) };
    for(float i = 0.0f; i <= length; i += 1.0f) {
        auto rastPos = utils::Vec2i{ static_cast<int>(startRasterFloat.x + i * dir.x), static_cast<int>(startRasterFloat.y + i * dir.y)};
        // TODO depth and color not correct! Must be interpolated
        renderTarget.drawPixel(rastPos, startScreen.depth, line.start.color);
    }
}


void Rasterizer::drawTriangleFilled(surface::RenderTarget &renderTarget, const mesh::Triangle& triangle) const {
    const std::vector<ScreenPixel> screenTriangle = {
            transformToScreen(triangle.vertices[0].position),
            transformToScreen(triangle.vertices[1].position),
            transformToScreen(triangle.vertices[2].position)
    };

    std::vector<utils::Vec2i> rasterTriangleSorted = {
        renderTarget.convertScreenToRaster(screenTriangle[0].position),
        renderTarget.convertScreenToRaster(screenTriangle[1].position),
        renderTarget.convertScreenToRaster(screenTriangle[2].position)
    };
    std::sort(begin(rasterTriangleSorted),
              end(rasterTriangleSorted),
              [](const auto& a, const auto& b) {
                return a.y < b.y;
              }
    );

    auto interpolateX = [](auto start, auto end, int value) {
        return start.x + static_cast<int>(
                    std::roundf(
                        static_cast<float>(end.x - start.x) *
                        (static_cast<float>(value) / static_cast<float>(end.y - start.y))
                    )
                );
    };

    for(int y = rasterTriangleSorted[0].y; y < rasterTriangleSorted[1].y; y++) {
        int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
        int xEnd = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[1], y);
        if(xStart > xEnd) {
            std::swap(xStart, xEnd);
        }
        for(int x = xStart; x <= xEnd; x++) {
            // TODO depth and color not correct! Must be interpolated
            renderTarget.drawPixel({x, y}, screenTriangle[0].depth, triangle.vertices[0].color);
        }
    }
    for(int y = rasterTriangleSorted[1].y; y < rasterTriangleSorted[2].y; y++) {
        int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
        int xEnd = interpolateX(rasterTriangleSorted[1], rasterTriangleSorted[2], y);
        if(xStart > xEnd) {
            std::swap(xStart, xEnd);
        }
        for(int x = xStart; x <= xEnd; x++) {
            // TODO depth and color not correct! Must be interpolated
            renderTarget.drawPixel({x, y}, screenTriangle[0].depth, triangle.vertices[0].color);
        }
    }
}


void Rasterizer::drawTriangleLines(surface::RenderTarget &renderTarget, const mesh::Triangle& triangle) const {
    drawLine(renderTarget, { triangle.vertices[0], triangle.vertices[1] });
    drawLine(renderTarget, { triangle.vertices[1], triangle.vertices[2] });
    drawLine(renderTarget, { triangle.vertices[2], triangle.vertices[0] });
}


} }
