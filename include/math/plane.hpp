//--------------------------------------------------------------------------------------------------
// Copyright 2022-2023 Nikita Fediuchin. All rights reserved.
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
//--------------------------------------------------------------------------------------------------

#pragma once
#include "math/line.hpp"
#include "math/matrix.hpp"
#include "math/triangle.hpp"

namespace math
{

#define FRUSTUM_PLANE_COUNT 6

using namespace std;

struct Plane
{
private:
	float3 normal;
public:
	float distance;

	Plane(const float3& normal = float3::top,
		float distance = 0.0f, bool normalize = true) noexcept
	{
		if (normalize) this->normal = math::normalize(normal);
		else this->normal = normal;
		this->distance = distance;
	}
	Plane(const Triangle& triangle) noexcept
	{
		normal = cross(triangle.points[1] - triangle.points[0],
			triangle.points[2] - triangle.points[0]);
		if (length(normal) > 0.0f) normal = normalize(normal);
		distance = dot(normal, triangle.points[0]);
	}

	const float3& getNormal() const noexcept { return normal; }
	void setNormal(const float3& normal, bool normalize = true) noexcept
	{
		if (normalize) this->normal = math::normalize(normal);
		else this->normal = normal;
	}

	static const Plane left, right, bottom, top, back, front;
};

//--------------------------------------------------------------------------------------------------
// Returns distance to the plane.
static float distance(const Plane& plane, const float3& point) noexcept {
	return dot(plane.getNormal(), point) + plane.distance; }
static float3 closestPoint(const Plane& plane, const float3& point) noexcept {
	return point - plane.getNormal() * distance(plane, point); }

static float3 closestPoint(const Triangle& triangle, const float3& point) noexcept
{
    auto p = closestPoint(Plane(triangle), point);
    if (isInside(triangle, p)) return p;
    auto ab = Line(triangle.points[0], triangle.points[1]);
    auto bc = Line(triangle.points[1], triangle.points[2]);
    auto ca = Line(triangle.points[2], triangle.points[0]);
    auto c0 = closestPoint(ab, p);
    auto c1 = closestPoint(bc, p);
    auto c2 = closestPoint(ca, p);
    auto m0 = length2(p - c0);
    auto m1 = length2(p - c1);
    auto m2 = length2(p - c2);
    auto m = min(m0, m1, m2);
    if (m == m0) return c0;
    if (m == m1) return c1;
    return c2;
}

//--------------------------------------------------------------------------------------------------
// Returns unnormalized plane normals.
static void extractFrustumPlanes(const float4x4& frustum, Plane* planes) noexcept
{
	// Gribb & Hartmann method
	planes[0] = Plane(float3(frustum.c0.w + frustum.c0.x, frustum.c1.w + frustum.c1.x,
		frustum.c2.w + frustum.c2.x), frustum.c3.w + frustum.c3.x, false);
	planes[1] = Plane(float3(frustum.c0.w - frustum.c0.x, frustum.c1.w - frustum.c1.x,
		frustum.c2.w - frustum.c2.x), frustum.c3.w - frustum.c3.x, false);
	planes[2] = Plane(float3(frustum.c0.w - frustum.c0.y, frustum.c1.w - frustum.c1.y,
		frustum.c2.w - frustum.c2.y), frustum.c3.w - frustum.c3.y, false); // Flipped Vulkan NDC
	planes[3] = Plane(float3(frustum.c0.w + frustum.c0.y, frustum.c1.w + frustum.c1.y,
		frustum.c2.w + frustum.c2.y), frustum.c3.w + frustum.c3.y, false); // Flipped Vulkan NDC
	planes[4] = Plane(float3(frustum.c0.z,
		frustum.c1.z, frustum.c2.z), frustum.c3.z, false);
	planes[5] = Plane(float3(frustum.c0.w - frustum.c0.z, frustum.c1.w - frustum.c1.z,
		frustum.c2.w - frustum.c2.z), frustum.c3.w - frustum.c3.z, false);
}
static void normalizeFrustumPlanes(Plane* planes) noexcept
{
	auto normal = planes[0].getNormal(); auto l = length(normal);
	planes[0].setNormal(normal / l, false); planes[0].distance /= l;
	normal = planes[1].getNormal(); l = length(normal);
	planes[1].setNormal(normal / l, false); planes[1].distance /= l;
	normal = planes[2].getNormal(); l = length(normal);
	planes[2].setNormal(normal / l, false); planes[2].distance /= l;
	normal = planes[3].getNormal(); l = length(normal);
	planes[3].setNormal(normal / l, false); planes[3].distance /= l;
	normal = planes[4].getNormal(); l = length(normal);
	planes[4].setNormal(normal / l, false); planes[4].distance /= l;
	normal = planes[5].getNormal(); l = length(normal);
	planes[5].setNormal(normal / l, false); planes[5].distance /= l;
}

} // math