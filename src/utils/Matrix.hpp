#ifndef MATRIX_HPP
#define MATRIX_HPP


#include "utils/Vec.hpp"

namespace conrast { namespace utils {

template <typename T>
struct Mat4 {
	// [column-index][row-index]
	T values[4][4] = { T() };

	Vec4<T> multVec(Vec4<T> vec) const {
		return {
			vec.x * values[0][0] + vec.y * values[0][1] + vec.z * values[0][2] + vec.w * values[0][3],
			vec.x * values[1][0] + vec.y * values[1][1] + vec.z * values[1][2] + vec.w * values[1][3],
			vec.x * values[2][0] + vec.y * values[2][1] + vec.z * values[2][2] + vec.w * values[2][3],
			vec.x * values[3][0] + vec.y * values[3][1] + vec.z * values[3][2] + vec.w * values[3][3]
		};
	}
};

using Mat4f = Mat4<float>;

}}

#endif // MATRIX_HPP
