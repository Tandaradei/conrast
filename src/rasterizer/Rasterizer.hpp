#ifndef RASTERIZER_HPP
#define RASTERIZER_HPP

#include "render/Framebuffer.hpp"
#include "mesh/Line.hpp"
#include "mesh/Triangle.hpp"
#include "mesh/Mesh.hpp"
#include "rasterizer/PerspectiveCamera.hpp"

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

        FillType fillType = FillType::Fill;
    };

public:
    Rasterizer(utils::Vec2i rasterSize, Options m_options, PerspectiveCamera& camera);

	void setRasterSize(utils::Vec2i rasterSize);
    void setOptions(Options m_options);

	void setCamera(PerspectiveCamera& camera);

    void rasterize(render::Framebuffer& framebuffer, const mesh::Mesh& mesh) const;

private:
    utils::Vec2i transformScreenToRaster(utils::Vec2f screenPos) const;
    utils::Vec2f transformRasterToScreen(utils::Vec2i rasterPos) const;
    utils::Vec3f transformWorldToScreen(utils::Vec3f worldPos) const;
    utils::Vec3f transformScreenToWorld(utils::Vec3f screenPos) const;

    void drawLine(render::Framebuffer& framebuffer, const mesh::Line& line) const;
    void drawTriangleFilled(render::Framebuffer& framebuffer, const render::FragmentShader& fragShader, const mesh::Triangle& triangle) const;
    void drawTriangleLines(render::Framebuffer& framebuffer, const mesh::Triangle& triangle) const;

private:
    utils::Vec2i		m_rasterSize;
    Options				m_options;
    PerspectiveCamera&	m_camera;
};


} }

#endif // RASTERIZER_HPP
