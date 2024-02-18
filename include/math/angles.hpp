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

#if _WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>

namespace math
{

using namespace std;

static float radians(float degrees) noexcept { return degrees * ((float)M_PI / 180.0f); }
static float2 radians(float2 degrees) noexcept {
	return float2(radians(degrees.x), radians(degrees.y)); }
static float3 radians(const float3& degrees) noexcept {
	return float3(radians(degrees.x), radians(degrees.y), radians(degrees.z)); }
static float4 radians(const float4& degrees) noexcept
{
	return float4(radians(degrees.x), radians(degrees.y),
		radians(degrees.z), radians(degrees.w));
}

static float degrees(float radians) noexcept { return radians * (180.0f / (float)M_PI); }
static float2 degrees(float2 radians) noexcept {
	return float2(degrees(radians.x), degrees(radians.y)); }
static float3 degrees(const float3& radians) noexcept {
	return float3(degrees(radians.x), degrees(radians.y), degrees(radians.z)); }
static float4 degrees(const float4& radians) noexcept
{
	return float4(degrees(radians.x), degrees(radians.y),
		degrees(radians.z), degrees(radians.w));
}

}; // namespace math