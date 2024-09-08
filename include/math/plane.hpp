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
 */

#pragma once
#include "math/line.hpp"
#include "math/matrix.hpp"
#include "math/triangle.hpp"

namespace math
{

using namespace std;

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
	inline static const uint8 frustumCount = 6;
private:
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
	Plane(const float3& normal = float3::top, float distance = 0.0f, bool normalize = true) noexcept
	{
		if (normalize)
			this->normal = math::normalize(normal);
		else
			this->normal = normal;
		this->distance = distance;
	}
	/**
	 * @brief Calculates a new plane from the triangle. (Polygon)
	 * @param[in] triangle target triangle (polygon)
	 */
	Plane(const Triangle& triangle) noexcept
	{
		normal = cross(triangle.points[1] - triangle.points[0],
			triangle.points[2] - triangle.points[0]);
		if (length(normal) > 0.0f)
			normal = math::normalize(normal);
		distance = dot(normal, triangle.points[0]);
	}

	/**
	 * @brief Returns plane normal vector.
	 */
	const float3& getNormal() const noexcept { return normal; }
	/**
	 * @brief Sets plane normal vector.
	 * 
	 * @param[in] normal target plane normal vector
	 * @param normalize is normal vectorshould be normalized
	 */
	void setNormal(const float3& normal, bool normalize = true) noexcept
	{
		if (normalize)
			this->normal = math::normalize(normal);
		else
			this->normal = normal;
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

	static const Plane left, right, bottom, top, back, front;
};

/***********************************************************************************************************************
 * @brief Calculates distance between plane and point in 3D space.
 * 
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static float distance(const Plane& plane, const float3& point) noexcept
{
	return dot(plane.getNormal(), point) + plane.distance;
}
/**
 * @brief Calculates closest point on the plane to specified one.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static float3 closestPoint(const Plane& plane, const float3& point) noexcept
{
	return point - plane.getNormal() * distance(plane, point);
}

/**
 * @brief Calculates closest point on the triangle to specified one.
 *
 * @param[in] plane target plane to use
 * @param[in] point target point in 3D space
 */
static float3 closestPoint(const Triangle& triangle, const float3& point) noexcept;

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