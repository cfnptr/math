// Copyright 2022-2026 Nikita Fediuchin. All rights reserved.
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
 * @brief Common single instruction multiple data (SIMD) 16 bit floating point vector functions.
 */

#pragma once
#include "math/vector/float.hpp"
#include "math/simd/vector/int.hpp"

#if defined(MATH_SIMD_SUPPORT_AVX2) || defined(MATH_SIMD_SUPPORT_NEON) || defined(FLT16_MIN)
namespace math
{

/**
 * @brief A 4-component SIMD vector of 16-bit floating-point values. (half4)
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] f16x4
{
	union
	{
		_simd_f64 data;
		half4 halfs;
		short4 shorts;
		ushort4 ushorts;
	};

	f16x4(const f16x4& v) noexcept = default;
	f16x4& operator=(const f16x4& v) noexcept = default;

	/**
	 * @brief Creates a new zero initialized 4-component SIMD vector of 16-bit floating-point values. (half4)
	 */
	f16x4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_setzero_si128();
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdup_n_f16(0.0f);
		#else
		halfs = half4::zero;
		#endif
	}
	/**
	 * @brief Creates a new 4-component SIMD vector of 16-bit floating-point values. (half4)
	 * @param xyzw target value for all vector components
	 */
	explicit f16x4(half xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_set1_ps(xyzw), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdup_n_f16(xyzw);
		#else
		halfs = half4(xyzw);
		#endif
	}
	/**
	 * @brief Creates a new 4-component SIMD vector of 16-bit floating-point values. (half4)
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	f16x4(half x, half y, half z, half w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_set_ps(w, z, y, x), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float16x4_t){ x, y, z, w };
		#else
		halfs = half4(x, y, z, w);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4-component SIMD vector of 16-bit floating-point values. (half4)
	 * @warning This constructor duplicates Z component to the W component!
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	f16x4(half x, half y, half z) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_set_ps(z, z, y, x), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float16x4_t){ x, y, z, z };
		#else
		halfs = half4(x, y, z, z);
		#endif
	}
	/**
	 * @brief Creates a new 4-component SIMD vector of 16-bit floating-point values. (half4)
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	f16x4(f16x4 xyz, half w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE4_1)
		data = _mm_blend_epi16(xyz.data, _mm_set1_epi16(*(short*)&w), 8);
		#elif defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_insert_epi16(xyz.data, *(uint16*)&w, 3);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vset_lane_f16(w, xyz.data, 3);
		#else
		halfs = xyz.halfs; halfs.w = w;
		#endif
	}

	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_NEON)
	f16x4(_simd_f64 data) noexcept : data(data) { }
	#endif

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector first component value.
	 */
	half getX() const noexcept { return halfs[0]; }
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	half getY() const noexcept { return halfs[1]; }
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	half getZ() const noexcept { return halfs[2]; }
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	half getW() const noexcept { return halfs[3]; }

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(half value) noexcept { halfs[0] = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(half value) noexcept { halfs[1] = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(half value) noexcept { halfs[2] = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(half value) noexcept { halfs[3] = value; }

	/**
	 * @brief Sets SIMD vector Z component value to the W component.
	 * @note Useful when you want to prevent SIMD division by zero.
	 */
	void fixW() noexcept { halfs[3] = getZ(); }

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	half& operator[](psize i) noexcept { return halfs[i]; }
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	half operator[](psize i) const noexcept { return halfs[i]; }

	explicit operator half4() const noexcept { return halfs; }
	explicit operator half3() const noexcept { return (half3)halfs; }
	explicit operator half2() const noexcept { return (half2)halfs; }

	// TODO: math functions after adding AVX512 support.

	static const f16x4 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top, back, front;
};

//**********************************************************************************************************************
inline const f16x4 f16x4::zero = f16x4(0.0f);
inline const f16x4 f16x4::one = f16x4(1.0f);
inline const f16x4 f16x4::minusOne = f16x4(-1.0f);
inline const f16x4 f16x4::min = f16x4(FLT16_MIN);
inline const f16x4 f16x4::minusMin = f16x4(-FLT16_MIN);
inline const f16x4 f16x4::max = f16x4(FLT16_MAX);
inline const f16x4 f16x4::minusMax = f16x4(-FLT16_MAX);
inline const f16x4 f16x4::epsilon = f16x4(FLT16_EPSILON);
inline const f16x4 f16x4::inf = f16x4(INFINITY);
inline const f16x4 f16x4::minusInf = f16x4(-INFINITY);
inline const f16x4 f16x4::nan = f16x4(NAN);
inline const f16x4 f16x4::left = f16x4(-1.0f, 0.0f, 0.0f, 0.0f);
inline const f16x4 f16x4::right = f16x4(1.0f, 0.0f, 0.0f, 0.0f);
inline const f16x4 f16x4::bottom = f16x4(0.0f, -1.0f, 0.0f, 0.0f);
inline const f16x4 f16x4::top = f16x4(0.0f, 1.0f, 0.0f, 0.0f);
inline const f16x4 f16x4::back = f16x4(0.0f, 0.0f, -1.0f, 0.0f);
inline const f16x4 f16x4::front = f16x4(0.0f, 0.0f, 1.0f, 0.0f);

} // namespace math
#endif