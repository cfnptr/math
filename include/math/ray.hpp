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
 * @brief Common ray functions.
 */

#pragma once
#include "math/line.hpp"

namespace math
{

using namespace std;

/**
 * @brief Infinite ray structure. (In 3D space)
 * @details Defined by an origin point and direction vector.
 */
struct Ray
{
private:
	float3 direction;
public:
	/**
	 * @brief Ray origin point in 3D space.
	 */
	float3 origin;

	/**
	 * @brief Creates a new ray structure.
	 * 
	 * @param[in] origin ray origin point in 3D space
	 * @param[in] direction ray direction vector in 3D space
	 * @param normalize is direction vector should be normalized
	 */
	Ray(const float3& origin = float3(0.0f), const float3& direction = float3::front, bool normalize = true) noexcept
	{
		if (normalize)
			this->direction = math::normalize(direction);
		else
			this->direction = direction;
		this->origin = origin;
	}

	/**
	 * @brief Returns ray direction vector in 3D space.
	 */
	const float3& getDirection() const noexcept {return direction; }
	/**
	 * @brief Sets ray direction vector in 3D space.
	 * 
	 * @param[in] direction target ray direction vector
	 * @param normalize is direction vector should be normalized
	 */
	void setDirection(const float3& direction, bool normalize = true) noexcept
	{
		if (normalize)
			this->direction = math::normalize(direction);
		else
			this->direction = direction;
	}

	/**
	 * @brief Normalizes ray direction vector.
	 */
	void normalize() noexcept { direction /= length(direction);  }

	Ray operator*(const float3& v) const noexcept { return Ray(origin * v, direction * v); }
	Ray operator/(const float3& v) const noexcept { return Ray(origin / v, direction / v); }
	Ray operator+(const float3& v) const noexcept { return Ray(origin + v, direction + v); }
	Ray operator-(const float3& v) const noexcept { return Ray(origin - v, direction - v); }

	Ray& operator*=(const float3& v) noexcept { direction *= v; origin *= v; return *this; }
	Ray& operator/=(const float3& v) noexcept { direction /= v; origin /= v; return *this; }
	Ray& operator+=(const float3& v) noexcept { direction += v; origin += v; return *this; }
	Ray& operator-=(const float3& v) noexcept { direction -= v; origin -= v; return *this; }
	
	static const Ray left, right, bottom, top, back, front;
};

/**
 * @brief Calculates closest point on ray to the specified one.
 *
 * @param[in] ray target ray to use
 * @param[in] point target point in 3D space
 */
static float3 closestPoint(const Ray& ray, const float3& point) noexcept
{
	auto a = ray.origin;
	auto b = ray.origin + ray.getDirection();
	auto v = b - a;
	auto t = dot(point - a, v) / dot(v, v);
	return a + ray.getDirection() * std::max(t, 0.0f);
}

} // namespace math