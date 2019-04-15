#ifndef VEC_HPP
#define VEC_HPP


#include <cmath>

namespace conrast { namespace utils {

template <typename T>
struct Vec2 {
    T x;
    T y;

    Vec2 operator+(Vec2<T> const& other) const {
        return Vec2<T>(x + other.x, y + other.y);
    }

    Vec2& operator+=(Vec2<T> const& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator-(Vec2<T> const& other) const {
        return Vec2<T>{ x - other.x, y - other.y };
    }

    Vec2& operator-=(Vec2<T> const& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2 operator*(const float factor) const {
        return Vec2<T>{ x * factor, y * factor };
    }

    Vec2& operator*=(const float factor) {
        x *= factor;
        y *= factor;
        return *this;
    }

    Vec2 operator/(const float factor) const {
        return Vec2<T>{ x / factor, y / factor };
    }

    Vec2& operator/=(const float factor) {
        x /= factor;
        y /= factor;
        return *this;
    }

    float squaredLength() const {
        return static_cast<float>(x * x + y * y);
    }

    float length() const {
        return std::sqrt(squaredLength());
    }

    Vec2& normalize() {
        const float length = this->length();
        x /= length;
        y /= length;
        return *this;
    }

    Vec2 normalized() const {
        const float length = this->length();
        return { x / length, y / length };
    }

};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;
};

using Vec3f = Vec3<float>;


} }

#endif // VEC_HPP
