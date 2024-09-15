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

#include "math/aabb.hpp"

using namespace math;

//**********************************************************************************************************************
float2 raycast2(const Aabb& aabb, const Ray& ray) noexcept
{
	auto origin = ray.origin;
	auto directionInv = float3(1.0f) / ray.getDirection();
	auto aabbMin = aabb.getMin(), aabbMax = aabb.getMax();

	auto t1 = (aabbMin.x - origin.x) * directionInv.x;
	auto t2 = (aabbMax.x - origin.x) * directionInv.x;
	auto t3 = (aabbMin.y - origin.y) * directionInv.y;
	auto t4 = (aabbMax.y - origin.y) * directionInv.y;
	auto t5 = (aabbMin.z - origin.z) * directionInv.z;
	auto t6 = (aabbMax.z - origin.z) * directionInv.z;

	auto tMin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	auto tMax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
	return float2(tMin, tMax);
}
float2 raycast2I(const Aabb& aabb, const Ray& ray) noexcept
{
	auto origin = ray.origin;
	auto directionInv = ray.getDirection();
	auto aabbMin = aabb.getMin(), aabbMax = aabb.getMax();

	auto t1 = (aabbMin.x - origin.x) * directionInv.x;
	auto t2 = (aabbMax.x - origin.x) * directionInv.x;
	auto t3 = (aabbMin.y - origin.y) * directionInv.y;
	auto t4 = (aabbMax.y - origin.y) * directionInv.y;
	auto t5 = (aabbMin.z - origin.z) * directionInv.z;
	auto t6 = (aabbMax.z - origin.z) * directionInv.z;

	auto tMin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	auto tMax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));
	return float2(tMin, tMax);
}

float raycast1(const Aabb& aabb, const Ray& ray) noexcept
{
	auto origin = ray.origin;
	auto directionInv = float3(1.0f) / ray.getDirection();
	auto aabbMin = aabb.getMin(), aabbMax = aabb.getMax();

	auto t1 = (aabbMin.x - origin.x) * directionInv.x;
	auto t2 = (aabbMax.x - origin.x) * directionInv.x;
	auto t3 = (aabbMin.y - origin.y) * directionInv.y;
	auto t4 = (aabbMax.y - origin.y) * directionInv.y;
	auto t5 = (aabbMin.z - origin.z) * directionInv.z;
	auto t6 = (aabbMax.z - origin.z) * directionInv.z;

	return std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
}
float raycast1I(const Aabb& aabb, const Ray& ray) noexcept
{
	auto origin = ray.origin;
	auto directionInv = ray.getDirection();
	auto aabbMin = aabb.getMin(), aabbMax = aabb.getMax();

	auto t1 = (aabbMin.x - origin.x) * directionInv.x;
	auto t2 = (aabbMax.x - origin.x) * directionInv.x;
	auto t3 = (aabbMin.y - origin.y) * directionInv.y;
	auto t4 = (aabbMax.y - origin.y) * directionInv.y;
	auto t5 = (aabbMin.z - origin.z) * directionInv.z;
	auto t6 = (aabbMax.z - origin.z) * directionInv.z;

	return std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
}

//**********************************************************************************************************************
bool isAabbIntersected(const float3& center, const float3& extent, const Triangle& triangle) noexcept
{
	auto v0 = triangle.points[0] - center;
	auto v1 = triangle.points[1] - center;
	auto v2 = triangle.points[2] - center;
	auto f0 = v1 - v0, f1 = v2 - v1, f2 = v0 - v2;

	auto a = float3(0.0f, -f0.z, f0.y);
	auto p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	auto r = extent.y * std::abs(f0.z) + extent.z * std::abs(f0.y);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(0.0f, -f1.z, f1.y);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.y * std::abs(f1.z) + extent.z * std::abs(f1.y);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(0.0f, -f2.z, f2.y);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.y * std::abs(f2.z) + extent.z * std::abs(f2.y);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(f0.z, 0.0f, -f0.x);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.x * std::abs(f0.z) + extent.z * std::abs(f0.x);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(f1.z, 0.0f, -f1.x);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.x * std::abs(f1.z) + extent.z * std::abs(f1.x);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(f2.z, 0.0f, -f2.x);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.x * std::abs(f2.z) + extent.z * std::abs(f2.x);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(-f0.y, f0.x, 0.0f);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.x * std::abs(f0.y) + extent.y * std::abs(f0.x);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(-f1.y, f1.x, 0.0f);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.x * std::abs(f1.y) + extent.y * std::abs(f1.x);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	a = float3(-f2.y, f2.x, 0.0f);
	p0 = dot(v0, a), p1 = dot(v1, a), p2 = dot(v2, a);
	r = extent.x * std::abs(f2.y) + extent.y * std::abs(f2.x);
	if (std::max(-max(p0, p1, p2), min(p0, p1, p2)) > r)
		return false;

	if (max(v0.x, v1.x, v2.x) < -extent.x || min(v0.x, v1.x, v2.x) > extent.x)
		return false;
	if (max(v0.y, v1.y, v2.y) < -extent.y || min(v0.y, v1.y, v2.y) > extent.y)
		return false;
	if (max(v0.z, v1.z, v2.z) < -extent.z || min(v0.z, v1.z, v2.z) > extent.z)
		return false;

	auto normal = cross(f0, f1);
	auto distance = std::abs(dot(normal, v0));
	r = extent.x * std::abs(normal.x) + extent.y * std::abs(normal.y) + extent.z * std::abs(normal.z);
	return distance <= r;
}

//**********************************************************************************************************************
bool isBehindFrustum(const Aabb& aabb, const float4x4& model,
	const Plane* planes, uint8 planeCount = Plane::frustumCount) noexcept
{
	auto min = aabb.getMin(), max = aabb.getMax();
	auto v0 = model * float4(min, 1.0f);
	auto v1 = model * float4(min.x, min.y, max.z, 1.0f);
	auto v2 = model * float4(min.x, max.y, min.z, 1.0f);
	auto v3 = model * float4(min.x, max.y, max.z, 1.0f);
	auto v4 = model * float4(max.x, min.y, min.z, 1.0f);
	auto v5 = model * float4(max.x, min.y, max.z, 1.0f);
	auto v6 = model * float4(max.x, max.y, min.z, 1.0f);
	auto v7 = model * float4(max, 1.0f);

	auto p0 = (float3)v0, p1 = (float3)v1;
	auto p2 = (float3)v2, p3 = (float3)v3;
	auto p4 = (float3)v4, p5 = (float3)v5;
	auto p6 = (float3)v6, p7 = (float3)v7;

	for (uint8 i = 0; i < planeCount; i++)
	{
		auto plane = planes[i];
		auto distance0 = distance(plane, p0);
		auto distance1 = distance(plane, p1);
		auto distance2 = distance(plane, p2);
		auto distance3 = distance(plane, p3);
		auto distance4 = distance(plane, p4);
		auto distance5 = distance(plane, p5);
		auto distance6 = distance(plane, p6);
		auto distance7 = distance(plane, p7);

		if (distance0 < 0.0f && distance1 < 0.0f &&
			distance2 < 0.0f && distance3 < 0.0f &&
			distance4 < 0.0f && distance5 < 0.0f &&
			distance6 < 0.0f && distance7 < 0.0f)
		{
			return true;
		}
	}

	return false;
}