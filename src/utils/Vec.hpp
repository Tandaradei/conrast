#ifndef VEC_HPP
#define VEC_HPP


#include <stdint.h>
#ifndef _WIN32
#include <unistd.h>
#endif
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
using Vec2i = Vec2<int32_t>;

template <typename T>
struct Vec3 {
    T x;
    T y;
    T z;

    Vec3 operator+(Vec3<T> const& other) const {
        return Vec3<T>{ x + other.x, y + other.y, z + other.z };
    }

    Vec3& operator+=(Vec3<T> const& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vec3 operator-(Vec3<T> const& other) const {
        return Vec3<T>{ x - other.x, y - other.y, z - other.z };
    }

    Vec3& operator-=(Vec3<T> const& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vec3 operator*(const float factor) const {
        return Vec3<T>{ x * factor, y * factor, z * factor };
    }

    Vec3& operator*=(const float factor) {
        x *= factor;
        y *= factor;
        z *= factor;
        return *this;
    }

    Vec3 operator/(const float factor) const {
        return Vec3<T>{ x / factor, y / factor, z / factor };
    }

    Vec3& operator/=(const float factor) {
        x /= factor;
        y /= factor;
        z /= factor;
        return *this;
    }

    float dot(Vec3<T> const& other) const {
        return static_cast<float>(x * other.x + y * other.y + z * other.z);
    }

    Vec3<T> cross(Vec3<T> const& other) const {
        return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
        };
    }

    float squaredLength() const {
        return this->dot(*this);
    }

    float length() const {
        return std::sqrt(squaredLength());
    }

    Vec3& normalize() {
        const float length = this->length();
        x /= length;
        y /= length;
        z /= length;
        return *this;
    }

    Vec3 normalized() const {
        const float length = this->length();
        return { x / length, y / length, z / length };
    }

    operator Vec2<T>() const {
        return { x, y };
    }

};

using Vec3f = Vec3<float>;

template <typename T>
struct Vec4 {
	T x;
	T y;
	T z;
	T w;

	Vec4(T x, T y, T z, T w)
		: x(x), y(y), z(z), w(w)
	{}

	Vec4(Vec3<T> vec3, T w)
		: x(vec3.x),
		y(vec3.y),
		z(vec3.z),
		w(w)
	{}

	Vec3<T> toVec3() {
		if (w != 0.0f) {
			return { x / w, y / w, z / w };
		}
		return { x, y, z };
	}
};

using Vec4f = Vec4<float>;

} }

#endif // VEC_HPP
