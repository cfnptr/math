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
 * @brief Common radians/degrees conversion functions.
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

/**
 * @brief Converts specified value in degrees to radians.
 * @param degrees target value in degrees
 */
static constexpr float radians(float degrees) noexcept { return degrees * ((float)M_PI / 180.0f); }
/**
 * @brief Converts specified vector in degrees to radians.
 * @param degrees target vector in degrees
 */
static constexpr float2 radians(float2 degrees) noexcept { return degrees * ((float)M_PI / 180.0f); }
/**
 * @brief Converts specified vector in degrees to radians.
 * @param degrees target vector in degrees
 */
static constexpr float3 radians(float3 degrees) noexcept { return degrees * ((float)M_PI / 180.0f); }
/**
 * @brief Converts specified vector in degrees to radians.
 * @param degrees target vector in degrees
 */
static constexpr float4 radians(float4 degrees) noexcept { return degrees * ((float)M_PI / 180.0f); }
/**
 * @brief Converts specified SIMD vector in degrees to radians.
 * @param degrees target SIMD vector in degrees
 */
static f32x4 radians(f32x4 degrees) noexcept { return degrees * (float)M_PI / 180.0f; }

/**
 * @brief Converts specified value in radians to degrees.
 * @param degrees target vector in radians
 */
static constexpr float degrees(float radians) noexcept { return radians * (180.0f / (float)M_PI); }
/**
 * @brief Converts specified vector in radians to degrees.
 * @param degrees target vector in radians
 */
static constexpr float2 degrees(float2 radians) noexcept { return radians * (180.0f / (float)M_PI); }
/**
 * @brief Converts specified vector in radians to degrees.
 * @param degrees target vector in radians
 */
static constexpr float3 degrees(float3 radians) noexcept { return radians * (180.0f / (float)M_PI); }
/**
 * @brief Converts specified vector in radians to degrees.
 * @param degrees target vector in radians
 */
static constexpr float4 degrees(float4 radians) noexcept { return radians * (180.0f / (float)M_PI); }
/**
 * @brief Converts specified SIMD vector in radians to degrees.
 * @param degrees target SIMD vector in radians
 */
static f32x4 degrees(f32x4 radians) noexcept { return radians * 180.0f / (float)M_PI; }

}; // namespace math