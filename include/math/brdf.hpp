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
 * @brief Calculates gaussian blur kernel buffer coefficient count.
 * @param kernelWidth gaussian blur kernel width
 */
static constexpr uint8 calcGaussCoeffCount(uint8 kernelWidth) noexcept
{
	return (kernelWidth - 1u) / 4u + 1u;
}

static constexpr uint32 ggxKernelWidth = 21;
static constexpr double ggxSigma0 = (ggxKernelWidth + 1) / 6.0;
static constexpr auto ggxCoeffCount = calcGaussCoeffCount(ggxKernelWidth);

/**
 * @brief Calculates spherical GGX distribution blur LOD count.
 * @param bufferSize target blur buffer size in texels
 */
static uint8 calcGgxBlurLodCount(uint2 bufferSize) noexcept
{
	auto lodCount = calcMipCount(bufferSize); 
	// Note: We don't go lower than 16 texel in one dimension.
	return (uint8)std::max(std::min(4, (int)lodCount), (int)lodCount - 4);
}
/**
 * @brief Calculates spherical GGX distribution blur LOD offset.
 * 
 * @param bufferSize target blur buffer size in texels
 * @param fieldOfView camera field of view in radians
 */
static float calcGgxLodOffset(uint2 bufferSize, float fieldOfView) noexcept
{
	constexpr float d = 1.0f; // Note: Texel size of the blur buffer in world units at 1 meter.
	auto texelSizeAtOneMeter = (d * std::tan(fieldOfView * 0.5f)) / bufferSize.y;
	return -std::log2(float(M_SQRT2 * ggxSigma0) * texelSizeAtOneMeter);
}

/***********************************************************************************************************************
 * @brief GGX microfacet distribution function. (Ground Glass Model)
 * 
 * @details 
 * The GGX distribution is effective for rendering realistic reflections, especially on surfaces that have varying 
 * degrees of roughness, such as metals, plastics, and other materials with glossy or shiny finishes.
 * 
 * @param noh dot product between the surface normal (n) and the half-vector (h)
 * @param linearRoughness spread of microfacets on a surface (0.0-1.0 / smooth-rough)
 */
static constexpr float ggx(float noh, float linearRoughness) noexcept
{
	auto oneMinusNohSquared = 1.0f - noh * noh;
	auto a = noh * linearRoughness;
	auto k = linearRoughness / (a * a + oneMinusNohSquared);
	return k * k * M_1_PI;
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
 * @param invSampleCount inversed sample count (1.0f / sampleCount)
 */
static constexpr float2 hammersley(uint32 index, float invSampleCount) noexcept
{
	constexpr auto tof = 0.5f / 0x80000000u;
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
static f32x4 importanceSamplingNdfDggx(float2 u, float linearRoughness) noexcept
{
	auto a2 = linearRoughness * linearRoughness;
	auto phi = u.x * float(M_PI * 2.0);
	auto cosTheta2 = (1.0f - u.y) / std::fma(a2 - 1.0f, u.y, 1.0f);
	auto cosTheta = std::sqrt(cosTheta2);
	auto sinTheta = std::sqrt(1.0f - cosTheta2);
	return f32x4(std::cos(phi) * sinTheta, std::sin(phi) * sinTheta, cosTheta);
}
// TODO: use faster alg +7.5%: https://arxiv.org/pdf/2306.05044

/**
 * @brief Computes diffuse irradiance from spherical harmonics (SH) using a 3rd-order.
 *
 * @details
 * This function evaluates irradiance (light arriving at a surface) from an environment map, 
 * encoded using spherical harmonics (SH), for a given surface normal.
 * 
 * @param normal target sample normal vector
 * @param[in] shBuffer IBL spherical harmonics buffer 
 */
static f32x4 diffuseIrradiance(float3 normal, const f32x4* shBuffer) noexcept
{
	auto qb = float4(normal.y * normal.x, normal.y * normal.z, 
		std::fma(normal.z * normal.z, 3.0f, -1.0f), normal.z * normal.x);
	auto ft = normal.x * normal.x - normal.y * normal.y;

	auto irradiance = shBuffer[0];
	irradiance += shBuffer[1] * normal.y;
	irradiance += shBuffer[2] * normal.z;
	irradiance += shBuffer[3] * normal.x;
	irradiance += shBuffer[4] * qb.x;
	irradiance += shBuffer[5] * qb.y;
	irradiance += shBuffer[6] * qb.z;
	irradiance += shBuffer[7] * qb.w;
	irradiance += shBuffer[8] * ft;
	return max(irradiance, f32x4::zero);
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
/**
 * @brief Converts remapped reflectance to the index of refraction.
 * @param reflectance target remapped reflectance
 */
static float reflectanceToIOR(float reflectance) noexcept
{
	auto sqrtF0 = reflectance * 0.4f;
	return (1.0f + sqrtF0) / (1.0f - sqrtF0);
}

} // namespace math::brdf