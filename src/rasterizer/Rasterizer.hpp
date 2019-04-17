#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "../surface/RenderTarget.hpp"
#include "../mesh/Line.hpp"
#include "../mesh/Triangle.hpp"

namespace conrast { namespace rast {

class Rasterizer
{
public:
    struct Options {
        enum class FillType {
            Point,
            Line,
            Fill
        };
        enum class VertexStruct {
            Points,
            Lines,
            LineStrip,
            Triangles,
            TriangleStrip
        };

        FillType fillType = FillType::Fill;
        VertexStruct vertexStruct = VertexStruct::TriangleStrip;
    };

    struct Camera {
        float imagePlaneHorizontalSize = 1.6f;
        float imagePlaneVerticalSize = 0.9f;
    };

    struct ScreenPixel {
        utils::Vec2f position;
        float depth;
    };

public:
    Rasterizer();
    Rasterizer(Options m_options);
    void setOptions(Options m_options);

    void render(surface::RenderTarget& renderTarget, const std::vector<mesh::Vertex>& vertices) const;

private:
    ScreenPixel transformToScreen(utils::Vec3f position) const;
    utils::Vec3f transformToWorld(utils::Vec3f screenPos) const;
    color::Color getInterpolatedColor(utils::Vec3f screenPos, const std::vector<mesh::Vertex> triangle) const;

    void drawLine(surface::RenderTarget& renderTarget, const mesh::Line& line) const;
    void drawTriangle(surface::RenderTarget& renderTarget, const mesh::Triangle& triangle) const;

private:
    Options m_options;
    Camera m_camera;
};


} }

#endif // RASTERIZER_HPP
