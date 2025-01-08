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
 * @brief Common mathematics functions.
 */

#pragma once
#include "math/types.hpp"

#if _WIN32
#define _USE_MATH_DEFINES
#define NOMINMAX
#endif

#include <algorithm>
#include <cmath>
#include <cassert>

namespace math
{

using namespace std;

static constexpr float min(float a, float b, float c) { return std::min(std::min(a, b), c); }
static constexpr float max(float a, float b, float c) { return std::max(std::max(a, b), c); }
static constexpr int32 min(int32 a, int32 b, int32 c) { return std::min(std::min(a, b), c); }
static constexpr int32 max(int32 a, int32 b, int32 c) { return std::max(std::max(a, b), c); }

static float repeat(float v) noexcept
{
	if (v < 0.0f)
		return 1.0f - std::fmod(-v, 1.0f);
	if (v >= 1.0f)
		return std::fmod(v, 1.0f);
	return v;
}
static float sign(float v) noexcept
{
	if (v == 0.0f)
		return 0.0f;
	return std::signbit(v) ? -1.0f : 1.0f;
}
static float lerp(float a, float b, float t) noexcept
{
	assert(t >= 0.0f);
	assert(t <= 1.0f);
	return a + t * (b - a);
}
static float lerpDelta(float a, float b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}
static float gain(float x, float k) noexcept
{
	auto a = 0.5f * std::pow(2.0f * ((x < 0.5f) ? x : 1.0f - x), k);
	return (x < 0.5f) ? a : 1.0f - a;
}

} // namespace math