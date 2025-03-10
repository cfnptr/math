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
 * @brief Common SIMD matrix transformation functions.
 */

#pragma once
#include "math/matrix/transform.hpp"
#include "math/simd/matrix/float.hpp"

namespace math
{

/**
 * @brief Returns total SIMD matrix translation transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static simd_f32_4 getTranslation(const simd_f32_4x4& m) noexcept
{
	return m.c3;
}
/**
 * @brief Sets total SIMD matrix translation transformation of an object in 3D space.
 * 
 * @param[out] m target model SIMD matrix to set
 * @param t target object position
 */
static void setTranslation(simd_f32_4x4& m, simd_f32_4 t) noexcept
{
	m.c3 = simd_f32_4(t, m.c3.getW());
}

/**
 * @brief Creates a new SIMD matrix with a specified object position in 3D space.
 * @param t target object translation
 */
static simd_f32_4x4 translate(simd_f32_4 t) noexcept
{
	return simd_f32_4x4(simd_f32_4(1.0f, 0.0f, 0.0f, 0.0f), simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f),
		simd_f32_4(0.0f, 0.0f, 1.0f, 0.0f), simd_f32_4(t, 1.0f));
}
/**
 * @brief Applies translation transformation to an object in 3D space. [r = m * translate(t)]
 * 
 * @param[in] m target model SIMD matrix to translate
 * @param t target object translation
 */
static simd_f32_4x4 translate(const simd_f32_4x4& m, simd_f32_4 t) noexcept
{
	return simd_f32_4x4(m.c0, m.c1, m.c2, simd_f32_4(m.c3 + multiply3x3(m, t), m.c3.getW()));
}
/**
 * @brief Applies translation transformation to an object in 3D space. [r = translate(t) * m]
 * 
 * @param t target object translation
 * @param[in] m target model SIMD matrix to translate
 */
static simd_f32_4x4 translate(simd_f32_4 t, const simd_f32_4x4& m) noexcept
{
	return simd_f32_4x4(m.c0, m.c1, m.c2, simd_f32_4(m.c3 + t, m.c3.getW()));
}

/***********************************************************************************************************************
 * @brief Creates a new SIMD matrix with a specified object scale in 3D space.
 * @param s target object scale
 */
static simd_f32_4x4 scale(simd_f32_4 s) noexcept
{
	return simd_f32_4x4(
		simd_f32_4(s.getX(), 0.0f, 0.0f, 0.0f),
		simd_f32_4(0.0f, s.getY(), 0.0f, 0.0f),
		simd_f32_4(0.0f, 0.0f, s.getZ(), 0.0f),
		simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Applies scale transformation to an object in 3D space. [r = m * scale(s)]
 *
 * @param[in] m target model SIMD matrix to scale
 * @param s target object scale
 */
static simd_f32_4x4 scale(const simd_f32_4x4& m, simd_f32_4 s) noexcept
{
	return simd_f32_4x4(m.c0 * simd_f32_4(s.getX()), 
		m.c1 * simd_f32_4(s.getY()), m.c2 * simd_f32_4(s.getZ()), m.c3);
}
/**
 * @brief Applies scale transformation to an object in 3D space. [r = scale(s) * m]
 *
 * @param[in] m target model SIMD matrix to scale
 * @param s target object scale
 */
static simd_f32_4x4 scale(simd_f32_4 s, const simd_f32_4x4& m) noexcept
{
	auto sm = scale(s);
	return simd_f32_4x4(sm * m.c0, sm * m.c1, sm * m.c2, sm * m.c3);
}

/**
 * @brief Extracts total SIMD matrix scale transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static simd_f32_4 extractScale(const simd_f32_4x4& m) noexcept
{
	return simd_f32_4(lengthSq3(m.c0), lengthSq3(m.c1), lengthSq3(m.c2));
}
/**
 * @brief Extracts total SIMD matrix 2D scale transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static float2 extractScale2(const simd_f32_4x4& m) noexcept
{
	return float2(lengthSq3(m.c0), length3(m.c1));
}

/***********************************************************************************************************************
 * @brief Creates a new SIMD matrix with a specified object rotation in 3D space.
 * @param q target object rotation
 */
static simd_f32_4x4 rotate(simd_f32_quat q) noexcept
{
	auto x = q.getX(), y = q.getY(), z = q.getZ(), w = q.getW();
	auto xx = x * x, yy = y * y, zz = z * z;
	auto xz = x * z, xy = x * y, yz = y * z;
	auto wx = w * x, wy = w * y, wz = w * z;

	return simd_f32_4x4(
		simd_f32_4(1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f),
		simd_f32_4(2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f),
		simd_f32_4(2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f),
		simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Calculates a new rotation SIMD matrix from look vectors in 3D space.
 *
 * @param lookFrom viewer position in 3D space
 * @param lookTo object position in 3D space
 * @param up space up direction vector
 */
static simd_f32_4x4 rotate(simd_f32_4 lookFrom, simd_f32_4 lookTo, 
	simd_f32_4 up = simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f)) noexcept
{
	auto f = normalize3(lookTo - lookFrom);
	auto s = normalize3(cross3(up, f));
	auto u = cross3(f, s);

	return simd_f32_4x4(simd_f32_4(s, 0.0f), simd_f32_4(u, 0.0f), 
		simd_f32_4(f, 0.0f), simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Calculates a new SIMD matrix from direction vector in 3D space.
 *
 * @param front view direction vector in 3D space
 * @param up space up direction vector
 */
static simd_f32_4x4 rotate(simd_f32_4 front, simd_f32_4 up = simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f)) noexcept
{
	auto s = normalize3(cross3(up, front));
	auto u = cross3(front, s);

	return simd_f32_4x4(simd_f32_4(s, 0.0f), simd_f32_4(u, 0.0f), 
		simd_f32_4(front, 0.0f), simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief Extracts total SIMD matrix rotation transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static simd_f32_4x4 extractRotation(const simd_f32_4x4& m) noexcept
{
	auto invScale = 1.0f / extractScale(m);
	auto c0 = m.c0 * invScale.getX();
	auto c1 = m.c1 * invScale.getY();
	auto c2 = m.c2 * invScale.getZ();
	
	return simd_f32_4x4(simd_f32_4(c0, 0.0f), simd_f32_4(c1, 0.0f), 
		simd_f32_4(c2, 0.0f), simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Extracts total SIMD matrix rotation transformation of an object in 3D space.
 * @warning Matrix should be only translated and/or rotated, without scaling!!!
 * @param[in] m target model SIMD matrix to extract from
 */
static simd_f32_4x4 extractRotationOnly(const simd_f32_4x4& m) noexcept
{
	return simd_f32_4x4(simd_f32_4(m.c0, 0.0f), simd_f32_4(m.c1, 0.0f), 
		simd_f32_4(m.c2, 0.0f), simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief Extracts total SIMD matrix rotation quaternion of an object in 3D space.
 * @param m target rotation SIMD matrix to extract from
 */
static simd_f32_quat extractQuat(simd_f32_4x4 m) noexcept
{
	auto c0X = m.c0.getX(), c1Y = m.c1.getY(), c2Z = m.c2.getZ();
	auto fourXSquaredMinus1 = c0X - c1Y - c2Z;
	auto fourYSquaredMinus1 = c1Y - c0X - c2Z;
	auto fourZSquaredMinus1 = c2Z - c0X - c1Y;
	auto fourWSquaredMinus1 = c0X + c1Y + c2Z;

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
	case 0: return simd_f32_quat((m.c1.getZ() - m.c2.getY()) * mult, 
		(m.c2.getX() - m.c0.getZ()) * mult, (m.c0.getY() - m.c1.getX()) * mult, biggestVal);
	case 1: return simd_f32_quat(biggestVal, (m.c0.getY() + m.c1.getX()) * mult, 
		(m.c2.getX() + m.c0.getZ()) * mult, (m.c1.getZ() - m.c2.getY()) * mult);
	case 2: return simd_f32_quat((m.c0.getY() + m.c1.getX()) * mult, biggestVal, 
		(m.c1.getZ() + m.c2.getY()) * mult, (m.c2.getX() - m.c0.getZ()) * mult);
	case 3: return simd_f32_quat((m.c2.getX() + m.c0.getZ()) * mult, 
		(m.c1.getZ() + m.c2.getY()) * mult, biggestVal, (m.c0.getY() - m.c1.getX()) * mult);
	default: abort();
	}
}

/***********************************************************************************************************************
 * @brief Calculates object model SIMD matrix from it position, rotation and scale.
 *
 * @param position object position in 3D space
 * @param rotation object rotation in 3D space
 * @param scale object scale in 3D space
 */
static simd_f32_4x4 calcModel(simd_f32_4 position = simd_f32_4::zero,
	simd_f32_quat rotation = simd_f32_quat::identity, simd_f32_4 scale = simd_f32_4::one) noexcept
{
	return scale == simd_f32_4::one ? translate(position, rotate(normalize3(rotation))) :
		translate(position) * rotate(normalize3(rotation)) * math::scale(scale);
}
/**
 * @brief Extracts total SIMD matrix position, rotation and scale of an object in 3D space. (Decompose)
 *
 * @param[in] m target model SIMD matrix to extract from
 * @param[out] position object position in 3D space
 * @param[out] rotation object rotation in 3D space
 * @param[out] scale object scale in 3D space
 */
static void extractTransform(const simd_f32_4x4& m, simd_f32_4& position, 
	simd_f32_quat& rotation, simd_f32_4& scale) noexcept
{
	position = getTranslation(m);
	rotation = extractQuat(extractRotation(m));
	scale = extractScale(m);
}
/**
 * @brief Extracts total SIMD matrix position and rotation of an object in 3D space. (Decompose)
 *
 * @param[in] m target model SIMD matrix to extract from
 * @param[out] position object position in 3D space
 * @param[out] rotation object rotation in 3D space
 */
static void extractTransform(const simd_f32_4x4& m, simd_f32_4& position, simd_f32_quat& rotation) noexcept
{
	position = getTranslation(m);
	rotation = extractQuat(extractRotationOnly(m));
}

/***********************************************************************************************************************
 * @brief Calculates a new SIMD model matrix from look vectors in 3D space.
 *
 * @param[in] from viewer position in 3D space
 * @param[in] to object position in 3D space
 * @param[in] up space up direction vector
 */
static simd_f32_4x4 lookAt(simd_f32_4 from, simd_f32_4 to, simd_f32_4 up = simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f)) noexcept
{
	auto f = normalize3(to - from);
	auto s = normalize3(cross3(up, f));
	auto u = cross3(f, s);

	return simd_f32_4x4(simd_f32_4(s, -dot3(s, from)), simd_f32_4(u, -dot3(u, from)), 
		simd_f32_4(f, -dot3(f, from)), simd_f32_4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Calculates a new SIMD quaternion from direction vector in 3D space.
 *
 * @param direction viewer direction in 3D space
 * @param up space up direction vector
 */
static simd_f32_quat lookAtQuat(simd_f32_4 direction, simd_f32_4 up = simd_f32_4(0.0f, 1.0f, 0.0f, 0.0f)) noexcept
{
	auto right = cross3(up, direction);
	auto c0 = right * (1.0f / std::sqrt(std::max(0.00001f, dot3(right, right))));
	auto c1 = cross3(right, c0);
	auto m = simd_f32_4x4(c0, c1, direction);
	return extractQuat(m);
}

/**
 * @brief Calculates translated/rotated SIMD matrix inverse.
 * @warning Matrix should be only translated and/or rotated, without scaling!!!
 * @param[in] m target SIMD matrix to inverse
 */
static simd_f32_4x4 inverseTransRot(const simd_f32_4x4& m)
{
	auto t = transpose4x4(m);
	setTranslation(t, -multiply3x3(t, getTranslation(m)));
	return t;
}

} // namespace math