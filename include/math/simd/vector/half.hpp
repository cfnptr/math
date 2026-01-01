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
 * @brief Common single instruction multiple data (SIMD) 16-bit floating point vector functions.
 */

#pragma once
#include "math/simd/vector/float.hpp"

#if defined(MATH_SIMD_SUPPORT_AVX2) || defined(MATH_SIMD_SUPPORT_NEON) || defined(FLT16_MIN)
namespace math
{

/**
 * @brief SIMD 4 component 16bit floating point vector structure. (half4)
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(8) f16x4
{
	union
	{
		_simd_f64 data;
		half floats[4];
		int16 ints[4];
		uint16 uints[4];
	};

	f16x4(const f16x4& v) noexcept = default;
	f16x4& operator=(const f16x4& v) noexcept = default;

	/**
	 * @brief Creates a new zero initialized SIMD 4 component 16bit floating point vector structure. (half4)
	 */
	f16x4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = 0;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdup_n_f16(0.0f);
		#else
		memset(floats, 0, sizeof(half) * 4);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 16bit floating point vector structure. (half4)
	 * @param xyzw target value for all vector components
	 */
	explicit f16x4(half xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		_mm_storel_epi64((__m128i*)&data, _mm_cvtps_ph(_mm_set1_ps(xyzw), _MM_FROUND_TO_NEAREST_INT));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdup_n_f16(xyzw);
		#else
		floats[0] = xyzw; floats[1] = xyzw; floats[2] = xyzw; floats[3] = xyzw;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 16bit floating point vector structure. (half4)
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	f16x4(half x, half y, half z, half w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		_mm_storel_epi64((__m128i*)&data, _mm_cvtps_ph(_mm_set_ps(w, z, y, x), _MM_FROUND_TO_NEAREST_INT));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float16x4_t){ x, y, z, w };
		#else
		floats[0] = x; floats[1] = y; floats[2] = z; floats[3] = w;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 16bit floating point vector structure. (half4)
	 * @warning This constructor duplicates Z component to the W component!
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	f16x4(half x, half y, half z) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		_mm_storel_epi64((__m128i*)&data, _mm_cvtps_ph(_mm_set_ps(z, z, y, x), _MM_FROUND_TO_NEAREST_INT));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float16x4_t){ x, y, z, z };
		#else
		floats[0] = x; floats[1] = y; floats[2] = z; floats[3] = z;
		#endif
	}

	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_NEON)
	/**
	 * @brief Creates a new SIMD 4 component 16bit floating point vector structure. (half4)
	 * @param data target vector floating point SIMD data
	 */
	f16x4(_simd_f64 data) noexcept : data(data) { }
	#endif

	/**
	 * @brief Creates a new SIMD 4 component 16bit floating point vector structure. (half4)
	 * @param v target vector unsigned integer SIMD data
	 */
	explicit f16x4(f32x4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		_mm_storel_epi64((__m128i*)&data, _mm_cvtps_ph(v.data, _MM_FROUND_TO_NEAREST_INT));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vcvt_f16_f32(v.data);
		#else
		floats[0] = (half)v.floats[0]; floats[1] = (half)v.floats[1];
		floats[2] = (half)v.floats[2]; floats[3] = (half)v.floats[3];
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector first component value.
	 */
	half getX() const noexcept { return floats[0]; }
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	half getY() const noexcept { return floats[1]; }
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	half getZ() const noexcept { return floats[2]; }
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	half getW() const noexcept { return floats[3]; }

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(half value) noexcept { floats[0] = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(half value) noexcept { floats[1] = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(half value) noexcept { floats[2] = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(half value) noexcept { floats[3] = value; }

	/**
	 * @brief Sets SIMD vector Z component value to the W component.
	 * @note Useful when you want to prevent SIMD division by zero.
	 */
	void fixW() noexcept { floats[3] = getZ(); }

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	half& operator[](psize i) noexcept { return floats[i]; }
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	half operator[](psize i) const noexcept { return floats[i]; }

	/**
	 * @brief Returns as 4 component unsigned integer SIMD vector.
	 */
	explicit operator f32x4() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_cvtph_ps(_mm_loadl_epi64((__m128i*)&data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcvt_f32_f16(data);
		#else
		return f32x4(floats[0], floats[1], floats[2], floats[3]);
		#endif
	}

	// TODO: math functions after adding AVX512 support.
};

} // namespace math
#endif