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

using namespace std;

struct Line
{
	float3 start;
	float3 end;

	Line(const float3& start, const float3& end) noexcept {
		this->start = start; this->end = end; }
	Line() = default;

	float3 getVector() const noexcept { return end - start; }

	Line operator*(const float3& v) const noexcept { return Line(start * v, end * v); }
	Line operator/(const float3& v) const noexcept { return Line(start / v, end / v); }
	Line operator+(const float3& v) const noexcept { return Line(start + v, end + v); }
	Line operator-(const float3& v) const noexcept { return Line(start - v, end - v); }

	Line& operator*=(const float3& v) noexcept { start *= v; end *= v; return *this; }
	Line& operator/=(const float3& v) noexcept { start /= v; end /= v; return *this; }
	Line& operator+=(const float3& v) noexcept { start += v; end += v; return *this; }
	Line& operator-=(const float3& v) noexcept { start -= v; end -= v; return *this; }
};

//------------------------------------------------------------------------------------------------------------
static float3 closestPoint(const Line& line, const float3& point) noexcept
{
	auto a = line.start;
	auto v = line.getVector();
	auto t = dot(point - a, v) / dot(v, v); 
	return a + v * std::clamp(t, 0.0f, 1.0f);
}
static float3 closestPoint(const Line& line, const float3& point, float& t) noexcept
{
	auto a = line.start;
	auto v = line.getVector();
	t = dot(point - a, v) / dot(v, v); 
	return a + v * std::clamp(t, 0.0f, 1.0f);
}

} // namespace math