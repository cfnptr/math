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
#include "math/vector/double.hpp"
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
		data = vdup_n_f16(0.0_hf);
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

	explicit f16x4(u32x4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_cvtepi32_ps(v.data), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vcvt_f32_f16(vcvtq_f32_u32(v.data));
		#else
		halfs = (half4)v.uints;
		#endif
	}
	explicit f16x4(i32x4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_cvtepi32_ps(v.data), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vcvt_f32_f16(vcvtq_f32_s32(v.data));
		#else
		halfs = (half4)v.ints;
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Creates a new 4-component SIMD vector of 16-bit floating-point values. (half4)
	 * @param v target 4 component vector value
	 */
	explicit f16x4(half4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_set_ps(v.w, v.z, v.y, v.x), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float16x4_t){ v.x, v.y, v.z, v.w };
		#else
		halfs = v;
		#endif
	}
	/**
	 * @brief Creates a new 4-component SIMD vector of 16-bit floating-point values. (half4)
	 * @warning This constructor duplicates Z component to the W component!
	 * @param v target 3 component vector value
	 */
	explicit f16x4(half3 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_cvtps_ph(_mm_set_ps(v.z, v.z, v.y, v.x), _MM_FROUND_TO_NEAREST_INT);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float16x4_t){ v.x, v.y, v.z, v.z };
		#else
		halfs = half4(v, v.z);
		#endif
	}

	explicit f16x4(double4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(float4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(long4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(ulong4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(int4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(uint4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(short4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(ushort4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(sbyte4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(byte4 v) noexcept { *this = (f16x4)half4(v); }
	explicit f16x4(double3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(float3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(long3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(ulong3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(int3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(uint3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(short3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(ushort3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(sbyte3 v) noexcept { *this = (f16x4)half3(v); }
	explicit f16x4(byte3 v) noexcept { *this = (f16x4)half3(v); }

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

	explicit operator double4() const noexcept { return (double4)halfs; }
	explicit operator float4() const noexcept { return (float4)halfs; }
	explicit operator half4() const noexcept { return halfs; }
	explicit operator long4() const noexcept { return (long4)halfs; }
	explicit operator ulong4() const noexcept { return (ulong4)halfs; }
	explicit operator int4() const noexcept { return (int4)halfs; }
	explicit operator uint4() const noexcept { return (uint4)halfs; }
	explicit operator short4() const noexcept { return (short4)halfs; }
	explicit operator ushort4() const noexcept { return (ushort4)halfs; }
	explicit operator sbyte4() const noexcept { return (sbyte4)halfs; }
	explicit operator byte4() const noexcept { return (byte4)halfs; }
	explicit operator double3() const noexcept { return (double3)halfs; }
	explicit operator float3() const noexcept { return (float3)halfs; }
	explicit operator half3() const noexcept { return (half3)halfs; }
	explicit operator long3() const noexcept { return (long3)halfs; }
	explicit operator ulong3() const noexcept { return (ulong3)halfs; }
	explicit operator int3() const noexcept { return (int3)halfs; }
	explicit operator uint3() const noexcept { return (uint3)halfs; }
	explicit operator short3() const noexcept { return (short3)halfs; }
	explicit operator ushort3() const noexcept { return (ushort3)halfs; }
	explicit operator sbyte3() const noexcept { return (sbyte3)halfs; }
	explicit operator byte3() const noexcept { return (byte3)halfs; }
	explicit operator double2() const noexcept { return (double2)halfs; }
	explicit operator float2() const noexcept { return (float2)halfs; }
	explicit operator half2() const noexcept { return (half2)halfs; }
	explicit operator long2() const noexcept { return (long2)halfs; }
	explicit operator ulong2() const noexcept { return (ulong2)halfs; }
	explicit operator int2() const noexcept { return (int2)halfs; }
	explicit operator uint2() const noexcept { return (uint2)halfs; }
	explicit operator short2() const noexcept { return (short2)halfs; }
	explicit operator ushort2() const noexcept { return (ushort2)halfs; }
	explicit operator sbyte2() const noexcept { return (sbyte2)halfs; }
	explicit operator byte2() const noexcept { return (byte2)halfs; }

	// TODO: math functions after adding AVX512 / AVX10 support.

	//******************************************************************************************************************
	bool operator==(f16x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) == 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminv_u16(vceq_f16(data, v.data)) == 0xFFFFFFFFu;
		#else
		return halfs == v.halfs;
		#endif
	}
	bool operator!=(f16x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) != 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminv_u16(vceq_f16(data, v.data)) == 0u;
		#else
		return halfs != v.halfs;
		#endif
	}

	bool operator==(half n) const noexcept { return *this == f16x4(n); }
	bool operator!=(half n) const noexcept { return *this != f16x4(n); }

	static const f16x4 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top, back, front;
};

//**********************************************************************************************************************
inline const f16x4 f16x4::zero = f16x4(0.0_hf);
inline const f16x4 f16x4::one = f16x4(1.0_hf);
inline const f16x4 f16x4::minusOne = f16x4(-1.0_hf);
inline const f16x4 f16x4::min = f16x4(FLT16_MIN);
inline const f16x4 f16x4::minusMin = f16x4(-FLT16_MIN);
inline const f16x4 f16x4::max = f16x4(FLT16_MAX);
inline const f16x4 f16x4::minusMax = f16x4(-FLT16_MAX);
inline const f16x4 f16x4::epsilon = f16x4(FLT16_EPSILON);
inline const f16x4 f16x4::inf = f16x4((half)INFINITY);
inline const f16x4 f16x4::minusInf = f16x4((half)-INFINITY);
inline const f16x4 f16x4::nan = f16x4((half)NAN);
inline const f16x4 f16x4::left = f16x4(-1.0_hf, 0.0_hf, 0.0_hf, 0.0_hf);
inline const f16x4 f16x4::right = f16x4(1.0_hf, 0.0_hf, 0.0_hf, 0.0_hf);
inline const f16x4 f16x4::bottom = f16x4(0.0_hf, -1.0_hf, 0.0_hf, 0.0_hf);
inline const f16x4 f16x4::top = f16x4(0.0_hf, 1.0_hf, 0.0_hf, 0.0_hf);
inline const f16x4 f16x4::back = f16x4(0.0_hf, 0.0_hf, -1.0_hf, 0.0_hf);
inline const f16x4 f16x4::front = f16x4(0.0_hf, 0.0_hf, 1.0_hf, 0.0_hf);

} // namespace math
#endif