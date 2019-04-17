#include "Rasterizer.hpp"

namespace conrast { namespace  rast {

Rasterizer::Rasterizer()
{}


Rasterizer::Rasterizer(Rasterizer::Options options)
    : m_options(options)
{}


void Rasterizer::setOptions(Rasterizer::Options options) {
    m_options = options;
}


void Rasterizer::render(surface::RenderTarget& renderTarget, const std::vector<mesh::Vertex>& vertices) const {
    switch(m_options.vertexStruct) {
        case Options::VertexStruct::Points: {
            for(const auto& vertex : vertices) {
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
            if(vertices.size() < 2 || vertices.size() % 2 != 0) {
                return;
            }
            for(auto it = vertices.begin(); it != vertices.cend(); ) {
                drawLine(renderTarget, { *it++, *it++ });
            }
            break;
        }
        case Options::VertexStruct::LineStrip: {
            if(vertices.size() < 2) {
                return;
            }
            for(auto it = vertices.begin() + 1; it != vertices.cend(); it++) {
                drawLine(renderTarget, { *(it-1), *it });
            }
            break;
        }
        case Options::VertexStruct::Triangles: {
            if(vertices.size() < 3 || vertices.size() % 3 != 0) {
                return;
            }
            for(auto it = vertices.begin(); it != vertices.cend(); ) {
                drawTriangle(renderTarget, { *it++, *it++, *it++ });
            }
            break;
        }
        case Options::VertexStruct::TriangleStrip: {
            if(vertices.size() < 3) {
                return;
            }
            mesh::Triangle triangle = { vertices[0], vertices[1], vertices[2] };
            for(auto it = vertices.begin() + 3; it != vertices.cend(); ) {
                drawTriangle(renderTarget, triangle);
                triangle.vertices[0] = triangle.vertices[1];
                triangle.vertices[1] = triangle.vertices[2];
                triangle.vertices[2] = *it++;
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


void Rasterizer::drawTriangle(surface::RenderTarget &renderTarget, const mesh::Triangle& triangle) const {
    drawLine(renderTarget, { triangle.vertices[0], triangle.vertices[1] });
    drawLine(renderTarget, { triangle.vertices[1], triangle.vertices[2] });
    drawLine(renderTarget, { triangle.vertices[2], triangle.vertices[0] });
}


} }
