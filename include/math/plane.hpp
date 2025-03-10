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
 * @brief Common infinite plane functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/line.hpp"
#include "math/matrix.hpp"
#include "math/triangle.hpp"

namespace math
{

/**
 * @brief Infinite plane container. (In 3D space)
 * @details Defined by a normal vector and distance to the plane.
 */
struct [[nodiscard]] Plane
{
public:
	/**
	 * @brief Frustum plane count. (Box side count)
	 */
	static constexpr uint8 frustumCount = 6;
protected:
	simd_f32_4 normDist = simd_f32_4::zero;
public:

	/**
	 * @brief Creates a new plane structure. (In 3D space)
	 * 
	 * @param normal target plane normal vector in 3D space
	 * @param distance target distance to the plane
	 * @param normalize is normal vector should be normalized
	 */
	Plane(simd_f32_4 normal, float distance = 0.0f, bool normalize = true) noexcept :
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
		normDist = simd_f32_4(normal, distance);
	}

	/**
	 * @brief Returns plane normal vector in 3D space.
	 */
	const simd_f32_4& getNormal() const noexcept { return normDist; }
	/**
	 * @brief Sets plane normal vector in 3D space.
	 * 
	 * @param normal target plane normal vector in 3D space
	 * @param normalize is normal vector should be normalized
	 */
	void setNormal(simd_f32_4 normal, bool normalize = true) noexcept
	{
		normDist = simd_f32_4(normalize ? normalize3(normal) : normal, normDist.getW());
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

	static const Plane left, right, bottom, top, back, front;
};

inline const Plane Plane::left = Plane(simd_f32_4(-1.0f, 0.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::right = Plane(simd_f32_4(1.0f, 0.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::bottom = Plane(simd_f32_4(0.0f, -1.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::top = Plane(simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::back = Plane(simd_f32_4(0.0f, 0.0f, -1.0f, 0.0f), 0.0f, false);
inline const Plane Plane::front = Plane(simd_f32_4(0.0f, 0.0f, 1.0f, 0.0f), 0.0f, false);

/***********************************************************************************************************************
 * @brief Returns distance between plane and point in 3D space.
 * 
 * @param[in] plane target plane to use
 * @param point target point in 3D space
 */
static float distance3(const Plane& plane, simd_f32_4 point) noexcept
{
	return dot3(plane.getNormal(), point) + plane.getDistance();
}
/**
 * @brief Returns closest point on the plane to specified one in 3D space.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static simd_f32_4 closestPoint(const Plane& plane, simd_f32_4 point) noexcept
{
	return point - plane.getNormal() * simd_f32_4(distance3(plane, point));
}

/**
 * @brief Returns closest point on the triangle to specified one in 3D space.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static simd_f32_4 closestPoint(const Triangle& triangle, simd_f32_4 point) noexcept
{
	auto p = closestPoint(Plane(triangle), point);
	if (isInside(triangle, p))
		return p;

	auto ab = Line(triangle.p0, triangle.p1), bc = Line(triangle.p1, triangle.p2), ca = Line(triangle.p2, triangle.p0);
	auto c0 = closestPoint(ab, p), c1 = closestPoint(bc, p), c2 = closestPoint(ca, p);
	auto v = simd_f32_4(lengthSq3(p - c0), lengthSq3(p - c1), lengthSq3(p - c2));
	auto m = min3(v);

	if (m == v.getX())
		return c0;
	if (m == v.getY())
		return c1;
	return c2;
}

/***********************************************************************************************************************
 * @brief Extracts projection matrix frustum planes.
 * @warning Returned planes are unnormalized! Use @ref normalizePlanes().
 *
 * @param[in] frustum target projection matrix
 * @param[out] planes frustum plane array (6 planes)
 */
static void extractFrustumPlanes(const simd_f32_4x4& frustum, Plane* planes) noexcept
{
	auto t = transpose4x4(frustum);
	auto c0W = t.c0.getW(), c1W = t.c1.getW(), c2W = t.c2.getW(), c3W = t.c3.getW();
	
	// Gribb & Hartmann method
	planes[0] = Plane(simd_f32_4(t.c3 + t.c0, 0.0f), c3W + c0W, false);
	planes[1] = Plane(simd_f32_4(t.c3 - t.c0, 0.0f), c3W - c0W, false);
	planes[2] = Plane(simd_f32_4(t.c3 - t.c1, 0.0f), c3W - c1W, false); // Flipped Vulkan NDC!
	planes[3] = Plane(simd_f32_4(t.c3 + t.c1, 0.0f), c3W + c1W, false); // Flipped Vulkan NDC!
	planes[4] = Plane(simd_f32_4(t.c2,        0.0f),       c2W, false);
	planes[5] = Plane(simd_f32_4(t.c3 - t.c2, 0.0f), c3W - c2W, false);
}
/**
 * @brief Normalizes specified planes.
 *
 * @param[out] planes target plane array
 * @param planeCount plane array size
 */
static void normalizePlanes(Plane* planes, psize planeCount) noexcept
{
	for (psize i = 0; i < planeCount; i++)
		planes[i].normalize();
}

} // namespace math