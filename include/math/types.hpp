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
 * @brief Common integer variable types.
 */

#pragma once

#define __STDC_WANT_IEC_60559_TYPES_EXT__
#include <cfloat>
#include <cstdint>
#include <cstddef>

#if defined(__AVX2__)
#include <immintrin.h>
#endif

namespace math
{
/**
 * @brief A signed 8-bit integer type. (-128 to 127)
 */
typedef int8_t int8;
/**
 * @brief A signed 16-bit integer type. (-32,768 to 32,767)
 */
typedef int16_t int16;
/**
 * @brief A signed 32-bit integer type. (-2,147,483,648 to 2,147,483,647)
 */
typedef int32_t int32;
/**
 * @brief A signed 64-bit integer type. (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807)
 */
typedef int64_t int64;

/**
 * @brief An unsigned 8-bit integer type. (0 to 255)
 */
typedef uint8_t uint8;
/**
 * @brief An unsigned 16-bit integer type. (0 to 65,535)
 */
typedef uint16_t uint16;
/**
 * @brief An unsigned 32-bit integer type. (0 to 4,294,967,295)
 */
typedef uint32_t uint32;
/**
 * @brief An unsigned 64-bit type. (0 to 18,446,744,073,709,551,615)
 */
typedef uint64_t uint64;

/**
 * @brief Unsigned pointer type. (CPU architecture dependant!)
 */
typedef size_t psize;

//**********************************************************************************************************************
#ifndef FLT16_MIN // Note: MSVC half float support.

#define FLT16_MIN     0.00006103515625f /**< Minimum positive value representable as a 16-bit float. */
#define FLT16_MAX     65504.0f          /**< Maximum representable finite positive 16-bit value. */
#define FLT16_EPSILON 0.0009765625f     /**< Smallest positive 16-bit value. */

#define FLT16_MANT_DIG     11
#define FLT16_DECIMAL_DIG  5
#define FLT16_DIG          3
#define FLT16_MIN_EXP     -13
#define FLT16_MIN_10_EXP  -4
#define FLT16_MAX_EXP      16
#define FLT16_MAX_10_EXP   4
#define FLT16_RADIX        2

/**
 * @brief An IEEE-754 half-precision 16-bit floating-point number.
 */
struct half
{
	uint16_t data = 0;

	static uint16_t floatToHalf(float f) noexcept
	{
		auto i = *(const int*)&f;
		auto s =  (i >> 16) & 0x00008000;
		auto e = ((i >> 23) & 0x000000ff) - (127 - 15);
		auto m =          i & 0x007fffff;

		if (e <= 0)
		{
			if (e < -10) return s;
			m = m | 0x00800000;
			auto t = 14 - e;
			auto a = (1 << (t - 1)) - 1;
			auto b = (m >> t) & 1;
			m = (m + a + b) >> t;
			return s | m;
		}
		else if (e == 0xff - (127 - 15))
		{
			if (m == 0) return s | 0x7c00;
			else
			{
				m >>= 13;
				return s | 0x7c00 | m | (m == 0);
			}
		}
		else
		{
			m = m + 0x00000fff + ((m >> 13) & 1);
			if (m & 0x00800000) { m = 0; e += 1; }
			if (e > 30)
			{
				volatile float f = 1e10f;
				for (int i = 0; i < 10; i++) f *= f;
				return s | 0x7c00;
			}
			return s | (e << 10) | (m >> 13);
		}
	}
	static int halfToFloat(int h) noexcept
	{
		auto s = (h >> 15) & 0x00000001;
		auto e = (h >> 10) & 0x0000001f;
		auto m =  h        & 0x000003ff;

		if (e == 0)
		{
			if (m == 0) return s << 31;
			else
			{
				while (!(m & 0x00000400)) { m <<= 1; e -= 1; }
				e += 1; m &= ~0x00000400;
			}
		}
		else if (e == 31)
		{
			if (m == 0) return (s << 31) | 0x7f800000;
			else return (s << 31) | 0x7f800000 | (m << 13);
		}

		e = e + (127 - 15); m = m << 13;
		return (s << 31) | (e << 23) | m;
	}
	half(float f) noexcept
	{
		#if defined(__AVX2__)
		data = _cvtss_sh(f, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
		#else
		data = floatToHalf(f);
		#endif
	}
	operator float() const noexcept
	{
		#if defined(__AVX2__)
		return _cvtsh_ss(data);
		#else
		auto i = halfToFloat(data);
		return *(const float)&i;
		#endif
	}
};
#else
/**
 * @brief An IEEE-754 half-precision 16-bit floating-point number.
 */
typedef _Float16 half;
#endif

/**
 * @brief Half-precision 16-bit floating-point number literal.
 */
constexpr half operator""_hf(long double val) { return static_cast<half>(val); }

} // namespace math