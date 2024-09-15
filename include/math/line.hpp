// Copyright 2022-2024 Nikita Fediuchin. All rights reserved.
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

#pragma once
#include "math/vector.hpp"

/***********************************************************************************************************************
 * @file
 * @brief Common line functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

namespace math
{

using namespace std;

/**
 * @brief Line structure. (In 3D space)
 * @details Defined by a start and end points in the space.
 */
struct Line
{
	/**
	 * @brief Line start point in the space.
	 */
	float3 start = float3(0.0f);
	/**
	 * @brief Line end point in the space.
	 */
	float3 end = float3(0.0f);

	/**
	 * @brief Creates a new line structure.
	 * 
	 * @param[in] start target line start point in the space
	 * @param[in] end target line end point in the space
	 */
	Line(const float3& start, const float3& end) noexcept { this->start = start; this->end = end; }
	/**
	 * @brief Creates a new zero size line structure.
	 */
	Line() = default;

	/**
	 * @brief Returns line direction vector. (Unnormalized)
	 */
	float3 getVector() const noexcept { return end - start; }
	/**
	 * @brief Returns line direction vector. (Normalized)
	 */
	float3 getVectorNorm() const noexcept { return normalize(end - start); }

	Line operator*(const float3& v) const noexcept { return Line(start * v, end * v); }
	Line operator/(const float3& v) const noexcept { return Line(start / v, end / v); }
	Line operator+(const float3& v) const noexcept { return Line(start + v, end + v); }
	Line operator-(const float3& v) const noexcept { return Line(start - v, end - v); }

	Line& operator*=(const float3& v) noexcept { start *= v; end *= v; return *this; }
	Line& operator/=(const float3& v) noexcept { start /= v; end /= v; return *this; }
	Line& operator+=(const float3& v) noexcept { start += v; end += v; return *this; }
	Line& operator-=(const float3& v) noexcept { start -= v; end -= v; return *this; }
};

/**
 * @brief Returns closest point on line to the specified one.
 * 
 * @param[in] line target line to use
 * @param[in] point target point in the space
 */
static float3 closestPoint(const Line& line, const float3& point) noexcept
{
	auto a = line.start;
	auto v = line.getVector();
	auto t = dot(point - a, v) / dot(v, v); 
	return a + v * std::clamp(t, 0.0f, 1.0f);
}
/**
 * @brief Returns closest point on line to the specified one.
 *
 * @param[in] line target line to use
 * @param[in] point target point in the space
 * @param[out] t distance to the closest point
 */
static float3 closestPoint(const Line& line, const float3& point, float& t) noexcept
{
	auto a = line.start;
	auto v = line.getVector();
	t = dot(point - a, v) / dot(v, v); 
	return a + v * std::clamp(t, 0.0f, 1.0f);
}

} // namespace math