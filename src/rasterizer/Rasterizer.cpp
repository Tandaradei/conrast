#include "Rasterizer.hpp"

#include <algorithm>

#include "utils/Geometry.hpp"

namespace conrast { namespace  rast {

Rasterizer::Rasterizer()
{}


Rasterizer::Rasterizer(utils::Vec2i rasterSize, Rasterizer::Options options)
    : m_rasterSize(rasterSize),
      m_options(options)
{}


void Rasterizer::setRasterSize(utils::Vec2i rasterSize) {
    m_rasterSize = rasterSize;
}


void Rasterizer::setOptions(Rasterizer::Options options) {
    m_options = options;
}


utils::Vec2i Rasterizer::transformScreenToRaster(utils::Vec2f screenPos) const {
    utils::Vec2f halfSize{ static_cast<float>(m_rasterSize.x) * 0.5f, static_cast<float>(m_rasterSize.y) * 0.5f };
    return {
        static_cast<int>(halfSize.x + screenPos.x * halfSize.x),
        static_cast<int>(halfSize.y + screenPos.y * halfSize.y)
    };
}


utils::Vec2f Rasterizer::transformRasterToScreen(utils::Vec2i rasterPos) const {
    utils::Vec2f halfSize{ static_cast<float>(m_rasterSize.x) * 0.5f, static_cast<float>(m_rasterSize.y) * 0.5f };
    return {
        (static_cast<float>(rasterPos.x) - halfSize.x) / halfSize.x,
        (static_cast<float>(rasterPos.y) - halfSize.y) / halfSize.y
    };
}


utils::Vec3f Rasterizer::transformWorldToScreen(utils::Vec3f position) const {
    return { position.x / position.z, -position.y / position.z , position.z };
}


utils::Vec3f Rasterizer::transformScreenToWorld(utils::Vec3f screenPos) const {
    return { screenPos.x * screenPos.z, -screenPos.y * screenPos.z, screenPos.z };
}


void Rasterizer::fillGBuffer(render::GBuffer &gBuffer, const mesh::Mesh &mesh) const {
    switch(m_options.vertexStruct) {
        case Options::VertexStruct::Points: {
            for(const auto& index : mesh.indexes) {
                const auto& vertex = mesh.vertices[index];
                if(vertex.position.z >= 1.0f) {
                    auto posScreen = transformWorldToScreen(vertex.position);
                    if(posScreen.x >= -1.0f && posScreen.x <= 1.0f
                        && posScreen.y >= -1.0f && posScreen.y <= 1.0f) {
                        auto rasterPos = transformScreenToRaster({ posScreen.x, posScreen.y });
                        float depth = posScreen.z - 1.0f;
                        auto& gBufferValue = gBuffer.getValueMut(rasterPos);
                        if(depth < gBufferValue.depth) {
                            gBufferValue.diffuse = vertex.color;
                            gBufferValue.depth = depth;
                        }
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
                drawLine(gBuffer, { mesh.vertices[*it++], mesh.vertices[*it++] });
            }
            break;
        }
        case Options::VertexStruct::LineStrip: {
            if(mesh.indexes.size() < 2) {
                return;
            }
            for(auto it = mesh.indexes.begin() + 1; it != mesh.indexes.cend(); it++) {
                drawLine(gBuffer, { mesh.vertices[*(it-1)], mesh.vertices[*it] });
            }
            break;
        }
        case Options::VertexStruct::Triangles: {
            if(mesh.indexes.size() < 3 || mesh.indexes.size() % 3 != 0) {
                return;
            }
            if(m_options.fillType == Options::FillType::Fill) {
                for(auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
                    drawTriangleFilled(gBuffer, { mesh.vertices[*it++], mesh.vertices[*it++], mesh.vertices[*it++] });
                }
            }
            else if(m_options.fillType == Options::FillType::Line) {
                for(auto it = mesh.indexes.begin(); it != mesh.indexes.cend(); ) {
                    drawTriangleLines(gBuffer, { mesh.vertices[*it++], mesh.vertices[*it++], mesh.vertices[*it++] });
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
                    drawTriangleFilled(gBuffer, triangle);
                    triangle.vertices[0] = triangle.vertices[1];
                    triangle.vertices[1] = triangle.vertices[2];
                    triangle.vertices[2] = mesh.vertices[*it];
                }
            }
            else if(m_options.fillType == Options::FillType::Line) {
                for(auto it = mesh.indexes.begin() + 3; it != mesh.indexes.cend(); it++) {
                    drawTriangleLines(gBuffer, triangle);
                    triangle.vertices[0] = triangle.vertices[1];
                    triangle.vertices[1] = triangle.vertices[2];
                    triangle.vertices[2] = mesh.vertices[*it];
                }
            }
            break;
        }
    }

}




void Rasterizer::drawLine(render::GBuffer& gBuffer, const mesh::Line& line) const {
    auto startScreen = transformWorldToScreen(line.start.position);
    auto endScreen = transformWorldToScreen(line.end.position);
    auto startRaster = transformScreenToRaster({ startScreen.x, startScreen.y });
    auto endRaster = transformScreenToRaster({ endScreen.x, endScreen.y });
    auto startToEnd = endRaster - startRaster;
    float length = startToEnd.length();
    utils::Vec2f dir = utils::Vec2f{ static_cast<float>(startToEnd.x), static_cast<float>(startToEnd.y) } / length;
    auto startRasterFloat = utils::Vec2f{ static_cast<float>(startRaster.x), static_cast<float>(startRaster.y) };
    for(float i = 0.0f; i <= length; i += 1.0f) {
        auto rasterPos = utils::Vec2i{ static_cast<int>(startRasterFloat.x + i * dir.x), static_cast<int>(startRasterFloat.y + i * dir.y)};
        if(rasterPos.x < 0 || rasterPos.x >= m_rasterSize.x || rasterPos.y < 0 || rasterPos.y >= m_rasterSize.y) {
            continue;
        }
        float depth = startScreen.z - 1.0f;
        auto& gBufferValue = gBuffer.getValueMut(rasterPos);
        // TODO color and depth must be interpolated!
        if(depth < gBufferValue.depth) {
            gBufferValue.diffuse = line.start.color;
            gBufferValue.depth = depth;
        }
    }
}


void Rasterizer::drawTriangleFilled(render::GBuffer& gBuffer, const mesh::Triangle& triangle) const {
    const auto as = transformWorldToScreen(triangle.vertices[0].position);
    const auto bs = transformWorldToScreen(triangle.vertices[1].position);
    const auto cs = transformWorldToScreen(triangle.vertices[2].position);

    std::vector<utils::Vec2i> rasterTriangleSorted = {
        transformScreenToRaster(as),
        transformScreenToRaster(bs),
        transformScreenToRaster(cs)
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

    auto clamp = [](int value, int min, int max) {
        if(value < min) return min;
        if(value > max) return max;
        return value;
    };

    auto drawPixel = [&](const utils::Vec3f& a, const utils::Vec3f& b, const utils::Vec3f& c, utils::Vec2i rasterPos) {
        auto screenPoint2D = transformRasterToScreen(rasterPos);
        utils::Vec3f ws = utils::geometry::calc2DBarycentric(a, b, c, screenPoint2D);
        //if(ws.x < 0.0f || ws.y < 0.0f || ws.z < 0.0f || ws.x + ws.y + ws.z > 1.0f) { return; }
        float z = 1.0f /
               ((1.0f / a.z) * ws.x +
               (1.0f / b.z) * ws.y +
               (1.0f / c.z) * ws.z);
        utils::Vec3f p = transformScreenToWorld({ screenPoint2D.x, screenPoint2D.y, z });
        utils::Vec3f ww = utils::geometry::calc3DBarycentric(
                triangle.vertices[0].position,
                triangle.vertices[1].position,
                triangle.vertices[2].position,
                p);
        auto color = triangle.vertices[0].color * ww.x +
                     triangle.vertices[1].color * ww.y +
                     triangle.vertices[2].color * ww.z;
        float depth = z - 1.0f;
        auto& gBufferValue = gBuffer.getValueMut(rasterPos);
        if(depth < gBufferValue.depth) {
            gBufferValue.diffuse = color;
            gBufferValue.depth = depth;
        }
    };
    // Upper part
    int yStart = clamp(rasterTriangleSorted[0].y, 0, m_rasterSize.y);
    int yEnd = clamp(rasterTriangleSorted[1].y, 0, m_rasterSize.y);
    for(int y = yStart; y < yEnd; y++) {
        int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
        int xEnd = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[1], y);
        if(xStart > xEnd) {
            std::swap(xStart, xEnd);
        }
        xStart = clamp(xStart, 0, m_rasterSize.x - 1);
        xEnd = clamp(xEnd, 0, m_rasterSize.x - 1);
        for(int x = xStart; x < xEnd; x++) {
            drawPixel(as, bs, cs, { x, y });
        }
    }
    // Lower part
    yStart = clamp(rasterTriangleSorted[1].y, 0, m_rasterSize.y);
    yEnd = clamp(rasterTriangleSorted[2].y, 0, m_rasterSize.y);
    for(int y = yStart; y < yEnd; y++) {
        int xStart = interpolateX(rasterTriangleSorted[0], rasterTriangleSorted[2], y);
        int xEnd = interpolateX(rasterTriangleSorted[1], rasterTriangleSorted[2], y);
        if(xStart > xEnd) {
            std::swap(xStart, xEnd);
        }
        xStart = clamp(xStart, 0, m_rasterSize.x - 1);
        xEnd = clamp(xEnd, 0, m_rasterSize.x - 1);
        for(int x = xStart; x < xEnd; x++) {
            drawPixel(as, bs, cs, { x, y });
        }
    }
}


void Rasterizer::drawTriangleLines(render::GBuffer& gBuffer, const mesh::Triangle& triangle) const {
    drawLine(gBuffer, { triangle.vertices[0], triangle.vertices[1] });
    drawLine(gBuffer, { triangle.vertices[1], triangle.vertices[2] });
    drawLine(gBuffer, { triangle.vertices[2], triangle.vertices[0] });
}


} }
