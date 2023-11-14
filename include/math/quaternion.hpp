//--------------------------------------------------------------------------------------------------
// Copyright 2022-2023 Nikita Fediuchin. All rights reserved.
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
//--------------------------------------------------------------------------------------------------

// All angles are in radians.

#pragma once
#include "math/vector.hpp"

namespace math
{

using namespace std;

struct quat : public float4
{
	quat(float x, float y, float z, float w) noexcept : float4(x, y, z, w) { }
	quat(const float4& xyzw = quat::identity) noexcept : float4(xyzw) { }
	quat(const float3& eulerAngles) noexcept
	{
		auto sin = math::sin(eulerAngles * 0.5f);
		auto cos = math::cos(eulerAngles * 0.5f);
		x = sin.x * cos.y * cos.z - cos.x * sin.y * sin.z;
		y = cos.x * sin.y * cos.z + sin.x * cos.y * sin.z;
		z = cos.x * cos.y * sin.z - sin.x * sin.y * cos.z;
		w = cos.x * cos.y * cos.z + sin.x * sin.y * sin.z;
	}
	quat(float angle, const float3& axis) noexcept
	{
		auto sinus = std::sin(angle * 0.5f);
		x = axis.x * sinus;
		y = axis.y * sinus;
		z = axis.z * sinus;
		w = std::cos(angle * 0.5f);
	}

	quat operator*(const quat& q) const noexcept
	{
		return quat(
			w * q.x + x * q.w + y * q.z - z * q.y,
			w * q.y + y * q.w + z * q.x - x * q.z,
			w * q.z + z * q.w + x * q.y - y * q.x,
			w * q.w - x * q.x - y * q.y - z * q.z);
	}
	float3 operator*(const float3& q) const noexcept
	{
		auto v = float3(x, y, z);
		auto cv = math::cross(v, q);
		auto ccv = math::cross(v, cv);
		return q + ((cv * w) + ccv) * 2.0f;
	}
	quat& operator*=(const quat& q) noexcept { return *this = *this * q; }

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
	float getYaw() const noexcept {
		return std::asin(std::clamp(-2.0f * (x * z - w * y), -1.0f, 1.0f)); }
	float getRoll() const noexcept {
		return std::atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z); }
	float3 toEulerAngles() const noexcept {
		return float3(getPitch(), getYaw(), getRoll()); }

	static const quat identity;
};

//--------------------------------------------------------------------------------------------------
static quat normalize(const quat& q) noexcept
{
	auto l = length(q);
	assert(l > 0.0f);
	auto il = (1.0f / l);
	return quat(q.x * il, q.y * il, q.z * il, q.w * il);
}
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
		return quat(lerp(a.x, c.x, t), lerp(a.y, c.y, t),
			lerp(a.z, c.z, t), lerp(a.w, c.w, t));
	}
	else
	{
		auto angle = std::acos(cosTheta);
		return (a * std::sin((1.0f - t) * angle) + 
			c * std::sin(t * angle)) / std::sin(angle);
	}
}

static quat conjugate(const quat& q) noexcept { return quat(-q.x, -q.y, -q.z, q.w); }
static quat inverse(const quat& q) noexcept { return conjugate(q) / dot(q, q);  }
static float3 operator*(const float3& v, const quat& q) noexcept { return inverse(q) * v; }

} // math