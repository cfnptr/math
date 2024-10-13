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
 * @brief Axis Aligned Bounding Box functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/ray.hpp"
#include "math/plane.hpp"

namespace math
{

using namespace std;

/**
 * @brief Axis Aligned Bounding Box structure. (AABB)
 * 
 * @details
 * A simple and efficient way to represent the boundaries of a 3D or 2D object for collision detection or 
 * spatial queries in game development and computer graphics. The sides of the bounding box are aligned with the 
 * coordinate axes (e.g., X, Y, and Z axes in 3D space). This means that the edges of the box do not rotate with 
 * the object but remain parallel to the axes. Bounding box defines a rectangular (2D) or cuboid (3D) volume that 
 * surrounds an object, used to approximate the object's shape for efficient calculations.
 */
struct Aabb
{
protected:
	float3 min, max;
public:
	/**
	 * @brief Creates a new Axis Aligned Bounding Box. (AABB)
	 * 
	 * @param[in] min minimum bounding box corner position in the space
	 * @param[in] max maximum bounding box corner position in the space
	 */
	constexpr Aabb(const float3& min = float3(0.0f), const float3& max = float3(0.0f)) noexcept : min(min), max(max)
	{
		assert(min <= max);
	}

	/**
	 * @brief Returns minimum AABB corner position in the space.
	 * @details The point that has the smallest values for all axes.
	 */
	const float3& getMin() const noexcept { return min; }
	/**
	 * @brief Returns maximum AABB corner position in the space.
	 * @details The point that has the biggest values for all axes.
	 */
	const float3& getMax() const noexcept { return max; }

	/**
	 * @brief Sets minimum AABB corner position in the space.
	 * @details See the @ref getMin().
	 * @param[in] min minimum bounding box corner position in the space
	 */
	void setMin(const float3& min) noexcept
	{
		assert(min <= this->max);
		this->min = min;
	}
	/**
	 * @brief Sets maximum AABB corner position in the space.
	 * @details See the @ref setMax().
	 * @param[in] max maximum bounding box corner position in the space
	 */
	void setMax(const float3& max) noexcept
	{
		assert(max >= this->min);
		this->max = max;
	}
	/**
	 * @brief Sets minimum and maximum AABB corner position in the space.
	 * @details See the @ref getMin() and @ref getMax().
	 * 
	 * @param[in] min minimum bounding box corner position in the space
	 * @param[in] max maximum bounding box corner position in the space
	 */
	void set(const float3& min, const float3& max) noexcept
	{
		assert(min <= max);
		this->min = min;
		this->max = max;
	}
	
	/**
	 * @brief Sets size and position of the bounding box.
	 * 
	 * @param[in] size target size of the bounding box
	 * @param[in] position target position of the bounding box in space
	 */
	void setSize(const float3& size, const float3& position = float3(0.0f)) noexcept
	{
		assert(size >= 0.0f);
		auto extent = size * 0.5f;
		min = position - extent;
		max = position + extent;
	}

	/**
	 * @brief Returns size of the bounding box.
	 */
	constexpr float3 getSize() const noexcept { return max - min; }
	/**
	 * @brief Returns position of the bounding box.
	 */
	constexpr float3 getPosition() const noexcept { return (min + max) * 0.5f; }

	/*******************************************************************************************************************
	 * @brief Sets extent and position of the bounding box.
	 * 
	 * @param[in] extent target extent of the bounding box (half size)
	 * @param[in] position target position of the bounding box in space
	 */
	void setExtent(const float3& extent, const float3& position = float3(0.0f)) noexcept
	{
		assert(extent >= 0.0f);
		min = position - extent;
		max = position + extent;
	}

	/**
	 * @brief Returns extent and position of the bounding box.
	 * 
	 * @param[out] extent target extent of the bounding box (half size)
	 * @param[out] position target position of the bounding box in space
	 */
	void getExtent(float3& extent, float3& position) const noexcept
	{
		extent = (max - min) * 0.5f;
		position = min + extent;
	}
	/**
	 * @brief Returns extent of the bounding box. (half size)
	 */
	constexpr float3 getExtent() const noexcept { return (max - min) * 0.5f; }

	/**
	 * @brief Extends bounding box min and max corner positions.
	 * @param[in] point target point to include into the bounding box
	 */
	void extend(const float3& point) noexcept
	{
		min = math::min(min, point);
		max = math::max(max, point); 
	}
	/**
	 * @brief Extends bounding box min and max corner positions.
	 * @param[in] aabb target AABB to include into the bounding box
	 */
	void extend(const Aabb& aabb) noexcept
	{
		min = math::min(min, aabb.min);
		max = math::max(max, aabb.max); 
	}

	/**
	 * @brief Calculates area of the AABB.
	 */
	constexpr float calcArea() const noexcept
	{
		auto extent = max - min;
		return extent.x * extent.y + extent.y * extent.z + extent.z * extent.x;
	}

	constexpr Aabb operator*(const float3& v) const noexcept { return Aabb(min * v, max * v); }
	constexpr Aabb operator/(const float3& v) const noexcept { return Aabb(min / v, max / v); }
	constexpr Aabb operator+(const float3& v) const noexcept { return Aabb(min + v, max + v); }
	constexpr Aabb operator-(const float3& v) const noexcept { return Aabb(min - v, max - v); }
	Aabb& operator*=(const float3& v) noexcept { min *= v; max *= v; return *this; }
	Aabb& operator/=(const float3& v) noexcept { min /= v; max /= v; return *this; }
	Aabb& operator+=(const float3& v) noexcept { min += v; max += v; return *this; }
	Aabb& operator-=(const float3& v) noexcept { min -= v; max -= v; return *this; }
	constexpr bool operator==(const Aabb& v) const noexcept { return min == v.min && max == v.max; }
	constexpr bool operator!=(const Aabb& v) const noexcept { return min != v.min || max != v.max; }
	constexpr bool operator<(const Aabb& v) const noexcept { return min < v.min && max < v.max; }
	constexpr bool operator>(const Aabb& v) const noexcept { return min > v.min && max > v.max; }
	constexpr bool operator<=(const Aabb& v) const noexcept { return min <= v.min && max <= v.max; }
	constexpr bool operator>=(const Aabb& v) const noexcept { return min >= v.min && max >= v.max; }
	
	static const Aabb zero, one, two, half;
};

inline const Aabb Aabb::zero = Aabb(float3(0.0f), float3(0.0f));
inline const Aabb Aabb::one = Aabb(float3(-0.5f), float3(0.5f));
inline const Aabb Aabb::two = Aabb(float3(-1.0f), float3(1.0f));
inline const Aabb Aabb::half = Aabb(float3(-0.25f), float3(0.25f));

/**
 * @brief Returns true if first AABB binary representation is less than the second.
 * 
 * @param[in] a first AABB to binary compare
 * @param[in] b secong AABB to binary compare
 */
static bool isBinaryLess(const Aabb& a, const Aabb& b) noexcept { return memcmp(&a, &b, sizeof(float3) * 2) < 0; }

/***********************************************************************************************************************
 * @brief Returns true if point is inside the AABB.
 * 
 * @param[in] aabb target AABB to check
 * @param[in] point target point in the space
 */
static bool isInside(const Aabb& aabb, const float3& point) noexcept
{
	return point >= aabb.getMin() && point <= aabb.getMax();
}
/**
 * @brief Returns closest point inside AABB to the specified one.
 *
 * @param[in] aabb target AABB to use
 * @param[in] point target point in the space
 */
static float3 closestPoint(const Aabb& aabb, const float3& point) noexcept
{
	return clamp(point, aabb.getMin(), aabb.getMax());
}

/**
 * @brief Calculates where ray intersects the AABB.
 * @return Distance to the intersection points.
 *
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space
 */
float2 raycast2(const Aabb& aabb, const Ray& ray) noexcept;
/**
 * @brief Calculates where ray intersects the AABB. (Ray is inversed!)
 * @return Distance to the intersection points.
 *
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space (inversed)
 */
float2 raycast2I(const Aabb& aabb, const Ray& ray) noexcept;

/**
 * @brief Calculates where ray intersects the AABB.
 * @return Distance to the first intersection point.
 *
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space
 */
float raycast1(const Aabb& aabb, const Ray& ray) noexcept;
/**
 * @brief Calculates where ray intersects the AABB. (Ray is inversed!)
 * @return Distance to the first intersection point.
 *
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space (inversed)
 */
float raycast1I(const Aabb& aabb, const Ray& ray) noexcept;

/**
 * @brief Returns true if ray is intersecting the AABB.
 * @param raycastDists resulting raycast distances
 */
static bool isAabbIntersected(float2 raycastDists) noexcept
{
	// If tMax < 0.0f, ray is intersecting AABB, but whole AABB is behind us.
	return raycastDists.x <= raycastDists.y && raycastDists.y >= 0.0f;
}

/**
 * @brief Returns true if ray intersects the AABB.
 * 
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space
 */
static bool raycast(const Aabb& aabb, const Ray& ray) noexcept
{
	return isAabbIntersected(raycast2(aabb, ray));
}
/**
 * @brief Returns true if ray intersects the AABB. (Ray is inversed!)
 *
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space (inversed)
 */
static bool raycastI(const Aabb& aabb, const Ray& ray) noexcept
{
	return isAabbIntersected(raycast2I(aabb, ray));
}

/**
 * @brief Returns true if one AABB intersects another.
 *
 * @param[in] a first AABB to check
 * @param[in] b second AABB to chech
 */
static bool isIntersected(const Aabb& a, const Aabb& b) noexcept
{
	return a.getMin() <= b.getMax() && a.getMax() >= b.getMin();
}

/**
 * @brief Returns true if triangle intersects the AABB.
 * @details Usefull for a fast 3D model voxelization.
 *
 * @param[in] center target AABB center point in the space
 * @param[in] extent target AABB extent (half size)
 * @param[in] triangle target triangle in the space
 */
bool isAabbIntersected(const float3& center, const float3& extent, const Triangle& triangle) noexcept;

/**
 * @brief Returns true if AABB is behind the frustum planes.
 * 
 * @details
 * Usefull for a fast view frustum culling. It is a technique used in 3D rendering and game engines to improve 
 * performance by avoiding the rendering of objects that are outside the camera's view, or view frustum. The view 
 * frustum is a truncated pyramid-shaped volume that represents everything the camera can potentially see in the 
 * scene, based on its position, orientation, and field of view.
 *
 * @param[in] aabb target AABB to check
 * @param[in] model AABB transformation matrix
 * @param[in] planes target frustum planes
 * @param[in] planeCount frustum plane count
 */
bool isBehindFrustum(const Aabb& aabb, const float4x4& model,
	const Plane* planes, uint8 planeCount = Plane::frustumCount) noexcept;

} // namespace math