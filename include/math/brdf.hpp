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
//
// Bidirectional Reflectance Distribution Function
// Based on this: https://google.github.io/filament/Filament.html

/***********************************************************************************************************************
 * @file
 * @brief Common Bidirectional Reflectance Distribution Function functions. (BRDF)
 * 
 * @details
 * BRDF is a model used in physically based rendering (PBR) to simulate how light interacts with rough surfaces.
 * Based on this project: https://google.github.io/filament/Filament.html
 */

#pragma once
#include "math/vector.hpp"

namespace math::brdf
{

/**
 * @brief GGX microfacet distribution function. (Ground Glass Model)
 * 
 * @details 
 * The GGX distribution is effective for rendering realistic reflections, especially on surfaces that have varying 
 * degrees of roughness, such as metals, plastics, and other materials with glossy or shiny finishes.
 * 
 * @param noh dot product between the surface normal (n) and the half-vector (h)
 * @param roughness spread of microfacets on a surface (0.0-1.0 / smooth-rough)
 */
static constexpr float ggx(float noh, float roughness) noexcept
{
    auto f = (roughness - 1.0f) * ((roughness + 1.0f) * (noh * noh)) + 1.0f;
    return (roughness * roughness) / ((float)M_PI * f * f);
}

/**
 * @brief Hammersley sampling function.
 *
 * @details
 * The sampling techniques for generating well-distributed points on a surface or within a volume. It is widely 
 * applied in global illumination, ray tracing, and other areas of computer graphics where importance sampling or 
 * quasi-random sampling is needed to improve the efficiency of rendering.
 *
 * @param index target index of the sample
 * @param invSampleCount iversed sample count (1.0f / sampleCount)
 */
static constexpr float2 hammersley(uint32 index, float invSampleCount) noexcept
{
    constexpr auto tof = 0.5f / 0x80000000U;
    auto bits = index;
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float2(index * invSampleCount, bits * tof);
}
/**
 * @brief DGGX NDF importance sampling function.
 *
 * @details
 * The importance sampling technique applied to the Normal Distribution Function (NDF) of the GGX microfacet model. 
 * This technique is widely used in physically based rendering (PBR) to sample directions for reflection more 
 * efficiently, particularly for materials that exhibit specular reflections.
 *
 * @param u spherical coordinates
 * @param a roughness value
 */
static float3 importanceSamplingNdfDggx(float2 u, float a) noexcept
{
    auto phi = 2.0f * (float)M_PI * u.x;
    auto cosTheta2 = (1.0f - u.y) / (1.0f + (a + 1.0f) * ((a - 1.0f) * u.y));
    auto cosTheta = std::sqrt(cosTheta2);
    auto sinTheta = std::sqrt(1.0f - cosTheta2);
    return float3(sinTheta * std::cos(phi), sinTheta * std::sin(phi), cosTheta);
}

/**
 * @brief Converts IOR value to the remapped reflectance.
 * @param ior target index of refraction
 */
static float iorToReflectance(float ior) noexcept
{
    auto f0 = ((ior - 1.0f) * (ior - 1.0f)) / ((ior + 1.0f) * (ior + 1.0f));
    return std::sqrt(f0 * (1.0f / 0.16f));
}

} // namespace math::brdf