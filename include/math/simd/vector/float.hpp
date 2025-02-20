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
#include "math/vector/float.hpp"
#include "math/simd/vector/uint.hpp"

namespace math
{

/**
 * @brief SIMD 4 component 32bit floating point vector structure.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_f32x4
{
	union
	{
		_simd_f128 data; /** Packed SIMD 4 component 32bit floating point vector data. */
		float values[4];
	};

	/**
	 * @brief Creates a new zero initialized SIMD 4 component 32bit floating point vector structure.
	 */
	simd_f32x4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_setzero_ps();
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_f32(0.0f);
		#else
		data[0] = 0.0f; data[1] = 0.0f; data[2] = 0.0f; data[3] = 0.0f;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit simd_f32x4(float xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set1_ps(xyzw);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_f32(xyzw);
		#else
		data[0] = xyzw; data[1] = xyzw; data[2] = xyzw; data[3] = xyzw;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	simd_f32x4(float x, float y, float z, float w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(w, z, y, x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { x, y, z, w };
		#else
		data[0] = x; data[1] = y; data[2] = z; data[3] = w;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param data target vector SIMD data
	 */
	simd_f32x4(_simd_f128 data) : data(data) { }

	/*******************************************************************************************************************
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target 4 component vector value
	 */
	explicit simd_f32x4(float4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(v.w, v.z, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { v.x, v.y, v.z, v.w };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.z; data[3] = v.w;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target 3 component vector value
	 */
	explicit simd_f32x4(float3 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(v.z, v.z, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { v.x, v.y, v.z, v.z };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.z; data[3] = v.z;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target 2 component vector value
	 */
	explicit simd_f32x4(float2 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(v.y, v.y, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = { v.x, v.y, v.y, v.y };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.y; data[3] = v.y;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param[in] v target 4 component vector value pointer (unaligned)
	 */
	explicit simd_f32x4(const float4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_loadu_ps((const float*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_f32((const float*)v);
		#else
		data[0] = v->x; data[1] = v->y; data[2] = v->z; data[3] = v->w;
		#endif
	}
	
	/*******************************************************************************************************************
	 * @brief Loads SIMD 4 component 32bit floating point aligned vector value.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[in] v target 4 component vector value pointer (aligned)
	 */
	void loadAligned(const float4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_load_ps((const float*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_f32((const float*)v);
		#else
		data[0] = v->x; data[1] = v->y; data[2] = v->z; data[3] = v->w;
		#endif
	}
	/**
	 * @brief Stores SIMD 4 component 32bit floating point unaligned vector value.
	 * @param[out] v target 4 component vector value pointer (unaligned)
	 */
	void store(float4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_storeu_ps((float*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_f32((float*)v, data);
		#else
		v[0] = values[0]; v[1] = values[1]; v[2] = values[2]; v[3] = values[3];
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector first component value.
	 */
	float getX() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cvtss_f32(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 0);
		#else
		return values[0];
		#endif
	}
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	float getY() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return values[1];
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 1);
		#else
		return values[1];
		#endif
	}
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	float getZ() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return values[2];
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 2);
		#else
		return values[2];
		#endif
	}
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	float getW() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return values[3];
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 3);
		#else
		return values[3];
		#endif
	}

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(float value) noexcept { values[0] = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(float value) noexcept { values[1] = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(float value) noexcept { values[2] = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(float value) noexcept { values[3] = value; }

	/**
	 * @brief Swizzles SIMD vector components.
	 * 
	 * @tparam X first vector component swizzle index
	 * @tparam Y second vector component swizzle index
	 * @tparam Z third vector component swizzle index
	 * @tparam W fourth vector component swizzle index
	 */
	template<uint32 X, uint32 Y, uint32 Z, uint32 W>
	simd_f32x4 swizzle() const noexcept
	{
		static_assert(X <= 3, "SwizzleX template parameter out of range");
		static_assert(Y <= 3, "SwizzleY template parameter out of range");
		static_assert(Z <= 3, "SwizzleZ template parameter out of range");
		static_assert(W <= 3, "SwizzleW template parameter out of range");

		#if defined(JPH_USE_SSE)
		return _mm_shuffle_ps(data, data, _MM_SHUFFLE(X, Y, Z, W));
		#elif defined(JPH_USE_NEON)
		return __builtin_shufflevector(data, data, X, Y, Z, W);
		#else
		return Vec4(values[X], values[Y], values[Z], values[W]);
		#endif
	}

	simd_f32x4 splatX() const noexcept { return swizzle<SwX, SwX, SwX, SwX>(); }
	simd_f32x4 splatY() const noexcept { return swizzle<SwY, SwY, SwY, SwY>(); }
	simd_f32x4 splatZ() const noexcept { return swizzle<SwZ, SwZ, SwZ, SwZ>(); }
	simd_f32x4 splatW() const noexcept { return swizzle<SwW, SwW, SwW, SwW>(); }

	// TODO: swizzle for uint vector

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return values[i];
	}
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return values[i];
	}

	/**
	 * @brief Returns SIMD vector as 4 component floating point vector. (xyzw)
	 */
	explicit operator float4() const noexcept { return *((float4*)values); }
	/**
	 * @brief Returns SIMD vector as 3 component floating point vector. (xyz)
	 */
	explicit operator float3() const noexcept { return *((float3*)values); }
	/**
	 * @brief Returns SIMD vector as 2 component floating point vector. (xy)
	 */
	explicit operator float2() const noexcept { return *((float2*)values); }
	/**
	 * @brief Returns SIMD first vector component value. (x)
	 */
	explicit operator float() const noexcept { return getX(); }

	//******************************************************************************************************************
	simd_f32x4 operator+(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_add_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vaddq_f32(data, v.data);
		#else
		return simd_f32x4(values[0] + v.values[0], values[1] + v.values[1],
			values[2] + v.values[2], values[3] + v.values[3]);
		#endif
	}
	simd_f32x4 operator-(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vsubq_f32(data, v.data);
		#else
		return simd_f32x4(values[0] - v.values[0], values[1] - v.values[1],
			values[2] - v.values[2], values[3] - v.values[3]);
		#endif
	}
	simd_f32x4 operator*(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_mul_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_f32(data, v.data);
		#else
		return simd_f32x4(values[0] * v.values[0], values[1] * v.values[1],
			values[2] * v.values[2], values[3] * v.values[3]);
		#endif
	}
	simd_f32x4 operator/(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_div_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vdivq_f32(data, v.data);
		#else
		return simd_f32x4(values[0] / v.values[0], values[1] / v.values[1],
			values[2] / v.values[2], values[3] / v.values[3]);
		#endif
	}
	simd_f32x4 operator-() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_ps(data, _mm_set1_ps(-0.0f));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vnegq_f32(data);
		#else
		return simd_f32x4(-values[0], -values[1], -values[2], -values[3]);
		#endif
	}

	simd_f32x4& operator+=(simd_f32x4 v) noexcept { *this = *this + v; return *this; }
	simd_f32x4& operator-=(simd_f32x4 v) noexcept { *this = *this - v; return *this; }
	simd_f32x4& operator*=(simd_f32x4 v) noexcept { *this = *this * v; return *this; }
	simd_f32x4& operator/=(simd_f32x4 v) noexcept { *this = *this / v; return *this; }
	simd_f32x4& operator+=(float n) noexcept { *this = *this + simd_f32x4(n); return *this; }
	simd_f32x4& operator-=(float n) noexcept { *this = *this - simd_f32x4(n); return *this; }
	simd_f32x4& operator*=(float n) noexcept { *this = *this * simd_f32x4(n); return *this; }
	simd_f32x4& operator/=(float n) noexcept { *this = *this / simd_f32x4(n); return *this; }
	simd_f32x4& operator=(float n) noexcept { *this = simd_f32x4(n); return *this; }

	//******************************************************************************************************************
	bool operator==(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_ps(_mm_cmpeq_ps(data, v.data)) == 0b1111;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_f32(data, v.data)) == 0xFFFFFFFFu;
		#else
		return values[0] == v.values[0] && values[1] == v.values[1] && 
			values[2] == v.values[2] && values[3] == v.values[3];
		#endif
	}
	bool operator!=(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_ps(_mm_cmpeq_ps(data, v.data)) != 0b1111;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_f32(data, v.data)) == 0u;
		#else
		return values[0] != v.values[0] || values[1] != v.values[1] || 
			values[2] != v.values[2] || values[3] != v.values[3];
		#endif
	}
	simd_u32x4 operator<(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmplt_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcltq_f32(data, v.data);
		#else
		return simd_u32x4(values[0] < v.values[0] ? 0xFFFFFFFFu : 0, values[1] < v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] < v.values[2] ? 0xFFFFFFFFu : 0, values[3] < v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32x4 operator>(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmpgt_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgtq_f32(data, v.data);
		#else
		return simd_u32x4(values[0] > v.values[0] ? 0xFFFFFFFFu : 0, values[1] > v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] > v.values[2] ? 0xFFFFFFFFu : 0, values[3] > v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32x4 operator<=(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmple_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcleq_f32(data, v.data);
		#else
		return simd_u32x4(values[0] <= v.values[0] ? 0xFFFFFFFFu : 0, values[1] <= v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] <= v.values[2] ? 0xFFFFFFFFu : 0, values[3] <= v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32x4 operator>=(simd_f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmpge_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgeq_f32(data, v.data);
		#else
		return simd_u32x4(values[0] >= v.values[0] ? 0xFFFFFFFFu : 0, values[1] >= v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] >= v.values[2] ? 0xFFFFFFFFu : 0, values[3] >= v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}

	static const simd_f32x4 zero, one, minusOne;
};

inline const simd_f32x4 simd_f32x4::zero = simd_f32x4(0.0f);
inline const simd_f32x4 simd_f32x4::one = simd_f32x4(1.0f);
inline const simd_f32x4 simd_f32x4::minusOne = simd_f32x4(-1.0f);

//**********************************************************************************************************************
static simd_f32x4 operator+(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) + v; }
static simd_f32x4 operator-(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) - v; }
static simd_f32x4 operator*(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) * v; }
static simd_f32x4 operator/(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) / v; }
static bool operator==(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) == v; }
static bool operator!=(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) != v; }
static simd_u32x4 operator<(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) < v; }
static simd_u32x4 operator>(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) > v; }
static simd_u32x4 operator<=(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) <= v; }
static simd_u32x4 operator>=(float n, simd_f32x4 v) noexcept { return simd_f32x4(n) >= v; }

} // namespace math