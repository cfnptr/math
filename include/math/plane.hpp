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
struct Plane
{
public:
	/**
	 * @brief Frustum plane count. (Box side count)
	 */
	static constexpr uint8 frustumCount = 6;
protected:
	float3 normal;
public:
	/**
	 * @brief Distance to the plane in 3D space.
	 */
	float distance;

	/**
	 * @brief Creates a new plane structure.
	 * 
	 * @param[in] normal target plane normal vector
	 * @param distance target distance to the plane
	 * @param normalize is normal vector should be normalized
	 */
	constexpr Plane(const float3& normal = float3::top, float distance = 0.0f, bool normalize = true) noexcept :
		normal(normalize ? math::normalize(normal) : normal), distance(distance) { }
	/**
	 * @brief Calculates a new plane from the triangle. (Polygon)
	 * @param[in] triangle target triangle (polygon)
	 */
	Plane(const Triangle& triangle) noexcept
	{
		normal = cross(triangle.p1 - triangle.p0,
			triangle.p2 - triangle.p0);
		if (length(normal) > 0.0f)
			normal = math::normalize(normal);
		distance = dot(normal, triangle.p0);
	}

	/**
	 * @brief Returns plane normal vector.
	 */
	constexpr const float3& getNormal() const noexcept { return normal; }
	/**
	 * @brief Sets plane normal vector.
	 * 
	 * @param[in] normal target plane normal vector
	 * @param normalize is normal vectorshould be normalized
	 */
	void setNormal(const float3& normal, bool normalize = true) noexcept
	{
		this->normal = normalize ? math::normalize(normal) : normal;
	}
	/**
	 * @brief Normalizes plane normal vector.
	 */
	void normalize() noexcept
	{
		auto l = length(normal);
		normal /= l;
		distance /= l;
	}

	constexpr bool operator==(const Plane& p) const noexcept { return normal == p.normal && distance == p.distance; }
	constexpr bool operator!=(const Plane& p) const noexcept { return normal != p.normal || distance != p.distance; }

	static const Plane left, right, bottom, top, back, front;
};

inline const Plane Plane::left = Plane(float3(-1.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::right = Plane(float3(1.0f, 0.0f, 0.0f), 0.0f, false);
inline const Plane Plane::bottom = Plane(float3(0.0f, -1.0f, 0.0f), 0.0f, false);
inline const Plane Plane::top = Plane(float3(0.0f, 1.0f, 0.0f), 0.0f, false);
inline const Plane Plane::back = Plane(float3(0.0f, 0.0f, -1.0f), 0.0f, false);
inline const Plane Plane::front = Plane(float3(0.0f, 0.0f, 1.0f), 0.0f, false);

/***********************************************************************************************************************
 * @brief Calculates distance between plane and point in 3D space.
 * 
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static constexpr float distance(const Plane& plane, const float3& point) noexcept
{
	return dot(plane.getNormal(), point) + plane.distance;
}
/**
 * @brief Calculates closest point on the plane to specified one.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static constexpr float3 closestPoint(const Plane& plane, const float3& point) noexcept
{
	return point - plane.getNormal() * distance(plane, point);
}

/**
 * @brief Calculates closest point on the triangle to specified one.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static float3 closestPoint(const Triangle& triangle, const float3& point) noexcept
{
	auto p = closestPoint(Plane(triangle), point);
	if (isInside(triangle, p))
		return p;

	auto ab = Line(triangle.p0, triangle.p1);
	auto bc = Line(triangle.p1, triangle.p2);
	auto ca = Line(triangle.p2, triangle.p0);
	auto c0 = closestPoint(ab, p);
	auto c1 = closestPoint(bc, p);
	auto c2 = closestPoint(ca, p);
	auto m0 = length2(p - c0);
	auto m1 = length2(p - c1);
	auto m2 = length2(p - c2);
	auto m = min(m0, m1, m2);

	if (m == m0)
		return c0;
	if (m == m1)
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
static void extractFrustumPlanes(const float4x4& frustum, Plane* planes) noexcept
{
	// Gribb & Hartmann method
	planes[0] = Plane(float3(frustum.c0.w + frustum.c0.x, frustum.c1.w + frustum.c1.x,
		frustum.c2.w + frustum.c2.x), frustum.c3.w + frustum.c3.x, false);
	planes[1] = Plane(float3(frustum.c0.w - frustum.c0.x, frustum.c1.w - frustum.c1.x,
		frustum.c2.w - frustum.c2.x), frustum.c3.w - frustum.c3.x, false);
	planes[2] = Plane(float3(frustum.c0.w - frustum.c0.y, frustum.c1.w - frustum.c1.y,
		frustum.c2.w - frustum.c2.y), frustum.c3.w - frustum.c3.y, false); // Flipped Vulkan NDC!
	planes[3] = Plane(float3(frustum.c0.w + frustum.c0.y, frustum.c1.w + frustum.c1.y,
		frustum.c2.w + frustum.c2.y), frustum.c3.w + frustum.c3.y, false); // Flipped Vulkan NDC!
	planes[4] = Plane(float3(frustum.c0.z,
		frustum.c1.z, frustum.c2.z), frustum.c3.z, false);
	planes[5] = Plane(float3(frustum.c0.w - frustum.c0.z, frustum.c1.w - frustum.c1.z,
		frustum.c2.w - frustum.c2.z), frustum.c3.w - frustum.c3.z, false);
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