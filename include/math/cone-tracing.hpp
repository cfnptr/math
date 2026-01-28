// Copyright 2022-2026 Nikita Fediuchin. All rights reserved.
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
 * @brief Common cone tracing functions.
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

// TODO: add docs:

constexpr uint8 diffuseConeCount = 6;

constexpr const float diffuseConeWeights[diffuseConeCount] =
{
	0.25f, 0.15f, 0.15f, 0.15f, 0.15f, 0.15f
};

constexpr const float3 diffuseConeDirs[diffuseConeCount] =
{
	float3( 0.0f,       0.0f,      1.0f),
	float3( 0.0f,       0.866025f, 0.5f),
	float3( 0.823639f,  0.267617f, 0.5f),
	float3( 0.509037f, -0.700629f, 0.5f),
	float3(-0.509037f, -0.700629f, 0.5f),
	float3(-0.823639f,  0.267617f, 0.5f)
};

static float roughnessToAperture(float roughness) noexcept // Polynomial approximation of the specular GGX
{
	return std::tan(0.0003474660443456835f + (roughness * (1.3331290497744692f - (roughness * 0.5040552688878546f))));
}

} // namespace math