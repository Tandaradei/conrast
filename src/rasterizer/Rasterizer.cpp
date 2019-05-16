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
                    if(posScreen.x >= -1.0f && posScreen.x <= 1.0f
                        && posScreen.y >= -1.0f && posScreen.y <= 1.0f) {
                        auto rasterPos = renderTarget.convertScreenToRaster({ posScreen.x, posScreen.y });
                        renderTarget.drawPixel(rasterPos, posScreen.z - 1.0f, vertex.color);
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


utils::Vec3f Rasterizer::transformToScreen(utils::Vec3f position) const {
    return { position.x / position.z, -position.y / position.z , position.z };
}


utils::Vec3f Rasterizer::transformToWorld(utils::Vec3f screenPos) const {
    return { screenPos.x * screenPos.z, -screenPos.y * screenPos.z, screenPos.z };
}


float Rasterizer::get2DTriangleArea(utils::Vec2f a, utils::Vec2f b, utils::Vec2f c) const {
    return std::abs(
                a.x * (b.y - c.y) +
                b.x * (c.y - a.y) +
                c.x * (a.y - b.y)
           ) * 0.5f;
}


utils::Vec3f Rasterizer::get2DBarycentric(utils::Vec2f a, utils::Vec2f b, utils::Vec2f c, utils::Vec2f p) const {
    const float area = get2DTriangleArea(a, b, c);
    return {
        get2DTriangleArea(b, c, p) / area,
        get2DTriangleArea(c, a, p) / area,
        get2DTriangleArea(a, b, p) / area
    };
}


float Rasterizer::get3DTriangleArea(utils::Vec3f a, utils::Vec3f b, utils::Vec3f c) const {
    const auto ab = b - a;
    const auto ac = c - a;
    return ab.cross(ac).length() * 0.5f;
}


utils::Vec3f Rasterizer::get3DBarycentric(utils::Vec3f a, utils::Vec3f b, utils::Vec3f c, utils::Vec3f p) const {
    const float area = get3DTriangleArea(a, b, c);
    return {
        get3DTriangleArea(b, c, p) / area,
        get3DTriangleArea(c, a, p) / area,
        get3DTriangleArea(a, b, p) / area
    };
}


void Rasterizer::drawLine(surface::RenderTarget& renderTarget, const mesh::Line& line) const {
    auto startScreen = transformToScreen(line.start.position);
    auto endScreen = transformToScreen(line.end.position);
    auto startRaster = renderTarget.convertScreenToRaster({ startScreen.x, startScreen.y });
    auto endRaster = renderTarget.convertScreenToRaster({ endScreen.x, endScreen.y });
    auto startToEnd = endRaster - startRaster;
    float length = startToEnd.length();
    utils::Vec2f dir = utils::Vec2f{ static_cast<float>(startToEnd.x), static_cast<float>(startToEnd.y) } / length;
    auto startRasterFloat = utils::Vec2f{ static_cast<float>(startRaster.x), static_cast<float>(startRaster.y) };
    for(float i = 0.0f; i <= length; i += 1.0f) {
        auto rastPos = utils::Vec2i{ static_cast<int>(startRasterFloat.x + i * dir.x), static_cast<int>(startRasterFloat.y + i * dir.y)};
        float depth = 0.0f;
        // TODO depth and color not correct! Must be interpolated
        renderTarget.drawPixel(rastPos, depth, line.start.color);
    }
}


void Rasterizer::drawTriangleFilled(surface::RenderTarget &renderTarget, const mesh::Triangle& triangle) const {
    const auto as = transformToScreen(triangle.vertices[0].position);
    const auto bs = transformToScreen(triangle.vertices[1].position);
    const auto cs = transformToScreen(triangle.vertices[2].position);

    std::vector<utils::Vec2i> rasterTriangleSorted = {
        renderTarget.convertScreenToRaster(as),
        renderTarget.convertScreenToRaster(bs),
        renderTarget.convertScreenToRaster(cs)
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
                        (static_cast<float>(value - start.y) / static_cast<float>(end.y - start.y))
                    )
                );
    };

    auto drawPixel = [&](const utils::Vec3f& a, const utils::Vec3f& b, const utils::Vec3f& c, utils::Vec2i rasterPoint) {
        auto screenPoint2D = renderTarget.convertRasterToScreen({ rasterPoint.x, rasterPoint.y });
        utils::Vec3f ws = get2DBarycentric(a, b, c, screenPoint2D);
        //if(ws.x < 0.0f || ws.y < 0.0f || ws.z < 0.0f || ws.x + ws.y + ws.z > 1.0f) { return; }
        float z = 1.0f /
               ((1.0f / a.z) * ws.x +
               (1.0f / b.z) * ws.y +
               (1.0f / c.z) * ws.z);
        utils::Vec3f p = transformToWorld({ screenPoint2D.x, screenPoint2D.y, z });
        utils::Vec3f ww = get3DBarycentric(
                triangle.vertices[0].position,
                triangle.vertices[1].position,
                triangle.vertices[2].position,
                p);
        auto color = triangle.vertices[0].color * ww.x +
                     triangle.vertices[1].color * ww.y +
                     triangle.vertices[2].color * ww.z;
        renderTarget.drawPixel(rasterPoint, z - 1.0f, color);
    };
    // Upper part
    for(int y = rasterTriangleSorted[0].y; y < rasterTriangleSorted[1].y; y++) {
        int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
        int xEnd = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[1], y);
        if(xStart > xEnd) {
            std::swap(xStart, xEnd);
        }
        for(int x = xStart; x < xEnd; x++) {
            drawPixel(as, bs, cs, { x, y });
        }
    }
    // Lower part
    for(int y = rasterTriangleSorted[1].y; y < rasterTriangleSorted[2].y; y++) {
        int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
        int xEnd = interpolateX(rasterTriangleSorted[1], rasterTriangleSorted[2], y);
        if(xStart > xEnd) {
            std::swap(xStart, xEnd);
        }
        for(int x = xStart; x < xEnd; x++) {
            drawPixel(as, bs, cs, { x, y });
        }
    }
}


void Rasterizer::drawTriangleLines(surface::RenderTarget &renderTarget, const mesh::Triangle& triangle) const {
    drawLine(renderTarget, { triangle.vertices[0], triangle.vertices[1] });
    drawLine(renderTarget, { triangle.vertices[1], triangle.vertices[2] });
    drawLine(renderTarget, { triangle.vertices[2], triangle.vertices[0] });
}


} }
