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
 * @brief Common single instruction multiple data (SIMD) types.
 */

#pragma once
#include "math/types.hpp"

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)

#include <xmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>

#define MATH_SIMD_SUPPORT_SSE
#define MATH_SIMD_VECTOR_ALIGNMENT 16

#if defined(__AVX2__)
#define MATH_SIMD_SUPPORT_AVX2
#endif
#if defined(__AVX__) || defined(MATH_SIMD_SUPPORT_AVX2)
#define MATH_SIMD_SUPPORT_AVX2
#endif
#if defined(__SSE4_2__) || defined(MATH_SIMD_SUPPORT_AVX2)
#define MATH_SIMD_SUPPORT_SSE4_2
#endif
#if defined(__SSE4_1__) || defined(MATH_SIMD_SUPPORT_SSE4_2)
#define MATH_SIMD_SUPPORT_SSE4_1
#endif

#elif defined(__aarch64__) || defined(_M_ARM64)

#include <arm_neon.h>
#define MATH_SIMD_SUPPORT_NEON
#define MATH_SIMD_VECTOR_ALIGNMENT 16

#elif defined(__arm__) || defined(_M_ARM)
#define MATH_SIMD_VECTOR_ALIGNMENT 8
#endif

namespace math
{

#if defined(MATH_SIMD_SUPPORT_SSE)
typedef __m128 _simd_f128;
typedef __m128i _simd_i128;
typedef __m128i _simd_u128;
#elif defined(MATH_SIMD_SUPPORT_NEON)
typedef float32x4_t _simd_f128;
typedef int32x4_t _simd_i128;
typedef uint32x4_t _simd_u128;
#else
typedef float _simd_f128[4];
typedef int32 _simd_i128[4];
typedef uint32 _simd_u128[4];
#endif

} // namespace math