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

#include "math/plane.hpp"

using namespace math;

const Plane Plane::left = Plane(float3(-1.0f, 0.0f, 0.0f), 0.0f, false);
const Plane Plane::right = Plane(float3(1.0f, 0.0f, 0.0f), 0.0f, false);
const Plane Plane::bottom = Plane(float3(0.0f, -1.0f, 0.0f), 0.0f, false);
const Plane Plane::top = Plane(float3(0.0f, 1.0f, 0.0f), 0.0f, false);
const Plane Plane::back = Plane(float3(0.0f, 0.0f, -1.0f), 0.0f, false);
const Plane Plane::front = Plane(float3(0.0f, 0.0f, 1.0f), 0.0f, false);

float3 closestPoint(const Triangle& triangle, const float3& point) noexcept
{
    auto p = closestPoint(Plane(triangle), point);
    if (isInside(triangle, p))
        return p;

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

    if (m == m0)
        return c0;
    if (m == m1)
        return c1;
    return c2;
}