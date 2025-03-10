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
#include "math/simd/vector/int.hpp"

#if defined(MATH_SIMD_SUPPORT_AVX2)
#define MATH_SIMD_FMA(mul1, mul2, add) _mm_fmadd_ps(mul1, mul2, add)  // r = mul1 * mul2 + add
#elif defined(MATH_SIMD_SUPPORT_SSE)
#define MATH_SIMD_FMA(mul1, mul2, add) _mm_add_ps(add, _mm_mul_ps(mul1, mul2))
#elif defined(MATH_SIMD_SUPPORT_NEON)
#define MATH_SIMD_FMA(mul1, mul2, add) vmlaq_f32(add, mul1, mul2)
#endif

namespace math
{

/**
 * @brief SIMD 4 component 32bit floating point vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_f32_4
{
	union
	{
		_simd_f128 data;
		float4 floats;
		int4 ints;
		uint4 uints;
	};

	simd_f32_4(const simd_f32_4& v) = default;
	simd_f32_4&	operator=(const simd_f32_4& v) = default;

	/**
	 * @brief Creates a new zero initialized SIMD 4 component 32bit floating point vector structure.
	 */
	simd_f32_4() noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_setzero_ps();
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_f32(0.0f);
		#else
		floats = float4::zero;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit simd_f32_4(float xyzw) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set1_ps(xyzw);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vdupq_n_f32(xyzw);
		#else
		floats = float4(xyzw);
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
	simd_f32_4(float x, float y, float z, float w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(w, z, y, x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float32x4_t){ x, y, z, w };
		#else
		floats = float4(x, y, z, w);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @warning This constructor duplicates Z component to the W component!
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	simd_f32_4(float x, float y, float z) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(z, z, y, x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float32x4_t){ x, y, z, z };
		#else
		floats = float4(x, y, z, z);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 *
	 * @param xyz first, second and third vector component values
	 * @param w fourth vector component value
	 */
	simd_f32_4(simd_f32_4 xyz, float w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE4_1)
		data = _mm_blend_ps(xyz.data, _mm_set1_ps(w), 8);
		#elif defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(w, xyz.floats.z, xyz.floats.y, xyz.floats.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vsetq_lane_f32(w, xyz.data, 3);
		#else
		floats = xyz.floats; floats.w = w;
		#endif
	}

	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_NEON)
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param data target vector floating point SIMD data
	 */
	simd_f32_4(_simd_f128 data) : data(data) { }
	#endif

	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target vector unsigned integer SIMD data
	 */
	explicit simd_f32_4(simd_u32_4 v)
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_cvtepi32_ps(v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vcvtq_f32_u32(v.data);
		#else
		floats = v.floats;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target vector signed integer SIMD data
	 */
	explicit simd_f32_4(simd_i32_4 v)
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_cvtepi32_ps(v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vcvtq_f32_s32(v.data);
		#else
		floats = v.floats;
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target 4 component vector value
	 */
	explicit simd_f32_4(float4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(v.w, v.z, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float32x4_t){ v.x, v.y, v.z, v.w };
		#else
		floats = v;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target 3 component vector value
	 */
	explicit simd_f32_4(float3 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(v.z, v.z, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float32x4_t){ v.x, v.y, v.z, v.z };
		#else
		floats = float4(v, v.z);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param v target 2 component vector value
	 */
	explicit simd_f32_4(float2 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(v.y, v.y, v.y, v.x);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = (float32x4_t){ v.x, v.y, v.y, v.y };
		#else
		floats = float4(v, v.y, v.y);
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param[in] v target 4 component vector value pointer (unaligned)
	 */
	explicit simd_f32_4(const float* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_loadu_ps(v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_f32(v);
		#else
		floats = *v;
		#endif
	}
	
	/*******************************************************************************************************************
	 * @brief Loads SIMD 4 component 32bit floating point aligned vector values.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[in] v target 4 component vector value pointer (aligned)
	 */
	void loadAligned(const float* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_load_ps(v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_f32(v);
		#else
		floats = *((const float4*)v);
		#endif
	}

	/**
	 * @brief Stores SIMD 4 component 32bit floating point unaligned vector values.
	 * @param[out] v target 4 component vector value pointer (unaligned)
	 */
	void store(float* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_storeu_ps(v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_f32(v, data);
		#else
		*((float4*)v) = floats;
		#endif
	}
	/**
	 * @brief Stores SIMD 4 component 32bit floating point aligned vector values.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[out] v target 4 component vector value pointer (aligned)
	 */
	void storeAligned(float* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_store_ps(v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_f32(v, data);
		#else
		*((float4*)v) = floats;
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
		return floats.x;
		#endif
	}
	/**
	 * @brief Returns SIMD vector second component value.
	 */
	float getY() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 1);
		#else
		return floats.y;
		#endif
	}
	/**
	 * @brief Returns SIMD vector third component value.
	 */
	float getZ() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 2);
		#else
		return floats.z;
		#endif
	}
	/**
	 * @brief Returns SIMD vector fourth component value.
	 */
	float getW() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vgetq_lane_f32(data, 3);
		#else
		return floats.w;
		#endif
	}

	/**
	 * @brief Sets SIMD vector first component value.
	 * @param value target X vector component value
	 */
	void setX(float value) noexcept { floats.x = value; }
	/**
	 * @brief Sets SIMD vector second component value.
	 * @param value target Y vector component value
	 */
	void setY(float value) noexcept { floats.y = value; }
	/**
	 * @brief Sets SIMD vector third component value.
	 * @param value target Z vector component value
	 */
	void setZ(float value) noexcept { floats.z = value; }
	/**
	 * @brief Sets SIMD vector fourth component value.
	 * @param value target W vector component value
	 */
	void setW(float value) noexcept { floats.w = value; }

	/**
	 * @brief Swizzles SIMD vector components.
	 * 
	 * @tparam X first vector component swizzle index
	 * @tparam Y second vector component swizzle index
	 * @tparam Z third vector component swizzle index
	 * @tparam W fourth vector component swizzle index
	 */
	template<uint32 X, uint32 Y, uint32 Z, uint32 W = SwU>
	simd_f32_4 swizzle() const noexcept
	{
		static_assert(X <= 3, "X template parameter out of range");
		static_assert(Y <= 3, "Y template parameter out of range");
		static_assert(Z <= 3, "Z template parameter out of range");
		static_assert(W <= 3, "W template parameter out of range");

		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_shuffle_ps(data, data, _MM_SHUFFLE(W, Z, Y, X));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return __builtin_shufflevector(data, data, X, Y, Z, W);
		#else
		return simd_f32_4(floats[X], floats[Y], floats[Z], floats[W]);
		#endif
	}

	simd_f32_4 splatX() const noexcept { return swizzle<SwX, SwX, SwX, SwX>(); }
	simd_f32_4 splatY() const noexcept { return swizzle<SwY, SwY, SwY, SwY>(); }
	simd_f32_4 splatZ() const noexcept { return swizzle<SwZ, SwZ, SwZ, SwZ>(); }
	simd_f32_4 splatW() const noexcept { return swizzle<SwW, SwW, SwW, SwW>(); }

	/*******************************************************************************************************************
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept { return floats[i]; }
	/**
	 * @brief Returns SIMD vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept { return floats[i]; }

	/**
	 * @brief Returns as 4 component unsigned integer SIMD vector.
	 */
	explicit operator simd_u32_4() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cvttps_epi32(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcvtq_u32_f32(data);
		#else
		return simd_u32_4((uint4)floats);
		#endif
	}
	/**
	 * @brief Returns as 4 component signed integer SIMD vector.
	 */
	explicit operator simd_i32_4() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_cvttps_epi32(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcvtq_s32_f32(data);
		#else
		return simd_i32_4((uint4)floats);
		#endif
	}

	/**
	 * @brief Returns SIMD vector as 4 component floating point vector. (xyzw)
	 */
	explicit operator float4() const noexcept { return floats; }
	/**
	 * @brief Returns SIMD vector as 3 component floating point vector. (xyz)
	 */
	explicit operator float3() const noexcept { return (float3)floats; }
	/**
	 * @brief Returns SIMD vector as 2 component floating point vector. (xy)
	 */
	explicit operator float2() const noexcept { return (float2)floats; }
	/**
	 * @brief Returns SIMD first vector component value. (x)
	 */
	explicit operator float() const noexcept { return getX(); }

	//******************************************************************************************************************
	simd_f32_4 operator+(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_add_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vaddq_f32(data, v.data);
		#else
		return simd_f32_4(floats + v.floats);
		#endif
	}
	simd_f32_4 operator-(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vsubq_f32(data, v.data);
		#else
		return simd_f32_4(floats - v.floats);
		#endif
	}
	simd_f32_4 operator*(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_mul_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_f32(data, v.data);
		#else
		return simd_f32_4(floats * v.floats);
		#endif
	}
	simd_f32_4 operator/(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_div_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vdivq_f32(data, v.data);
		#else
		return simd_f32_4(floats / v.floats);
		#endif
	}
	simd_f32_4 operator-() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_ps(data, _mm_set1_ps(-0.0f));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vnegq_f32(data);
		#else
		return simd_f32_4(-floats);
		#endif
	}
	simd_f32_4 operator+(float n) const noexcept { return *this + simd_f32_4(n); }
	simd_f32_4 operator-(float n) const noexcept { return *this - simd_f32_4(n); }
	simd_f32_4 operator*(float n) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_n_f32(data, n);
		#else
		return *this * simd_f32_4(n);
		#endif
	}
	simd_f32_4 operator/(float n) const noexcept { return *this / simd_f32_4(n); }

	simd_f32_4& operator+=(simd_f32_4 v) noexcept { *this = *this + v; return *this; }
	simd_f32_4& operator-=(simd_f32_4 v) noexcept { *this = *this - v; return *this; }
	simd_f32_4& operator*=(simd_f32_4 v) noexcept { *this = *this * v; return *this; }
	simd_f32_4& operator/=(simd_f32_4 v) noexcept { *this = *this / v; return *this; }
	simd_f32_4& operator+=(float n) noexcept { *this = *this + n; return *this; }
	simd_f32_4& operator-=(float n) noexcept { *this = *this - n; return *this; }
	simd_f32_4& operator*=(float n) noexcept { *this = *this * n; return *this; }
	simd_f32_4& operator/=(float n) noexcept { *this = *this / n; return *this; }
	simd_f32_4& operator=(float n) noexcept { *this = simd_f32_4(n); return *this; }

	//******************************************************************************************************************
	bool operator==(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_ps(_mm_cmpeq_ps(data, v.data)) == 0b1111;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_f32(data, v.data)) == 0xFFFFFFFFu;
		#else
		return floats == v.floats;
		#endif
	}
	bool operator!=(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_movemask_ps(_mm_cmpeq_ps(data, v.data)) != 0b1111;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vminvq_u32(vceqq_f32(data, v.data)) == 0u;
		#else
		return floats != v.floats;
		#endif
	}
	simd_u32_4 operator<(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmplt_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcltq_f32(data, v.data);
		#else
		return simd_u32_4(floats < v.floats);
		#endif
	}
	simd_u32_4 operator>(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmpgt_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgtq_f32(data, v.data);
		#else
		return simd_u32_4(floats > v.floats);
		#endif
	}
	simd_u32_4 operator<=(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmple_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcleq_f32(data, v.data);
		#else
		return simd_u32_4(floats <= v.floats);
		#endif
	}
	simd_u32_4 operator>=(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmpge_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgeq_f32(data, v.data);
		#else
		return simd_u32_4(floats >= v.floats);
		#endif
	}

	bool operator==(float n) const noexcept { return *this == simd_f32_4(n); }
	bool operator!=(float n) const noexcept { return *this != simd_f32_4(n); }
	simd_u32_4 operator<(float n) const noexcept { return *this < simd_f32_4(n); }
	simd_u32_4 operator>(float n) const noexcept { return *this > simd_f32_4(n); }
	simd_u32_4 operator<=(float n) const noexcept { return *this <= simd_f32_4(n); }
	simd_u32_4 operator>=(float n) const noexcept { return *this >= simd_f32_4(n); }

	static const simd_f32_4 zero, one, minusOne, min, minusMin, max, minusMax, epsilon, inf, minusInf, nan;
};

//**********************************************************************************************************************
inline const simd_f32_4 simd_f32_4::zero = simd_f32_4(0.0f);
inline const simd_f32_4 simd_f32_4::one = simd_f32_4(1.0f);
inline const simd_f32_4 simd_f32_4::minusOne = simd_f32_4(-1.0f);
inline const simd_f32_4 simd_f32_4::min = simd_f32_4(FLT_MIN);
inline const simd_f32_4 simd_f32_4::minusMin = simd_f32_4(-FLT_MIN);
inline const simd_f32_4 simd_f32_4::max = simd_f32_4(FLT_MAX);
inline const simd_f32_4 simd_f32_4::minusMax = simd_f32_4(-FLT_MAX);
inline const simd_f32_4 simd_f32_4::epsilon = simd_f32_4(FLT_EPSILON);
inline const simd_f32_4 simd_f32_4::inf = simd_f32_4(INFINITY);
inline const simd_f32_4 simd_f32_4::minusInf = simd_f32_4(-INFINITY);
inline const simd_f32_4 simd_f32_4::nan = simd_f32_4(NAN);

static simd_f32_4 operator+(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) + v; }
static simd_f32_4 operator-(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) - v; }
static simd_f32_4 operator*(float n, simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_NEON)
	return vmulq_n_f32(v.data, n);
	#else
	return simd_f32_4(n) * v;
	#endif
}
static simd_f32_4 operator/(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) / v; }
static bool operator==(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) == v; }
static bool operator!=(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) != v; }
static simd_u32_4 operator<(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) < v; }
static simd_u32_4 operator>(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) > v; }
static simd_u32_4 operator<=(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) <= v; }
static simd_u32_4 operator>=(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) >= v; }

/**
 * @brief Casts from the 4 component unsigned integer to floating point SIMD vector. (Doesn't change the bits)
 */
static simd_f32_4 uintAsFloat(simd_u32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_castsi128_ps(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vreinterpretq_f32_u32(v.data);
	#else
	return *((const simd_f32_4*)&v);
	#endif
}
/**
 * @brief Casts from the 4 component signed integer to floating point SIMD vector. (Doesn't change the bits)
 */
static simd_f32_4 intAsFloat(simd_i32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_castsi128_ps(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vreinterpretq_f32_s32(v.data);
	#else
	return *((const simd_f32_4*)&v);
	#endif
}

/**
 * @brief Casts as 4 component floating point to unsigned integer SIMD vector. (Doesn't change the bits)
 */
static simd_u32_4 floatAsUint(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_castps_si128(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vreinterpretq_u32_f32(v.data);
	#else
	return *((const simd_u32_4*)&v);
	#endif
}
/**
 * @brief Casts as 4 component floating point to signed integer SIMD vector. (Doesn't change the bits)
 */
static simd_i32_4 floatAsInt(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_castps_si128(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vreinterpretq_s32_f32(v.data);
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
static simd_u32_4 equal(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_castps_si128(_mm_cmpeq_ps(a.data, b.data));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vceqq_f32(a.data, b.data);
	#else
	return simd_u32_4(equal(a.floats, b.floats));
	#endif
}
/**
 * @brief Compares two SIMD vectors component wise if they are not equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static simd_u32_4 notEqual(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_castps_si128(_mm_cmpneq_ps(a.data, b.data));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmvnq_u32(vceqq_f32(a.data, b.data));
	#else
	return simd_u32_4(notEqual(a.floats, b.floats));
	#endif
}

/**
 * @brief Returns true if first SIMD vector binary representation is less than the second.
 *
 * @param a first SIMD vector to binary compare
 * @param b second SIMD vector to binary compare
 */
static bool isBinaryLess(simd_f32_4 a, simd_f32_4 b) noexcept { return memcmp(&a, &b, sizeof(simd_f32_4)) < 0; }

/**
 * @brief Selects between two SIMD vector components based on the control vector values.
 * 
 * @param c control SIMD vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static simd_f32_4 select(simd_u32_4 c, simd_f32_4 t, simd_f32_4 f) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_blendv_ps(f.data, t.data, _mm_castsi128_ps(c.data));
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	auto isTrue = _mm_castsi128_ps(_mm_srai_epi32(c.data, 31));
	return _mm_or_ps(_mm_and_ps(isTrue, t.data), _mm_andnot_ps(isTrue, f.data));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vbslq_f32(vreinterpretq_u32_s32(vshrq_n_s32(vreinterpretq_s32_u32(c.data), 31)), t.data, f.data);
	#else
	return simd_f32_4(select(c.floats, t.floats, f.floats));
	#endif
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of the SIMD vector.
 * 
 * @param a first SIMD vector to find minimum
 * @param b second SIMD vector to find minimum
 */
static simd_f32_4 min(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_min_ps(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vminq_f32(a.data, b.data);
	#else
	return simd_f32_4(min(a.floats, b.floats));
	#endif
}
/**
 * @brief Returns maximum value for each component of the SIMD vector.
 * 
 * @param a first SIMD vector to find maximum
 * @param b second SIMD vector to find maximum
 */
static simd_f32_4 max(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_max_ps(a.data, b.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmaxq_f32(a.data, b.data);
	#else
	return simd_f32_4(max(a.floats, b.floats));
	#endif
}

/**
 * @brief Returns minimum value of 4D SIMD vector components.
 * @param v target SIMD vector
 */
static float min4(simd_f32_4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of 4D SIMD vector components.
 * @param v target SIMD vector
 */
static float max4(simd_f32_4 v) noexcept
{
	auto m = max(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = max(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}

/**
 * @brief Returns minimum value of 3D SIMD vector components.
 * @param v target SIMD vector
 */
static float min3(simd_f32_4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwZ, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of 3D SIMD vector components.
 * @param v target SIMD vector
 */
static float max3(simd_f32_4 v) noexcept
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
static simd_f32_4 clamp(simd_f32_4 v, simd_f32_4 min, simd_f32_4 max) noexcept
{
	return math::max(math::min(v, max), min);
}

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first SIMD vector multiplier
 * @param mul2 second SIMD vector multiplier
 * @param add SIMD vector addend
 */
static simd_f32_4 fma(simd_f32_4 mul1, simd_f32_4 mul2, simd_f32_4 add) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_AVX2) || defined(MATH_SIMD_SUPPORT_NEON)
	return MATH_SIMD_FMA(mul1.data, mul2.data, add.data);
	#else
	return simd_f32_4(fma(mul1.floats, mul2.floats, add.floats));
	#endif
}
/**
 * @brief Returns absolute value for each component of the SIMD vector.
 * @param v target SIMD vector
 */
static simd_f32_4 abs(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	if constexpr (std::numeric_limits<float>::is_iec559)
		return _mm_and_ps(v.data, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
	else
		return _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), v.data), v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vabsq_f32(v.data);
	#else
	return simd_f32_4(abs(v.floats));
	#endif
}
/**
 * @brief Returns square root for each component of the SIMD vector.
 * @param v target SIMD vector
 */
static simd_f32_4 sqrt(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_sqrt_ps(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vsqrtq_f32(v.data);
	#else
	return simd_f32_4(sqrt(v.floats));
	#endif
}

/**
 * @brief Returns sign for each component of the SIMD vector.
 * @param v target SIMD vector
 */
static simd_f32_4 sign(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_or_ps(_mm_and_ps(v.data, _mm_set1_ps(-1.0f)), _mm_set1_ps(1.0f));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vreinterpretq_f32_u32(vorrq_u32(vandq_u32(vreinterpretq_u32_f32(v.data), 
		vreinterpretq_u32_f32(vdupq_n_f32(-1.0f))), vreinterpretq_u32_f32(vdupq_n_f32(1.0f))));
	#else
	return simd_f32_4(sign(v.floats));
	#endif
}
/**
 * @brief Returns sign bits of the SIMD vector. (4 bits)
 * @param v target SIMD vector
 */
static int signBits(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_movemask_ps(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto shift = (int32x4_t){ 0, 1, 2, 3 };
	return vaddvq_u32(vshlq_u32(vshrq_n_u32(vreinterpretq_u32_f32(v.data), 31), shift));
	#else
	return signBits(v.floats);
	#endif
}

/**
 * @brief Rounds each component of the SIMD vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target SIMD vector
 */
static simd_f32_4 round(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_round_ps(v.data, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vrndnq_f32(v.data);
	#else
	return simd_f32_4(round(v.floats));
	#endif
}
/**
 * @brief Rounds each component of the SIMD vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target SIMD vector
 */
static simd_f32_4 floor(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_round_ps(v.data, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vrndmq_f32(v.data);
	#else
	return simd_f32_4(floor(v.floats));
	#endif
}
/**
 * @brief Rounds each component of the SIMD vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target SIMD vector
 */
static simd_f32_4 ceil(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_round_ps(v.data, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vrndpq_f32(v.data);
	#else
	return simd_f32_4(ceil(v.floats));
	#endif
}
/**
 * @brief Rounds each component of the SIMD vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target SIMD vector
 */
static simd_f32_4 trunc(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_round_ps(v.data, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vrndq_f32(v.data);
	#else
	return simd_f32_4(trunc(v.floats));
	#endif
}

/***********************************************************************************************************************
 * @brief Returns dot product between two 4D SIMD vector.
 * 
 * @param a first SIMD vector to dot
 * @param b second SIMD vector to dot
 */
static simd_f32_4 dotV4(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_dp_ps(a.data, b.data, 0xff);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vdupq_n_f32(vaddvq_f32(vmulq_f32(a.data, b.data)));
	#else
	return simd_f32_4(dot(a.floats, b.floats));
	#endif
}
/**
 * @brief Returns dot product between two 4D SIMD vector.
 * 
 * @param a first SIMD vector to dot
 * @param b second SIMD vector to dot
 */
static float dot4(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_cvtss_f32(_mm_dp_ps(a.data, b.data, 0xff));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vaddvq_f32(vmulq_f32(a.data, b.data));
	#else
	return dot(a.floats, b.floats);
	#endif
}

/**
 * @brief Returns dot product between two 3D SIMD vector.
 * 
 * @param a first SIMD vector to dot
 * @param b second SIMD vector to dot
 */
static simd_f32_4 dotV3(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_dp_ps(a.data, b.data, 0x7f);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vdupq_n_f32(vaddvq_f32(vsetq_lane_f32(0, vmulq_f32(a.data, b.data), 3)));
	#else
	return simd_f32_4(dot((float3)a.floats, (float3)b.floats));
	#endif
}
/**
 * @brief Returns dot product between two 3D SIMD vector.
 * 
 * @param a first SIMD vector to dot
 * @param b second SIMD vector to dot
 */
static float dot3(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_cvtss_f32(_mm_dp_ps(a.data, b.data, 0x7f));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vaddvq_f32(vsetq_lane_f32(0, vmulq_f32(a.data, b.data), 3));
	#else
	return dot((float3)a.floats, (float3)b.floats);
	#endif
}

/**
 * @brief Returns cross product between two 3D SIMD vector.
 * 
 * @param a first SIMD vector to cross
 * @param b second SIMD vector to cross
 */
static simd_f32_4 cross3(simd_f32_4 a, simd_f32_4 b) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	auto r = _mm_sub_ps(
		_mm_mul_ps(_mm_shuffle_ps(b.data, b.data, _MM_SHUFFLE(0, 0, 2, 1)), a.data), 
		_mm_mul_ps(_mm_shuffle_ps(a.data, a.data, _MM_SHUFFLE(0, 0, 2, 1)), b.data));
	return _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 0, 2, 1));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto r = vsubq_f32(
		vmulq_f32(__builtin_shufflevector(b.data, b.data, 1, 2, 0, 0), a.data), 
		vmulq_f32(__builtin_shufflevector(a.data, a.data, 1, 2, 0, 0), b.data));
	return __builtin_shufflevector(r, r, 1, 2, 0, 0);
	#else
	auto r = cross((float3)a.floats, (float3)b.floats);
	return simd_f32_4(r.x, r.y, r.z); // TODO: not sure if this is the same result as SIMD, check this.
	#endif
}

/***********************************************************************************************************************
 * @brief Returns squared length of the 4D SIMD vector. (length ^ 2)
 * @param v target SIMD vector
 */
static float lengthSq4(simd_f32_4 v) noexcept { return dot4(v, v); }
/**
 * @brief Returns length of the 4D SIMD vector.
 * @param v target SIMD vector
 */
static float length4(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v.data, v.data, 0xff)));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vget_lane_f32(vsqrt_f32(vdup_n_f32(vaddvq_f32(vmulq_f32(v.data, v.data)))), 0);
	#else
	return length(v.floats);
	#endif
}

/**
 * @brief Returns squared length of the 3D SIMD vector. (length ^ 2)
 * @param v target SIMD vector
 */
static float lengthSq3(simd_f32_4 v) noexcept { return dot3(v, v); }
/**
 * @brief Returns length of the 3D SIMD vector.
 * @param v target SIMD vector
 */
static float length3(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v.data, v.data, 0x7f)));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vget_lane_f32(vsqrt_f32(vdup_n_f32(vaddvq_f32(vsetq_lane_f32(0, vmulq_f32(v.data, v.data), 3)))), 0);
	#else
	return length((float3)v.floats);
	#endif
}

/***********************************************************************************************************************
 * @brief Returns squared distance between two 4D SIMD points. (distance ^ 2)
 * 
 * @param a first SIMD point
 * @param b second SIMD point
 */
static float distanceSq4(simd_f32_4 a, simd_f32_4 b) noexcept { return lengthSq4(a - b); }
/**
 * @brief Returns distance between two 4D SIMD points.
 * 
 * @param a first SIMD point
 * @param b second SIMD point
 */
static float distance4(simd_f32_4 a, simd_f32_4 b) noexcept { return length4(a - b); }

/**
 * @brief Returns squared distance between two 3D SIMD points. (distance ^ 2)
 * 
 * @param a first SIMD point
 * @param b second SIMD point
 */
static float distanceSq3(simd_f32_4 a, simd_f32_4 b) noexcept { return lengthSq3(a - b); }
/**
 * @brief Returns distance between two 3D SIMD points.
 * 
 * @param a first SIMD point
 * @param b second SIMD point
 */
static float distance3(simd_f32_4 a, simd_f32_4 b) noexcept { return length3(a - b); }

/**
 * @brief Returns normalized 4D SIMD vector. (With length of 1.0f)
 * @param v target SIMD vector to normalize
 */
static simd_f32_4 normalize4(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_div_ps(v.data, _mm_sqrt_ps(_mm_dp_ps(v.data, v.data, 0xff)));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vdivq_f32(v.data, vsqrtq_f32(vdupq_n_f32(vaddvq_f32(vmulq_f32(v.data, v.data)))));
	#else
	return v / simd_f32_4(length4(v));
	#endif
}
/**
 * @brief Returns normalized 3D SIMD vector. (With length of 1.0f)
 * @param v target SIMD vector to normalize
 */
static simd_f32_4 normalize3(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_div_ps(v.data, _mm_sqrt_ps(_mm_dp_ps(v.data, v.data, 0x7f)));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vdivq_f32(v.data, vsqrtq_f32(vdupq_n_f32(
		vaddvq_f32(vsetq_lane_f32(0, vmulq_f32(v.data, v.data), 3)))));
	#else
	auto r = normalize((float3)v.floats);
	return simd_f32_4(r.x, r.y, r.z);
	#endif
}

/**
 * @brief Returns true if SIMD vector is normalized with specified tolerance.
 * 
 * @param v target SIMD vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized4(simd_f32_4 v, float tolerance = 1.0e-6f) noexcept
{
	return std::abs(lengthSq4(v) - 1.0f) <= tolerance;
}
/**
 * @brief Returns true if SIMD vector is normalized with specified tolerance.
 * 
 * @param v target SIMD vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized3(simd_f32_4 v, float tolerance = 1.0e-6f) noexcept
{
	return std::abs(lengthSq3(v) - 1.0f) <= tolerance;
}

/***********************************************************************************************************************
 * @brief Returns float remainder of numer/denom for each element of the SIMD vector.
 * 
 * @param n quatient numerator SIMD vector
 * @param d quatient denominator SIMD vector
 */
static simd_f32_4 mod(simd_f32_4 n, simd_f32_4 d) noexcept
{
    return n - floor(n / d) * d;
}

/**
 * @brief Returns natural logarithm for each element of the SIMD vector. [r = inv(e^x)]
 * @param v target SIMD vector
 */
static simd_f32_4 log(simd_f32_4 v) noexcept
{
	if constexpr (std::numeric_limits<float>::is_iec559)
	{
		// Based on sleefsimdsp.c from the Sleef library.
		auto o = v < simd_f32_4::min;
		v = select(o, v * ((float)((int64)1 << 32) * (float)((int64)1 << 32)), v);

		auto e = ((floatAsUint(v * (1.0f / 0.75f)) >> 23u) & 0xFFu) - 0x7Fu;
		auto m = intAsFloat(floatAsInt(v) + ((-uintAsInt(e)) << 23));
		e = select(o, e - 64, e);

		auto x = (m - simd_f32_4::one) / (m + simd_f32_4::one);
		auto x2 = x * x;

		auto t = simd_f32_4(0.2392828464508056640625f);
		t = fma(t, x2, simd_f32_4(0.28518211841583251953125f));
		t = fma(t, x2, simd_f32_4(0.400005877017974853515625f));
		t = fma(t, x2, simd_f32_4(0.28518211841583251953125f));
		t = fma(t, x2, simd_f32_4(0.666666686534881591796875f));
		t = fma(t, x2, simd_f32_4(2.0f));

		x = fma(x, t, simd_f32_4(0.693147180559945286226764f) * (simd_f32_4)e);
		x = select(equal(v, simd_f32_4::inf) | equal(v, simd_f32_4::minusInf), simd_f32_4::minusInf, x);
		x = select((v < simd_f32_4::zero) | equal(v, simd_f32_4::nan), simd_f32_4::nan, x);
		x = select(equal(v, simd_f32_4::zero), simd_f32_4::minusInf, x);
		return x;
	}
	else
	{
		return simd_f32_4(std::log(v.getX()), std::log(v.getY()), 
			std::log(v.getZ()), std::log(v.getW()));
	}
}
/**
 * @brief Returns base-e exponential function for each element of the SIMD vector. [r = e^x]
 * @param v target SIMD vector
 */
static simd_f32_4 exp(simd_f32_4 v) noexcept
{
	if constexpr (std::numeric_limits<float>::is_iec559)
	{
		// Based on sleefsimdsp.c from the Sleef library.
		auto s = v * M_LOG2E;
		auto q = (simd_i32_4)select(s < 0.0f, s - 0.5f, s + 0.5f);
		auto qFloat = (simd_f32_4)q;
		s = fma(qFloat, simd_f32_4(-0.693145751953125f), v);
		s = fma(qFloat, simd_f32_4(-1.428606765330187045e-06f), s);

		auto u = simd_f32_4(0.000198527617612853646278381f);
		u = fma(u, s, simd_f32_4(0.00139304355252534151077271f));
		u = fma(u, s, simd_f32_4(0.00833336077630519866943359f));
		u = fma(u, s, simd_f32_4(0.0416664853692054748535156f));
		u = fma(u, s, simd_f32_4(0.166666671633720397949219f));
		u = fma(u, s, simd_f32_4(0.5f));
  
		u = fma(s * s, u, s) + simd_f32_4::one;
		u = u * intAsFloat(((q >> 1) + 0x7f) << 23) * 
			intAsFloat(((q - (q >> 1)) + 0x7f) << 23);

		u = uintAsFloat(floatAsUint(u) & (v >= -104.0f));
		u = select(v > 104.0f, simd_f32_4::inf, u);
		return u;
	}
	else
	{
		return simd_f32_4(std::exp(v.getX()), std::exp(v.getY()), 
			std::exp(v.getZ()), std::exp(v.getW()));
	}
}

/***********************************************************************************************************************
 * @brief Returns base b raised to the power e for each element of the SIMD vector.
 * 
 * @param b SIMD vector with base values
 * @param e SIMD vector with exponent values
 */
static simd_f32_4 pow(simd_f32_4 b, simd_f32_4 e) noexcept
{
	// TODO: use SIMD implementation from the sleefsimdsp.c
	return simd_f32_4(std::pow(b.getX(), e.getX()), std::pow(b.getY(), e.getY()),
		std::pow(b.getZ(), e.getZ()), std::pow(b.getW(), e.getW()));
}
/**
 * @brief Returns base b raised to the power e for each element of the SIMD vector. (Fast approximation)
 * @warning It has lower precision compared to the pow() function!
 * 
 * @param b SIMD vector with base values
 * @param e SIMD vector with exponent values
 */
static simd_f32_4 fastPow(simd_f32_4 b, simd_f32_4 e) noexcept
{
	if constexpr (std::numeric_limits<float>::is_iec559)
	{
		// Based on sleefsimdsp.c from the Sleef library.
		auto r = exp(log(abs(b)) * e);
		auto eInt = (simd_i32_4)e; auto eAbs = abs(e);
		auto eIsInt = equal(e, (simd_f32_4)eInt) | (eAbs >= ((int64)1 << 24));
		auto eIsOdd = notEqual(eInt & 1, simd_i32_4::zero) & eIsInt & (eAbs < ((int64)1 << 24));
		r *= select((b < simd_f32_4::zero) & eIsOdd, simd_f32_4::minusOne, simd_f32_4::one);
		r = uintAsFloat(bic(floatAsUint(r), equal(b, simd_f32_4::zero)));
		r = select(equal(e, simd_f32_4::zero), simd_f32_4::one, r);
		return r;
	}
	else
	{
		return pow(b, e);
	}
}

/***********************************************************************************************************************
 * @brief Calculates sine and cosine for each element of the SIMD vector.
 * 
 * @param v target SIMD vector to get sin and cos from
 * @param[out] sin SIMD vector with sine values
 * @param[out] cos SIMD vector with cosine values
 */
static void sinCos(simd_f32_4 v, simd_f32_4& sin, simd_f32_4& cos) noexcept
{
	if constexpr (std::numeric_limits<float>::is_iec559)
	{
		// Based on sinf.c from the cephes library
		auto sinSign = floatAsUint(v) & 0x80000000u;
		auto x = uintAsFloat(floatAsUint(v) ^ sinSign);
		auto quadrant = (simd_u32_4)fma(simd_f32_4(M_2_PI), x, simd_f32_4(0.5f));
		auto floatQuadrant = (simd_f32_4)quadrant;
		x = ((x - floatQuadrant * 1.5703125f) - floatQuadrant * 
			0.0004837512969970703125f) - floatQuadrant * 7.549789948768648e-8f;
	
		auto x2 = x * x;
		auto taylorCos = fma((2.443315711809948e-5f * x2 - 1.388731625493765e-3f), x2, 
			simd_f32_4(4.166664568298827e-2f)) * x2 * x2 - 0.5f * x2 + simd_f32_4::one;
		auto taylorSin = (fma(simd_f32_4(-1.9515295891e-4f), x2, 
			simd_f32_4(8.3321608736e-3f)) * x2 - 1.6666654611e-1f) * x2 * x + x;

		auto bit1 = quadrant << 31u, bit2 = (quadrant << 30u) & 0x80000000u;
		auto s = select(bit1, taylorCos, taylorSin);
		auto c = select(bit1, taylorSin, taylorCos);

		sinSign ^= bit2;
		auto cosSign = bit1 ^ bit2;
		sin = uintAsFloat(floatAsUint(s) ^ sinSign);
		cos = uintAsFloat(floatAsUint(c) ^ cosSign);
	}
	else
	{
		sin = simd_f32_4(std::sin(v.getX()), std::sin(v.getY()), 
			std::sin(v.getZ()), std::sin(v.getW()));
		cos = simd_f32_4(std::cos(v.getX()), std::cos(v.getY()), 
			std::cos(v.getZ()), std::cos(v.getW()));
	}
}

/***********************************************************************************************************************
 * @brief Remaps each component of SIMD vector to the 0.0 - 1.0 range.
 * @param v target SIMD vector
 */
static simd_f32_4 repeat(simd_f32_4 v) noexcept
{
	auto r = select(v < 0.0f, 1.0f - mod(-v, simd_f32_4::one), v);
	return select(v < 1.0f, r, mod(v, simd_f32_4::one));
}

/**
 * @brief Linearly interpolates each component of the SIMD vector between a and b using t.
 * 
 * @param a minimum SIMD vector (t == 0.0)
 * @param b maximum SIMD vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static simd_f32_4 lerp(simd_f32_4 a, simd_f32_4 b, float t) noexcept { return a * (1.0f - t) + b * t; }
/**
 * @brief Linearly interpolates each component of the SIMD vector between a and b using t, taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum SIMD vector (t == 0.0)
 * @param b maximum SIMD vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 * @param dt current delta time
 */
static simd_f32_4 lerpDelta(simd_f32_4 a, simd_f32_4 b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}

} // namespace math