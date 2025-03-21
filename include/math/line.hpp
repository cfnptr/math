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

#pragma once
#include "math/vector.hpp"

/***********************************************************************************************************************
 * @file
 * @brief Common line functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

namespace math
{

/**
 * @brief Line structure. (In 3D space)
 * @details Defined by a start and end points in the space.
 */
struct [[nodiscard]] Line
{
	/**
	 * @brief Line start point in 3D space.
	 */
	f32x4 start = f32x4::zero;
	/**
	 * @brief Line end point in 3D space.
	 */
	f32x4 end = f32x4::zero;

	/**
	 * @brief Creates a new line structure. (In 3D space)
	 * 
	 * @param start target line start point in the space
	 * @param end target line end point in the space
	 */
	Line(f32x4 start, f32x4 end) noexcept : start(start), end(end) { }
	/**
	 * @brief Creates a new zero size line structure.
	 */
	Line() = default;

	/**
	 * @brief Returns line direction vector in 3D space.
	 * @param normalize is direction vector should be normalized
	 */
	f32x4 getDirection(bool normalize = true) const noexcept
	{
		return normalize ? normalize3(end - start) : end - start;
	}

	Line operator*(f32x4 v) const noexcept { return Line(start * v, end * v); }
	Line operator/(f32x4 v) const noexcept { return Line(start / v, end / v); }
	Line operator+(f32x4 v) const noexcept { return Line(start + v, end + v); }
	Line operator-(f32x4 v) const noexcept { return Line(start - v, end - v); }
	Line& operator*=(f32x4 v) noexcept { start *= v; end *= v; return *this; }
	Line& operator/=(f32x4 v) noexcept { start /= v; end /= v; return *this; }
	Line& operator+=(f32x4 v) noexcept { start += v; end += v; return *this; }
	Line& operator-=(f32x4 v) noexcept { start -= v; end -= v; return *this; }
	bool operator==(const Line& v) const noexcept { return !memcmp(this, &v, sizeof(Line)); }
	bool operator!=(const Line& v) const noexcept { return memcmp(this, &v, sizeof(Line)); }
};

/**
 * @brief Returns closest point on line to the specified one in 3D space.
 * 
 * @param[in] line target line to use
 * @param point target point in 3D space
 */
static f32x4 closestPoint(const Line& line, f32x4 point) noexcept
{
	auto a = line.start, d = line.getDirection(false);
	auto t = dot3(point - a, d) / dot3(d, d);
	return fma(d, f32x4(std::clamp(t, 0.0f, 1.0f)), a);
}
/**
 * @brief Returns closest point on line to the specified one in 3D space.
 *
 * @param[in] line target line to use
 * @param point target point in 3D space
 * @param[out] t distance to the closest point
 */
static f32x4 closestPoint(const Line& line, f32x4 point, float& t) noexcept
{
	auto a = line.start, d = line.getDirection(false);
	t = dot3(point - a, d) / dot3(d, d);
	return fma(d, f32x4(std::clamp(t, 0.0f, 1.0f)), a);
}

} // namespace math