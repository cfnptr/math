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

/**
 * @brief An IEEE-754 half-precision 16-bit floating-point number.
 */
typedef _Float16 half;
/**
 * @brief Half-precision 16-bit floating-point number literal.
 */
constexpr half operator""_hf(long double val) { return static_cast<half>(val); }

} // namespace math