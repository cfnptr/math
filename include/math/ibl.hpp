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

#pragma once
#include "math/vector.hpp"

/***********************************************************************************************************************
 * @file
 * @brief Common Image Based Lighting functions. (IBL)
 * 
 * @details 
 * IBL is a technique used in physically based rendering (PBR) to simulate realistic lighting in 3D scenes by using an 
 * image to define the light environment. Instead of relying solely on traditional light sources like point lights, 
 * directional lights, or spotlights, IBL captures the complexity of real-world lighting, including ambient light, 
 * reflections, and diffuse lighting, by using images (often HDRI, High Dynamic Range Images) that represent the 
 * surrounding environment.
 * 
 * Based on this project: https://google.github.io/filament/Filament.html
 */

namespace math::ibl
{

using namespace math;

/**
 * @brief Size of the Diffuse Fresnel Glossiness Look-Up Table in pixels. (DFG LUT)
 * 
 * @details 
 * This table is used to precompute certain values related to specular reflections and Fresnel effects, optimizing 
 * the real-time rendering of materials, especially those with varying roughness and reflectance.
 */
const int32 iblDfgSize = 128;

/**
 * @brief Spherical harmonics band count.
 */
const int32 shBandCount = 3;
/**
 * @brief Spherical harmonics coefficient count. (3 * 3)
 */
const int32 shCoefCount = 9;

/**********************************************************************************************************************
 * @brief Converts texture coordinates to the clip space.
 * 
 * @param coords target texture coordinates.
 * @param invDim inverted texture dimension (size)
 */
static float2 coordsToST(uint2 coords, float invDim) noexcept
{
	return fma(1.0f - ((float2)coords + 0.5f) * invDim, float2(2.0f), float2(-1.0f));
}
/**
 * @brief Converts clip space coordinates to the cubemap direction.
 *
 * @param st target clip space coordinates.
 * @param face cubemap side index
 */
static float3 stToDir(float2 st, uint32 face) noexcept
{
	float3 dir;
	switch (face)
	{
	case 0: dir = float3( 1.0f,  st.y,  st.x); break;
	case 1: dir = float3(-1.0f,  st.y, -st.x); break;
	case 2: dir = float3(-st.x,  1.0f, -st.y); break;
	case 3: dir = float3(-st.x, -1.0f,  st.y); break;
	case 4: dir = float3(-st.x,  st.y,  1.0f); break;
	case 5: dir = float3( st.x,  st.y, -1.0f); break;
	default: abort();
	}
	return normalize(dir);
}
/**
 * @brief Converts texture coordinates to the cubemap direction.
 *
 * @param coords target texture coordinates.
 * @param invDim inverted texture dimension (size)
 */
static float3 coordsToDir(const uint3& coords, float invDim) noexcept
{
	auto st = coordsToST((uint2)coords, invDim);
	return stToDir(st, coords.z);
}

} // namespace math::ibl