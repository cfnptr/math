// Copyright 2022-2025 Nikita Fediuchin. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/***********************************************************************************************************************
 * @file
 * @brief Common single instruction multiple data (SIMD) floating point vector functions.
 */

#pragma once
#include "math/matrix/float.hpp"
#include "math/simd/vector/float.hpp"

namespace math
{

/**
 * @brief SIMD 32bit floating point 4x4 matrix structure.
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_f32_4x4
{
	simd_f32_4 columns[4];

	/**
	 * @brief Creates a new zero initialized SIMD 32bit floating point 4x4 matrix structure.
	 */
	simd_f32_4x4() noexcept = default;
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure.
	 * 
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 * @param c2 third matrix column value
	 * @param c3 fourth matrix column value
	 */
	simd_f32_4x4(simd_f32_4 c0, simd_f32_4 c1, simd_f32_4 c2, simd_f32_4 c3) noexcept :
		columns { c0, c1, c2, c3 } { };
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure.
	 * @param xyzw target value for all matrix vector components
	 */
	explicit simd_f32_4x4(float v) noexcept :
		columns { simd_f32_4(v), simd_f32_4(v), simd_f32_4(v), simd_f32_4(v) } { };
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure.
	 * @param v target 4x4 matrix value
	 */
	explicit simd_f32_4x4(const float4x4& v) noexcept { *this = *((const simd_f32_4x4*)&v); }

	/**
	 * @brief Returns SIMD matrix column by index.
	 * @param i target column index
	 */
	simd_f32_4& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return columns[i];
	}
	/**
	 * @brief Returns SIMD matrix column by index.
	 * @param i target column index
	 */
	simd_f32_4 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return columns[i];
	}

	/*******************************************************************************************************************
	 * @brief Multiplies all SIMD matrix columns by specified value.
	 * @param v target multiplier value
	 */
	simd_f32_4x4 operator*(float v) const noexcept
	{
		auto m = simd_f32_4(v);
		return simd_f32_4x4(columns[0] * m, columns[1] * m, columns[2] * m, columns[3] * m);
	}
	/**
	 * @brief Calculates dot product between two SIMD matrices.
	 * @param m target SIMD matrix to dot by
	 */
	simd_f32_4x4 operator*(const simd_f32_4x4& m) const noexcept
	{
		simd_f32_4x4 result;
		#if defined(MATH_SIMD_SUPPORT_SSE)
		for (int i = 0; i < 4; ++i)
		{
			auto c = m.columns[i].data;
			auto r = _mm_mul_ps(columns[0].data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(0, 0, 0, 0)));
			r = _mm_add_ps(r, _mm_mul_ps(columns[1].data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(1, 1, 1, 1))));
			r = _mm_add_ps(r, _mm_mul_ps(columns[2].data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(2, 2, 2, 2))));
			r = _mm_add_ps(r, _mm_mul_ps(columns[3].data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 3, 3, 3))));
			result.columns[i].data = r;
		}
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		for (int i = 0; i < 4; ++i)
		{
			auto c = m.columns[i].data;
			auto r = vmulq_f32(columns[0].data, vdupq_laneq_f32(c, 0));
			r = vmlaq_f32(r, columns[1].data, vdupq_laneq_f32(c, 1));
			r = vmlaq_f32(r, columns[2].data, vdupq_laneq_f32(c, 2));
			r = vmlaq_f32(r, columns[3].data, vdupq_laneq_f32(c, 3));
			result.columns[i].data = r;
		}
		#else
		for (int i = 0; i < 4; ++i)
		{
			result.columns[i] = 
				columns[0] * simd_f32_4(m.columns[i].values[0]) + 
				columns[1] * simd_f32_4(m.columns[i].values[1]) + 
				columns[2] * simd_f32_4(m.columns[i].values[2]) + 
				columns[3] * simd_f32_4(m.columns[i].values[3]);
		}
		#endif
		return result;
	}
	/**
	 * @brief Calculates dot product between SIMD matrix and vector.
	 * @param v target SIMD vector to dot by
	 */
	simd_f32_4 operator*(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		auto r = _mm_mul_ps(columns[0].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0)));
		r = _mm_add_ps(r, _mm_mul_ps(columns[1].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1))));
		r = _mm_add_ps(r, _mm_mul_ps(columns[2].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2))));
		r = _mm_add_ps(r, _mm_mul_ps(columns[3].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 3, 3, 3))));
		return r;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		auto r = vmulq_f32(mCcolumnsol[0].data, vdupq_laneq_f32(v.data, 0));
		r = vmlaq_f32(r, columns[1].data, vdupq_laneq_f32(v.data, 1));
		r = vmlaq_f32(r, columns[2].data, vdupq_laneq_f32(v.data, 2));
		r = vmlaq_f32(r, columns[3].data, vdupq_laneq_f32(v.data, 3));
		return r;
		#else
		return simd_f32_4(
			columns[0].values[0] * v.values[0] + columns[1].values[0] * v.values[1] + 
				columns[2].values[0] * v.values[2] + columns[3].values[0] * v.values[3],
			columns[0].values[1] * v.values[0] + columns[1].values[1] * v.values[1] + 
				columns[2].values[1] * v.values[2] + columns[3].values[1] * v.values[3],
			columns[0].values[2] * v.values[0] + columns[1].values[2] * v.values[1] + 
				columns[2].values[2] * v.values[2] + columns[3].values[2] * v.values[3],
			columns[0].values[3] * v.values[0] + columns[1].values[3] * v.values[1] + 
				columns[2].values[3] * v.values[2] + columns[3].values[3] * v.values[3]);
		#endif
	}

	simd_f32_4x4& operator*=(simd_f32_4x4 v) noexcept { *this = *this * v; return *this; }
	simd_f32_4x4& operator*=(float n) noexcept { *this = *this * n; return *this; }
	
	bool operator==(const simd_f32_4x4& m) const noexcept
	{
		return areAllTrue(compare(columns[0], m.columns[0]) & compare(columns[1], m.columns[1]) &
			compare(columns[2], m.columns[2]) & compare(columns[3], m.columns[3]));
	}
	bool operator!=(const simd_f32_4x4& m) const noexcept { return !(*this == m); }

	static const simd_f32_4x4 zero, one, minusOne, inf, minusInf, nan, identity;
};

//**********************************************************************************************************************
inline const simd_f32_4x4 simd_f32_4x4::zero = simd_f32_4x4(0.0f);
inline const simd_f32_4x4 simd_f32_4x4::one = simd_f32_4x4(1.0f);
inline const simd_f32_4x4 simd_f32_4x4::minusOne = simd_f32_4x4(-1.0f);
inline const simd_f32_4x4 simd_f32_4x4::inf = simd_f32_4x4(INFINITY);
inline const simd_f32_4x4 simd_f32_4x4::minusInf = simd_f32_4x4(-INFINITY);
inline const simd_f32_4x4 simd_f32_4x4::nan = simd_f32_4x4(NAN);
inline const simd_f32_4x4 simd_f32_4x4::identity = simd_f32_4x4(
	simd_f32_4(1.0f, 0.0f, 0.0f, 0.0f),
	simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f),
	simd_f32_4(0.0f, 0.0f, 1.0f, 0.0f),
	simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f)
);

/**
 * @brief Returns true if first SIMD matrix binary representation is less than the second.
 *
 * @param a first SIMD matrix to binary compare
 * @param b second SIMD matrix to binary compare
 */
static bool isBinaryLess(simd_f32_4x4 a, simd_f32_4x4 b) noexcept { return memcmp(&a, &b, sizeof(simd_f32_4x4)) < 0; }

/**
 * @brief Calculates 3x3 dot product between SIMD matrix and vector.
 * @param[int] m target SIMD matrix to use
 * @param v target SIMD vector to dot by
 */
static simd_f32_4 multiply3x3(const simd_f32_4x4& m, simd_f32_4 v) noexcept
{
	simd_f32_4 result;
	#if defined(MATH_SIMD_SUPPORT_SSE)
	auto r = _mm_mul_ps(m.columns[0].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0)));
	r = _mm_add_ps(r, _mm_mul_ps(m.columns[1].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1))));
	r = _mm_add_ps(r, _mm_mul_ps(m.columns[2].data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2))));
	result = r;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto r = vmulq_f32(m.columns[0].data, vdupq_laneq_f32(v.data, 0));
	r = vmlaq_f32(r, m.columns[1].data, vdupq_laneq_f32(v.data, 1));
	r = vmlaq_f32(r, m.columns[2].data, vdupq_laneq_f32(v.data, 2));
	result = r;
	#else
	result = simd_f32_4(
		m.columns[0].values[0] * v.values[0] + m.columns[1].values[0] * 
			v.values[1] + m.columns[2].values[0] * v.values[2],
		m.columns[0].values[1] * v.values[0] + m.columns[1].values[1] * 
			v.values[1] + m.columns[2].values[1] * v.values[2],
		m.columns[0].values[2] * v.values[0] + m.columns[1].values[2] * 
			v.values[1] + m.columns[2].values[2] * v.values[2],
		0.0f);
	#endif
	return result.swizzle<SwX, SwY, SwZ, SwZ>();
}

} // namespace math