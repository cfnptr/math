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
 * @brief Common floating point quaternion functions.
 * 
 * @details
 * Quaternion is a mathematical concept used to represent 3D rotations. It consists of four components (one real part 
 * and three imaginary parts) and is more efficient and stable for representing rotations than traditional methods 
 * like Euler angles or rotation matrices. Quaternions help avoid problems like gimbal lock and allow for smooth 
 * interpolation between rotations (known as SLERP). They are crucial for 3D transformations in animations, camera 
 * controls, object rotations, and physics simulations in real-time graphics.
 */

#pragma once
#include "math/simd/vector/float.hpp"

namespace math
{

/**
 * @brief SIMD 32bit floating point quaternion rotation container. (In 3D space)
 * @details Represents rotation using complex numbers, avoiding gimbal lock problem.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) quat : public f32x4
{
	/**
	 * @brief Creates a new identity SIMD 32bit floating point quaternion structure.
	 * @note Identity quaternion represents rotation of 0 degrees around all axis.
	 * @param xyzw quaternion parts vector
	 */
	quat(f32x4 xyzw = identity) noexcept : f32x4(xyzw) { }
	/**
	 * @brief Creates a new SIMD 32bit floating point quaternion structure.
	 * 
	 * @param x imaginary vector X part
	 * @param y imaginary vector Y part
	 * @param z imaginary vector Z part
	 * @param w real scalar part
	 */
	quat(float x, float y, float z, float w) noexcept : f32x4(x, y, z, w) { }

	#if defined(MATH_SIMD_SUPPORT_SSE) || defined(MATH_SIMD_SUPPORT_NEON)
	/**
	 * @brief Creates a new SIMD 32bit floating point quaternion structure.
	 * @param data target vector floating point SIMD data
	 */
	quat(_simd_f128 data) : f32x4(data) { }
	#endif
	
	/**
	 * @brief Creates a new SIMD quaternion structure from the angle and axis. (In radians)
	 * 
	 * @param angle target rotation around axis in radians
	 * @param axis target 3D axis to rotate around
	 */
	quat(float angle, f32x4 axis) noexcept
	{
		f32x4 s, c;
		sinCos(f32x4(angle * 0.5f), s, c);
		*this = select(u32x4(0, 0, 0, UINT32_MAX), c, axis * s);
	}

	/**
	 * @brief Rotates this SIMD quaternion by the specified one.
	 * @param q target SIMD quaternion to rotate by
	 */
	quat operator*(quat q) const noexcept
	{
		auto x = getX(), y = getY(), z = getZ(), w = getW();
		auto qX = q.getX(), qY = q.getY(), qZ = q.getZ(), qW = q.getW();
		return quat(
			w * qX + x * qW + y * qZ - z * qY,
			w * qY + y * qW + z * qX - x * qZ,
			w * qZ + z * qW + x * qY - y * qX,
			w * qW - x * qX - y * qY - z * qZ);
	}
	/**
	 * @brief Rotates 3D vector by this SIMD quaternion.
	 * @param v target 3D vector to rotate
	 */
	f32x4 operator*(f32x4 v) const noexcept
	{
		auto cq = cross3(*this, v), ccq = cross3(*this, cq);
		return fma(fma(cq, splatW(), ccq), f32x4(2.0f), v);
	}
	/**
	 * @brief Rotates this SIMD quaternion by the specified one.
	 * @param v target SIMD quaternion to rotate by
	 */
	quat& operator*=(quat v) noexcept { return *this = *this * v; }

	/**
	 * @brief Extracts SIMD quaternion rotation around X axis. (In radians)
	 */
	float extractPitch() const noexcept
	{
		auto x = getX(), y = getY(), z = getZ(), w = getW();
		auto yy = 2.0f * (y * z + w * x);
		auto xx = w * w - x * x - y * y + z * z;

		// Avoid atan2(0, 0) - handle singularity - Matiis
		if (std::abs(xx) <= FLT_EPSILON || std::abs(yy) <= FLT_EPSILON)
			return 2.0f * std::atan2(x, w);
		return std::atan2(yy, xx);
	}
	/**
	 * @brief Extracts SIMD quaternion around Y axis. (In radians)
	 */
	float extractYaw() const noexcept
	{
		return std::asin(std::clamp(-2.0f * (getX() * getZ() - getW() * getY()), -1.0f, 1.0f));
	}
	/**
	 * @brief Extracts SIMD quaternion around Z axis. (In radians)
	 */
	float extractRoll() const noexcept
	{
		auto x = getX(), y = getY(), z = getZ(), w = getW();
		return std::atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z);
	}
	/**
	 * @brief Calculates SIMD quaternion euler angles. (In radians)
	 */
	f32x4 extractEulerAngles() const noexcept { return f32x4(extractPitch(), extractYaw(), extractRoll()); }

	static const quat identity;
};

//**********************************************************************************************************************
inline const quat quat::identity = quat(0.0f, 0.0f, 0.0f, 1.0f);

/**
 * @brief Returns normalized SIMD quaternion. (Improves precision)
 * @param q target SIMD quaternion to normalize
 */
static quat normalize(quat q) noexcept { return normalize4(q); }

/**
 * @brief Creates a new SIMD quaternion structure from the euler angles. (In radians)
 * @param eulerAngles target 3D euler angles SIMD vector
 */
static quat fromEulerAngles(f32x4 eulerAngles) noexcept
{
	f32x4 s, c;
	sinCos(eulerAngles * 0.5f, s, c);
	auto sX = s.getX(), sY = s.getY(), sZ = s.getZ();
	auto cX = c.getX(), cY = c.getY(), cZ = c.getZ();
	return quat(
		sX * cY * cZ - cX * sY * sZ,
		cX * sY * cZ + sX * cY * sZ,
		cX * cY * sZ - sX * sY * cZ,
		cX * cY * cZ + sX * sY * sZ);
}

/**
 * @brief SIMD quaternion spherical linear interpolation from a to b.
 * 
 * @param a starting SIMD quaternion value
 * @param b target SIMD quaternion value
 * @param t interpolation value (from 0.0 to 1.0)
 */
static quat slerp(quat a, quat b, float t) noexcept
{
	auto cosTheta = dot4(a, b); auto c = (f32x4)b;
	if (cosTheta < 0.0f)
	{
		c = -b;
		cosTheta = -cosTheta;
	}

	if (cosTheta > 1.0f - FLT_EPSILON)
	{
		return lerp(a, c, t);
	}
	else
	{
		auto angle = std::acos(cosTheta);
		return ((f32x4)a * std::sin((1.0f - t) * angle) + c * std::sin(t * angle)) / std::sin(angle);
	}
}

/**
 * @brief Inverts (undoes) SIMD quaternion rotation.
 * @param q target quaternion to conjugate
 */
static quat conjugate(quat q) noexcept
{
	return q.flipSign<-1, -1, -1, 1>();
}
/**
 * @brief Calculates inverse of the SIMD quaternion.
 * @param q target quaternion to inverse
 */
static quat inverse(quat q) noexcept { return conjugate(q) / dot4(q, q);  }

/**
 * @brief Rotates 3D vector by the inversed SIMD quaternion.
 * 
 * @param v target 3D vector to rotate
 * @param q target SIMD quaternion to use
 */
static f32x4 operator*(f32x4 v, quat q) noexcept { return inverse(q) * v; }

} // namespace math