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
 * @brief Common single instruction multiple data (SIMD) signed integer vector functions.
 */

#pragma once
#include "math/vector/int.hpp"
#include "math/simd/vector/uint.hpp"

namespace math
{

/**
 * @brief SIMD 4 component 32bit signed integer vector structure.
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_i32_4
{
	union
	{
		_simd_i128 data;
		int4 ints;
		uint4 uints;
		float4 floats;
	};

	simd_i32_4(const simd_i32_4& v) = default;
	simd_i32_4&	operator=(const simd_i32_4& v) = default;

	/**
	 * @brief Creates a new zero initialized SIMD 4 component 32bit signed integer vector structure.
	 */
	simd_i32_4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_setzero_si128();
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_s32(0);
		#else
		ints = int4::zero;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit simd_i32_4(int32 xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set1_epi32(xyzw);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_s32(xyzw);
		#else
		ints = int4(xyzw);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	simd_i32_4(int32 x, int32 y, int32 z, int32 w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)w, (int)z, (int)y, (int)x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (int32x4_t){ x, y, z, w };
		#else
		ints = int4(x, y, z, w);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 * @warning This constructor duplicates Z component to the W component!
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	simd_i32_4(int32 x, int32 y, int32 z) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)z, (int)z, (int)y, (int)x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (int32x4_t){ x, y, z, z };
		#else
		ints = int4(x, y, z, z);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 *
	 * @param xyz first, second and third vector component values
	 * @param w fourth vector component value
	 */
	simd_i32_4(simd_i32_4 xyz, int32 w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_blend_epi32(xyz.data, _mm_set1_epi32(w), 8);
		#elif defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32(w, xyz.ints.z, xyz.ints.y, xyz.ints.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vsetq_lane_s32(w, xyz.data, 3);
		#else
		ints = xyz.ints; ints.w = w;
		#endif
	}

	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_NEON)
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 * @param data target vector SIMD data
	 */
	simd_i32_4(_simd_i128 data) : data(data) { }
	#endif

	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target vector unsigned integer SIMD data
	 */
	explicit simd_i32_4(simd_u32_4 v)
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = v.data;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vreinterpretq_s32_u32(v.data);
		#else
		ints = v.ints;
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 * @param v target 4 component vector value
	 */
	explicit simd_i32_4(int4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32(v.w, v.z, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (int32x4_t){ v.x, v.y, v.z, v.w };
		#else
		ints = v;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 * @param v target 3 component vector value
	 */
	explicit simd_i32_4(int3 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32(v.z, v.z, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (int32x4_t){ v.x, v.y, v.z, v.z };
		#else
		ints = int4(v, v.z);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit signed integer vector structure.
	 * @param v target 2 component vector value
	 */
	explicit simd_i32_4(int2 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32(v.y, v.y, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (int32x4_t){ v.x, v.y, v.y, v.y };
		#else
		ints = int4(v, v.y, v.y);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component vector 32bit signed integer structure.
	 * @param[in] v target 4 component vector value pointer (unaligned)
	 */
	explicit simd_i32_4(const int32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_loadu_si128((const __m128i*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_s32(v);
		#else
		ints = *v;
		#endif
	}
	
	/*******************************************************************************************************************
	 * @brief Loads SIMD 4 component 32bit signed integer aligned vector values.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[in] v target 4 component vector value pointer (aligned)
	 */
	void loadAligned(const int32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_load_si128((const __m128i*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_s32(v);
		#else
		ints = *((const int4*)v);
		#endif
	}

	/**
	 * @brief Stores SIMD 4 component 32bit signed integer unaligned vector values.
	 * @param[out] v target 4 component vector value pointer (unaligned)
	 */
	void store(int32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_storeu_si128((__m128i*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_s32(v, data);
		#else
		*((int4*)v) = ints;
		#endif
	}
	/**
	 * @brief Stores SIMD 4 component 32bit signed integer aligned vector values.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[out] v target 4 component vector value pointer (aligned)
	 */
	void storeAligned(int32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_store_si128((__m128i*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_s32(v, data);
		#else
		*((int4*)v) = ints;
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector first component value.
	 */
	int32 getX() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cvtsi128_si32(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_s32(data, 0);
		#else
		return ints.x;
		#endif
	}
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	int32 getY() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_s32(data, 1);
		#else
		return ints.y;
		#endif
	}
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	int32 getZ() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_s32(data, 2);
		#else
		return ints.z;
		#endif
	}
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	int32 getW() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_s32(data, 3);
		#else
		return ints.w;
		#endif
	}

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(int32 value) noexcept { ints.x = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(int32 value) noexcept { ints.y = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(int32 value) noexcept { ints.z = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(int32 value) noexcept { ints.w = value; }

	/**
	 * @brief Swizzles SIMD vector components.
	 * 
	 * @tparam X first vector component swizzle index
	 * @tparam Y second vector component swizzle index
	 * @tparam Z third vector component swizzle index
	 * @tparam W fourth vector component swizzle index
	 */
	template<uint32 X, uint32 Y, uint32 Z, uint32 W = SwU>
	simd_i32_4 swizzle() const noexcept
	{
		static_assert(X <= 3, "X template parameter out of range");
		static_assert(Y <= 3, "Y template parameter out of range");
		static_assert(Z <= 3, "Z template parameter out of range");
		static_assert(W <= 3, "W template parameter out of range");

		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_shuffle_epi32(data, _MM_SHUFFLE(W, Z, Y, X));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return __builtin_shufflevector(data, data, X, Y, Z, W);
		#else
		return simd_i32_4(ints[X], ints[Y], ints[Z], ints[W]);
		#endif
	}

	simd_i32_4 splatX() const noexcept { return swizzle<SwX, SwX, SwX, SwX>(); }
	simd_i32_4 splatY() const noexcept { return swizzle<SwY, SwY, SwY, SwY>(); }
	simd_i32_4 splatZ() const noexcept { return swizzle<SwZ, SwZ, SwZ, SwZ>(); }
	simd_i32_4 splatW() const noexcept { return swizzle<SwW, SwW, SwW, SwW>(); }

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	int32& operator[](psize i) noexcept { return ints[i]; }
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	int32 operator[](psize i) const noexcept { return ints[i]; }

	/**
	 * @brief Returns as 4 component unsigned integer SIMD vector.
	 */
	explicit operator simd_u32_4() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return data;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vreinterpretq_u32_s32(data);
		#else
		return simd_u32_4((uint4)ints);
		#endif
	}

	/**
	 * @brief Returns SIMD vector as 4 component signed integer vector. (xyzw)
	 */
	explicit operator int4() const noexcept { return ints; }
	/**
	 * @brief Returns SIMD vector as 3 component signed integer vector. (xyz)
	 */
	explicit operator int3() const noexcept { return (int3)ints; }
	/**
	 * @brief Returns SIMD vector as 2 component signed integer vector. (xy)
	 */
	explicit operator int2() const noexcept { return (int2)ints; }
	/**
	 * @brief Returns SIMD first vector component value. (x)
	 */
	explicit operator int32() const noexcept { return getX(); }

	//******************************************************************************************************************
	simd_i32_4 operator+(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_add_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vaddq_s32(data, v.data);
		#else
		return simd_i32_4(ints + v.ints);
		#endif
	}
	simd_i32_4 operator-(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vsubq_s32(data, v.data);
		#else
		return simd_i32_4(ints - v.ints);
		#endif
	}
	simd_i32_4 operator*(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE4_1)
		return _mm_mullo_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_s32(data, v.data);
		#else
		return simd_i32_4(ints * v.ints);
		#endif
	}
	simd_i32_4 operator/(simd_i32_4 v) const noexcept { return simd_i32_4(ints / v.ints); }
	simd_i32_4 operator%(simd_i32_4 v) const noexcept { return simd_i32_4(ints % v.ints); }

	//******************************************************************************************************************
	simd_i32_4 operator&(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_and_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vandq_s32(data, v.data);
		#else
		return simd_i32_4(ints & v.ints);
		#endif
	}
	simd_i32_4 operator|(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_or_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vorrq_s32(data, v.data);
		#else
		return simd_i32_4(ints | v.ints);
		#endif
	}
	simd_i32_4 operator^(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return veorq_s32(data, v.data);
		#else
		return simd_i32_4(ints ^ v.ints);
		#endif
	}
	simd_i32_4 operator>>(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_srav_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_s32(data, vnegq_s32(v.data));
		#else
		return simd_i32_4(ints >> v.ints);
		#endif
	}
	simd_i32_4 operator<<(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_sllv_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_s32(data, v.data);
		#else
		return simd_i32_4(ints << v.ints);
		#endif
	}
	simd_i32_4 operator>>(int32 n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_srai_epi32(data, n);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_s32(data, vdupq_n_s32(-n));
		#else
		return simd_i32_4(ints >> n);
		#endif
	}
	simd_i32_4 operator<<(int32 n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_slli_epi32(data, n);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_s32(data, vdupq_n_s32(n));
		#else
		return simd_i32_4(ints << n);
		#endif
	}
	simd_i32_4 operator-() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_epi32(_mm_setzero_si128(), data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vnegq_s32(data);
		#else
		return simd_i32_4(-ints);
		#endif
	}
	simd_i32_4 operator!() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_and_si128(_mm_cmpeq_epi32(data, _mm_setzero_si128()), _mm_set1_epi32(1));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vandq_s32(vreinterpretq_s32_u32(vceqq_s32(data, vdupq_n_s32(0))), vdupq_n_s32(1));
		#else
		return simd_i32_4(!ints);
		#endif
	}
	simd_i32_4 operator~() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_si128(data, _mm_set1_epi32(0xFFFFFFFF));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmvnq_s32(data);
		#else
		return simd_i32_4(~ints);
		#endif
	}

	//******************************************************************************************************************
	simd_i32_4 operator+(int32 n) const noexcept { return *this + simd_i32_4(n); }
	simd_i32_4 operator-(int32 n) const noexcept { return *this - simd_i32_4(n); }
	simd_i32_4 operator*(int32 n) const noexcept { return *this * simd_i32_4(n); }
	simd_i32_4 operator/(int32 n) const noexcept { return *this / simd_i32_4(n); }
	simd_i32_4 operator%(int32 n) const noexcept { return *this % simd_i32_4(n); }
	simd_i32_4 operator&(int32 n) const noexcept { return *this & simd_i32_4(n); }
	simd_i32_4 operator|(int32 n) const noexcept { return *this | simd_i32_4(n); }
	simd_i32_4 operator^(int32 n) const noexcept { return *this ^ simd_i32_4(n); }
	
	simd_i32_4& operator+=(simd_i32_4 v) noexcept { *this = *this + v; return *this; }
	simd_i32_4& operator-=(simd_i32_4 v) noexcept { *this = *this - v; return *this; }
	simd_i32_4& operator*=(simd_i32_4 v) noexcept { *this = *this * v; return *this; }
	simd_i32_4& operator/=(simd_i32_4 v) noexcept { *this = *this / v; return *this; }
	simd_i32_4& operator%=(simd_i32_4 v) noexcept { *this = *this % v; return *this; }
	simd_i32_4& operator&=(simd_i32_4 v) noexcept { *this = *this & v; return *this; }
	simd_i32_4& operator|=(simd_i32_4 v) noexcept { *this = *this | v; return *this; }
	simd_i32_4& operator^=(simd_i32_4 v) noexcept { *this = *this ^ v; return *this; }
	simd_i32_4& operator>>=(simd_i32_4 v) noexcept { *this = *this >> v; return *this; }
	simd_i32_4& operator<<=(simd_i32_4 v) noexcept { *this = *this << v; return *this; }

	simd_i32_4& operator+=(int32 n) noexcept { *this = *this + simd_i32_4(n); return *this; }
	simd_i32_4& operator-=(int32 n) noexcept { *this = *this - simd_i32_4(n); return *this; }
	simd_i32_4& operator*=(int32 n) noexcept { *this = *this * simd_i32_4(n); return *this; }
	simd_i32_4& operator/=(int32 n) noexcept { *this = *this / simd_i32_4(n); return *this; }
	simd_i32_4& operator%=(int32 n) noexcept { *this = *this % simd_i32_4(n); return *this; }
	simd_i32_4& operator&=(int32 n) noexcept { *this = *this & simd_i32_4(n); return *this; }
	simd_i32_4& operator|=(int32 n) noexcept { *this = *this | simd_i32_4(n); return *this; }
	simd_i32_4& operator^=(int32 n) noexcept { *this = *this ^ simd_i32_4(n); return *this; }
	simd_i32_4& operator>>=(int32 n) noexcept { *this = *this >> n; return *this; }
	simd_i32_4& operator<<=(int32 n) noexcept { *this = *this << n; return *this; }
	simd_i32_4& operator=(int32 n) noexcept { *this = simd_i32_4(n); return *this; }

	//******************************************************************************************************************
	bool operator==(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) == 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_s32(data, v.data)) == 0xFFFFFFFFu;
		#else
		return ints == v.ints;
		#endif
	}
	bool operator!=(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) != 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_s32(data, v.data)) == 0u;
		#else
		return ints != v.ints;
		#endif
	}
	simd_u32_4 operator<(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cmplt_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcltq_s32(data, v.data);
		#else
		return simd_u32_4(ints < v.ints);
		#endif
	}
	simd_u32_4 operator>(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cmpgt_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgtq_s32(data, v.data);
		#else
		return simd_u32_4(ints > v.ints);
		#endif
	}
	simd_u32_4 operator<=(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_or_si128(_mm_cmplt_epi32(data, v.data), _mm_cmpeq_epi32(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcleq_s32(data, v.data);
		#else
		return simd_u32_4(ints <= v.ints);
		#endif
	}
	simd_u32_4 operator>=(simd_i32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_or_si128(_mm_cmpgt_epi32(data, v.data), _mm_cmpeq_epi32(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgeq_s32(data, v.data);
		#else
		return simd_u32_4(ints >= v.ints);
		#endif
	}

	bool operator==(int32 n) const noexcept { return *this == simd_i32_4(n); }
	bool operator!=(int32 n) const noexcept { return *this != simd_i32_4(n); }
	simd_u32_4 operator<(int32 n) const noexcept { return *this < simd_i32_4(n); }
	simd_u32_4 operator>(int32 n) const noexcept { return *this > simd_i32_4(n); }
	simd_u32_4 operator<=(int32 n) const noexcept { return *this <= simd_i32_4(n); }
	simd_u32_4 operator>=(int32 n) const noexcept { return *this >= simd_i32_4(n); }

	static const simd_i32_4 zero, one, minusOne, min, max;
};

inline const simd_i32_4 simd_i32_4::zero = simd_i32_4(0);
inline const simd_i32_4 simd_i32_4::one = simd_i32_4(1);
inline const simd_i32_4 simd_i32_4::minusOne = simd_i32_4(-1);
inline const simd_i32_4 simd_i32_4::min = simd_i32_4(INT32_MIN);
inline const simd_i32_4 simd_i32_4::max = simd_i32_4(INT32_MAX);

static simd_i32_4 operator+(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) + v; }
static simd_i32_4 operator-(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) - v; }
static simd_i32_4 operator*(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) * v; }
static simd_i32_4 operator/(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) / v; }
static simd_i32_4 operator%(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) % v; }
static simd_i32_4 operator&(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) & v; }
static simd_i32_4 operator|(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) | v; }
static simd_i32_4 operator^(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) ^ v; }
static simd_i32_4 operator>>(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) >> v; }
static simd_i32_4 operator<<(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) << v; }
static bool operator==(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) == v; }
static bool operator!=(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) != v; }
static simd_u32_4 operator<(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) < v; }
static simd_u32_4 operator>(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) > v; }
static simd_u32_4 operator<=(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) <= v; }
static simd_u32_4 operator>=(int32 n, simd_i32_4 v) noexcept { return simd_i32_4(n) >= v; }

/**
 * @brief Casts from the 4 component unsigned integer to signed integer SIMD vector. (Doesn't change the bits)
 */
static simd_i32_4 uintAsInt(simd_u32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return v.data;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vreinterpretq_s32_u32(v.data);
	#else
	return *((const simd_i32_4*)&v);
	#endif
}

/***********************************************************************************************************************
 * @brief Compares two SIMD vectors component wise if they are equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static simd_u32_4 equal(simd_i32_4 a, simd_i32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_cmpeq_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vceqq_s32(a.data, b.data);
	#else
	return simd_u32_4(equal(a.ints, b.ints));
	#endif
}
/**
 * @brief Compares two SIMD vectors component wise if they are not equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static simd_u32_4 notEqual(simd_i32_4 a, simd_i32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_xor_si128(_mm_cmpeq_epi32(a.data, b.data), _mm_set1_epi32(0xFFFFFFFF));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmvnq_u32(vceqq_s32(a.data, b.data));
	#else
	return simd_u32_4(notEqual(a.ints, b.ints));
	#endif
}

/**
 * @brief SIMD vector bitwise bit clear component wise. [r = a & (~b)]
 *
 * @param a first SIMD vector
 * @param b second SIMD vector
 */
static simd_i32_4 bic(simd_i32_4 a, simd_i32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_andnot_si128(b.data, a.data); // flipped
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vbicq_s32(a.data, b.data);
	#else
	return simd_i32_4(a.ints & (~b.ints));
	#endif
}

/**
 * @brief Returns true if first SIMD vector binary representation is less than the second.
 *
 * @param a first SIMD vector to binary compare
 * @param b second SIMD vector to binary compare
 */
static bool isBinaryLess(simd_i32_4 a, simd_i32_4 b) noexcept { return memcmp(&a, &b, sizeof(simd_i32_4)) < 0; }

/**
 * @brief Selects between two SIMD vector components based on the control vector values.
 * 
 * @param c control SIMD vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static simd_i32_4 select(simd_u32_4 c, simd_i32_4 t, simd_i32_4 f) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_castps_si128(_mm_blendv_ps(_mm_castsi128_ps(f.data), 
		_mm_castsi128_ps(t.data), _mm_castsi128_ps(c.data)));
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	auto isTrue = _mm_castsi128_ps(_mm_srai_epi32(c.data, 31));
	return _mm_castps_si128(_mm_or_ps(_mm_and_ps(isTrue, _mm_castsi128_ps(t.data)), 
		_mm_andnot_ps(isTrue, _mm_castsi128_ps(f.data))));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vbslq_s32(vreinterpretq_u32_s32(vshrq_n_s32(vreinterpretq_s32_u32(c.data), 31)), t.data, f.data);
	#else
	return simd_i32_4(select(c.ints, t.ints, f.ints));
	#endif
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of the SIMD vector.
 * 
 * @param a first SIMD vector to find minimum
 * @param b second SIMD vector to find minimum
 */
static simd_i32_4 min(simd_i32_4 a, simd_i32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_min_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vminq_s32(a.data, b.data);
	#else
	return simd_i32_4(min(a.ints, b.ints));
	#endif
}
/**
 * @brief Returns maximum value for each component of the SIMD vector.
 * 
 * @param a first SIMD vector to find maximum
 * @param b second SIMD vector to find maximum
 */
static simd_i32_4 max(simd_i32_4 a, simd_i32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_max_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmaxq_s32(a.data, b.data);
	#else
	return simd_i32_4(max(a.ints, b.ints));
	#endif
}

/**
 * @brief Returns minimum value of all SIMD vector components.
 * @param v target SIMD vector
 */
static float min(simd_i32_4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of all SIMD vector components.
 * @param v target SIMD vector
 */
static float max(simd_i32_4 v) noexcept
{
	auto m = max(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = max(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}

/**
 * @brief Clamps SIMD vector components between min and max values.
 * 
 * @param v target SIMD vector to clamp
 * @param min SIMD vector with minimum values
 * @param max SIMD vector with maximum values
 */
static simd_i32_4 clamp(simd_i32_4 v, simd_i32_4 min, simd_i32_4 max) noexcept
{
	return math::max(math::min(v, max), min);
}

} // namespace math