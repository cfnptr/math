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
 * @brief Common single instruction multiple data (SIMD) floating point quaternion functions.
 */

#pragma once
#include "math/simd/vector/float.hpp"

namespace math
{

/**
 * @brief SIMD quaternion rotation container. (In 3D space)
 * @details Represents rotation using complex numbers, avoiding gimbal lock problem.
 */
struct [[nodiscard]] alignas(MATH_SIMD_VECTOR_ALIGNMENT) simd_f32_quat : public simd_f32_4
{
	/**
	 * @brief Creates a new identity SIMD quaternion structure.
	 * @note Identity quaternion represents rotation of 0 degrees around all axis.
	 * @param xyzw quaternion parts vector
	 */
	simd_f32_quat(simd_f32_4 xyzw = identity) noexcept : simd_f32_4(xyzw) { }
	/**
	 * @brief Creates a new SIMD quaternion structure.
	 * 
	 * @param x imaginary vector X part
	 * @param y imaginary vector Y part
	 * @param z imaginary vector Z part
	 * @param w real scalar part
	 */
	simd_f32_quat(float x, float y, float z, float w) noexcept : simd_f32_4(x, y, z, w) { }
	
	/**
	 * @brief Creates a new SIMD quaternion structure from the angle and axis. (In radians)
	 * 
	 * @param angle target rotation around axis in radians
	 * @param axis target 3D axis to rotate around
	 */
	simd_f32_quat(float angle, simd_f32_4 axis) noexcept
	{
		simd_f32_4 s, c;
		sinCos(simd_f32_4(angle * 0.5f), s, c);
		*this = select(simd_u32_4(0, 0, 0, UINT32_MAX), c, axis * s);
	}

	/**
	 * @brief Rotates this SIMD quaternion by the specified one.
	 * @param q target SIMD quaternion to rotate by
	 */
	simd_f32_quat operator*(simd_f32_quat q) const noexcept
	{
		auto x = getX(), y = getY(), z = getZ(), w = getW();
		auto qX = q.getX(), qY = q.getY(), qZ = q.getZ(), qW = q.getW();
		return simd_f32_quat(
			w * qX + x * qW + y * qZ - z * qY,
			w * qY + y * qW + z * qX - x * qZ,
			w * qZ + z * qW + x * qY - y * qX,
			w * qW - x * qX - y * qY - z * qZ);
	}
	/**
	 * @brief Rotates 3D vector by this SIMD quaternion.
	 * @param v target 3D vector to rotate
	 */
	simd_f32_4 operator*(simd_f32_4 v) const noexcept
	{
		auto cq = cross3(*this, v), ccq = cross3(*this, cq);
		return fma(fma(cq, simd_f32_4(getW()), ccq), simd_f32_4(2.0f), v);
	}
	/**
	 * @brief Rotates this SIMD quaternion by the specified one.
	 * @param q target SIMD quaternion to rotate by
	 */
	simd_f32_4& operator*=(simd_f32_4 q) noexcept { return *this = *this * q; }

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
	simd_f32_4 extractEulerAngles() const noexcept { return simd_f32_4(extractPitch(), extractYaw(), extractRoll()); }

	static const simd_f32_quat identity;
};

//**********************************************************************************************************************
inline const simd_f32_quat simd_f32_quat::identity = simd_f32_quat(0.0f, 0.0f, 0.0f, 1.0f);

/**
 * @brief Creates a new SIMD quaternion structure from the euler angles. (In radians)
 * @param eulerAngles target 3D euler angles SIMD vector
 */
static simd_f32_quat fromEulerAngles(simd_f32_4 eulerAngles) noexcept
{
	simd_f32_4 s, c;
	sinCos(eulerAngles * 0.5f, s, c);
	auto sX = s.getX(), sY = s.getY(), sZ = s.getZ();
	auto cX = c.getX(), cY = c.getY(), cZ = c.getZ();
	return simd_f32_quat(
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
static simd_f32_quat slerp(simd_f32_quat a, simd_f32_quat b, float t) noexcept
{
	auto cosTheta = dot4(a, b); auto c = (simd_f32_4)b;
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
		return ((simd_f32_4)a * std::sin((1.0f - t) * angle) + c * std::sin(t * angle)) / std::sin(angle);
	}
}

/**
 * @brief Inverts (undoes) SIMD quaternion rotation.
 * @param q target quaternion to conjugate
 */
static simd_f32_quat conjugate(simd_f32_quat q) noexcept
{
	static const auto mask = floatAsUint(simd_f32_4(-0.0f, -0.0f, -0.0f, 0.0f));
	return uintAsFloat(floatAsUint(q) ^ mask);
}
/**
 * @brief Calculates inverse of the SIMD quaternion.
 * @param q target quaternion to inverse
 */
static simd_f32_quat inverse(simd_f32_quat q) noexcept { return conjugate(q) / dot4(q, q);  }

/**
 * @brief Rotates 3D vector by the inversed SIMD quaternion.
 * 
 * @param v target 3D vector to rotate
 * @param q target SIMD quaternion to use
 */
static simd_f32_4 operator*(simd_f32_4 v, simd_f32_quat q) noexcept { return inverse(q) * v; }

} // namespace math