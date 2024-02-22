//------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------

#pragma once
#include "math/aabb.hpp"

namespace math
{

using namespace std;

struct Sphere
{
	float3 position;
	float radius;

	Sphere(float radius, const float3& position = float3(0.0f)) noexcept {
		this->position = position; this->radius = radius; }
	Sphere() = default;

	static const Sphere one, two, half;
};

//------------------------------------------------------------------------------------------------------------
static bool isInside(const Sphere& sphere, const float3& point) noexcept
{
	auto difference = sphere.position - point;
  	return length2(difference) < sphere.radius * sphere.radius;
}

static float3 closestPoint(const Sphere& sphere, const float3& point) noexcept
{
    auto sphereToPoint = normalize(point - sphere.position);
    return sphere.position + sphereToPoint * sphere.radius;
}

static bool isIntersected(const Sphere& a, const Sphere& b) noexcept
{
    auto d = a.position - b.position;
    auto s = a.radius + b.radius;
    return length2(d) <= s * s;
}
static bool isIntersected(const Sphere& a, const Aabb& b) noexcept
{
	auto c = closestPoint(b, a.position);
	auto d2 = length2(a.position - c);
	return d2 < a.radius * a.radius;
}

} // namespace math