#include "Geometry.hpp"

namespace conrast { namespace utils {
namespace geometry {
// 2D
float calc2DTriangleArea(Vec2f a, Vec2f b, Vec2f c) {
    return std::abs(
                a.x * (b.y - c.y) +
                b.x * (c.y - a.y) +
                c.x * (a.y - b.y)
           ) * 0.5f;
}


Vec3f calc2DBarycentric(Vec2f a, Vec2f b, Vec2f c, Vec2f p) {
    const float area = calc2DTriangleArea(a, b, c);
    const float u = calc2DTriangleArea(b, c, p) / area;
    const float v = calc2DTriangleArea(c, a, p) / area;
    return {
        u,
        v,
        (1.0f - u - v)
    };
}

// 3D
float calc3DTriangleArea(Vec3f a, Vec3f b, Vec3f c) {
    const auto ab = b - a;
    const auto ac = c - a;
    return ab.cross(ac).length() * 0.5f;
}

Vec3f calc3DBarycentric(Vec3f a, Vec3f b, Vec3f c, Vec3f p) {
    const float area = calc3DTriangleArea(a, b, c);
    const float u = calc3DTriangleArea(b, c, p) / area;
    const float v = calc3DTriangleArea(c, a, p) / area;
    return {
        u,
        v,
        (1.0f - u - v)
    };
}

}
}}
