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
//
// Bidirectional Reflectance Distribution Function
// Based on this: https://google.github.io/filament/Filament.html
//--------------------------------------------------------------------------------------------------

#pragma once
#include "math/vector.hpp"

namespace math::brdf
{

using namespace math;

static float ggx(float noh, float roughness)
{
    auto f = (roughness - 1.0f) * ((roughness + 1.0f) * (noh * noh)) + 1.0f;
    return (roughness * roughness) / ((float)M_PI * f * f);
}
static float2 hammersley(uint32 index, float invSampleCount)
{
    const auto tof = 0.5f / 0x80000000U;
    auto bits = index;
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float2(index * invSampleCount, bits * tof);
}
static float3 importanceSamplingNdfDggx(float2 u, float a)
{
    auto phi = 2.0f * (float)M_PI * u.x;
    auto cosTheta2 = (1.0f - u.y) / (1.0f + (a + 1.0f) * ((a - 1.0f) * u.y));
    auto cosTheta = std::sqrt(cosTheta2);
    auto sinTheta = std::sqrt(1.0f - cosTheta2);
    return float3(sinTheta * std::cos(phi), sinTheta * std::sin(phi), cosTheta);
}

} // math::brdf