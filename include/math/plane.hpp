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
 * @brief Common infinite plane functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/line.hpp"
#include "math/triangle.hpp"

namespace math
{

/**
 * @brief Infinite plane container. (In 3D space)
 * @details Defined by a normal vector and distance to the plane.
 */
struct [[nodiscard]] Plane
{

protected:
	f32x4 normDist = f32x4::zero;
public:

	/**
	 * @brief Creates a new plane structure. (In 3D space)
	 * 
	 * @param normal target plane normal vector in 3D space
	 * @param distance target distance to the plane
	 * @param normalize is normal vector should be normalized
	 */
	Plane(f32x4 normal, float distance = 0.0f, bool normalize = true) noexcept :
		normDist(normalize ? normalize3(normal) : normal) { normDist.setW(distance); }
	/**
	 * @brief Creates a new empty plane structure.
	 */
	Plane() = default;

	/**
	 * @brief Calculates a new plane from the triangle. (Polygon)
	 * @param[in] triangle target triangle (polygon)
	 */
	Plane(const Triangle& triangle) noexcept
	{
		auto normal = cross3(triangle.p1 - triangle.p0, triangle.p2 - triangle.p0);
		if (length3(normal) > 0.0f)
			normal = normalize3(normal);
		auto distance = dot3(normal, triangle.p0);
		normDist = f32x4(normal, distance);
	}

	/**
	 * @brief Returns plane normal vector in 3D space.
	 */
	f32x4 getNormal() const noexcept { return normDist; }
	/**
	 * @brief Sets plane normal vector in 3D space.
	 * 
	 * @param normal target plane normal vector in 3D space
	 * @param normalize is normal vector should be normalized
	 */
	void setNormal(f32x4 normal, bool normalize = true) noexcept
	{
		normDist = f32x4(normalize ? normalize3(normal) : normal, normDist.getW());
	}

	/**
	 * @brief Returns distance to the plane.
	 */
	float getDistance() const noexcept { return normDist.getW(); }
	/**
	 * @brief Sets distance to the plane.
	 * @param distance target distance to the plane
	 */
	void setDistance(float distance) noexcept { return normDist.setW(distance); }

	/**
	 * @brief Normalizes plane normal vector.
	 */
	void normalize() noexcept { normDist /= length3(normDist); }

	bool operator==(const Plane& v) const noexcept { return !memcmp(this, &v, sizeof(Plane)); }
	bool operator!=(const Plane& v) const noexcept { return memcmp(this, &v, sizeof(Plane)); }

	static const Plane left, right, bottom, top, back, front;
};

inline const Plane Plane::left = Plane(f32x4(-1.0f, 0.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::right = Plane(f32x4(1.0f, 0.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::bottom = Plane(f32x4(0.0f, -1.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::top = Plane(f32x4(0.0f, 1.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::back = Plane(f32x4(0.0f, 0.0f, -1.0f, 0.0f), 0.0f, false);
inline const Plane Plane::front = Plane(f32x4(0.0f, 0.0f, 1.0f, 0.0f), 0.0f, false);

/***********************************************************************************************************************
 * @brief Returns distance between plane and point in 3D space.
 * 
 * @param[in] plane target plane to use
 * @param point target point in 3D space
 */
static float distance3(const Plane& plane, f32x4 point) noexcept
{
	return dot3(plane.getNormal(), point) + plane.getDistance();
}
/**
 * @brief Returns closest point on the plane to specified one in 3D space.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static f32x4 closestPoint(const Plane& plane, f32x4 point) noexcept
{
	return point - plane.getNormal() * f32x4(distance3(plane, point));
}

/**
 * @brief Returns closest point on the triangle to specified one in 3D space.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static f32x4 closestPoint(const Triangle& triangle, f32x4 point) noexcept
{
	auto p = closestPoint(Plane(triangle), point);
	if (isInside(triangle, p))
		return p;

	auto ab = Line(triangle.p0, triangle.p1), bc = Line(triangle.p1, triangle.p2), ca = Line(triangle.p2, triangle.p0);
	auto c0 = closestPoint(ab, p), c1 = closestPoint(bc, p), c2 = closestPoint(ca, p);
	auto v = f32x4(lengthSq3(p - c0), lengthSq3(p - c1), lengthSq3(p - c2));
	auto m = min3(v);

	if (m == v.getX())
		return c0;
	if (m == v.getY())
		return c1;
	return c2;
}

} // namespace math