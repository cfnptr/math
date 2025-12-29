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
 * @brief Common integer variable types.
 */

#pragma once

#define __STDC_WANT_IEC_60559_TYPES_EXT__
#include <cstdint>
#include <cstddef>

namespace math
{

/**
 * @brief Signed 8bit integer type. (-128 to 127)
 */
typedef int8_t int8;
/**
 * @brief Signed 16bit integer type. (-32,768 to 32,767)
 */
typedef int16_t int16;
/**
 * @brief Signed 32bit integer type. (-2,147,483,648 to 2,147,483,647)
 */
typedef int32_t int32;
/**
 * @brief Signed 64bit integer type. (-9,223,372,036,854,775,808 to 9,223,372,036,854,775,807)
 */
typedef int64_t int64;

/**
 * @brief Unsigned 8bit integer type. (0 to 255)
 */
typedef uint8_t uint8;
/**
 * @brief Unsigned 16bit integer type. (0 to 65,535)
 */
typedef uint16_t uint16;
/**
 * @brief Unsigned 32bit integer type. (0 to 4,294,967,295)
 */
typedef uint32_t uint32;
/**
 * @brief Unsigned 64bit integer type. (0 to 18,446,744,073,709,551,615)
 */
typedef uint64_t uint64;

/**
 * @brief Unsigned pointer type. (CPU architecture dependant)
 */
typedef size_t psize;

/**
 * @brief Signed 16bit floating point type. (Half precission float)
 */
typedef _Float16 half;

} // namespace math