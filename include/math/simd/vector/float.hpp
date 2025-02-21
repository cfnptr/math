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

namespace math
{

/**
 * @brief SIMD 4 component 32bit floating point vector structure.
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_f32_4
{
	union
	{
		_simd_f128 data; /** Packed SIMD 4 component 32bit floating point vector data. */
		float values[4];
	};

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
		data[0] = 0.0f; data[1] = 0.0f; data[2] = 0.0f; data[3] = 0.0f;
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
	simd_f32_4(float x, float y, float z, float w) noexcept
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
	 *
	 * @param xyz first, second and third vector component values
	 * @param w fourth vector component value
	 */
	simd_f32_4(simd_f32_4 xyz, float w) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_set_ps(w, xyz.values[2], xyz.values[1], xyz.values[0]);
		#elif defined(MATH_SIMD_SUPPORT_SSE4_1)
		data = _mm_blend_ps(xyz.data, _mm_set1_ps(w), 8);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vsetq_lane_f32(w, xyz.data, 3);
		#else
		values[0] = xyz.values[0]; values[1] = xyz.values[1]; 
		values[2] = xyz.values[2]; values[3] = w;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param data target vector floating point SIMD data
	 */
	simd_f32_4(_simd_f128 data) : data(data) { }
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param data target vector unsigned integer SIMD data
	 */
	explicit simd_f32_4(simd_u32_4 v)
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		this->data = _mm_cvtepi32_ps(v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		this->data = vcvtq_f32_u32(v.data);
		#else
		values[0] = (float)v.values[0]; values[1] = (float)v.values[1];
		values[2] = (float)v.values[2]; values[3] = (float)v.values[3];
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param data target vector signed integer SIMD data
	 */
	explicit simd_f32_4(simd_i32_4 v)
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		this->data = _mm_cvtepi32_ps(v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		this->data = vcvtq_f32_s32(v.data);
		#else
		values[0] = (float)v.values[0]; values[1] = (float)v.values[1];
		values[2] = (float)v.values[2]; values[3] = (float)v.values[3];
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
		data = { v.x, v.y, v.z, v.w };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.z; data[3] = v.w;
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
		data = { v.x, v.y, v.z, v.z };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.z; data[3] = v.z;
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
		data = { v.x, v.y, v.y, v.y };
		#else
		data[0] = v.x; data[1] = v.y; data[2] = v.y; data[3] = v.y;
		#endif
	}
	/**
	 * @brief Creates a new SIMD 4 component 32bit floating point vector structure.
	 * @param[in] v target 4 component vector value pointer (unaligned)
	 */
	explicit simd_f32_4(const float4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_loadu_ps((const float*)v);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vld1q_f32((const float*)v);
		#else
		data[0] = v->x; data[1] = v->y; data[2] = v->z; data[3] = v->w;
		#endif
	}

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
		return simd_u32_4((uint32)values[0], (uint32)values[1], (uint32)values[2], (uint32)values[3]);
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
		return simd_i32_4((int32)values[0], (int32)values[1], (int32)values[2], (int32)values[3]);
		#endif
	}

	/*******************************************************************************************************************
	 * @brief Casts as 4 component unsigned integer SIMD vector. (Doesn't change the bits)
	 */
	simd_u32_4 castToUint() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vreinterpretq_u32_f32(data);
		#else
		return *((const simd_u32_4*)this);
		#endif
	}
	/**
	 * @brief Casts as 4 component signed integer SIMD vector. (Doesn't change the bits)
	 */
	simd_i32_4 castToInt() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vreinterpretq_us32_f32(data);
		#else
		return *((const simd_i32_4*)this);
		#endif
	}

	/**
	 * @brief Casts from the 4 component unsigned integer SIMD vector. (Doesn't change the bits)
	 */
	void castFrom(simd_u32_4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_castsi128_ps(v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vreinterpretq_f32_u32(v.data);
		#else
		*this = *((const simd_f32_4*)&v);
		#endif
	}
	/**
	 * @brief Casts from the 4 component signed integer SIMD vector. (Doesn't change the bits)
	 */
	void castFrom(simd_i32_4 v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		data = _mm_castsi128_ps(v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		data = vreinterpretq_f32_s32(v.data);
		#else
		*this = *((const simd_f32_4*)&v);
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
	void store(float* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_storeu_ps(v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_f32(v, data);
		#else
		v[0] = values[0]; v[1] = values[1]; v[2] = values[2]; v[3] = values[3];
		#endif
	}
	/**
	 * @brief Stores SIMD 4 component 32bit floating point aligned vector value.
	 * @warning Specified vector pointer must be aligned in the memory!!!
	 * @param[out] v target 4 component vector value pointer (aligned)
	 */
	void storeAligned(float4* v) noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		_mm_store_ps((float*)v, data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		vst1q_f32((float*)v, data);
		#else
		v->x = values[0]; v->y = values[1]; v->z = values[2]; v->w = values[3];
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
		#if defined(MATH_SIMD_SUPPORT_NEON)
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
		#if defined(MATH_SIMD_SUPPORT_NEON)
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
		#if defined(MATH_SIMD_SUPPORT_NEON)
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
		return simd_f32_4(values[X], values[Y], values[Z], values[W]);
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
	simd_f32_4 operator+(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_add_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vaddq_f32(data, v.data);
		#else
		return simd_f32_4(values[0] + v.values[0], values[1] + v.values[1],
			values[2] + v.values[2], values[3] + v.values[3]);
		#endif
	}
	simd_f32_4 operator-(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_sub_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vsubq_f32(data, v.data);
		#else
		return simd_f32_4(values[0] - v.values[0], values[1] - v.values[1],
			values[2] - v.values[2], values[3] - v.values[3]);
		#endif
	}
	simd_f32_4 operator*(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_mul_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vmulq_f32(data, v.data);
		#else
		return simd_f32_4(values[0] * v.values[0], values[1] * v.values[1],
			values[2] * v.values[2], values[3] * v.values[3]);
		#endif
	}
	simd_f32_4 operator/(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_div_ps(data, v.data);
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vdivq_f32(data, v.data);
		#else
		return simd_f32_4(values[0] / v.values[0], values[1] / v.values[1],
			values[2] / v.values[2], values[3] / v.values[3]);
		#endif
	}
	simd_f32_4 operator-() const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_xor_ps(data, _mm_set1_ps(-0.0f));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vnegq_f32(data);
		#else
		return simd_f32_4(-values[0], -values[1], -values[2], -values[3]);
		#endif
	}

	simd_f32_4& operator+=(simd_f32_4 v) noexcept { *this = *this + v; return *this; }
	simd_f32_4& operator-=(simd_f32_4 v) noexcept { *this = *this - v; return *this; }
	simd_f32_4& operator*=(simd_f32_4 v) noexcept { *this = *this * v; return *this; }
	simd_f32_4& operator/=(simd_f32_4 v) noexcept { *this = *this / v; return *this; }
	simd_f32_4& operator+=(float n) noexcept { *this = *this + simd_f32_4(n); return *this; }
	simd_f32_4& operator-=(float n) noexcept { *this = *this - simd_f32_4(n); return *this; }
	simd_f32_4& operator*=(float n) noexcept { *this = *this * simd_f32_4(n); return *this; }
	simd_f32_4& operator/=(float n) noexcept { *this = *this / simd_f32_4(n); return *this; }
	simd_f32_4& operator=(float n) noexcept { *this = simd_f32_4(n); return *this; }

	//******************************************************************************************************************
	bool operator==(simd_f32_4 v) const noexcept
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
	bool operator!=(simd_f32_4 v) const noexcept
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
	simd_u32_4 operator<(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmplt_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcltq_f32(data, v.data);
		#else
		return simd_u32_4(values[0] < v.values[0] ? 0xFFFFFFFFu : 0, values[1] < v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] < v.values[2] ? 0xFFFFFFFFu : 0, values[3] < v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32_4 operator>(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmpgt_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgtq_f32(data, v.data);
		#else
		return simd_u32_4(values[0] > v.values[0] ? 0xFFFFFFFFu : 0, values[1] > v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] > v.values[2] ? 0xFFFFFFFFu : 0, values[3] > v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32_4 operator<=(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmple_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcleq_f32(data, v.data);
		#else
		return simd_u32_4(values[0] <= v.values[0] ? 0xFFFFFFFFu : 0, values[1] <= v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] <= v.values[2] ? 0xFFFFFFFFu : 0, values[3] <= v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}
	simd_u32_4 operator>=(simd_f32_4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE)
		return _mm_castps_si128(_mm_cmpge_ps(data, v.data));
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		return vcgeq_f32(data, v.data);
		#else
		return simd_u32_4(values[0] >= v.values[0] ? 0xFFFFFFFFu : 0, values[1] >= v.values[1] ? 0xFFFFFFFFu : 0,
			values[2] >= v.values[2] ? 0xFFFFFFFFu : 0, values[3] >= v.values[3] ? 0xFFFFFFFFu : 0);
		#endif
	}

	static const simd_f32_4 zero, one, minusOne, inf, minusInf, nan;
};

inline const simd_f32_4 simd_f32_4::zero = simd_f32_4(0.0f);
inline const simd_f32_4 simd_f32_4::one = simd_f32_4(1.0f);
inline const simd_f32_4 simd_f32_4::minusOne = simd_f32_4(-1.0f);
inline const simd_f32_4 simd_f32_4::inf = simd_f32_4(INFINITY);
inline const simd_f32_4 simd_f32_4::minusInf = simd_f32_4(-INFINITY);
inline const simd_f32_4 simd_f32_4::nan = simd_f32_4(NAN);

static simd_f32_4 operator+(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) + v; }
static simd_f32_4 operator-(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) - v; }
static simd_f32_4 operator*(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) * v; }
static simd_f32_4 operator/(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) / v; }
static bool operator==(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) == v; }
static bool operator!=(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) != v; }
static simd_u32_4 operator<(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) < v; }
static simd_u32_4 operator>(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) > v; }
static simd_u32_4 operator<=(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) <= v; }
static simd_u32_4 operator>=(float n, simd_f32_4 v) noexcept { return simd_f32_4(n) >= v; }

/***********************************************************************************************************************
 * @brief Compares two SIMD vectors component wise if they are equal.
 *
 * @param a first SIMD vector to compare
 * @param b second SIMD vector to compare
 */
static simd_u32_4 compare(simd_f32_4 a, simd_f32_4 b)
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return simd_f32_4(_mm_cmpeq_ps(a.data, b.data)).castToUint();
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vceqq_f32(a.data, b.data);
	#else
	return simd_u32_4(a.values[0] == b.values[0] ? 0xFFFFFFFFu : 0, a.values[1] == b.values[1] ? 0xFFFFFFFFu : 0,
		a.values[2] == b.values[2] ? 0xFFFFFFFFu : 0, a.values[3] == b.values[3] ? 0xFFFFFFFFu : 0);
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
static simd_f32_4 select(simd_u32_4 c, simd_f32_4 t, simd_f32_4 f)
{
	#if defined(MATH_SIMD_SUPPORT_SSE4_1)
	return _mm_blendv_ps(f.data, t.data, _mm_castsi128_ps(c.data));
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	auto isTrue = _mm_castsi128_ps(_mm_srai_epi32(c.data, 31));
	return _mm_or_ps(_mm_and_ps(isTrue, t.data), _mm_andnot_ps(isTrue, f.data));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vbslq_f32(vreinterpretq_u32_s32(vshrq_n_s32(vreinterpretq_s32_u32(c.data), 31)), t.data, f.data);
	#else
	return simd_u32_4(
		c.values[0] & 0x80000000u ? t.values[0] : f.values[0], 
		c.values[1] & 0x80000000u ? t.values[1] : f.values[1],
		c.values[2] & 0x80000000u ? t.values[2] : f.values[2],
		c.values[3] & 0x80000000u ? t.values[3] : f.values[3]);
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
	return simd_f32_4(std::min(a.values[0], b.values[0]), std::min(a.values[1], b.values[1]),
		std::min(a.values[2], b.values[2]), std::min(a.values[3], b.values[3]));
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
	return simd_f32_4(std::max(a.values[0], b.values[0]), std::max(a.values[1], b.values[1]),
		max::max(a.values[2], b.values[2]), std::max(a.values[3], b.values[3]));
	#endif
}

/**
 * @brief Returns minimum value of all SIMD vector components.
 * @param v target SIMD vector
 */
static float min(simd_f32_4 v) noexcept
{
	auto m = min(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = min(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}
/**
 * @brief Returns maximum value of all SIMD vector components.
 * @param v target SIMD vector
 */
static float max(simd_f32_4 v) noexcept
{
	auto m = max(v, v.swizzle<SwY, SwU, SwW, SwU>());
	m = max(m, m.swizzle<SwZ, SwU, SwU, SwU>());
	return m.getX();
}

/**
 * @brief Clamps SIMD vector component values between min and max values.
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
	#if defined(MATH_SIMD_SUPPORT_AVX2)
	return _mm_fmadd_ps(mul1.data, mul2.data, add.data);
	#elif defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_add_ps(_mm_mul_ps(mul1.data, mul2.data), add.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vmlaq_f32(add.data, mul1.data, mul2.data);
	#else
	return simd_f32_4(
		mul1.values[0] * mul2.values[0] + add.values[0],
		mul1.values[1] * mul2.values[1] + add.values[1],
		mul1.values[2] * mul2.values[2] + add.values[2],
		mul1.values[3] * mul2.values[3] + add.values[3]);
	#endif
}
/**
 * @brief Returns absolute value for each component of the SIMD vector.
 * @param v target SIMD vector
 */
static simd_f32_4 abs(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), v.data), v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vabsq_f32(v.data);
	#else
	return simd_f32_4(std::abs(v.values[0]), std::abs(v.values[1]), std::abs(v.values[2]), std::abs(v.values[3]));
	#endif
}
/**
 * @brief Returns square root of the SIMD vector.
 * @param v target SIMD vector
 */
static simd_f32_4 sqrt(simd_f32_4 v) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	return _mm_sqrt_ps(v.data);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vsqrtq_f32(v.data);
	#else
	return simd_f32_4(std::sqrt(v.values[0]), std::sqrt(v.values[1]), 
		std::sqrt(v.values[2]), std::sqrt(v.values[3]));
	#endif
}

/**
 * @brief Returns sign of the SIMD vector.
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
	return simd_f32_4(std::signbit(v.values[0]) ? -1.0f : 1.0f, std::signbit(v.values[1]) ? -1.0f : 1.0f,
		std::signbit(v.values[2]) ? -1.0f : 1.0f, std::signbit(v.values[3]) ? -1.0f : 1.0f);
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
	auto shift = { 0, 1, 2, 3 };
	return vaddvq_u32(vshlq_u32(vshrq_n_u32(vreinterpretq_u32_f32(v.data), 31), shift));
	#else
	return (std::signbit(v.values[0]) ? 1 : 0) | (std::signbit(v.values[1]) ? 2 : 0) | 
		(std::signbit(v.values[2]) ? 4 : 0) | (std::signbit(v.values[3]) ? 8 : 0);
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
	return simd_f32_4((a.values[0] * b.values[0] + a.values[1] * b.values[1]) + 
		(a.values[2] * b.values[2] + a.values[3] * b.values[3]));
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
	return (a.values[0] * b.values[0] + a.values[1] * b.values[1]) + 
		(a.values[2] * b.values[2] + a.values[3] * b.values[3]);
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
	return simd_f32_4(a.values[0] * b.values[0] + a.values[1] * b.values[1] + a.values[2] * b.values[2]);
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
	return a.values[0] * b.values[0] + a.values[1] * b.values[1] + a.values[2] * b.values[2];
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
	auto result = simd_f32_4(a.values[1] * b.values[2] - a.values[2] * b.values[1],
		a.values[2] * b.values[0] - a.values[0] * b.values[2],
		a.values[0] * b.values[1] - a.values[1] * b.values[0], 0.0f);
	result.values[3] = result.values[2];
	return result;
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
	return std::sqrt((v.values[0] * v.values[0] + v.values[1] * v.values[1]) + 
		(v.values[2] * v.values[2] + v.values[3] * v.values[3]));
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
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v.data, v.data, 0xff)));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	return vget_lane_f32(vsqrt_f32(vdup_n_f32(vaddvq_f32(vmulq_f32(v.data, v.data)))), 0);
	#else
	return std::sqrt((v.values[0] * v.values[0] + v.values[1] * v.values[1]) + 
		(v.values[2] * v.values[2] + v.values[3] * v.values[3]));
	#endif
}

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
	return v / simd_f32_4(length3(v));
	#endif
}

} // namespace math