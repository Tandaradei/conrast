#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP


#include "utils/Vec.hpp"

namespace conrast { namespace utils {
namespace geometry {
// 2D
float calc2DTriangleArea(Vec2f a, Vec2f b, Vec2f c);
Vec3f calc2DBarycentric(Vec2f a, Vec2f b, Vec2f c, Vec2f p);
// 3D
float calc3DTriangleArea(Vec3f a, Vec3f b, Vec3f c);
Vec3f calc3DBarycentric(Vec3f a, Vec3f b, Vec3f c, Vec3f p);

}
} }

#endif // GEOMETRY_HPP
