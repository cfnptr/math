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
 * @brief Common single instruction multiple data (SIMD) types.
 */

#pragma once
#include "math/types.hpp"

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)

#include <xmmintrin.h>
#include <emmintrin.h>
#include <tmmintrin.h>

#define MATH_SIMD_SUPPORT_SSE
#define MATH_SIMD_VECTOR_ALIGNMENT 16

// TODO: AVX512 support when more than 50% devices will be supported on steam hardware survey.

#if defined(__AVX2__)
#include <immintrin.h>
#define MATH_SIMD_SUPPORT_AVX2
#endif
#if defined(__SSE4_1__)
#include <smmintrin.h>
#define MATH_SIMD_SUPPORT_SSE4_1
#endif

#elif defined(__aarch64__) || defined(_M_ARM64)

#include <arm_neon.h>
#define MATH_SIMD_SUPPORT_NEON
#define MATH_SIMD_VECTOR_ALIGNMENT 16

#elif defined(__arm__) || defined(_M_ARM)
#define MATH_SIMD_VECTOR_ALIGNMENT 8
#endif

#if defined(_MSC_VER)
#include <intrin.h>
#endif

namespace math
{

#if defined(MATH_SIMD_SUPPORT_SSE)
typedef __m128 _simd_f128;
typedef uint64 _simd_f64;
typedef __m128i _simd_i128;
typedef __m128i _simd_u128;
#elif defined(MATH_SIMD_SUPPORT_NEON)
typedef float32x4_t _simd_f128;
typedef float16x4_t _simd_f64;
typedef int32x4_t _simd_i128;
typedef uint32x4_t _simd_u128;
#else
typedef float _simd_f128[4];
typedef half _simd_f64[4];
typedef int32 _simd_i128[4];
typedef uint32 _simd_u128[4];
#endif

/**
 * @brief Returns number of trailing zero bits. (How many low bits are zero)
 * @param v target value to count
 */
static uint32 countTrailingZeros(uint32 v) noexcept
{
	#if defined(__BMI__) || defined(__BMI1__)
	return _tzcnt_u32(v);
	#elif defined(_MSC_VER)
	if (v == 0u) return 32u;
	unsigned long result;
	_BitScanForward(&result, v);
	return result;
	#else
	return v ? __builtin_ctz(v) : 32u;
	#endif
}
/**
 * @brief Returns number of leading zero bits. (How many high bits are zero)
 * @param v target value to count
 */
static uint32 countLeadingZeros(uint32 v) noexcept
{
	#if defined(__LZCNT__)
	return _lzcnt_u32(v);
	#elif defined(_MSC_VER)
		#if defined(__arm__)
		return _CountLeadingZeros(v);
		#else
		if (v == 0u) return 32u;
		unsigned long result;
		_BitScanReverse(&result, v);
		return 31u - result;
		#endif
	#else
	return v ? __builtin_clz(v) : 32u;
	#endif
}

/**
 * @brief Returns number of 1 bits in a value
 * @param v target value to count
 */
inline uint32 countBits(uint32 v)
{
	#if defined(__POPCNT__)
	return _mm_popcnt_u32(v);
	#elif defined(_MSC_VER)
		#if defined(__arm__)
		return _CountOneBits(v);
		#else
		v = v - ((v >> 1u) & 0x55555555u);
		v = (v & 0x33333333u) + ((v >> 2u) & 0x33333333u);
		v = (v + (v >> 4u)) & 0x0F0F0F0Fu;
		return (v * 0x01010101u) >> 24u;
		#endif
	#else
	return __builtin_popcount(v);
	#endif
}

/**
 * @brief Returns next higher power of 2 of a value, or the value itself.
 * @param v target value to use
 */
static uint32 calcNextPowerOf2(uint32 v) noexcept
{
	return v <= 1 ? 1 : 1u << (32u - countLeadingZeros(v - 1u));
}

} // namespace math