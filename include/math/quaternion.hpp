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
 * @brief Common quaternion functions.
 * 
 * @details
 * Quaternion is a mathematical concept used to represent 3D rotations. It consists of four components (one real part 
 * and three imaginary parts) and is more efficient and stable for representing rotations than traditional methods 
 * like Euler angles or rotation matrices. Quaternions help avoid problems like gimbal lock and allow for smooth 
 * interpolation between rotations (known as SLERP). They are crucial for 3D transformations in animations, camera 
 * controls, object rotations, and physics simulations in real-time graphics.
 * 
 * Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/float.hpp"

namespace math
{

using namespace std;

/***********************************************************************************************************************
 * @brief Quaternion rotation container. (In 3D space)
 * @details Represents rotation using complex numbers, avoiding gimbal lock problem.
 */
struct quat : public float4
{
	/**
	 * @brief Creates a new quaternion structure.
	 * 
	 * @param x imaginary vector X part.
	 * @param y imaginary vector Y part.
	 * @param z imaginary vector Z part.
	 * @param w real scalar part.
	 */
	constexpr quat(float x, float y, float z, float w) noexcept : float4(x, y, z, w) { }
	/**
	 * @brief Creates a new identity quaternion structure.
	 * @param[in] xyzw quaternion parts vector.
	 */
	constexpr quat(const float4& xyzw = quat::identity) noexcept : float4(xyzw) { }
	/**
	 * @brief Creates a new quaternion structure from the euler angles. (In radians)
	 * @param[in] eulerAngles target euler angles vector
	 */
	quat(const float3& eulerAngles) noexcept
	{
		auto sin = math::sin(eulerAngles * 0.5f);
		auto cos = math::cos(eulerAngles * 0.5f);
		x = sin.x * cos.y * cos.z - cos.x * sin.y * sin.z;
		y = cos.x * sin.y * cos.z + sin.x * cos.y * sin.z;
		z = cos.x * cos.y * sin.z - sin.x * sin.y * cos.z;
		w = cos.x * cos.y * cos.z + sin.x * sin.y * sin.z;
	}
	/**
	 * @brief Creates a new quaternion structure from the angle and axis. (In radians)
	 * 
	 * @param angle target rotation around axis in radians
	 * @param[in] axis target axis to rotate around
	 */
	quat(float angle, const float3& axis) noexcept
	{
		auto sinus = std::sin(angle * 0.5f);
		x = axis.x * sinus;
		y = axis.y * sinus;
		z = axis.z * sinus;
		w = std::cos(angle * 0.5f);
	}

	/**
	 * @brief Rotates this quaternion by the specified one.
	 * @param[in] q target quaternion to rotate by
	 */
	constexpr quat operator*(const quat& q) const noexcept
	{
		return quat(
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x,
			w * q.w - x * q.x - y * q.y - z * q.z);
	}
	/**
	 * @brief Rotates vector by this quaternion.
	 * @param[in] v target vector to rotate
	 */
	float3 operator*(const float3& v) const noexcept
	{
		auto q = float3(x, y, z);
		auto cq = math::cross(q, v);
		auto ccq = math::cross(q, cq);
		return v + ((cq * w) + ccq) * 2.0f;
	}
	/**
	 * @brief Rotates this quaternion by the specified one.
	 * @param[in] q target quaternion to rotate by
	 */
	quat& operator*=(const quat& q) noexcept { return *this = *this * q; }

	/**
	 * @brief Extracts quaternion rotation around X axis. (In radians)
	 */
	float getPitch() const noexcept
	{
		auto yy = 2.0f * (y * z + w * x);
		auto xx = w * w - x * x - y * y + z * z;

		// Avoid atan2(0, 0) - handle singularity - Matiis
		if (std::abs(xx) <= numeric_limits<float>::epsilon() ||
			std::abs(yy) <= numeric_limits<float>::epsilon())
		{
			return 2.0f * std::atan2(x, w);
		}

		return std::atan2(yy, xx);
	}
	/**
	 * @brief Extracts quaternion around Y axis. (In radians)
	 */
	float getYaw() const noexcept { return std::asin(std::clamp(-2.0f * (x * z - w * y), -1.0f, 1.0f)); }
	/**
	 * @brief Extracts quaternion around Z axis. (In radians)
	 */
	float getRoll() const noexcept { return std::atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z); }
	/**
	 * @brief Calculates quaternion euler angles. (In radians)
	 */
	float3 toEulerAngles() const noexcept { return float3(getPitch(), getYaw(), getRoll()); }

	/**
	 * @brief Quaternion with zero rotation.
	 */
	static const quat identity;
};

inline const quat quat::identity = quat(0.0f, 0.0f, 0.0f, 1.0f);

/***********************************************************************************************************************
 * @brief Normalizes quaternion.
 * @param[in] q target quaternion to normalize
 */
static quat normalize(const quat& q) noexcept
{
	auto l = length(q);
	assert(l > 0.0f);
	auto il = (1.0f / l);
	return quat(q.x * il, q.y * il, q.z * il, q.w * il);
}
/**
 * @brief Quaternion spherical linear interpolation from a to b.
 * 
 * @param[in] a starting quaternion value
 * @param[in] a target quaternion value
 * @param t interpolation value (from 0.0 to 1.0)
 */
static quat slerp(const quat& a, const quat& b, float t) noexcept
{
	auto cosTheta = dot(a, b);
	auto c = b;

	if (cosTheta < 0.0f)
	{
		c = -b;
		cosTheta = -cosTheta;
	}

	if (cosTheta > 1.0f - numeric_limits<float>::epsilon())
	{
		return quat(lerp(a.x, c.x, t), lerp(a.y, c.y, t), lerp(a.z, c.z, t), lerp(a.w, c.w, t));
	}
	else
	{
		auto angle = std::acos(cosTheta);
		return (a * std::sin((1.0f - t) * angle) +  c * std::sin(t * angle)) / std::sin(angle);
	}
}

/**
 * @brief Inverts (undoes) quaternion rotation.
 * @param[in] q target quaternion to conjugate
 */
static quat conjugate(const quat& q) noexcept { return quat(-q.x, -q.y, -q.z, q.w); }
/**
 * @brief Calculates inverse of the quaternion.
 * @param[in] q target quaternion to inverse
 */
static quat inverse(const quat& q) noexcept { return conjugate(q) / dot(q, q);  }

/**
 * @brief Rotates vector by the inversed quaternion.
 * 
 * @param[in] v target vector to rotate
 * @param[in] q target quaternion to use
 */
static float3 operator*(const float3& v, const quat& q) noexcept { return inverse(q) * v; }

} // namespace math