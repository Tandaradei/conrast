#ifndef FRAGMENTSHADER_HPP
#define FRAGMENTSHADER_HPP

#include <functional>

#include "utils/Vec.hpp"
#include "color/Color.hpp"

namespace conrast { namespace render {

struct FragmentShaderParameters
{
    utils::Vec2f screenPosition;
    color::RGB32f vertexColor;
    utils::Vec3f worldPosition;
    utils::Vec3f normal;
};

using FragmentShader = std::function<color::RGB8(const FragmentShaderParameters& params)>;


} }

#endif // FRAGMENTSHADER_HPP
