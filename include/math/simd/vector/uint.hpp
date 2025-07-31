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
 * @brief Common single instruction multiple data (SIMD) unsigned integer vector functions.
 */

#pragma once
#include "math/simd/types.hpp"
#include "math/vector/uint.hpp"

namespace math
{

static constexpr uint32 SwX = 0; /**< SIMD vector swizzle X component index. */
static constexpr uint32 SwY = 1; /**< SIMD vector swizzle Y component index. */
static constexpr uint32 SwZ = 2; /**< SIMD vector swizzle Z component index. */
static constexpr uint32 SwW = 3; /**< SIMD vector swizzle W component index. */
static constexpr uint32 SwU = 2; /**< SIMD vector swizzle unused component index. */

/**
 * @brief SIMD 4 component 32bit unsigned integer vector structure. (uint4)
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) u32x4
{
	union
	{
		_simd_u128 data;
		uint4 uints;
		int4 ints;
		float4 floats;
	};

	u32x4(const u32x4& v) = default;
	u32x4& operator=(const u32x4& v) = default;

	/**
	 * @brief Creates a new zero initialized SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 */
	u32x4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_setzero_si128();
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_u32(0);
		#else
		uints = uint4::zero;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 * @param xyzw target value for all vector components
	 */
	explicit u32x4(uint32 xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set1_epi32((int)xyzw);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_u32(xyzw);
		#else
		uints = uint4(xyzw);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	u32x4(uint32 x, uint32 y, uint32 z, uint32 w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)w, (int)z, (int)y, (int)x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (uint32x4_t){ x, y, z, w };
		#else
		uints = uint4(x, y, z, w);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 * @warning This constructor duplicates Z component to the W component!
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	u32x4(uint32 x, uint32 y, uint32 z) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)z, (int)z, (int)y, (int)x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (uint32x4_t){ x, y, z, z };
		#else
		uints = uint4(x, y, z, z);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 *
	 * @param xyz first, second and third vector component values
	 * @param w fourth vector component value
	 */
	u32x4(u32x4 xyz, uint32 w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		data = _mm_blend_epi32(xyz.data, _mm_set1_epi32((int)w), 8);
		#elif defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)w, (int)xyz.uints.z, (int)xyz.uints.y, (int)xyz.uints.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vsetq_lane_u32(w, xyz.data, 3);
		#else
		uints = xyz.uints; uints.w = w;
		#endif
	}

	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_NEON)
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 * @param data target vector SIMD data
	 */
	u32x4(_simd_u128 data) : data(data) { }
	#endif

	/*******************************************************************************************************************
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 * @param v target 4 component vector value
	 */
	explicit u32x4(uint4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)v.w, (int)v.z, (int)v.y, (int)v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (uint32x4_t){ v.x, v.y, v.z, v.w };
		#else
		uints = v;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 * @param v target 3 component vector value
	 */
	explicit u32x4(uint3 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)v.z, (int)v.z, (int)v.y, (int)v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (uint32x4_t){ v.x, v.y, v.z, v.z };
		#else
		uints = uint4(v, v.z);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure. (uint4)
	 * @param v target 2 component vector value
	 */
	explicit u32x4(uint2 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)v.y, (int)v.y, (int)v.y, (int)v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (uint32x4_t){ v.x, v.y, v.y, v.y };
		#else
		uints = uint4(v, v.y, v.y);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component vector 32bit unsigned integer structure. (uint4)
	 * @param[in] v target 4 component vector value pointer (unaligned)
	 */
	explicit u32x4(const uint32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_loadu_si128((const __m128i*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_u32(v);
		#else
		uints = *v;
		#endif
	}
	
	/*******************************************************************************************************************
	 * @brief Loads SIMD 4 component 32bit unsigned integer aligned vector value.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[in] v target 4 component vector value pointer (aligned)
	 */
	void loadAligned(const uint32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_load_si128((const __m128i*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_u32(v);
		#else
		uints = *((const uint4*)v);
		#endif
	}

	/**
	 * @brief Stores SIMD 4 component 32bit unsigned integer unaligned vector value.
	 * @param[out] v target 4 component vector value pointer (unaligned)
	 */
	void store(uint32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_storeu_si128((__m128i*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_u32(v, data);
		#else
		*((uint4*)v) = uints;
		#endif
	}
	/**
	 * @brief Stores SIMD 4 component 32bit unsigned integer aligned vector value.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[out] v target 4 component vector value pointer (aligned)
	 */
	void storeAligned(uint32* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_store_si128((__m128i*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_u32((uint32*)v, data);
		#else
		*((uint4*)v) = uints;
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector first component value.
	 */
	uint32 getX() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return (uint32)_mm_cvtsi128_si32(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 0);
		#else
		return uints.x;
		#endif
	}
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	uint32 getY() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 1);
		#else
		return uints.y;
		#endif
	}
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	uint32 getZ() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 2);
		#else
		return uints.z;
		#endif
	}
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	uint32 getW() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 3);
		#else
		return uints.w;
		#endif
	}

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(uint32 value) noexcept { uints.x = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(uint32 value) noexcept { uints.y = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(uint32 value) noexcept { uints.z = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(uint32 value) noexcept { uints.w = value; }

	/**
	 * @brief Sets SIMD vector Z component value to the W component.
	 * @note Usefull when you want to prevent SIMD division by zero.
	 */
	void fixW() noexcept { uints.w = getZ(); }

	/**
	 * @brief Swizzles SIMD vector components.
	 * 
	 * @tparam X first vector component swizzle index
	 * @tparam Y second vector component swizzle index
	 * @tparam Z third vector component swizzle index
	 * @tparam W fourth vector component swizzle index
	 */
	template<uint32 X, uint32 Y, uint32 Z, uint32 W>
	u32x4 swizzle() const noexcept
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
		return u32x4(uints[X], uints[Y], uints[Z], uints[W]);
		#endif
	}

	u32x4 splatX() const noexcept { return swizzle<SwX, SwX, SwX, SwX>(); }
	u32x4 splatY() const noexcept { return swizzle<SwY, SwY, SwY, SwY>(); }
	u32x4 splatZ() const noexcept { return swizzle<SwZ, SwZ, SwZ, SwZ>(); }
	u32x4 splatW() const noexcept { return swizzle<SwW, SwW, SwW, SwW>(); }

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	uint32& operator[](psize i) noexcept { return uints[i]; }
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	uint32 operator[](psize i) const noexcept { return uints[i]; }

	/**
	 * @brief Returns SIMD vector as 4 component unsigned integer vector. (xyzw)
	 */
	explicit operator uint4() const noexcept { return uints; }
	/**
	 * @brief Returns SIMD vector as 3 component unsigned integer vector. (xyz)
	 */
	explicit operator uint3() const noexcept { return (uint3)uints; }
	/**
	 * @brief Returns SIMD vector as 2 component unsigned integer vector. (xy)
	 */
	explicit operator uint2() const noexcept { return (uint2)uints; }
	/**
	 * @brief Returns SIMD first vector component value. (x)
	 */
	explicit operator uint32() const noexcept { return getX(); }

	//******************************************************************************************************************
	u32x4 operator+(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_add_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vaddq_u32(data, v.data);
		#else
		return u32x4(uints + v.uints);
		#endif
	}
	u32x4 operator-(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vsubq_u32(data, v.data);
		#else
		return u32x4(uints - v.uints);
		#endif
	}
	u32x4 operator*(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE4_1)
		return _mm_mullo_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_u32(data, v.data);
		#else
		return u32x4(uints * v.uints);
		#endif
	}
	u32x4 operator/(u32x4 v) const noexcept { return u32x4(uints / v.uints); }
	u32x4 operator%(u32x4 v) const noexcept { return u32x4(uints % v.uints); }

	//******************************************************************************************************************
	u32x4 operator&(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_and_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vandq_u32(data, v.data);
		#else
		return u32x4(uints & v.uints);
		#endif
	}
	u32x4 operator|(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_or_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vorrq_u32(data, v.data);
		#else
		return u32x4(uints | v.uints);
		#endif
	}
	u32x4 operator^(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return veorq_u32(data, v.data);
		#else
		return u32x4(uints ^ v.uints);
		#endif
	}
	u32x4 operator>>(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_srlv_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_u32(data, vnegq_s32(vreinterpretq_s32_u32(v.data)));
		#else
		return u32x4(uints >> v.uints);
		#endif
	}
	u32x4 operator<<(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_sllv_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_u32(data, vreinterpretq_s32_u32(v.data));
		#else
		return u32x4(uints << v.uints);
		#endif
	}
	u32x4 operator>>(uint32 n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_srli_epi32(data, n);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_u32(data, vdupq_n_s32(-((int32)n)));
		#else
		return u32x4(uints >> n);
		#endif
	}
	u32x4 operator<<(uint32 n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_slli_epi32(data, n);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_u32(data, vdupq_n_s32((int32)n));
		#else
		return u32x4(uints << n);
		#endif
	}
	u32x4 operator!() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_and_si128(_mm_cmpeq_epi32(data, _mm_setzero_si128()), _mm_set1_epi32(1));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vandq_u32(vceqq_u32(data, vdupq_n_u32(0)), vdupq_n_u32(1));
		#else
		return u32x4(!uints);
		#endif
	}
	u32x4 operator~() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_si128(data, _mm_set1_epi32(0xFFFFFFFF));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmvnq_u32(data);
		#else
		return u32x4(~uints);
		#endif
	}

	//******************************************************************************************************************
	u32x4 operator+(uint32 n) const noexcept { return *this + u32x4(n); }
	u32x4 operator-(uint32 n) const noexcept { return *this - u32x4(n); }
	u32x4 operator*(uint32 n) const noexcept { return *this * u32x4(n); }
	u32x4 operator/(uint32 n) const noexcept { return *this / u32x4(n); }
	u32x4 operator%(uint32 n) const noexcept { return *this % u32x4(n); }
	u32x4 operator&(uint32 n) const noexcept { return *this & u32x4(n); }
	u32x4 operator|(uint32 n) const noexcept { return *this | u32x4(n); }
	u32x4 operator^(uint32 n) const noexcept { return *this ^ u32x4(n); }

	u32x4& operator+=(u32x4 v) noexcept { *this = *this + v; return *this; }
	u32x4& operator-=(u32x4 v) noexcept { *this = *this - v; return *this; }
	u32x4& operator*=(u32x4 v) noexcept { *this = *this * v; return *this; }
	u32x4& operator/=(u32x4 v) noexcept { *this = *this / v; return *this; }
	u32x4& operator%=(u32x4 v) noexcept { *this = *this % v; return *this; }
	u32x4& operator&=(u32x4 v) noexcept { *this = *this & v; return *this; }
	u32x4& operator|=(u32x4 v) noexcept { *this = *this | v; return *this; }
	u32x4& operator^=(u32x4 v) noexcept { *this = *this ^ v; return *this; }
	u32x4& operator>>=(u32x4 v) noexcept { *this = *this >> v; return *this; }
	u32x4& operator<<=(u32x4 v) noexcept { *this = *this << v; return *this; }

	u32x4& operator+=(uint32 n) noexcept { *this = *this + u32x4(n); return *this; }
	u32x4& operator-=(uint32 n) noexcept { *this = *this - u32x4(n); return *this; }
	u32x4& operator*=(uint32 n) noexcept { *this = *this * u32x4(n); return *this; }
	u32x4& operator/=(uint32 n) noexcept { *this = *this / u32x4(n); return *this; }
	u32x4& operator%=(uint32 n) noexcept { *this = *this % u32x4(n); return *this; }
	u32x4& operator&=(uint32 n) noexcept { *this = *this & u32x4(n); return *this; }
	u32x4& operator|=(uint32 n) noexcept { *this = *this | u32x4(n); return *this; }
	u32x4& operator^=(uint32 n) noexcept { *this = *this ^ u32x4(n); return *this; }
	u32x4& operator>>=(uint32 n) noexcept { *this = *this >> n; return *this; }
	u32x4& operator<<=(uint32 n) noexcept { *this = *this << n; return *this; }
	u32x4& operator=(uint32 n) noexcept { *this = u32x4(n); return *this; }

	//******************************************************************************************************************
	bool operator==(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) == 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_u32(data, v.data)) == 0xFFFFFFFFu;
		#else
		return uints == v.uints;
		#endif
	}
	bool operator!=(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) != 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_u32(data, v.data)) == 0u;
		#else
		return uints != v.uints;
		#endif
	}
	u32x4 operator<(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		const auto mask = _mm_set1_epi32(0x80000000u);
		return _mm_cmplt_epi32(_mm_xor_si128(data, mask), _mm_xor_si128(v.data, mask));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcltq_u32(data, v.data);
		#else
		return u32x4(uints < v.uints);
		#endif
	}
	u32x4 operator>(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		const auto mask = _mm_set1_epi32(0x80000000u);
		return _mm_cmpgt_epi32(_mm_xor_si128(data, mask), _mm_xor_si128(v.data, mask));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgtq_u32(data, v.data);
		#else
		return u32x4(uints > v.uints);
		#endif
	}
	u32x4 operator<=(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		const auto mask = _mm_set1_epi32(0x80000000u);
		auto l = _mm_xor_si128(data, mask), r = _mm_xor_si128(v.data, mask);
		return _mm_or_si128(_mm_cmplt_epi32(l, r), _mm_cmpeq_epi32(l, r));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcleq_u32(data, v.data);
		#else
		return u32x4(uints <= v.uints);
		#endif
	}
	u32x4 operator>=(u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		const auto mask = _mm_set1_epi32(0x80000000u);
		auto l = _mm_xor_si128(data, mask), r = _mm_xor_si128(v.data, mask);
		return _mm_or_si128(_mm_cmpgt_epi32(l, r), _mm_cmpeq_epi32(l, r));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgeq_u32(data, v.data);
		#else
		return u32x4(uints >= v.uints);
		#endif
	}

	bool operator==(uint32 n) const noexcept { return *this == u32x4(n); }
	bool operator!=(uint32 n) const noexcept { return *this != u32x4(n); }
	u32x4 operator<(uint32 n) const noexcept { return *this < u32x4(n); }
	u32x4 operator>(uint32 n) const noexcept { return *this > u32x4(n); }
	u32x4 operator<=(uint32 n) const noexcept { return *this <= u32x4(n); }
	u32x4 operator>=(uint32 n) const noexcept { return *this >= u32x4(n); }

	static const u32x4 zero, one, max;
};

inline const u32x4 u32x4::zero = u32x4(0u);
inline const u32x4 u32x4::one = u32x4(1u);
inline const u32x4 u32x4::max = u32x4(UINT32_MAX);

static u32x4 operator+(uint32 n, u32x4 v) noexcept { return u32x4(n) + v; }
static u32x4 operator-(uint32 n, u32x4 v) noexcept { return u32x4(n) - v; }
static u32x4 operator*(uint32 n, u32x4 v) noexcept { return u32x4(n) * v; }
static u32x4 operator/(uint32 n, u32x4 v) noexcept { return u32x4(n) / v; }
static u32x4 operator%(uint32 n, u32x4 v) noexcept { return u32x4(n) % v; }
static u32x4 operator&(uint32 n, u32x4 v) noexcept { return u32x4(n) & v; }
static u32x4 operator|(uint32 n, u32x4 v) noexcept { return u32x4(n) | v; }
static u32x4 operator^(uint32 n, u32x4 v) noexcept { return u32x4(n) ^ v; }
static u32x4 operator>>(uint32 n, u32x4 v) noexcept { return u32x4(n) >> v; }
static u32x4 operator<<(uint32 n, u32x4 v) noexcept { return u32x4(n) << v; }
static bool operator==(uint32 n, u32x4 v) noexcept { return u32x4(n) == v; }
static bool operator!=(uint32 n, u32x4 v) noexcept { return u32x4(n) != v; }
static u32x4 operator<(uint32 n, u32x4 v) noexcept { return u32x4(n) < v; }
static u32x4 operator>(uint32 n, u32x4 v) noexcept { return u32x4(n) > v; }
static u32x4 operator<=(uint32 n, u32x4 v) noexcept { return u32x4(n) <= v; }
static u32x4 operator>=(uint32 n, u32x4 v) noexcept { return u32x4(n) >= v; }

/**
 * @brief Converts SIMD vector to the string. (space separated)
 * @param v target SIMD vector to convert
 */
static string toString(u32x4 v)
{
	return to_string(v.getX()) + " " + to_string(v.getY()) + " " + to_string(v.getZ()) + " " + to_string(v.getW());
}

/***********************************************************************************************************************
 * @brief Returns mask of SIMD vector components set to true. (4bits)
 */
static int getTrues(u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_ps(_mm_castsi128_ps(v.data));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto shift = (int32x4_t){ 0, 1, 2, 3 };
	return vaddvq_u32(vshlq_u32(vshrq_n_u32(v.data, 31), shift));
	#else
	return getTrues(v.uints);
	#endif
}
/**
 * @brief Returns true if all SIMD vector component bits are set true.
 */
static bool areAllTrue(u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_epi8(v.data) == 0xFFFF;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vminvq_u32(v.data) == 0xFFFFFFFFu;
	#else
	return areAllTrue(v.uints);
	#endif
}
/**
 * @brief Returns false if all SIMD vector component bits are set false.
 */
static bool areAllFalse(u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_testz_si128(v.data, v.data);
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	return !_mm_movemask_epi8(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return !vmaxvq_u32(v.data);
	#else
	return areAllFalse(v.uints);
	#endif
}
/**
 * @brief Returns true if any of SIMD vector component bits are set true.
 */
static bool areAnyTrue(u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return !_mm_testz_si128(v.data, v.data);
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_epi8(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmaxvq_u32(v.data);
	#else
	return areAnyTrue(v.uints);
	#endif
}
/**
 * @brief Returns false if any of SIMD vector component bits is set false.
 */
static bool areAnyFalse(u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_epi8(v.data) != 0xFFFF;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vminvq_u32(v.data) != 0xFFFFFFFFu;
	#else
	return areAnyFalse(v.uints);
	#endif
}

/***********************************************************************************************************************
 * @brief Compares two SIMD vectors component wise if they are equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static u32x4 equal(u32x4 a, u32x4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_cmpeq_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vceqq_u32(a.data, b.data);
	#else
	return u32x4(equal(a.uints, b.uints));
	#endif
}
/**
 * @brief Compares two SIMD vectors component wise if they are not equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static u32x4 notEqual(u32x4 a, u32x4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_xor_si128(_mm_cmpeq_epi32(a.data, b.data), _mm_set1_epi32(0xFFFFFFFF));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmvnq_u32(vceqq_u32(a.data, b.data));
	#else
	return u32x4(notEqual(a.uints, b.uints));
	#endif
}

/**
 * @brief SIMD vector bitwise bit clear component wise. [r = a & (~b)]
 *
 * @param a first SIMD vector
 * @param b second SIMD vector
 */
static u32x4 bic(u32x4 a, u32x4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_andnot_si128(b.data, a.data); // flipped
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vbicq_u32(a.data, b.data);
	#else
	return u32x4(a.uints & (~b.uints));
	#endif
}

/**
 * @brief Returns true if first SIMD vector binary representation is less than the second.
 *
 * @param a first SIMD vector to binary compare
 * @param b second SIMD vector to binary compare
 */
static bool isBinaryLess(u32x4 a, u32x4 b) noexcept { return memcmp(&a, &b, sizeof(u32x4)) < 0; }

/**
 * @brief Selects between two SIMD vector components based on the control vector values.
 * 
 * @param c control SIMD vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static u32x4 select(u32x4 c, u32x4 t, u32x4 f) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_castps_si128(_mm_blendv_ps(_mm_castsi128_ps(f.data), 
		_mm_castsi128_ps(t.data), _mm_castsi128_ps(c.data)));
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	auto isTrue = _mm_castsi128_ps(_mm_srai_epi32(c.data, 31));
	return _mm_castps_si128(_mm_or_ps(_mm_and_ps(isTrue, _mm_castsi128_ps(t.data)), 
		_mm_andnot_ps(isTrue, _mm_castsi128_ps(f.data))));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vbslq_u32(vreinterpretq_u32_s32(vshrq_n_s32(
		vreinterpretq_s32_u32(c.data), 31)), t.data, f.data);
	#else
	return u32x4(select(c.uints, t.uints, f.uints));
	#endif
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of the SIMD vector.
 * 
 * @param a first SIMD vector to find minimum
 * @param b second SIMD vector to find minimum
 */
static u32x4 min(u32x4 a, u32x4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_min_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vminq_u32(a.data, b.data);
	#else
	return u32x4(min(a.uints, b.uints));
	#endif
}
/**
 * @brief Returns maximum value for each component of the SIMD vector.
 * 
 * @param a first SIMD vector to find maximum
 * @param b second SIMD vector to find maximum
 */
static u32x4 max(u32x4 a, u32x4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_max_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmaxq_u32(a.data, b.data);
	#else
	return u32x4(max(a.uints, b.uints));
	#endif
}

/**
 * @brief Returns minimum value of all SIMD vector components.
 * @param v target SIMD vector
 */
static uint32 min(u32x4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of all SIMD vector components.
 * @param v target SIMD vector
 */
static uint32 max(u32x4 v) noexcept
{
	auto m = max(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = max(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}

/**
 * @brief Returns minimum value of 4D SIMD vector components.
 * @param v target SIMD vector
 */
static uint32 min4(u32x4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of 4D SIMD vector components.
 * @param v target SIMD vector
 */
static uint32 max4(u32x4 v) noexcept
{
	auto m = max(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = max(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}

/**
 * @brief Returns minimum value of 3D SIMD vector components.
 * @param v target SIMD vector
 */
static uint32 min3(u32x4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwZ, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of 3D SIMD vector components.
 * @param v target SIMD vector
 */
static uint32 max3(u32x4 v) noexcept
{
	auto m = max(v, v.swizzle<SwY, SwU, SwZ, SwU>());
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
static u32x4 clamp(u32x4 v, u32x4 min, u32x4 max) noexcept
{
	return math::max(math::min(v, max), min);
}

//**********************************************************************************************************************
static uint8 calcMipCount3(u32x4 size) noexcept
{
	return (uint8)(std::floor(std::log2((float)max3(size)))) + 1u;
}
static u32x4 calcSizeAtMip3(u32x4 sizeAt0, uint8 mip) noexcept
{
	return max(sizeAt0 / (uint32)std::exp2((float)mip), u32x4(1u));
}

} // namespace math