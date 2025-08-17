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
 * @brief Axis Aligned Bounding Box functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/ray.hpp"
#include "math/plane.hpp"

// TODO: Port more Jolt optimized BBox functions.

namespace math
{

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
struct [[nodiscard]] Aabb
{
protected:
	f32x4 min, max;
public:
	/**
	 * @brief Creates a new Axis Aligned Bounding Box in 3D space. (AABB)
	 * 
	 * @param min minimum bounding box corner position in 3D space
	 * @param max maximum bounding box corner position in 3d space
	 */
	Aabb(f32x4 min = f32x4::zero, f32x4 max = f32x4::zero) noexcept : min(min), max(max)
	{
		assert(areAllTrue(u32x4(min <= max, UINT32_MAX)));
	}

	/**
	 * @brief Returns minimum AABB corner position in 3D space.
	 * @details The point that has the smallest values for all axes.
	 */
	f32x4 getMin() const noexcept { return min; }
	/**
	 * @brief Returns maximum AABB corner position in 3D space.
	 * @details The point that has the biggest values for all axes.
	 */
	f32x4 getMax() const noexcept { return max; }

	/**
	 * @brief Sets minimum AABB corner position in 3D space.
	 * @details See the @ref getMin().
	 * @param min minimum bounding box corner position in 3D space
	 */
	void setMin(f32x4 min) noexcept
	{
		assert(areAllTrue(u32x4(min <= this->max, UINT32_MAX)));
		this->min = min;
	}
	/**
	 * @brief Sets maximum AABB corner position in 3D space.
	 * @details See the @ref setMax().
	 * @param max maximum bounding box corner position in 3D space
	 */
	void setMax(f32x4 max) noexcept
	{
		assert(areAllTrue(u32x4(this->min <= max, UINT32_MAX)));
		this->max = max;
	}

	/**
	 * @brief Sets minimum and maximum AABB corner position in 3D space.
	 * @details See the @ref getMin() and @ref getMax().
	 * 
	 * @param min minimum bounding box corner position in 3D space
	 * @param max maximum bounding box corner position in 3D space
	 */
	void set(f32x4 min, f32x4 max) noexcept
	{
		assert(areAllTrue(u32x4(min <= max, UINT32_MAX)));
		this->min = min; this->max = max;
	}
	/**
	 * @brief Tries to set minimum and maximum AABB corner position in 3D space.
	 * @return True if min and max values are valid, otherwise false.
	 * @details See the @ref getMin() and @ref getMax().
	 * 
	 * @param min minimum bounding box corner position in 3D space
	 * @param max maximum bounding box corner position in 3D space
	 */
	bool trySet(f32x4 min, f32x4 max) noexcept
	{
		if (areAnyTrue(u32x4(min > max, 0)))
			return false;
		this->min = min; this->max = max;
		return true;
	}
	
	/**
	 * @brief Sets size of the bounding box.
	 * @param size target size of the bounding box
	 */
	void setSize(f32x4 size) noexcept
	{
		assert(areAllTrue(size >= 0.0f));
		auto extent = size * 0.5f;
		min = -extent; max = extent;
	}
	/**
	 * @brief Sets size and position of the bounding box in 3D space.
	 * 
	 * @param size target size of the bounding box
	 * @param position target position of the bounding box in 3D space
	 */
	void setSize(f32x4 size, f32x4 position) noexcept
	{
		assert(areAllTrue(size >= 0.0f));
		auto extent = size * 0.5f;
		min = position - extent; max = position + extent;
	}

	/**
	 * @brief Returns size of the bounding box.
	 */
	f32x4 getSize() const noexcept { return max - min; }
	/**
	 * @brief Returns position of the bounding box in 3D space.
	 */
	f32x4 getPosition() const noexcept { return (min + max) * 0.5f; }

	/*******************************************************************************************************************
	 * @brief Sets extent and position of the bounding box in 3D space.
	 * @param extent target extent of the bounding box (half size)
	 */
	void setExtent(f32x4 extent) noexcept
	{
		assert(areAllTrue(extent >= 0.0f));
		min = -extent; max = extent;
	}
	/**
	 * @brief Sets extent and position of the bounding box in 3D space.
	 * 
	 * @param extent target extent of the bounding box (half size)
	 * @param position target position of the bounding box in 3D space
	 */
	void setExtent(f32x4 extent, f32x4 position) noexcept
	{
		assert(areAllTrue(extent >= 0.0f));
		min = position - extent; max = position + extent;
	}

	/**
	 * @brief Returns extent of the bounding box. (half size)
	 */
	f32x4 getExtent() const noexcept { return (max - min) * 0.5f; }
	/**
	 * @brief Returns extent and position of the bounding box in 3D space.
	 * 
	 * @param extent target extent of the bounding box (half size)
	 * @param position target position of the bounding box in 3D space
	 */
	void getExtent(f32x4& extent, f32x4& position) const noexcept
	{
		extent = (max - min) * 0.5f; position = min + extent;
	}

	/**
	 * @brief Extends bounding box min and max corner positions in 3D space.
	 * @param point target point to include into the bounding box in 3D space
	 */
	void extend(f32x4 point) noexcept
	{
		min = math::min(min, point); max = math::max(max, point); 
	}
	/**
	 * @brief Extends bounding box min and max corner positions in 3D space.
	 * @param[in] aabb target AABB to include into the bounding box
	 */
	void extend(const Aabb& aabb) noexcept
	{
		min = math::min(min, aabb.min); max = math::max(max, aabb.max); 
	}

	/**
	 * @brief Shrinks bounding box min and max corner positions in 3D space.
	 * @param point target point to limit the bounding box with in 3D space
	 */
	void shrink(f32x4 point) noexcept
	{
		min = math::max(min, point); max = math::min(max, point); 
	}
	/**
	 * @brief Extends bounding box min and max corner positions in 3D space.
	 * @param[in] aabb target AABB to limit the bounding box with
	 */
	void shrink(const Aabb& aabb) noexcept
	{
		min = math::max(min, aabb.min); max = math::min(max, aabb.max); 
	}

	/**
	 * @brief Translates bounding box in 3D space.
	 * @param translation target translation transformation in 3D space
	 */
	void translate(f32x4 translation) noexcept { min += translation; max += translation; }
	/**
	 * @brief Scales bounding box in 3D space.
	 * @param scale target scale transformation in 3D space
	 */
	void scale(f32x4 scale) noexcept { min *= scale; max *= scale; }

	// TODO: update min max using rotation matrix

	/**
	 * @brief Calculates area of the bounding box.
	 */
	float calcArea() const noexcept
	{
		auto extent = max - min;
		auto extentXXY = extent.swizzle<SwX, SwX, SwY>();
		auto extentYZZ = extent.swizzle<SwY, SwZ, SwZ>();
		return dot3(extentXXY, extentYZZ) * 2.0f;
	}
	/**
	 * @brief Calculates volume of the bounding box.
	 */
	float calcVolume() const noexcept
	{
		auto extent = max - min;
		return extent.getX() * extent.getY() * extent.getZ();
	}

	Aabb operator*(f32x4 v) const noexcept { return Aabb(min * v, max * v); }
	Aabb operator/(f32x4 v) const noexcept { return Aabb(min / v, max / v); }
	Aabb operator+(f32x4 v) const noexcept { return Aabb(min + v, max + v); }
	Aabb operator-(f32x4 v) const noexcept { return Aabb(min - v, max - v); }
	Aabb& operator*=(f32x4 v) noexcept { min *= v; max *= v; return *this; }
	Aabb& operator/=(f32x4 v) noexcept { min /= v; max /= v; return *this; }
	Aabb& operator+=(f32x4 v) noexcept { min += v; max += v; return *this; }
	Aabb& operator-=(f32x4 v) noexcept { min -= v; max -= v; return *this; }
	bool operator==(const Aabb& v) const noexcept { return !memcmp(this, &v, sizeof(Aabb)); }
	bool operator!=(const Aabb& v) const noexcept { return memcmp(this, &v, sizeof(Aabb)); }
	
	static const Aabb zero, one, two, half, full, inf;
};

inline const Aabb Aabb::zero = Aabb(f32x4::zero, f32x4::zero);
inline const Aabb Aabb::one = Aabb(f32x4(-0.5f), f32x4(0.5f));
inline const Aabb Aabb::two = Aabb(f32x4::minusOne, f32x4::one);
inline const Aabb Aabb::half = Aabb(f32x4(-0.25f), f32x4(0.25f));
inline const Aabb Aabb::full = Aabb(f32x4::min, f32x4::max);
inline const Aabb Aabb::inf = Aabb(f32x4::minusInf, f32x4::inf);

/**
 * @brief Returns true if first AABB binary representation is less than the second.
 * 
 * @param[in] a first AABB to binary compare
 * @param[in] b second AABB to binary compare
 */
static bool isBinaryLess(const Aabb& a, const Aabb& b) noexcept { return memcmp(&a, &b, sizeof(Aabb)) < 0; }

/***********************************************************************************************************************
 * @brief Returns true if point is inside the AABB in 3D space.
 * 
 * @param[in] aabb target AABB to check
 * @param point target point in the space
 */
static bool isInside(const Aabb& aabb, f32x4 point) noexcept
{
	return areAllTrue(aabb.getMin() <= point & aabb.getMax() >= point);
}
/**
 * @brief Returns true if other AABB is inside this AABB in 3D space.
 * 
 * @param[in] aabb this AABB
 * @param[in] other another AABB to check
 */
static bool isInside(const Aabb& aabb, const Aabb& other) noexcept
{
	return areAllTrue(aabb.getMin() <= other.getMin() & aabb.getMax() >= other.getMax());
}

/**
 * @brief Returns closest point inside AABB to the specified one in 3D space.
 *
 * @param[in] aabb target AABB to use
 * @param point target point in the space
 */
static f32x4 closestPoint(const Aabb& aabb, f32x4 point) noexcept
{
	return clamp(point, aabb.getMin(), aabb.getMax());
}

/***********************************************************************************************************************
 * @brief Calculates where ray intersects the AABB in 3D space. (Ray is inversed!)
 * @return Distance to the intersection points, or FLT_MAX; -FLT_MAX if no hit.
 *
 * @param aabb target AABB to raycast
 * @param ray target ray in the space (inversed!)
 */
static float2 raycast2I(Aabb aabb, Ray ray) noexcept
{
	auto t0 = (aabb.getMin() - ray.origin) * ray.getDirection();
	auto t1 = (aabb.getMax() - ray.origin) * ray.getDirection();
	auto tMin = select(ray.getParallel(), f32x4::minusMax, min(t0, t1));
	auto tMax = select(ray.getParallel(), f32x4::max, max(t0, t1));
	tMin = max(tMin, tMin.swizzle<SwY, SwZ, SwX>());
	tMin = max(tMin, tMin.swizzle<SwZ, SwX, SwY>());
	tMax = min(tMax, tMax.swizzle<SwY, SwZ, SwX>());
	tMax = min(tMax, tMax.swizzle<SwZ, SwX, SwY>());

	auto noParallelOverlap = (ray.origin < aabb.getMin()) | (ray.origin > aabb.getMax());
	auto noIntersection = (tMin > tMax) | (tMax < f32x4::zero) | (ray.getParallel() & noParallelOverlap);
	noIntersection |= noIntersection.splatY() | noIntersection.splatZ();

	return float2(
		select(noIntersection, f32x4::max, tMin).getX(), 
		select(noIntersection, f32x4::minusMax, tMax).getX());
}
/**
 * @brief Calculates where ray intersects the AABB in 3D space.
 * @return Distance to the intersection points, or FLT_MAX; -FLT_MAX if no hit.
 *
 * @param[in] aabb target AABB to raycast
 * @param ray target ray in the space
 */
static float2 raycast2(const Aabb& aabb, Ray ray) noexcept
{
	ray.setDirection(f32x4::one / ray.getDirection());
	return raycast2I(aabb, ray);
}

/***********************************************************************************************************************
 * @brief Calculates where ray intersects the AABB in 3D space. (Ray is inversed!)
 * @return Distance to the first intersection point, or FLT_MAX; -FLT_MAX if no hit.
 *
 * @param[in] aabb target AABB to raycast
 * @param[in] ray target ray in the space (inversed)
 */
static float raycast1I(const Aabb& aabb, const Ray& ray) noexcept
{
	auto t0 = (aabb.getMin() - ray.origin) * ray.getDirection();
	auto t1 = (aabb.getMax() - ray.origin) * ray.getDirection();
	auto tMin = select(ray.getParallel(), f32x4::minusMax, min(t0, t1));
	auto tMax = select(ray.getParallel(), f32x4::max, max(t0, t1));
	tMin = max(tMin, tMin.swizzle<SwY, SwZ, SwX>());
	tMin = max(tMin, tMin.swizzle<SwZ, SwX, SwY>());
	tMax = min(tMax, tMax.swizzle<SwY, SwZ, SwX>());
	tMax = min(tMax, tMax.swizzle<SwZ, SwX, SwY>());

	auto noParallelOverlap = (ray.origin < aabb.getMin()) | (ray.origin > aabb.getMax());
	auto noIntersection = (tMin > tMax) | (tMax < f32x4::zero) | (ray.getParallel() & noParallelOverlap);
	noIntersection |= noIntersection.splatY() | noIntersection.splatZ();
	return select(noIntersection, f32x4::max, tMin).getX();
}
/**
 * @brief Calculates where ray intersects the AABB in 3D space.
 * @return Distance to the first intersection point, or FLT_MAX; -FLT_MAX if no hit.
 *
 * @param[in] aabb target AABB to raycast
 * @param ray target ray in the space
 */
static float raycast1(const Aabb& aabb, Ray ray) noexcept
{
	ray.setDirection(f32x4::one / ray.getDirection());
	return raycast1I(aabb, ray);
}

/**
 * @brief Returns true if ray is intersecting the AABB.
 * @param raycastDists resulting raycast distances
 */
static constexpr bool isAabbIntersected(float2 raycastDists) noexcept
{
	// If tMax < 0.0f, ray is intersecting AABB, but whole AABB is behind us.
	return raycastDists.x <= raycastDists.y && raycastDists.y >= 0.0f;
}

/***********************************************************************************************************************
 * @brief Returns true if ray intersects the AABB in 3D space.
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
 * @param[in] b second AABB to check
 */
static bool isIntersected(const Aabb& a, const Aabb& b) noexcept
{
	return areAllTrue(a.getMin() <= b.getMax() & a.getMin() >= b.getMax());
}

/**
 * @brief Returns true if triangle intersects the AABB.
 * @details Useful for a fast 3D model voxelization.
 *
 * @param position target AABB position in 3D space
 * @param extent target AABB extent (half size)
 * @param[in] triangle target triangle in the space
 */
bool isAabbIntersected(f32x4 position, f32x4 extent, const Triangle& triangle) noexcept;

/***********************************************************************************************************************
 * @brief Returns true if AABB is behind the frustum planes.
 * 
 * @details
 * Useful for a fast view frustum culling. It is a technique used in 3D rendering and game engines to improve 
 * performance by avoiding the rendering of objects that are outside the camera's view, or view frustum. The view 
 * frustum is a truncated pyramid-shaped volume that represents everything the camera can potentially see in the 
 * scene, based on its position, orientation, and field of view.
 *
 * @param[in] planes target frustum planes
 * @param planeCount frustum plane count
 * @param[in] aabb target AABB to check
 * @param[in] model AABB transformation matrix
 */
static bool isBehindFrustum(const Plane* planes, uint8 planeCount, const Aabb& aabb, const f32x4x4& model) noexcept
{
	auto min = aabb.getMin(), max = aabb.getMax();
	auto minX = min.getX(), minY = min.getY(), minZ = min.getZ();
	auto maxX = max.getX(), maxY = max.getY(), maxZ = max.getZ();

	auto v0 = model * f32x4(min, 1.0f);
	auto v1 = model * f32x4(minX, minY, maxZ, 1.0f);
	auto v2 = model * f32x4(minX, maxY, minZ, 1.0f);
	auto v3 = model * f32x4(minX, maxY, maxZ, 1.0f);
	auto v4 = model * f32x4(maxX, minY, minZ, 1.0f);
	auto v5 = model * f32x4(maxX, minY, maxZ, 1.0f);
	auto v6 = model * f32x4(maxX, maxY, minZ, 1.0f);
	auto v7 = model * f32x4(max, 1.0f);

	for (uint8 i = 0; i < planeCount; i++)
	{
		auto plane = planes[i];
		auto d0 = f32x4(distance3(plane, v0), distance3(plane, v1), distance3(plane, v2), distance3(plane, v3));
		auto d1 = f32x4(distance3(plane, v4), distance3(plane, v5), distance3(plane, v6), distance3(plane, v7)); // TODO: use f32x4x8?
		
		if (areAllTrue(d0 < 0.0f & d1 < 0.0f))
			return true;
	}

	return false;
}

/**
 * @brief Returns true if AABB is behind the frustum planes.
 * @details See the @ref isBehindFrustum().
 *
 * @param[in] planes target frustum planes
 * @param planeCount frustum plane count
 * @param[in] aabb target AABB to check
 */
static bool isBehindFrustum(const Plane* planes, uint8 planeCount, const Aabb& aabb) noexcept
{
	auto min = aabb.getMin(), max = aabb.getMax();
	auto minX = min.getX(), minY = min.getY(), minZ = min.getZ();
	auto maxX = max.getX(), maxY = max.getY(), maxZ = max.getZ();

	auto v0 = f32x4(min, 1.0f);
	auto v1 = f32x4(minX, minY, maxZ, 1.0f);
	auto v2 = f32x4(minX, maxY, minZ, 1.0f);
	auto v3 = f32x4(minX, maxY, maxZ, 1.0f);
	auto v4 = f32x4(maxX, minY, minZ, 1.0f);
	auto v5 = f32x4(maxX, minY, maxZ, 1.0f);
	auto v6 = f32x4(maxX, maxY, minZ, 1.0f);
	auto v7 = f32x4(max, 1.0f);

	for (uint8 i = 0; i < planeCount; i++)
	{
		auto plane = planes[i];
		auto d0 = f32x4(distance3(plane, v0), distance3(plane, v1), distance3(plane, v2), distance3(plane, v3));
		auto d1 = f32x4(distance3(plane, v4), distance3(plane, v5), distance3(plane, v6), distance3(plane, v7));
		
		if (areAllTrue(d0 < 0.0f & d1 < 0.0f))
			return true;
	}

	return false;
}

} // namespace math