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

/***********************************************************************************************************************
 * @file
 * @brief Common projection matrix functions.
 * 
 * @details
 * Coordinate system: X-right, Y-up, Z-forward (Left handed)
 * Matrices order: Column-major. (OpenGL, Vulkan like)
 * floatNxM - N columns and M rows
 * 
 * Projection matrices are fixed for the Vulkan NDC space.
 * http://matthewwellings.com/blog/the-new-vulkan-coordinate-system/
 * 
 * Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/matrix.hpp"

namespace math
{

/***********************************************************************************************************************
 * @brief Calculates infinite reversed Z perspective projection matrix.
 *
 * @param fieldOfView camera field of view in radians
 * @param aspectRatio camera aspect ratio (ex. width / height)
 * @param nearPlane distance to the camera near plane
 */
static float4x4 calcPerspProjInfRevZ(float fieldOfView, float aspectRatio, float nearPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);
	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, nearPlane,
		0.0f, 0.0f, 1.0f, 0.0f);
}
/**
 * @brief Calculates reversed Z perspective projection matrix.
 *
 * @param fieldOfView camera field of view in radians
 * @param aspectRatio camera aspect ratio (ex. width / height)
 * @param nearPlane distance to the camera near plane
 * @param farPlane distance to the camera far plane
 */
static float4x4 calcPerspProjRevZ(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);
	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, nearPlane / (nearPlane - farPlane),
		-(nearPlane * farPlane) / (nearPlane - farPlane),
		0.0f, 0.0f, 1.0f, 0.0f);
}
/**
 * @brief Calculates perspective projection matrix.
 *
 * @param fieldOfView camera field of view in radians
 * @param aspectRatio camera aspect ratio (ex. width / height)
 * @param nearPlane distance to the camera near plane
 * @param farPlane distance to the camera far plane
 */
static float4x4 calcPerspProj(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);
	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, farPlane / (farPlane - nearPlane),
		-(farPlane * nearPlane) / (farPlane - nearPlane),
		0.0f, 0.0f, 1.0f, 0.0f);
}

/***********************************************************************************************************************
 * @brief Calculates reversed Z orthographic projection matrix.
 *
 * @param width camera width (ex. from -1.0 to 1.0)
 * @param height camera heght (ex. from -1.0 to 1.0)
 * @param depth camera depth (ex. from 0.0 to 1.0)
 */
static float4x4 calcOrthoProjRevZ(float2 width, float2 height, float2 depth) noexcept
{
	return float4x4(
		2.0f / (width.y - width.x), 0.0f, 0.0f, -(width.y + width.x) / (width.y - width.x),
		0.0f, -2.0f / (height.y - height.x), 0.0f, (height.y + height.x) / (height.y - height.x),
		0.0f, 0.0f, 1.0f / (depth.x - depth.y), -depth.y / (depth.x - depth.y),
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates orthographic projection matrix.
 *
 * @param width camera width (ex. from -1.0 to 1.0)
 * @param height camera heght (ex. from -1.0 to 1.0)
 * @param depth camera depth (ex. from 0.0 to 1.0)
 */
static float4x4 calcOrthoProj(float2 width, float2 height, float2 depth) noexcept
{
	return float4x4(
		2.0f / (width.y - width.x), 0.0f, 0.0f, -(width.y + width.x) / (width.y - width.x),
		0.0f, -2.0f / (height.y - height.x), 0.0f, (height.y + height.x) / (height.y - height.x),
		0.0f, 0.0f, 1.0f / (depth.y - depth.x), -depth.x / (depth.y - depth.x),
		0.0f, 0.0f, 0.0f, 1.0f);
}

} // namespace math