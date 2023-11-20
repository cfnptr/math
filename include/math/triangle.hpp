//------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------

#pragma once
#include "math/vector.hpp"

namespace math
{

#define TRIANGLE_POINT_COUNT 3

using namespace std;

struct Triangle
{
	float3 points[TRIANGLE_POINT_COUNT];
	Triangle(const float3& point0, const float3& point1, const float3& point2) noexcept {
		points[0] = point0; points[1] = point1; points[2] = point2; }
	Triangle() = default;

	Triangle operator*(const float3& v) const noexcept {
		return Triangle(points[0] * v, points[1] * v, points[2] * v); }
	Triangle operator/(const float3& v) const noexcept {
		return Triangle(points[0] / v, points[1] / v, points[2] / v); }
	Triangle operator+(const float3& v) const noexcept {
		return Triangle(points[0] + v, points[1] + v, points[2] + v); }
	Triangle operator-(const float3& v) const noexcept {
		return Triangle(points[0] - v, points[1] - v, points[2] - v); }

	Triangle& operator*=(const float3& v) noexcept {
		points[0] *= v; points[1] *= v; points[2] *= v; return *this; }
	Triangle& operator/=(const float3& v) noexcept {
		points[0] /= v; points[1] /= v; points[2] /= v; return *this; }
	Triangle& operator+=(const float3& v) noexcept {
		points[0] += v; points[1] += v; points[2] += v; return *this; }
	Triangle& operator-=(const float3& v) noexcept {
		points[0] -= v; points[1] -= v; points[2] -= v; return *this; }
};

//------------------------------------------------------------------------------------------------------------
static bool isInside(const Triangle& triangle, const float3& point) noexcept
{
	auto p0 = triangle.points[0] - point;
	auto p1 = triangle.points[1] - point;
	auto p2 = triangle.points[2] - point;
	auto u = cross(p1, p2), v = cross(p2, p0), w = cross(p0, p1);
	if (dot(u, v) < 0.0f || dot(u, w) < 0.0f) return false;
	return true;
}

static float3 barycentric(const Triangle& triangle, const float3& point) noexcept
{
	// Cramer's rule
	auto p0 = triangle.points[0];
	auto v0 = triangle.points[1] - p0;
	auto v1 = triangle.points[2] - p0;
	auto v2 = point - p0;
	auto d00 = dot(v0, v0), d01 = dot(v0, v1), d11 = dot(v1, v1);
	auto d20 = dot(v2, v0), d21 = dot(v2, v1);
	auto invDenom = 1.0f / (d00 * d11 - d01 * d01);
	auto v = (d11 * d20 - d01 * d21) * invDenom;
	auto w = (d00 * d21 - d01 * d20) * invDenom;
	return float3(1.0f - v - w, v, w);
}

} // math