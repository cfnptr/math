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
struct [[nodiscard]] Triangle
{
	/**
	 * @brief Triangle point count. (Polygon)
	 */
	static constexpr int32 pointCount = 3;

	simd_f32_4 p0 = simd_f32_4::zero; /**< First triangle vertex position. */
	simd_f32_4 p1 = simd_f32_4::zero; /**< Second triangle vertex position. */
	simd_f32_4 p2 = simd_f32_4::zero; /**< Third triangle vertex position. */

	/**
	 * @brief Creates a new triangle (polygon) structure. (In 3D space)
	 *
	 * @param p0 first triangle vertex position in 3D space
	 * @param p1 second triangle vertex position in 3D space
	 * @param p2 third triangle vertex position in 3D space
	 */
	Triangle(simd_f32_4 p0, simd_f32_4 p1, simd_f32_4 p2) noexcept : p0(p0), p1(p1), p2(p2) { }
	/**
	 * @brief Creates a new zero size triangle (polygon) structure.
	 */
	Triangle() = default;

	Triangle operator*(simd_f32_4 v) const noexcept { return Triangle(p0 * v, p1 * v, p2 * v); }
	Triangle operator/(simd_f32_4 v) const noexcept { return Triangle(p0 / v, p1 / v, p2 / v); }
	Triangle operator+(simd_f32_4 v) const noexcept { return Triangle(p0 + v, p1 + v, p2 + v); }
	Triangle operator-(simd_f32_4 v) const noexcept { return Triangle(p0 - v, p1 - v, p2 - v); }
	Triangle& operator*=(simd_f32_4 v) noexcept { p0 *= v; p1 *= v; p2 *= v; return *this; }
	Triangle& operator/=(simd_f32_4 v) noexcept { p0 /= v; p1 /= v; p2 /= v; return *this; }
	Triangle& operator+=(simd_f32_4 v) noexcept { p0 += v; p1 += v; p2 += v; return *this; }
	Triangle& operator-=(simd_f32_4 v) noexcept { p0 -= v; p1 -= v; p2 -= v; return *this; }
};

/**
 * @brief Returns true if point is inside the triangle in 3D space.
 *
 * @param[in] sphere target triangle to check
 * @param point target point in 3D space
 */
static bool isInside(const Triangle& triangle, simd_f32_4 point) noexcept
{
	auto p0 = triangle.p0 - point, p1 = triangle.p1 - point, p2 = triangle.p2 - point;
	auto u = cross3(p1, p2), v = cross3(p2, p0), w = cross3(p0, p1);
	if (dot3(u, v) < 0.0f || dot3(u, w) < 0.0f)
		return false;
	return true;
}

/**
 * @brief Returns triangle barycentric in 3D space.
 * @details Way of expressing the position of a point relative to a triangle.
 *
 * @param[in] triangle target triangle to use
 * @param point target point in 3D space
 */
static simd_f32_4 calcBarycentric(const Triangle& triangle, simd_f32_4 point) noexcept
{
	// Cramer's rule
	auto p0 = triangle.p0;
	auto v0 = triangle.p1 - p0, v1 = triangle.p2 - p0, v2 = point - p0;
	auto d00 = dot3(v0, v0), d01 = dot3(v0, v1), d11 = dot3(v1, v1);
	auto d20 = dot3(v2, v0), d21 = dot3(v2, v1);
	auto invDenom = 1.0f / (d00 * d11 - d01 * d01);
	auto v = (d11 * d20 - d01 * d21) * invDenom;
	auto w = (d00 * d21 - d01 * d20) * invDenom;
	return simd_f32_4(1.0f - v - w, v, w, 0.0f);
}

} // namespace math