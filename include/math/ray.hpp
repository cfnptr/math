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
 * @brief Common infinite ray functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

/**
 * @brief Infinite ray structure. (In 3D space)
 * @details Defined by an origin point and direction vector.
 */
struct [[nodiscard]] Ray
{
protected:
	f32x4 direction = f32x4::zero;
	u32x4 isParallel = u32x4::zero;
public:
	/**
	 * @brief Ray origin point in 3D space.
	 */
	f32x4 origin = f32x4::zero;

	/**
	 * @brief Creates a new ray structure. (In 3D space)
	 * 
	 * @param origin ray origin point in 3D space
	 * @param direction ray direction vector in 3D space
	 * @param normalize is direction vector should be normalized
	 */
	Ray(f32x4 origin, f32x4 direction, bool normalize = true) noexcept : 
		direction(normalize ? normalize3(direction) : direction), origin(origin) { }
	/**
	 * @brief Creates a new empty ray structure.
	 */
	Ray() = default;

	/**
	 * @brief Returns ray direction vector in 3D space.
	 */
	f32x4 getDirection() const noexcept { return direction; }
	/**
	 * @brief Sets ray direction vector in 3D space.
	 * 
	 * @param direction target ray direction vector
	 * @param normalize is direction vector should be normalized
	 */
	void setDirection(f32x4 direction, bool normalize = true) noexcept
	{
		this->direction = normalize ? normalize3(direction) : direction;
		isParallel = abs(direction) <= f32x4(1.0e-20f);
	}

	/**
	 * @brief Returns which of the ray direction axes are parallel.
	 */
	const u32x4& getParallel() const noexcept { return isParallel; }

	/**
	 * @brief Normalizes ray direction vector.
	 */
	void normalize() noexcept { direction /= length3(direction);  }

	Ray operator*(f32x4 v) const noexcept { return Ray(origin * v, direction * v); }
	Ray operator/(f32x4 v) const noexcept { return Ray(origin / v, direction / v); }
	Ray operator+(f32x4 v) const noexcept { return Ray(origin + v, direction + v); }
	Ray operator-(f32x4 v) const noexcept { return Ray(origin - v, direction - v); }
	Ray& operator*=(f32x4 v) noexcept { direction *= v; origin *= v; return *this; }
	Ray& operator/=(f32x4 v) noexcept { direction /= v; origin /= v; return *this; }
	Ray& operator+=(f32x4 v) noexcept { direction += v; origin += v; return *this; }
	Ray& operator-=(f32x4 v) noexcept { direction -= v; origin -= v; return *this; }
	bool operator==(const Ray& v) const noexcept { return !memcmp(this, &v, sizeof(Ray)); }
	bool operator!=(const Ray& v) const noexcept { return memcmp(this, &v, sizeof(Ray)); }
	
	static const Ray left, right, bottom, top, back, front;
};

inline const Ray Ray::left = Ray(f32x4::zero, f32x4(-1.0f, 0.0f, 0.0f, 0.0f), false);
inline const Ray Ray::right = Ray(f32x4::zero, f32x4(1.0f, 0.0f, 0.0f, 0.0f), false);
inline const Ray Ray::bottom = Ray(f32x4::zero, f32x4(0.0f, -1.0f, 0.0f, 0.0f), false);
inline const Ray Ray::top = Ray(f32x4::zero, f32x4(0.0f, 1.0f, 0.0f, 0.0f), false);
inline const Ray Ray::back = Ray(f32x4::zero, f32x4(0.0f, 0.0f, -1.0f, 0.0f), false);
inline const Ray Ray::front = Ray(f32x4::zero, f32x4(0.0f, 0.0f, 1.0f, 0.0f), false);

/**
 * @brief Returns closest point on ray to the specified one in 3D space.
 *
 * @param[in] ray target ray to use
 * @param point target point in 3D space
 */
static f32x4 closestPoint(const Ray& ray, f32x4 point) noexcept
{
	auto a = ray.origin, b = ray.origin + ray.getDirection();
	auto v = b - a; auto t = dot3(point - a, v) / dot3(v, v);
	return fma(ray.getDirection(), f32x4(std::max(t, 0.0f)), a);
}

/**
 * @brief Returns true if ray is intersecting the shape.
 * @param raycastDists resulting raycast distances
 */
static bool isIntersected(float2 raycastDists) noexcept
{
	// If tMax < 0.0f, ray is intersecting shape, but whole shape is behind us.
	return raycastDists.y > std::max(raycastDists.x, 0.0f);
}

} // namespace math