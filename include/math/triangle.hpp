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

/***********************************************************************************************************************
 * @file
 * @brief Common triangle (polygon) functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

/**
 * @brief Triangle or polygon structure. (In 3D space)
 * @details Defined by three points in 3D space.
 */
struct Triangle
{
	/**
	 * @brief Triangle point count. (Polygon)
	 */
	static constexpr int32 pointCount = 3;

	float3 p0; /**< First triangle vertex position. */
	float3 p1; /**< Second triangle vertex position. */
	float3 p2; /**< Third triangle vertex position. */

	/**
	 * @brief Creates a new triangle (polygon) structure.
	 *
	 * @param[in] p0 first triangle vertex position in 3D space
	 * @param[in] p1 second triangle vertex position in 3D space
	 * @param[in] p2 third triangle vertex position in 3D space
	 */
	constexpr Triangle(const float3& p0, const float3& p1, const float3& p2) noexcept : p0(p0), p1(p1), p2(p2) { }
	/**
	 * @brief Creates a new zero size triangle (polygon) structure.
	 */
	constexpr Triangle() = default;

	constexpr Triangle operator*(const float3& v) const noexcept { return Triangle(p0 * v, p1 * v, p2 * v); }
	constexpr Triangle operator/(const float3& v) const noexcept { return Triangle(p0 / v, p1 / v, p2 / v); }
	constexpr Triangle operator+(const float3& v) const noexcept { return Triangle(p0 + v, p1 + v, p2 + v); }
	constexpr Triangle operator-(const float3& v) const noexcept { return Triangle(p0 - v, p1 - v, p2 - v); }
	Triangle& operator*=(const float3& v) noexcept { p0 *= v; p1 *= v; p2 *= v; return *this; }
	Triangle& operator/=(const float3& v) noexcept { p0 /= v; p1 /= v; p2 /= v; return *this; }
	Triangle& operator+=(const float3& v) noexcept { p0 += v; p1 += v; p2 += v; return *this; }
	Triangle& operator-=(const float3& v) noexcept { p0 -= v; p1 -= v; p2 -= v; return *this; }
	constexpr bool operator==(const Triangle& t) const noexcept { return p0 == t.p0 && p1 == t.p1 && p2 == t.p2; }
	constexpr bool operator!=(const Triangle& t) const noexcept { return p0 != t.p0 || p1 != t.p1 || p2 != t.p2; }
};

/**
 * @brief Returns true if point is inside the triangle.
 *
 * @param[in] sphere target triangle to check
 * @param[in] point target point in the space
 */
static constexpr bool isInside(const Triangle& triangle, const float3& point) noexcept
{
	auto p0 = triangle.p0 - point;
	auto p1 = triangle.p1 - point;
	auto p2 = triangle.p2 - point;
	auto u = cross(p1, p2), v = cross(p2, p0), w = cross(p0, p1);
	if (dot(u, v) < 0.0f || dot(u, w) < 0.0f)
		return false;
	return true;
}

/**
 * @brief Calculates triangle barycentric.
 * @details Way of expressing the position of a point relative to a triangle.
 *
 * @param[in] triangle target triangle to use
 * @param[in] point target point in space
 */
static constexpr float3 calcBarycentric(const Triangle& triangle, const float3& point) noexcept
{
	// Cramer's rule
	auto p0 = triangle.p0;
	auto v0 = triangle.p1 - p0;
	auto v1 = triangle.p2 - p0;
	auto v2 = point - p0;
	auto d00 = dot(v0, v0), d01 = dot(v0, v1), d11 = dot(v1, v1);
	auto d20 = dot(v2, v0), d21 = dot(v2, v1);
	auto invDenom = 1.0f / (d00 * d11 - d01 * d01);
	auto v = (d11 * d20 - d01 * d21) * invDenom;
	auto w = (d00 * d21 - d01 * d20) * invDenom;
	return float3(1.0f - v - w, v, w);
}

} // namespace math