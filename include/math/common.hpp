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
 * @brief Common mathematics functions.
 */

#pragma once
#include <algorithm>
#include <cmath>
#include <cassert>

namespace math
{

using namespace std;

#define M_LN100 4.60517018598809136803598290936872842  // loge(100)

/**
 * @brief Returns the minimum of three values.
 * 
 * @tparam T target value type
 * @param a first value to find minimum
 * @param b second value to find minimum
 * @param c third value to find minimum
 */
template<typename T>
static constexpr const T& min(const T& a, const T& b, const T& c) { return std::min(std::min(a, b), c); }
/**
 * @brief Returns the maximum of three values.
 * 
 * @tparam T target value type
 * @param a first value to find maximum
 * @param b second value to find maximum
 * @param c third value to find maximum
 */
template<typename T>
static constexpr const T& max(const T& a, const T& b, const T& c) { return std::max(std::max(a, b), c); }

/**
 * @brief Clamps float value between the 0.0 and 1.0. (Inclusive range)
 * @param v target floating-point value to saturate
 */
static constexpr float saturate(float v) { return std::clamp(v, 0.0f, 1.0f); }
/**
 * @brief Clamps float value between the 0.0 and 1.0. (Inclusive range)
 * @param v target floating-point value to saturate
 */
static constexpr double saturate(double v) { return std::clamp(v, 0.0, 1.0); }

/**
 * @brief Returns specified float value sign.
 * @param v target floating-point value
 */
static float sign(float v) noexcept { return std::signbit(v) ? -1.0f : 1.0f; }
/**
 * @brief Returns specified float value sign.
 * @param v target floating-point value
 */
static double sign(double v) noexcept { return std::signbit(v) ? -1.0 : 1.0; }

/***********************************************************************************************************************
 * @brief Remaps specified value to the 0.0 - 1.0 range.
 * @param v target floating-point value to repeat
 */
static float repeat(float v) noexcept
{
	if (v < 0.0f)
		return 1.0f - std::fmod(-v, 1.0f);
	if (v >= 1.0f)
		return std::fmod(v, 1.0f);
	return v;
}
/**
 * @brief Remaps specified value to the 0.0 - 1.0 range.
 * @param v target floating-point value to repeat
 */
static double repeat(double v) noexcept
{
	if (v < 0.0)
		return 1.0 - std::fmod(-v, 1.0);
	if (v >= 1.0)
		return std::fmod(v, 1.0);
	return v;
}

/**
 * @brief Linearly interpolates between a and b values using t.
 * 
 * @param a minimum value (t == 0.0)
 * @param b maximum value (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static constexpr float lerp(float a, float b, float t) noexcept { return std::fma(t, b, std::fma(-t, a, a)); }
/**
 * @brief Linearly interpolates between a and b values using t.
 * 
 * @param a minimum value (t == 0.0)
 * @param b maximum value (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static constexpr double lerp(double a, double b, double t) noexcept { return std::fma(t, b, std::fma(-t, a, a)); }

/**
 * @brief Linearly interpolates between a and b values taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum value (t == 0.0)
 * @param b maximum value (t == 1.0)
 * @param dr target decay rate value
 * @param dt current delta time
 */
static float lerpDelta(float a, float b, float dr, float dt) noexcept { return lerp(b, a, std::exp(-dr * dt)); }
/**
 * @brief Linearly interpolates between a and b values taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum value (t == 0.0)
 * @param b maximum value (t == 1.0)
 * @param dr target decay rate value
 * @param dt current delta time
 */
static double lerpDelta(double a, double b, double dr, double dt) noexcept  { return lerp(b, a, std::exp(-dr * dt)); }

/**
 * @brief Converts seconds needed to reach 99% of the distance to the decay rate.
 * @details Use this function to calculate dt parameter for the lerpDelta().
 * @param time target time to convert in seconds
 */
static constexpr float secToDecRate(float time) noexcept  { return (float)M_LN100 / time; }
/**
 * @brief Converts seconds needed to reach 99% of the distance to the decay rate.
 * @details Use this function to calculate dt parameter for the lerpDelta().
 * @param time target time to convert in seconds
 */
static constexpr double secToDecRate(double time) noexcept  { return M_LN100 / time; }

/***********************************************************************************************************************
 * @brief Applies gain function to the x value.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target value to gain (0.0 - 1.0)
 * @param k gain factor
 */
static float gain(float x, float k) noexcept
{
	auto a = 0.5f * std::pow(2.0f * ((x < 0.5f) ? x : 1.0f - x), k);
	return (x < 0.5f) ? a : 1.0f - a;
}
/**
 * @brief Applies gain function to the x value.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target value to gain (0.0 - 1.0)
 * @param k gain factor
 */
static double gain(double x, double k) noexcept
{
	auto a = 0.5 * std::pow(2.0 * ((x < 0.5) ? x : 1.0 - x), k);
	return (x < 0.5) ? a : 1.0 - a;
}

/**
 * @brief Returns true if specified value is a power of 2.
 * 
 * @tparam T integer type of the value
 * @param v target integer value to check
 */
template <typename T>
static constexpr bool isPowerOf2(T v) noexcept
{
	return v > 0 && (v & (v - 1)) == 0;
}

} // namespace math