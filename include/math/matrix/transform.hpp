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
 * @brief Common matrix transformation functions.
 * 
 * @details
 * Coordinate system: X-right, Y-up, Z-forward (Left handed)
 * Matrices order: Column-major. (OpenGL, Vulkan like)
 * floatNxM - N columns and M rows
 * 
 * Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/matrix.hpp"

namespace math
{

/**
 * @brief Applies translation transformation to an object in 3D space.
 * 
 * @param[in] m target model matrix to translate
 * @param t target object translation
 */
static constexpr float4x4 translate(const float4x4& m, float3 t) noexcept
{
	return float4x4(m.c0, m.c1, m.c2, m.c0 * t.x + m.c1 * t.y + m.c2 * t.z + m.c3);
}
/**
 * @brief Creates a new matrix with a specified object position in 3D space.
 * @param t target object translation
 */
static constexpr float4x4 translate(float3 t) noexcept
{
	return float4x4(
		1.0f, 0.0f, 0.0f, t.x,
		0.0f, 1.0f, 0.0f, t.y,
		0.0f, 0.0f, 1.0f, t.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief Returns total matrix translation transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static constexpr float3 getTranslation(const float4x4& m) noexcept
{
	return (float3)m.c3;
}
/**
 * @brief Sets total matrix translation transformation of an object in 3D space.
 * 
 * @param[out] m target model matrix to set
 * @param t target object position
 */
static constexpr void setTranslation(float4x4& m, float3 t) noexcept
{
	m.c3 = float4(t, m.c3.w);
}

/**
 * @brief Adds translation of an object in 3D space to the matrix.
 * 
 * @param[out] m target model matrix to use
 * @param t target object position to add
 */
static constexpr void addTranslation(float4x4& m, float3 t) noexcept
{
	m.c3 = float4((float3)m.c3 + t, m.c3.w);
}

/***********************************************************************************************************************
 * @brief Applies scale transformation to an object in 3D space.
 *
 * @param[in] m target model matrix to scale
 * @param s target object scale
 */
static constexpr float4x4 scale(const float4x4& m, float3 s) noexcept
{
	return float4x4(m.c0 * s.x, m.c1 * s.y, m.c2 * s.z, m.c3);
}
/**
 * @brief Creates a new matrix with a specified object scale in 3D space.
 * @param s target object scale
 */
static constexpr float4x4 scale(float3 s) noexcept
{
	return float4x4(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief Extracts total matrix scale transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float3 extractScale(const float4x4& m) noexcept
{
	return float3(length((float3)m.c0), length((float3)m.c1), length((float3)m.c2));
}
/**
 * @brief Extracts total matrix 2D scale transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float2 extractScale2(const float4x4& m) noexcept
{
	return float2(length((float3)m.c0), length((float3)m.c1));
}

/***********************************************************************************************************************
 * @brief Creates a new matrix with a specified object rotation in 3D space.
 * @param q target object rotation
 */
static constexpr float4x4 rotate(quat q) noexcept
{
	auto xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
	auto xz = q.x * q.z, xy = q.x * q.y, yz = q.y * q.z;
	auto wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;

	return float4x4(
		1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
		2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f,
		2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates a new rotation matrix from look vectors in 3D space.
 *
 * @param[in] lookFrom viewer position in 3D space
 * @param[in] lookTo object position in 3D space
 * @param[in] up space up direction vector
 */
static float4x4 rotate(const float3& lookFrom, const float3& lookTo, const float3& up = float3::top) noexcept
{
	auto f = normalize(lookTo - lookFrom);
	auto s = normalize(cross(up, f));
	auto u = cross(f, s);

	return float4x4(
		s.x, s.y, s.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		f.x, f.y, f.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates a new matrix from direction vector in 3D space.
 *
 * @param[in] front view direction vector in 3D space
 * @param[in] up space up direction vector
 */
static float4x4 rotate(const float3& front, const float3& up = float3::top) noexcept
{
	auto f = front;
	auto s = normalize(cross(up, f));
	auto u = cross(f, s);

	return float4x4(
		s.x, s.y, s.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		f.x, f.y, f.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

/**
 * @brief Extracts total matrix rotation transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float4x4 extractRotation(const float4x4& m) noexcept
{
	auto invScale = 1.0f / extractScale(m);
	auto c0 = (float3)m.c0 * invScale.x;
	auto c1 = (float3)m.c1 * invScale.y;
	auto c2 = (float3)m.c2 * invScale.z;
	return float4x4(float4(c0, 0.0f), float4(c1, 0.0f), float4(c2, 0.0f), float4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief Extracts total matrix rotation quaternion of an object in 3D space.
 * @param[in] m target rotation matrix to extract from
 */
static quat extractQuat(const float3x3& m) noexcept
{
	auto fourXSquaredMinus1 = m.c0.x - m.c1.y - m.c2.z;
	auto fourYSquaredMinus1 = m.c1.y - m.c0.x - m.c2.z;
	auto fourZSquaredMinus1 = m.c2.z - m.c0.x - m.c1.y;
	auto fourWSquaredMinus1 = m.c0.x + m.c1.y + m.c2.z;

	int biggestIndex = 0;
	auto fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	auto biggestVal = std::sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
	auto mult = 0.25f / biggestVal;

	switch (biggestIndex)
	{
	case 0: return quat((m.c1.z - m.c2.y) * mult, (m.c2.x - m.c0.z) * mult, (m.c0.y - m.c1.x) * mult, biggestVal);
	case 1: return quat(biggestVal, (m.c0.y + m.c1.x) * mult, (m.c2.x + m.c0.z) * mult, (m.c1.z - m.c2.y) * mult);
	case 2: return quat((m.c0.y + m.c1.x) * mult, biggestVal, (m.c1.z + m.c2.y) * mult, (m.c2.x - m.c0.z) * mult);
	case 3: return quat((m.c2.x + m.c0.z) * mult, (m.c1.z + m.c2.y) * mult, biggestVal, (m.c0.y - m.c1.x) * mult);
	default: abort();
	}
}
/**
 * @brief Extracts total matrix rotation quaternion of an object in 3D space.
 * @param[in] m target rotation matrix to extract from
 */
static quat extractQuat(const float4x4& m) noexcept
{
	return extractQuat((float3x3)m);
}

/***********************************************************************************************************************
 * @brief Calculates object model matrix from it position, rotation and scale.
 *
 * @param[in] position object position in 3D space
 * @param[in] rotation object rotation in 3D space
 * @param[in] scale object scale in 3D space
 */
static float4x4 calcModel(const float3& position = float3(0.0f),
	const quat& rotation = quat::identity, const float3& scale = float3(1.0f)) noexcept
{
	return translate(position) * rotate(normalize(rotation)) * math::scale(scale);
}
/**
 * @brief Extracts total matrix position, rotation and scale of an object in 3D space. (Decompose)
 *
 * @param[in] m target model matrix to extract from
 * @param[out] position object position in 3D space
 * @param[out] scale object scale in 3D space
 * @param[out] rotation object rotation in 3D space
 */
static void extractTransform(const float4x4& m, float3& position, float3& scale, quat& rotation) noexcept
{
	position = getTranslation(m);
	scale = extractScale(m);
	rotation = extractQuat(extractRotation(m));
}

/***********************************************************************************************************************
 * @brief Calculates a new model matrix from look vectors in 3D space.
 *
 * @param[in] from viewer position in 3D space
 * @param[in] to object position in 3D space
 * @param[in] up space up direction vector
 */
static float4x4 lookAt(const float3& from, const float3& to, const float3& up = float3::top) noexcept
{
	auto f = normalize(to - from);
	auto s = normalize(cross(up, f));
	auto u = cross(f, s);
	return float4x4(
		s.x, s.y, s.z, -dot(s, from),
		u.x, u.y, u.z, -dot(u, from),
		f.x, f.y, f.z, -dot(f, from),
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates a new quaternion from direction vector in 3D space.
 *
 * @param[in] direction viewer direction in 3D space
 * @param[in] up space up direction vector
 */
static quat lookAtQuat(const float3& direction, const float3& up = float3::top) noexcept
{
	auto right = cross(up, direction);
	auto c0 = right * (1.0f / std::sqrt(std::max(0.00001f, dot(right, right))));
	auto c1 = cross(right, c0);
	auto m = float3x3(c0, c1, direction);
	return extractQuat(m);
}

} // namespace math