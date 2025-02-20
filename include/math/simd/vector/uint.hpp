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

/**
 * @brief SIMD 4 component 32bit unsigned integer vector structure.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_u32x4
{
	union
	{
		_simd_u128 data; /** Packed SIMD 4 component 32bit unsigned integer vector data. */
		uint32 values[4];
	};

	/**
	 * @brief Creates a new zero initialized SIMD 4 component 32bit unsigned integer vector structure.
	 */
	simd_u32x4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_setzero_si128();
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_u32(0);
		#else
		data[0] = 0; data[1] = 0; data[2] = 0; data[3] = 0;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit simd_u32x4(uint32 xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set1_epi32((int)xyzw);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_u32(xyzw);
		#else
		data[0] = xyzw; data[1] = xyzw; data[2] = xyzw; data[3] = xyzw;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	simd_u32x4(uint32 x, uint32 y, uint32 z, uint32 w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)w, (int)z, (int)y, (int)x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { x, y, z, w };
		#else
		data[0] = x; data[1] = y; data[2] = z; data[3] = w;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure.
	 * @param data target vector SIMD data
	 */
	simd_u32x4(_simd_u128 data) : data(data) { }

	/*******************************************************************************************************************
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure.
	 * @param v target 4 component vector value
	 */
	explicit simd_u32x4(uint4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)v.w, (int)v.z, (int)v.y, (int)v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { v.x, v.y, v.z, v.w };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.z; data[3] = v.w;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure.
	 * @param v target 3 component vector value
	 */
	explicit simd_u32x4(uint3 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)v.z, (int)v.z, (int)v.y, (int)v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { v.x, v.y, v.z, v.z };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.z; data[3] = v.z;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit unsigned integer vector structure.
	 * @param v target 2 component vector value
	 */
	explicit simd_u32x4(uint2 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_epi32((int)v.y, (int)v.y, (int)v.y, (int)v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { v.x, v.y, v.y, v.y };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.y; data[3] = v.y;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component vector 32bit unsigned integer structure.
	 * @param[in] v target 4 component vector value pointer (unaligned)
	 */
	explicit simd_u32x4(const uint4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_loadu_si128((const _simd_u128*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_u32((const uint32*)v);
		#else
		data[0] = v->x; data[1] = v->y; data[2] = v->z; data[3] = v->w;
		#endif
	}
	
	/*******************************************************************************************************************
	 * @brief Loads SIMD 4 component 32bit unsigned integer aligned vector value.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[in] v target 4 component vector value pointer (aligned)
	 */
	void loadAligned(const uint4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_load_si128((const _simd_u128*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_u32((const uint32*)v);
		#else
		data[0] = v->x; data[1] = v->y; data[2] = v->z; data[3] = v->w;
		#endif
	}
	/**
	 * @brief Stores SIMD 4 component 32bit unsigned integer unaligned vector value.
	 * @param[out] v target 4 component vector value pointer (unaligned)
	 */
	void store(uint4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_storeu_si128((_simd_u128*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_u32((uint32*)v, data);
		#else
		v[0] = values[0]; v[1] = values[1]; v[2] = values[2]; v[3] = values[3];
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
		return values[0];
		#endif
	}
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	uint32 getY() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return values[1];
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 1);
		#else
		return values[1];
		#endif
	}
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	uint32 getZ() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return values[2];
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 2);
		#else
		return values[2];
		#endif
	}
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	uint32 getW() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return values[3];
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_u32(data, 3);
		#else
		return values[3];
		#endif
	}

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(uint32 value) noexcept { values[0] = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(uint32 value) noexcept { values[1] = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(uint32 value) noexcept { values[2] = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(uint32 value) noexcept { values[3] = value; }

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	uint32& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return values[i];
	}
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	uint32 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return values[i];
	}

	/**
	 * @brief Returns SIMD vector as 4 component unsigned integer vector. (xyzw)
	 */
	explicit operator uint4() const noexcept { return *((uint4*)values); }
	/**
	 * @brief Returns SIMD vector as 3 component unsigned integer vector. (xyz)
	 */
	explicit operator uint3() const noexcept { return *((uint3*)values); }
	/**
	 * @brief Returns SIMD vector as 2 component unsigned integer vector. (xy)
	 */
	explicit operator uint2() const noexcept { return *((uint2*)values); }
	/**
	 * @brief Returns SIMD first vector component value. (x)
	 */
	explicit operator uint32() const noexcept { return getX(); }

	//******************************************************************************************************************
	simd_u32x4 operator+(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_add_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vaddq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] + v.values[0], values[1] + v.values[1],
			values[2] + v.values[2], values[3] + v.values[3]);
		#endif
	}
	simd_u32x4 operator-(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vsubq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] - v.values[0], values[1] - v.values[1],
			values[2] - v.values[2], values[3] - v.values[3]);
		#endif
	}
	simd_u32x4 operator*(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_mullo_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] * v.values[0], values[1] * v.values[1],
			values[2] * v.values[2], values[3] * v.values[3]);
		#endif
	}
	simd_u32x4 operator/(simd_u32x4 v) const noexcept
	{
		return simd_u32x4(values[0] / v.values[0], values[1] / v.values[1],
			values[2] / v.values[2], values[3] / v.values[3]);
	}
	simd_u32x4 operator%(simd_u32x4 v) const noexcept
	{
		return simd_u32x4(values[0] % v.values[0], values[1] % v.values[1],
			values[2] % v.values[2], values[3] % v.values[3]);
	}

	//******************************************************************************************************************
	simd_u32x4 operator&(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_and_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vandq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] & v.values[0], values[1] & v.values[1],
			values[2] & v.values[2], values[3] & v.values[3]);
		#endif
	}
	simd_u32x4 operator|(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_or_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vorrq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] | v.values[0], values[1] | v.values[1],
			values[2] | v.values[2], values[3] | v.values[3]);
		#endif
	}
	simd_u32x4 operator^(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_si128(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return veorq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] ^ v.values[0], values[1] ^ v.values[1],
			values[2] ^ v.values[2], values[3] ^ v.values[3]);
		#endif
	}
	simd_u32x4 operator>>(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_srlv_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_u32(data, vnegq_s32(vreinterpretq_s32_u32(v.data)));
		#else
		return simd_u32x4(values[0] >> v.values[0], values[1] >> v.values[1],
			values[2] >> v.values[2], values[3] >> v.values[3]);
		#endif
	}
	simd_u32x4 operator<<(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_sllv_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_u32(data, vreinterpretq_s32_u32(v.data));
		#else
		return simd_u32x4(values[0] << v.values[0], values[1] << v.values[1],
			values[2] << v.values[2], values[3] << v.values[3]);
		#endif
	}
	simd_u32x4 operator>>(uint32 n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_srli_epi32(data, n);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshrq_n_u32(data, n);
		#else
		return simd_u32x4(values[0] >> n, values[1] >> n, values[2] >> n, values[3] >> n);
		#endif
	}
	// TODO: use arithmetic shift right for signed integers!!!
	simd_u32x4 operator<<(uint32 n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		return _mm_slli_epi32(data, n);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vshlq_n_u32(data, n);
		#else
		return simd_u32x4(values[0] << n, values[1] << n, values[2] << n, values[3] << n);
		#endif
	}
	simd_u32x4 operator~() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_si128(data, _mm_set1_epi32(0xFFFFFFFF));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmvnq_u32(data);
		#else
		return simd_u32x4(~values[0], ~values[1], ~values[2], ~values[3]);
		#endif
	}

	//******************************************************************************************************************
	simd_u32x4& operator+=(simd_u32x4 v) noexcept { *this = *this + v; return *this; }
	simd_u32x4& operator-=(simd_u32x4 v) noexcept { *this = *this - v; return *this; }
	simd_u32x4& operator*=(simd_u32x4 v) noexcept { *this = *this * v; return *this; }
	simd_u32x4& operator/=(simd_u32x4 v) noexcept { *this = *this / v; return *this; }
	simd_u32x4& operator%=(simd_u32x4 v) noexcept { *this = *this % v; return *this; }
	simd_u32x4& operator&=(simd_u32x4 v) noexcept { *this = *this & v; return *this; }
	simd_u32x4& operator|=(simd_u32x4 v) noexcept { *this = *this | v; return *this; }
	simd_u32x4& operator^=(simd_u32x4 v) noexcept { *this = *this ^ v; return *this; }
	simd_u32x4& operator>>(simd_u32x4 v) noexcept { *this = *this >> v; return *this; }
	simd_u32x4& operator<<(simd_u32x4 v) noexcept { *this = *this << v; return *this; }

	simd_u32x4& operator+=(uint32 n) noexcept { *this = *this + simd_u32x4(n); return *this; }
	simd_u32x4& operator-=(uint32 n) noexcept { *this = *this - simd_u32x4(n); return *this; }
	simd_u32x4& operator*=(uint32 n) noexcept { *this = *this * simd_u32x4(n); return *this; }
	simd_u32x4& operator/=(uint32 n) noexcept { *this = *this / simd_u32x4(n); return *this; }
	simd_u32x4& operator%=(uint32 n) noexcept { *this = *this % simd_u32x4(n); return *this; }
	simd_u32x4& operator&=(uint32 n) noexcept { *this = *this & simd_u32x4(n); return *this; }
	simd_u32x4& operator|=(uint32 n) noexcept { *this = *this | simd_u32x4(n); return *this; }
	simd_u32x4& operator^=(uint32 n) noexcept { *this = *this ^ simd_u32x4(n); return *this; }
	simd_u32x4& operator>>=(uint32 n) noexcept { *this = *this >> n; return *this; }
	simd_u32x4& operator<<=(uint32 n) noexcept { *this = *this << n; return *this; }
	simd_u32x4& operator=(uint32 n) noexcept { *this = simd_u32x4(n); return *this; }

	//******************************************************************************************************************
	bool operator==(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) == 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_u32(data, v.data)) == 0xFFFFFFFFu;
		#else
		return values[0] == v.values[0] && values[1] == v.values[1] && 
			values[2] == v.values[2] && values[3] == v.values[3];
		#endif
	}
	bool operator!=(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_epi8(_mm_cmpeq_epi32(data, v.data)) != 0xFFFF;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_f32(data, v.data)) == 0u;
		#else
		return values[0] != v.values[0] || values[1] != v.values[1] || 
			values[2] != v.values[2] || values[3] != v.values[3];
		#endif
	}
	simd_u32x4 operator<(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cmplt_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcltq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] < v.values[0] ? 0xFFFFFFFFu : 0, values[1] < v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] < v.values[2] ? 0xFFFFFFFFu : 0, values[3] < v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32x4 operator>(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cmpgt_epi32(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgtq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] > v.values[0] ? 0xFFFFFFFFu : 0, values[1] > v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] > v.values[2] ? 0xFFFFFFFFu : 0, values[3] > v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32x4 operator<=(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		auto cmpLT = _mm_cmplt_epi32(data, v.data);
		auto cmpEQ = _mm_cmpeq_epi32(data, v.data);
		return _mm_or_si128(cmpLT, cmpEQ);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcleq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] <= v.values[0] ? 0xFFFFFFFFu : 0, values[1] <= v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] <= v.values[2] ? 0xFFFFFFFFu : 0, values[3] <= v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32x4 operator>=(simd_u32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		auto cmpGT = _mm_cmpgt_epi32(data, v.data);
		auto cmpEQ = _mm_cmpeq_epi32(data, v.data);
		return _mm_or_si128(cmpGT, cmpEQ);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgeq_u32(data, v.data);
		#else
		return simd_u32x4(values[0] >= v.values[0] ? 0xFFFFFFFFu : 0, values[1] >= v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] >= v.values[2] ? 0xFFFFFFFFu : 0, values[3] >= v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}

	static const simd_u32x4 zero, one;
};

inline const simd_u32x4 simd_u32x4::zero = simd_u32x4(0u);
inline const simd_u32x4 simd_u32x4::one = simd_u32x4(1u);

//**********************************************************************************************************************
static simd_u32x4 operator+(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) + v; }
static simd_u32x4 operator-(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) - v; }
static simd_u32x4 operator*(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) * v; }
static simd_u32x4 operator/(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) / v; }
static simd_u32x4 operator%(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) % v; }
static simd_u32x4 operator&(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) & v; }
static simd_u32x4 operator|(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) | v; }
static simd_u32x4 operator^(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) ^ v; }
static simd_u32x4 operator>>(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) >> v; }
static simd_u32x4 operator<<(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) << v; }
static bool operator==(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) == v; }
static bool operator!=(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) != v; }
static simd_u32x4 operator<(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) < v; }
static simd_u32x4 operator>(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) > v; }
static simd_u32x4 operator<=(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) <= v; }
static simd_u32x4 operator>=(uint32 n, simd_u32x4 v) noexcept { return simd_u32x4(n) >= v; }

/**
 * @brief Returns mask of SIMD vector components set to true. (4bits)
 */
static bool getTrues(simd_u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_ps(_mm_castsi128_ps(v.data));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	int32x4_t shift = { 0, 1, 2, 3 };
	return vaddvq_u32(vshlq_u32(vshrq_n_u32(v.data, 31), shift));
	#else
	return (v.values[0] >> 31) | ((v.values[1] >> 31) << 1) | 
		((v.values[2] >> 31) << 2) | ((v.values[3] >> 31) << 3);
	#endif
}
/**
 * @brief Returns true if all SIMD vector components are set true.
 */
static bool areAllTrue(simd_u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_epi8(v.data) == 0xFFFF;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vminvq_u32(v.data) == 0xFFFFFFFFu;
	#else
	return v.values[0] && v.values[1] && v.values[2] && v.values[3];
	#endif
}
/**
 * @brief Returns false if all SIMD vector components are set false.
 */
static bool areAllFalse(simd_u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_testz_si128(v.data, v.data);
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	return !_mm_movemask_epi8(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return !vmaxvq_u32(v.data);
	#else
	return !(v.values[0] || v.values[1] || v.values[2] || v.values[3]);
	#endif
}
/**
 * @brief Returns true if any of SIMD vector components are set true.
 */
static bool areAnyTrue(simd_u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return !_mm_testz_si128(v.data, v.data);
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_epi8(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmaxvq_u32(v.data);
	#else
	return v.values[0] || v.values[1] || v.values[2] || v.values[3];
	#endif
}
/**
 * @brief Returns false if any of SIMD vector components are set false.
 */
static bool areAnyFalse(simd_u32x4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_epi8(v.data) != 0xFFFF;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return !vminvq_u32(v.data);
	#else
	return !(v.values[0] && v.values[1] && v.values[2] && v.values[3]);
	#endif
}

/***********************************************************************************************************************
 * @brief Compares two SIMD vectors component wise if they are equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static simd_u32x4 compare(simd_u32x4 a, simd_u32x4 b)
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_cmpeq_epi32(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vceqq_u32(a.data, b.data);
	#else
	return simd_u32x4(a.values[0] == b.values[0] ? 0xFFFFFFFFu : 0, a.values[1] == b.values[1] ? 0xFFFFFFFFu : 0,
		a.values[2] == b.values[2] ? 0xFFFFFFFFu : 0, a.values[3] == b.values[3] ? 0xFFFFFFFFu : 0);
	#endif
}
/**
 * @brief Returns true if first SIMD vector binary representation is less than the second.
 *
 * @param a first SIMD vector to binary compare
 * @param b second SIMD vector to binary compare
 */
static bool isBinaryLess(simd_u32x4 a, simd_u32x4 b) noexcept { return memcmp(&a, &b, sizeof(simd_u32x4)) < 0; }

/**
 * @brief Selects between two SIMD vector components based on the control vector values.
 * 
 * @param c control SIMD vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static simd_u32x4 select(simd_u32x4 c, simd_u32x4 t, simd_u32x4 f) noexcept
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
	return simd_u32x4(
		c.values[0] & 0x80000000u ? t.values[0] : f.values[0], 
		c.values[1] & 0x80000000u ? t.values[1] : f.values[1],
		c.values[2] & 0x80000000u ? t.values[2] : f.values[2],
		c.values[3] & 0x80000000u ? t.values[3] : f.values[3]);
	#endif
}

} // namespace math