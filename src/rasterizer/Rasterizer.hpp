#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "surface/RenderTarget.hpp"
#include "mesh/Line.hpp"
#include "mesh/Triangle.hpp"
#include "mesh/Mesh.hpp"

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

public:
    Rasterizer();
    Rasterizer(Options m_options);
    void setOptions(Options m_options);

    void render(surface::RenderTarget& renderTarget, const mesh::Mesh& mesh) const;

private:
    utils::Vec3f transformToScreen(utils::Vec3f position) const;
    utils::Vec3f transformToWorld(utils::Vec3f screenPos) const;
    float get2DTriangleArea(utils::Vec2f a, utils::Vec2f b, utils::Vec2f c) const;
    utils::Vec3f get2DBarycentric(utils::Vec2f a, utils::Vec2f b, utils::Vec2f c, utils::Vec2f p) const;
    float get3DTriangleArea(utils::Vec3f a, utils::Vec3f b, utils::Vec3f c) const;
    utils::Vec3f get3DBarycentric(utils::Vec3f a, utils::Vec3f b, utils::Vec3f c, utils::Vec3f p) const;

    void drawLine(surface::RenderTarget& renderTarget, const mesh::Line& line) const;
    void drawTriangleFilled(surface::RenderTarget& renderTarget, const mesh::Triangle& triangle) const;
    void drawTriangleLines(surface::RenderTarget& renderTarget, const mesh::Triangle& triangle) const;

private:
    Options m_options;
    Camera m_camera;
};


} }

#endif // RASTERIZER_HPP
