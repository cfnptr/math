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

namespace math
{

/**
 * @brief SIMD 32bit floating point 4x4 matrix structure. (float4x4)
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 * @note Use it when you know how to implement a faster vectorized code.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) f32x4x4
{
	f32x4 c0, c1, c2, c3;

	/**
	 * @brief Creates a new zero initialized SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 */
	f32x4x4() noexcept = default;
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * @param n target value for all matrix vector components
	 */
	explicit f32x4x4(float n) noexcept : c0(n), c1(n), c2(n), c3(n) { }
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * @details See the @ref f32x4x4.
	 */
	f32x4x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2,
		float c0r3, float c1r3, float c2r3, float c3r3) noexcept :
		c0(f32x4(c0r0, c0r1, c0r2, c0r3)),
		c1(f32x4(c1r0, c1r1, c1r2, c1r3)),
		c2(f32x4(c2r0, c2r1, c2r2, c2r3)),
		c3(f32x4(c3r0, c3r1, c3r2, c3r3)) { }
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * 
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 * @param c2 third matrix column value
	 * @param c3 fourth matrix column value
	 */
	f32x4x4(f32x4 c0, f32x4 c1, f32x4 c2, f32x4 c3) noexcept : c0(c0), c1(c1), c2(c2), c3(c3) { }
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * @warning This constructor duplicates second column vector to the third column!
	 *
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 * @param c2 third matrix column value
	 */
	f32x4x4(f32x4 c0, f32x4 c1, f32x4 c2) noexcept : c0(c0), c1(c1), c2(c2), c3(c2) { }
	
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * @param[in] m target 4x4 matrix value
	 */
	explicit f32x4x4(const float4x4& m) noexcept { *this = *((const f32x4x4*)&m); }
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * 
	 * @param[in] m target 3x3 matrix value
	 * @param r3 third rows SIMD vector
	 */
	explicit f32x4x4(const float4x3& m, f32x4 r3 = f32x4::zero) noexcept : 
		c0(float4(m.c0, r3.getX())), c1(float4(m.c1, r3.getY())), 
		c2(float4(m.c2, r3.getZ())), c3(float4(m.c3, r3.getW())) { }
	/**
	 * @brief Creates a new SIMD 32bit floating point 4x4 matrix structure. (float4x4)
	 * 
	 * @param[in] m target 3x3 matrix value
	 * @param c3 third columns SIMD vector
	 * @param r3 third rows SIMD vector
	 */
	explicit f32x4x4(const float3x3& m, f32x4 c3 = f32x4::zero, f32x4 r3 = f32x4::zero) noexcept : 
		c0(float4(m.c0, r3.getX())), c1(float4(m.c1, r3.getY())), c2(float4(m.c2, r3.getZ())), c3(c3) { }

	/**
	 * @brief Returns SIMD matrix column by index.
	 * @param i target column index
	 */
	f32x4& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((f32x4*)this)[i];
	}
	/**
	 * @brief Returns SIMD matrix column by index.
	 * @param i target column index
	 */
	f32x4 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((f32x4*)this)[i];
	}

	/**
	 * @brief Returns SIMD matrix as 4x4 floating point matrix.
	 */
	explicit operator float4x4() const noexcept
	{
		return *((const float4x4*)this);
	}
	/**
	 * @brief Returns SIMD matrix as 4x3 floating point matrix.
	 */
	explicit operator float4x3() const noexcept
	{
		return float4x3((float3)c0, (float3)c1, (float3)c2, (float3)c3);
	}
	/**
	 * @brief Returns SIMD matrix as 3x4 floating point matrix.
	 */
	explicit operator float3x4() const noexcept
	{
		return float3x4((float4)c0, (float4)c1, (float4)c2);
	}
	/**
	 * @brief Returns SIMD matrix as 3x3 floating point matrix.
	 */
	explicit operator float3x3() const noexcept
	{
		return float3x3((float3)c0, (float3)c1, (float3)c2);
	}
	/**
	 * @brief Returns SIMD matrix as 3x3 floating point matrix.
	 */
	explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }

	/*******************************************************************************************************************
	 * @brief Adds specified value to the all SIMD matrix columns.
	 * @param n target value to add
	 */
	f32x4x4 operator+(float n) const noexcept
	{
		auto t = f32x4(n);
		return f32x4x4(c0 + t, c1 + t, c2 + t, c3 + t);
	}
	/**
	 * @brief Subtracts specified value from the all SIMD matrix columns.
	 * @param n target value to subtract
	 */
	f32x4x4 operator-(float n) const noexcept
	{
		auto t = f32x4(n);
		return f32x4x4(c0 - t, c1 - t, c2 - t, c3 - t);
	}
	/**
	 * @brief Multiplies all SIMD matrix columns by the specified value.
	 * @param n target value to multiply by
	 */
	f32x4x4 operator*(float n) const noexcept
	{
		auto t = f32x4(n);
		return f32x4x4(c0 * t, c1 * t, c2 * t, c3 * t);
	}
	/**
	 * @brief Divides all SIMD matrix columns by the specified value.
	 * @param n target value to divide by
	 */
	f32x4x4 operator/(float n) const noexcept
	{
		auto t = f32x4(n);
		return f32x4x4(c0 / t, c1 / t, c2 / t, c3 / t);
	}

	/**
	 * @brief Calculates dot product between two SIMD matrices.
	 * @param[in] m target SIMD matrix to dot by
	 */
	f32x4x4 operator*(const f32x4x4& m) const noexcept
	{
		f32x4x4 result;
		#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_AVX2)
		for (int i = 0; i < 4; ++i)
		{
			auto c = m[i].data;
			auto r = _mm_mul_ps(c0.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(0, 0, 0, 0)));
			r = MATH_SIMD_FMA(c1.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(1, 1, 1, 1)), r);
			r = MATH_SIMD_FMA(c2.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(2, 2, 2, 2)), r);
			r = MATH_SIMD_FMA(c3.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(3, 3, 3, 3)), r);
			result[i].data = r;
		}
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		for (int i = 0; i < 4; ++i)
		{
			auto c = m[i].data;
			auto r = vmulq_f32(c0.data, vdupq_laneq_f32(c, 0));
			r = vmlaq_f32(r, c1.data, vdupq_laneq_f32(c, 1));
			r = vmlaq_f32(r, c2.data, vdupq_laneq_f32(c, 2));
			r = vmlaq_f32(r, c3.data, vdupq_laneq_f32(c, 3));
			result[i].data = r;
		}
		#else
		result = f32x4x4((*((const float4x4*)this) * (*((const float4x4*)&m))));
		#endif
		return result;
	}
	/**
	 * @brief Calculates dot product between SIMD matrix and vector.
	 * @param v target SIMD vector to dot by
	 */
	f32x4 operator*(f32x4 v) const noexcept
	{
		#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_AVX2)
		auto r = _mm_mul_ps(c0.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0)));
		r = MATH_SIMD_FMA(c1.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1)), r);
		r = MATH_SIMD_FMA(c2.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2)), r);
		r = MATH_SIMD_FMA(c3.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(3, 3, 3, 3)), r);
		return r;
		#elif defined(MATH_SIMD_SUPPORT_NEON)
		auto r = vmulq_f32(c0.data, vdupq_laneq_f32(v.data, 0));
		r = vmlaq_f32(r, c1.data, vdupq_laneq_f32(v.data, 1));
		r = vmlaq_f32(r, c2.data, vdupq_laneq_f32(v.data, 2));
		r = vmlaq_f32(r, c3.data, vdupq_laneq_f32(v.data, 3));
		return r;
		#else
		return f32x4((*((const float4x4*)this) * (*((const float4*)&v))));
		#endif
	}

	f32x4x4& operator*=(const f32x4x4& m) noexcept { *this = *this * m; return *this; }
	f32x4x4& operator+=(float n) noexcept { *this = *this + n; return *this; }
	f32x4x4& operator-=(float n) noexcept { *this = *this - n; return *this; }
	f32x4x4& operator*=(float n) noexcept { *this = *this * n; return *this; }
	f32x4x4& operator/=(float n) noexcept { *this = *this / n; return *this; }
	
	bool operator==(const f32x4x4& m) const noexcept
	{
		return areAllTrue(equal(c0, m.c0) & equal(c1, m.c1) & equal(c2, m.c2) & equal(c3, m.c3));
	}
	bool operator!=(const f32x4x4& m) const noexcept
	{
		return areAnyTrue(notEqual(c0, m.c0) | notEqual(c1, m.c1) | notEqual(c2, m.c2) | notEqual(c3, m.c3));
	}

	static const f32x4x4 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, identity, ndcToUV, uvToNDC;
};

//**********************************************************************************************************************
inline const f32x4x4 f32x4x4::zero = f32x4x4(0.0f);
inline const f32x4x4 f32x4x4::one = f32x4x4(1.0f);
inline const f32x4x4 f32x4x4::minusOne = f32x4x4(-1.0f);
inline const f32x4x4 f32x4x4::min = f32x4x4(FLT_MIN);
inline const f32x4x4 f32x4x4::minusMin = f32x4x4(-FLT_MIN);
inline const f32x4x4 f32x4x4::max = f32x4x4(FLT_MAX);
inline const f32x4x4 f32x4x4::minusMax = f32x4x4(-FLT_MAX);
inline const f32x4x4 f32x4x4::epsilon = f32x4x4(FLT_EPSILON);
inline const f32x4x4 f32x4x4::inf = f32x4x4(INFINITY);
inline const f32x4x4 f32x4x4::minusInf = f32x4x4(-INFINITY);
inline const f32x4x4 f32x4x4::nan = f32x4x4(NAN);

inline const f32x4x4 f32x4x4::identity = f32x4x4
(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);
inline const f32x4x4 f32x4x4::ndcToUV = f32x4x4
(
	0.5f, 0.0f, 0.0f, 0.5f,
	0.0f, 0.5f, 0.0f, 0.5f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);
inline const f32x4x4 f32x4x4::uvToNDC = f32x4x4
(
	2.0f, 0.0f, 0.0f, -1.0f,
	0.0f, 2.0f, 0.0f, -1.0f,
	0.0f, 0.0f, 1.0f,  0.0f,
	0.0f, 0.0f, 0.0f,  1.0f
);

/**
 * @brief Returns true if first SIMD matrix binary representation is less than the second.
 *
 * @param[in] a first SIMD matrix to binary compare
 * @param[in] b second SIMD matrix to binary compare
 */
static bool isBinaryLess(const f32x4x4& a, const f32x4x4& b) noexcept
{
	return memcmp(&a, &b, sizeof(f32x4x4)) < 0;
}

/**
 * @brief Calculates 3x3 dot product between two SIMD matrices.
 * @param[in] a first SIMD matrix to use
 * @param[in] b second SIMD matrix to use
 */
static f32x4x4 multiply3x3(const f32x4x4& a, const f32x4x4& b) noexcept
{
	f32x4x4 result; 
	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_AVX2)
	for (int i = 0; i < 4; ++i)
	{
		auto c = b[i].data;
		auto r = _mm_mul_ps(a.c0.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(0, 0, 0, 0)));
		r = MATH_SIMD_FMA(a.c1.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(1, 1, 1, 1)), r);
		r = MATH_SIMD_FMA(a.c2.data, _mm_shuffle_ps(c, c, _MM_SHUFFLE(2, 2, 2, 2)), r);
		result[i].data = r;
	}
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	for (int i = 0; i < 4; ++i)
	{
		auto c = b[i].data;
		auto r = vmulq_f32(a.c0.data, vdupq_laneq_f32(c, 0));
		r = vmlaq_f32(r, a.c1.data, vdupq_laneq_f32(c, 1));
		r = vmlaq_f32(r, a.c2.data, vdupq_laneq_f32(c, 2));
		result[i].data = r;
	}
	#else
	result = f32x4x4((float3x3)a * (float3x3)b, a.c3);
	#endif
	return result;
}
/**
 * @brief Calculates 3x3 dot product between SIMD matrix and vector.
 * @param[in] m target SIMD matrix to use
 * @param v target SIMD vector to dot by
 */
static f32x4 multiply3x3(const f32x4x4& m, f32x4 v) noexcept
{
	f32x4 result;
	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_AVX2)
	auto r = _mm_mul_ps(m.c0.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(0, 0, 0, 0)));
	r = MATH_SIMD_FMA(m.c1.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(1, 1, 1, 1)), r);
	r = MATH_SIMD_FMA(m.c2.data, _mm_shuffle_ps(v.data, v.data, _MM_SHUFFLE(2, 2, 2, 2)), r);
	result = r;
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto r = vmulq_f32(m.c0.data, vdupq_laneq_f32(v.data, 0));
	r = vmlaq_f32(r, m.c1.data, vdupq_laneq_f32(v.data, 1));
	r = vmlaq_f32(r, m.c2.data, vdupq_laneq_f32(v.data, 2));
	result = r;
	#else
	auto t = float3x3((float3)m.c0, (float3)m.c1, (float3)m.c2) * (float3)v;
	result = f32x4(t.x, t.y, t.z, t.z);
	#endif
	return result.swizzle<SwX, SwY, SwZ, SwU>();
}

/**
 * @brief Calculates 4x4 SIMD matrix transpose. (Flips matrix over its diagonal)
 * @param[in] m target SIMD matrix to transpose
 */
static f32x4x4 transpose4x4(const f32x4x4& m) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	auto t1 = _mm_shuffle_ps(m.c0.data, m.c1.data, _MM_SHUFFLE(1, 0, 1, 0));
	auto t3 = _mm_shuffle_ps(m.c0.data, m.c1.data, _MM_SHUFFLE(3, 2, 3, 2));
	auto t2 = _mm_shuffle_ps(m.c2.data, m.c3.data, _MM_SHUFFLE(1, 0, 1, 0));
	auto t4 = _mm_shuffle_ps(m.c2.data, m.c3.data, _MM_SHUFFLE(3, 2, 3, 2));
	return f32x4x4(
		_mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0)),
		_mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1)),
		_mm_shuffle_ps(t3, t4, _MM_SHUFFLE(2, 0, 2, 0)),
		_mm_shuffle_ps(t3, t4, _MM_SHUFFLE(3, 1, 3, 1)));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto t1 = vzipq_f32(m.c0.data, m.c2.data);
	auto t2 = vzipq_f32(m.c1.data, m.c3.data);
	auto t3 = vzipq_f32(t1.val[0], t2.val[0]);
	auto t4 = vzipq_f32(t1.val[1], t2.val[1]);
	return f32x4x4(t3.val[0], t3.val[1], t4.val[0], t4.val[1]);
	#else
	return f32x4x4(transpose(*((const float4x4*)&m)));
	#endif
}
/**
 * @brief Calculates 3x3 SIMD matrix transpose. (Flips matrix over its diagonal)
 * @param[in] m target SIMD matrix to transpose
 */
static f32x4x4 transpose3x3(const f32x4x4& m) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE)
	auto zero = _mm_setzero_ps();
	auto t1 = _mm_shuffle_ps(m.c0.data, m.c1.data, _MM_SHUFFLE(1, 0, 1, 0));
	auto t3 = _mm_shuffle_ps(m.c0.data, m.c1.data, _MM_SHUFFLE(3, 2, 3, 2));
	auto t2 = _mm_shuffle_ps(m.c2.data, zero, _MM_SHUFFLE(1, 0, 1, 0));
	auto t4 = _mm_shuffle_ps(m.c2.data, zero, _MM_SHUFFLE(3, 2, 3, 2));
	return f32x4x4(
		_mm_shuffle_ps(t1, t2, _MM_SHUFFLE(2, 0, 2, 0)),
		_mm_shuffle_ps(t1, t2, _MM_SHUFFLE(3, 1, 3, 1)),
		_mm_shuffle_ps(t3, t4, _MM_SHUFFLE(2, 0, 2, 0)), m.c3);
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto t1 = vzipq_f32(m.c0.data, m.c2.data);
	auto t2 = vzipq_f32(m.c1.data, vdupq_n_f32(0));
	auto t3 = vzipq_f32(t1.val[0], t2.val[0]);
	auto t4 = vzipq_f32(t1.val[1], t2.val[1]);
	return f32x4x4(t3.val[0], t3.val[1], t4.val[0], m.c3);
	#else
	auto r = transpose((float3x3)m);
	return f32x4x4(
		f32x4(r.c0.x, r.c0.y, r.c0.z, m.c3.floats.x), 
		f32x4(r.c1.x, r.c1.y, r.c1.z, m.c3.floats.y), 
		f32x4(r.c2.x, r.c2.y, r.c2.z, m.c3.floats.z), m.c3);
	#endif
}

/**
 * @brief Calculates 4x4 SIMD matrix inverse. (Usefull for undoing transformations)
 * @param[in] m target SIMD matrix to inverse
 */
static f32x4x4 inverse4x4(const f32x4x4& m) noexcept
{
	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_AVX2)
	auto t1 = _mm_shuffle_ps(m.c0.data, m.c1.data, _MM_SHUFFLE(1, 0, 1, 0));
	auto r1 = _mm_shuffle_ps(m.c2.data, m.c3.data, _MM_SHUFFLE(1, 0, 1, 0));
	auto r0 = _mm_shuffle_ps(t1, r1, _MM_SHUFFLE(2, 0, 2, 0));
	r1 = _mm_shuffle_ps(r1, t1, _MM_SHUFFLE(3, 1, 3, 1));

	t1 = _mm_shuffle_ps(m.c0.data, m.c1.data, _MM_SHUFFLE(3, 2, 3, 2));
	auto r3 = _mm_shuffle_ps(m.c2.data, m.c3.data, _MM_SHUFFLE(3, 2, 3, 2));
	auto r2 = _mm_shuffle_ps(t1, r3, _MM_SHUFFLE(2, 0, 2, 0));
	r3 = _mm_shuffle_ps(r3, t1, _MM_SHUFFLE(3, 1, 3, 1));

	t1 = _mm_mul_ps(r2, r3);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 3, 0, 1));
	auto m0 = _mm_mul_ps(r1, t1);
	auto m1 = _mm_mul_ps(r0, t1);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	m0 = _mm_sub_ps(_mm_mul_ps(r1, t1), m0);
	m1 = _mm_sub_ps(_mm_mul_ps(r0, t1), m1);
	m1 = _mm_shuffle_ps(m1, m1, _MM_SHUFFLE(1, 0, 3, 2)); 

	t1 = _mm_mul_ps(r1, r2);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 3, 0, 1));
	m0 = MATH_SIMD_FMA(r3, t1, m0);
	auto m3 = _mm_mul_ps(r0, t1);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	m0 = _mm_sub_ps(m0, _mm_mul_ps(r3, t1));
	m3 = _mm_sub_ps(_mm_mul_ps(r0, t1), m3);
	m3 = _mm_shuffle_ps(m3, m3, _MM_SHUFFLE(1, 0, 3, 2));

	t1 = _mm_mul_ps(_mm_shuffle_ps(r1, r1, _MM_SHUFFLE(1, 0, 3, 2)), r3);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 3, 0, 1));
	r2 = _mm_shuffle_ps(r2, r2, _MM_SHUFFLE(1, 0, 3, 2));
	m0 = MATH_SIMD_FMA(r2, t1, m0);
	auto m2 = _mm_mul_ps(r0, t1);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	m0 = _mm_sub_ps(m0, _mm_mul_ps(r2, t1));
	m2 = _mm_sub_ps(_mm_mul_ps(r0, t1), m2);
	m2 = _mm_shuffle_ps(m2, m2, _MM_SHUFFLE(1, 0, 3, 2));

	t1 = _mm_mul_ps(r0, r1);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 3, 0, 1));
	m2 = MATH_SIMD_FMA(r3, t1, m2);
	m3 = _mm_sub_ps(_mm_mul_ps(r2, t1), m3);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	m2 = _mm_sub_ps(_mm_mul_ps(r3, t1), m2);
	m3 = _mm_sub_ps(m3, _mm_mul_ps(r2, t1));

	t1 = _mm_mul_ps(r0, r3);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 3, 0, 1));
	m1 = _mm_sub_ps(m1, _mm_mul_ps(r2, t1));
	m2 = MATH_SIMD_FMA(r1, t1, m2);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	m1 = MATH_SIMD_FMA(r2, t1, m1);
	m2 = _mm_sub_ps(m2, _mm_mul_ps(r1, t1));

	t1 = _mm_mul_ps(r0, r2);
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(2, 3, 0, 1));
	m1 = MATH_SIMD_FMA(r3, t1, m1);
	m3 = _mm_sub_ps(m3, _mm_mul_ps(r1, t1));
	t1 = _mm_shuffle_ps(t1, t1, _MM_SHUFFLE(1, 0, 3, 2));
	m1 = _mm_sub_ps(m1, _mm_mul_ps(r3, t1));
	m3 = MATH_SIMD_FMA(r1, t1, m3);

	auto d = _mm_mul_ps(r0, m0);
	d = _mm_add_ps(_mm_shuffle_ps(d, d, _MM_SHUFFLE(2, 3, 0, 1)), d);
	d = _mm_add_ss(_mm_shuffle_ps(d, d, _MM_SHUFFLE(1, 0, 3, 2)), d);
	d = _mm_div_ss(_mm_set_ss(1.0f), d);
	d = _mm_shuffle_ps(d, d, _MM_SHUFFLE(0, 0, 0, 0));

	return f32x4x4(_mm_mul_ps(d, m0), _mm_mul_ps(d, m1), 
		_mm_mul_ps(d, m2), _mm_mul_ps(d, m3));
	#elif defined(MATH_SIMD_SUPPORT_NEON)
	auto t1 = __builtin_shufflevector(m.c0.data, m.c1.data, 0, 1, 4, 5);
	auto r1 = __builtin_shufflevector(m.c2.data, m.c3.data, 0, 1, 4, 5);
	auto r0 = __builtin_shufflevector(t1, r1, 0, 2, 4, 6);
	r1 = __builtin_shufflevector(r1, t1, 1, 3, 5, 7);
	t1 = __builtin_shufflevector(m.c0.data, m.c1.data, 2, 3, 6, 7);
	auto r3 = __builtin_shufflevector(m.c2.data, m.c3.data, 2, 3, 6, 7);
	auto r2 = __builtin_shufflevector(t1, r3, 0, 2, 4, 6);
	r3 = __builtin_shufflevector(r3, t1, 1, 3, 5, 7);

	t1 = vmulq_f32(r2, r3);
	t1 = __builtin_shufflevector(t1, t1, 1, 0, 3, 2);
	auto m0 = vmulq_f32(r1, t1);
	auto m1 = vmulq_f32(r0, t1);
	t1 = __builtin_shufflevector(t1, t1, 2, 3, 0, 1);
	m0 = vsubq_f32(vmulq_f32(r1, t1), m0);
	m1 = vsubq_f32(vmulq_f32(r0, t1), m1);
	m1 = __builtin_shufflevector(m1, m1, 2, 3, 0, 1);

	t1 = vmulq_f32(r1, r2);
	t1 = __builtin_shufflevector(t1, t1, 1, 0, 3, 2);
	m0 = vmlaq_f32(m0, r3, t1);
	auto m3 = vmulq_f32(r0, t1);
	t1 = __builtin_shufflevector(t1, t1, 2, 3, 0, 1);
	m0 = vsubq_f32(m0, vmulq_f32(r3, t1));
	m3 = vsubq_f32(vmulq_f32(r0, t1), m3);
	m3 = __builtin_shufflevector(m3, m3, 2, 3, 0, 1);

	t1 = __builtin_shufflevector(r1, r1, 2, 3, 0, 1);
	t1 = vmulq_f32(t1, r3);
	t1 = __builtin_shufflevector(t1, t1, 1, 0, 3, 2);
	r2 = __builtin_shufflevector(r2, r2, 2, 3, 0, 1);
	m0 = vmlaq_f32(m0, r2, t1);
	auto m2 = vmulq_f32(r0, t1);
	t1 = __builtin_shufflevector(t1, t1, 2, 3, 0, 1);
	m0 = vsubq_f32(m0, vmulq_f32(r2, t1));
	m2 = vsubq_f32(vmulq_f32(r0, t1), m2);
	m2 = __builtin_shufflevector(m2, m2, 2, 3, 0, 1);

	t1 = vmulq_f32(r0, r1);
	t1 = __builtin_shufflevector(t1, t1, 1, 0, 3, 2);
	m2 = vmlaq_f32(m2, r3, t1);
	m3 = vsubq_f32(vmulq_f32(r2, t1), m3);
	t1 = __builtin_shufflevector(t1, t1, 2, 3, 0, 1);
	m2 = vsubq_f32(vmulq_f32(r3, t1), m2);
	m3 = vsubq_f32(m3, vmulq_f32(r2, t1));

	t1 = vmulq_f32(r0, r3);
	t1 = __builtin_shufflevector(t1, t1, 1, 0, 3, 2);
	m1 = vsubq_f32(m1, vmulq_f32(r2, t1));
	m2 = vmlaq_f32(m2, r1, t1);
	t1 = __builtin_shufflevector(t1, t1, 2, 3, 0, 1);
	m1 = vmlaq_f32(m1, r2, t1);
	m2 = vsubq_f32(m2, vmulq_f32(r1, t1));

	t1 = vmulq_f32(r0, r2);
	t1 = __builtin_shufflevector(t1, t1, 1, 0, 3, 2);
	m1 = vmlaq_f32(m1, r3, t1);
	m3 = vsubq_f32(m3, vmulq_f32(r1, t1));
	t1 = __builtin_shufflevector(t1, t1, 2, 3, 0, 1);
	m1 = vsubq_f32(m1, vmulq_f32(r3, t1));
	m3 = vmlaq_f32(m3, r1, t1);

	auto d = vmulq_f32(r0, m0);
	d = vdupq_n_f32(vaddvq_f32(d));
	d = vdivq_f32(vdupq_n_f32(1.0f), d);

	return f32x4x4(vmulq_f32(d, m0), vmulq_f32(d, m1), 
		vmulq_f32(d, m2), vmulq_f32(d, m3));
	#else
	return f32x4x4(inverse(*((const float4x4*)&m)));
	#endif
}

// TODO: inverse of the 3x3 matrix like in the Jolt lib.

} // namespace math