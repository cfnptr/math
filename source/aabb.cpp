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

#include "math/aabb.hpp"

//**********************************************************************************************************************
bool math::isAabbIntersected(f32x4 position, f32x4 extent, const Triangle& triangle) noexcept
{
	auto v = f32x4x4(triangle.p0 - position, 
		triangle.p1 - position, triangle.p2 - position, f32x4::zero);
	auto f0 = v.c1 - v.c0, f1 = v.c2 - v.c1, f2 = v.c0 - v.c2;
	auto f0X = f0.getX(), f0Y = f0.getY(), f0Z = f0.getZ();
	auto f1X = f1.getX(), f1Y = f1.getY(), f1Z = f1.getZ();
	auto f2X = f2.getX(), f2Y = f2.getY(), f2Z = f2.getZ();
	auto extX = extent.getX(), extY = extent.getY(), extZ = extent.getZ();

	auto a = f32x4(0.0f, -f0Z, f0Y);
	auto p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	auto r = extY * std::abs(f0Z) + extZ * std::abs(f0Y);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(0.0f, -f1Z, f1Y);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extY * std::abs(f1Z) + extZ * std::abs(f1Y);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(0.0f, -f2Z, f2Y);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extY * std::abs(f2Z) + extZ * std::abs(f2Y);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(f0Z, 0.0f, -f0X);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extX * std::abs(f0Z) + extZ * std::abs(f0X);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(f1Z, 0.0f, -f1X);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extX * std::abs(f1Z) + extZ * std::abs(f1X);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(f2Z, 0.0f, -f2X);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extX * std::abs(f2Z) + extZ * std::abs(f2X);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(-f0Y, f0X, 0.0f);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extX * std::abs(f0Y) + extY * std::abs(f0X);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(-f1Y, f1X, 0.0f);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extX * std::abs(f1Y) + extY * std::abs(f1X);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	a = f32x4(-f2Y, f2X, 0.0f);
	p = f32x4(dot3(v.c0, a), dot3(v.c1, a), dot3(v.c2, a));
	r = extX * std::abs(f2Y) + extY * std::abs(f2X);
	if (std::max(-max3(p), min3(p)) > r)
		return false;

	auto t = transpose3x3(v);
	if (max3(t.c0) < -extX || min3(t.c0) > extX || max3(t.c1) < -extY || 
		min3(t.c1) > extY || max3(t.c2) < -extZ || min3(t.c2) > extZ)
	{
		return false;
	}

	auto normal = cross3(f0, f1);
	auto distance = std::abs(dot3(normal, v.c0));
	r = extX * std::abs(normal.getX()) + extY * std::abs(normal.getY()) + extZ * std::abs(normal.getZ());
	return distance <= r;
}