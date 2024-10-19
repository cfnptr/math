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
 * @brief Common sphere functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/aabb.hpp"

namespace math
{

/**
 * @brief Sphere structure. (In 3D space)
 * @details Defined by a position point and radius.
 */
struct Sphere
{
	float3 position;
	float radius;

	/**
	 * @brief Creates a new sphere structure.
	 *
	 * @param radius target sphere radius
	 * @param[in] position sphere position in 3D space
	 */
	constexpr Sphere(float radius = 0.0f, const float3& position = float3(0.0f)) noexcept :
		position(position), radius(radius) { }

	constexpr bool operator==(const Sphere& s) const noexcept { return position == s.position && radius == s.radius; }
	constexpr bool operator!=(const Sphere& s) const noexcept { return position != s.position || radius != s.radius; }

	static const Sphere one, two, half;
};

inline const Sphere Sphere::one = Sphere(0.5f);
inline const Sphere Sphere::two = Sphere(1.0f);
inline const Sphere Sphere::half = Sphere(0.25f);

/**
 * @brief Returns true if point is inside the sphere.
 *
 * @param[in] sphere target sphere to check
 * @param[in] point target point in the space
 */
static bool isInside(const Sphere& sphere, const float3& point) noexcept
{
	auto difference = sphere.position - point;
  	return length2(difference) < sphere.radius * sphere.radius;
}

/**
 * @brief Calculates closest point on sphere to the specified one.
 *
 * @param[in] sphere target sphere to use
 * @param[in] point target point in 3D space
 */
static float3 closestPoint(const Sphere& sphere, const float3& point) noexcept
{
    auto sphereToPoint = normalize(point - sphere.position);
    return sphere.position + sphereToPoint * sphere.radius;
}

/**
 * @brief Returns true if one sphere intersects another.
 *
 * @param[in] a first sphere to check
 * @param[in] b second sphere to chech
 */
static bool isIntersected(const Sphere& a, const Sphere& b) noexcept
{
    auto d = a.position - b.position;
    auto s = a.radius + b.radius;
    return length2(d) <= s * s;
}
/**
 * @brief Returns true if sphere intersects AABB.
 *
 * @param[in] a target sphere to check
 * @param[in] b target AABB to chech
 */
static bool isIntersected(const Sphere& a, const Aabb& b) noexcept
{
	auto c = closestPoint(b, a.position);
	auto d2 = length2(a.position - c);
	return d2 < a.radius * a.radius;
}

} // namespace math