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
 * @brief Common sphere functions.
 * @details Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/
 */

#pragma once
#include "math/ray.hpp"
#include "math/aabb.hpp"

namespace math
{

/**
 * @brief Sphere structure. (In 3D space)
 * @details Defined by a position point and radius.
 */
struct [[nodiscard]] Sphere
{
protected:
	f32x4 posRad;
public:
	/**
	 * @brief Creates a new sphere structure.
	 *
	 * @param radius target sphere radius
	 * @param position sphere position in 3D space
	 */
	Sphere(float radius = 0.0f, f32x4 position = f32x4::zero) noexcept :
		posRad(position) { posRad.setW(radius); }

	/**
	 * @brief Returns sphere radius.
	 */
	float getRadius() const noexcept { return posRad.getW(); }
	/**
	 * @brief Sets sphere radius.
	 * @param radius target sphere radius
	 */
	void setRadius(float radius) noexcept { return posRad.setW(radius); }
	
	/**
	 * @brief Returns position of the sphere in 3D space.
	 */
	f32x4 getPosition() const noexcept { return posRad; }
	/**
	 * @brief Sets position of the sphere in 3D space.
	 * @param position target sphere position in 3D space
	 */
	void setPosition(f32x4 position) noexcept { posRad = f32x4(position, posRad.getW()); }

	bool operator==(Sphere v) const noexcept { return !memcmp(this, &v, sizeof(Sphere)); }
	bool operator!=(Sphere v) const noexcept { return memcmp(this, &v, sizeof(Sphere)); }

	static const Sphere one, two, half;
};

inline const Sphere Sphere::one = Sphere(0.5f);
inline const Sphere Sphere::two = Sphere(1.0f);
inline const Sphere Sphere::half = Sphere(0.25f);

/**
 * @brief Returns true if point is inside the sphere in 3D space.
 *
 * @param sphere target sphere to check
 * @param point target point in 3D space
 */
static bool isInside(Sphere sphere, f32x4 point) noexcept
{
	auto radius = sphere.getRadius();
	return lengthSq3(sphere.getPosition() - point) < radius * radius;
}

/**
 * @brief Calculates closest point on sphere to the specified one in 3D space.
 *
 * @param sphere target sphere to use
 * @param point target point in 3D space
 */
static f32x4 closestPoint(Sphere sphere, f32x4 point) noexcept
{
	auto dir = normalize3(point - sphere.getPosition());
	return fma(dir, f32x4(sphere.getRadius()), sphere.getPosition());
}

/**
 * @brief Returns true if one sphere intersects another.
 *
 * @param a first sphere to check
 * @param b second sphere to check
 */
static bool isIntersected(Sphere a, Sphere b) noexcept
{
	auto s = a.getRadius() + b.getRadius();
	return lengthSq3(a.getPosition() - b.getPosition()) <= s * s;
}
/**
 * @brief Returns true if sphere intersects AABB.
 *
 * @param sphere target sphere to check
 * @param[in] aabb target AABB to check
 */
static bool isIntersected(Sphere sphere, const Aabb& aabb) noexcept
{
	auto position = sphere.getPosition(); radius = sphere.getRadius();
	auto closPos = closestPoint(aabb, position);
	return lengthSq3(position - closPos) < radius * radius;
}

} // namespace math