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
 * @brief Common SIMD matrix transformation functions.
 */

#pragma once
#include "math/matrix.hpp"
#include "math/quaternion.hpp"

namespace math
{

/**
 * @brief Returns total SIMD matrix translation transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static f32x4 getTranslation(const f32x4x4& m) noexcept
{
	return m.c3;
}
/**
 * @brief Sets total SIMD matrix translation transformation of an object in 3D space.
 * 
 * @param[out] m target model SIMD matrix to set
 * @param t target object position
 */
static void setTranslation(f32x4x4& m, f32x4 t) noexcept
{
	m.c3 = f32x4(t, m.c3.getW());
}

/**
 * @brief Creates a new SIMD matrix with a specified object position in 3D space.
 * @param t target object translation
 */
static f32x4x4 translate(f32x4 t) noexcept
{
	return f32x4x4(f32x4(1.0f, 0.0f, 0.0f, 0.0f), f32x4(0.0f, 1.0f, 0.0f, 0.0f),
		f32x4(0.0f, 0.0f, 1.0f, 0.0f), f32x4(t, 1.0f));
}
/**
 * @brief Applies translation transformation to an object in 3D space. [r = m * translate(t)]
 * 
 * @param[in] m target model SIMD matrix to translate
 * @param t target object translation
 */
static f32x4x4 translate(const f32x4x4& m, f32x4 t) noexcept
{
	return f32x4x4(m.c0, m.c1, m.c2, f32x4(m.c3 + multiply3x3(m, t), m.c3.getW()));
}
/**
 * @brief Applies translation transformation to an object in 3D space. [r = translate(t) * m]
 * 
 * @param t target object translation
 * @param[in] m target model SIMD matrix to translate
 */
static f32x4x4 translate(f32x4 t, const f32x4x4& m) noexcept
{
	return f32x4x4(m.c0, m.c1, m.c2, f32x4(m.c3 + t, m.c3.getW()));
}

/***********************************************************************************************************************
 * @brief Creates a new SIMD matrix with a specified object scale in 3D space.
 * @param s target object scale
 */
static f32x4x4 scale(f32x4 s) noexcept
{
	return f32x4x4(f32x4(s.getX(), 0.0f, 0.0f, 0.0f), f32x4(0.0f, s.getY(), 0.0f, 0.0f),
		f32x4(0.0f, 0.0f, s.getZ(), 0.0f), f32x4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Applies scale transformation to an object in 3D space. [r = m * scale(s)]
 *
 * @param[in] m target model SIMD matrix to scale
 * @param s target object scale
 */
static f32x4x4 scale(const f32x4x4& m, f32x4 s) noexcept
{
	return f32x4x4(m.c0 * f32x4(s.getX()), m.c1 * f32x4(s.getY()), m.c2 * f32x4(s.getZ()), m.c3);
}
/**
 * @brief Applies scale transformation to an object in 3D space. [r = scale(s) * m]
 *
 * @param[in] m target model SIMD matrix to scale
 * @param s target object scale
 */
static f32x4x4 scale(f32x4 s, const f32x4x4& m) noexcept
{
	auto sm = scale(s);
	return f32x4x4(sm * m.c0, sm * m.c1, sm * m.c2, sm * m.c3);
}

/**
 * @brief Extracts total SIMD matrix scale transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static f32x4 extractScale(const f32x4x4& m) noexcept
{
	return f32x4(length3(m.c0), length3(m.c1), length3(m.c2));
}
/**
 * @brief Extracts total SIMD matrix 2D scale transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static float2 extractScale2(const f32x4x4& m) noexcept
{
	return float2(length3(m.c0), length3(m.c1));
}

/***********************************************************************************************************************
 * @brief Creates a new SIMD matrix with a specified object rotation in 3D space.
 * @param q target object rotation
 */
static f32x4x4 rotate(quat q) noexcept
{
	auto x = q.getX(), y = q.getY(), z = q.getZ(), w = q.getW();
	auto xx = x * x, yy = y * y, zz = z * z;
	auto xz = x * z, xy = x * y, yz = y * z;
	auto wx = w * x, wy = w * y, wz = w * z;

	return f32x4x4(
		f32x4(1.0f - 2.0f * (yy + zz), 2.0f * (xy + wz), 2.0f * (xz - wy), 0.0f),
		f32x4(2.0f * (xy - wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz + wx), 0.0f),
		f32x4(2.0f * (xz + wy), 2.0f * (yz - wx), 1.0f - 2.0f * (xx + yy), 0.0f),
		f32x4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Calculates a new rotation SIMD matrix from look vectors in 3D space.
 *
 * @param lookFrom viewer position in 3D space
 * @param lookTo object position in 3D space
 * @param up space up direction vector
 */
static f32x4x4 rotate(f32x4 lookFrom, f32x4 lookTo, f32x4 up = f32x4::top) noexcept
{
	auto f = normalize3(lookTo - lookFrom);
	auto s = normalize3(cross3(up, f));
	auto u = cross3(f, s);

	return f32x4x4(f32x4(s, 0.0f), f32x4(u, 0.0f), 
		f32x4(f, 0.0f), f32x4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Calculates a new SIMD matrix from direction vector in 3D space.
 *
 * @param front view direction vector in 3D space
 * @param up space up direction vector
 */
static f32x4x4 rotate(f32x4 front, f32x4 up = f32x4::top) noexcept
{
	auto s = normalize3(cross3(up, front));
	auto u = cross3(front, s);

	return f32x4x4(f32x4(s, 0.0f), f32x4(u, 0.0f), 
		f32x4(front, 0.0f), f32x4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief Extracts total SIMD matrix rotation transformation of an object in 3D space.
 * @param[in] m target model SIMD matrix to extract from
 */
static f32x4x4 extractRotation(const f32x4x4& m) noexcept
{
	auto invScale = 1.0f / extractScale(m);
	auto c0 = m.c0 * invScale.getX();
	auto c1 = m.c1 * invScale.getY();
	auto c2 = m.c2 * invScale.getZ();
	
	return f32x4x4(f32x4(c0, 0.0f), f32x4(c1, 0.0f), 
		f32x4(c2, 0.0f), f32x4(0.0f, 0.0f, 0.0f, 1.0f));
}
/**
 * @brief Extracts total SIMD matrix rotation transformation of an object in 3D space.
 * @warning Matrix should be only translated and/or rotated, without scaling!!!
 * @param[in] m target model SIMD matrix to extract from
 */
static f32x4x4 extractRotationOnly(const f32x4x4& m) noexcept
{
	return f32x4x4(f32x4(m.c0, 0.0f), f32x4(m.c1, 0.0f), 
		f32x4(m.c2, 0.0f), f32x4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief Extracts total SIMD matrix rotation quaternion of an object in 3D space.
 * @param m target rotation SIMD matrix to extract from
 */
static quat extractQuat(f32x4x4 m) noexcept
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
	case 0: return quat((m.c1.getZ() - m.c2.getY()) * mult, 
		(m.c2.getX() - m.c0.getZ()) * mult, (m.c0.getY() - m.c1.getX()) * mult, biggestVal);
	case 1: return quat(biggestVal, (m.c0.getY() + m.c1.getX()) * mult, 
		(m.c2.getX() + m.c0.getZ()) * mult, (m.c1.getZ() - m.c2.getY()) * mult);
	case 2: return quat((m.c0.getY() + m.c1.getX()) * mult, biggestVal, 
		(m.c1.getZ() + m.c2.getY()) * mult, (m.c2.getX() - m.c0.getZ()) * mult);
	case 3: return quat((m.c2.getX() + m.c0.getZ()) * mult, 
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
static f32x4x4 calcModel(f32x4 position = f32x4::zero,
	quat rotation = quat::identity, f32x4 scale = f32x4::one) noexcept
{
	return scale == f32x4::one ? translate(position, rotate(normalize(rotation))) :
		translate(position) * rotate(normalize(rotation)) * math::scale(scale);
}
/**
 * @brief Extracts total SIMD matrix position, rotation and scale of an object in 3D space. (Decompose)
 *
 * @param[in] m target model SIMD matrix to extract from
 * @param[out] position object position in 3D space
 * @param[out] rotation object rotation in 3D space
 * @param[out] scale object scale in 3D space
 */
static void extractTransform(const f32x4x4& m, f32x4& position, quat& rotation, f32x4& scale) noexcept
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
static void extractTransform(const f32x4x4& m, f32x4& position, quat& rotation) noexcept
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
static f32x4x4 lookAt(f32x4 from, f32x4 to, f32x4 up = f32x4::top) noexcept
{
	auto f = normalize3(to - from);
	auto s = normalize3(cross3(up, f));
	auto u = cross3(f, s);

	return transpose4x4(f32x4x4(f32x4(s, -dot3(s, from)), f32x4(u, -dot3(u, from)), 
		f32x4(f, -dot3(f, from)), f32x4(0.0f, 0.0f, 0.0f, 1.0f)));
}
/**
 * @brief Calculates a new SIMD quaternion from direction vector in 3D space.
 *
 * @param direction viewer direction in 3D space
 * @param up space up direction vector
 */
static quat lookAtQuat(f32x4 direction, f32x4 up = f32x4::top) noexcept
{
	auto right = cross3(up, direction);
	auto c0 = right * (1.0f / std::sqrt(std::max(0.00001f, dot3(right, right))));
	auto c1 = cross3(right, c0);
	auto m = f32x4x4(c0, c1, direction);
	return extractQuat(m);
}

/**
 * @brief Calculates translated/rotated SIMD matrix inverse.
 * @warning Matrix should be only translated and/or rotated, without scaling!!!
 * @param[in] m target SIMD matrix to inverse
 */
static f32x4x4 inverseTransRot(const f32x4x4& m)
{
	auto t = transpose4x4(m);
	setTranslation(t, -multiply3x3(t, getTranslation(m)));
	return t;
}

inline static const f32x4x4 leftLookAt = lookAt(f32x4::zero, f32x4::left, f32x4::top);
inline static const f32x4x4 rightLookAt = lookAt(f32x4::zero, f32x4::right, f32x4::top);
inline static const f32x4x4 bottomLookAt = lookAt(f32x4::zero, f32x4::bottom, f32x4::front);
inline static const f32x4x4 topLookAt = lookAt(f32x4::zero, f32x4::top, f32x4::back);
inline static const f32x4x4 backLookAt = lookAt(f32x4::zero, f32x4::back, f32x4::top);
inline static const f32x4x4 frontLookAt = lookAt(f32x4::zero, f32x4::front, f32x4::top);
inline static const f32x4x4 sideLookAts[6] = { leftLookAt, rightLookAt, bottomLookAt, topLookAt, backLookAt, frontLookAt };

} // namespace math