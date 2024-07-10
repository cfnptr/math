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

// Coordinate system: X-right, Y-up, Z-forward (Left handed)
// Matrices are column-major. (OpenGL, Vulkan like)
// floatNxM - N columns and M rows

#pragma once
#include "math/quaternion.hpp"

namespace math
{

//**********************************************************************************************************************
struct float2x2
{
	float2 c0, c1;

	explicit float2x2(float v = 0.0f) noexcept { this->c0 = v; this->c1 = v; }
	float2x2(float2 c0, float2 c1) noexcept { this->c0 = c0; this->c1 = c1; }
	float2x2(
		float c0r0, float c1r0,
		float c0r1, float c1r1) noexcept
	{
		this->c0 = float2(c0r0, c0r1);
		this->c1 = float2(c1r0, c1r1);
	}
	
	float2& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((float2*)this)[i];
	}
	float2 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((float2*)this)[i];
	}

	float2x2 operator*(float v) const noexcept { return float2x2(c0 * v, c1 * v); }
	float2x2 operator*(const float2x2& m) const noexcept
	{
		return float2x2(
			c0 * m.c0.x + c1 * m.c0.y,
			c0 * m.c1.x + c1 * m.c1.y);
	}
	float2 operator*(float2 v) const noexcept
	{
		return float2(
			c0.x * v.x + c1.x * v.y,
			c0.y * v.x + c1.y * v.y);
	}
	float2x2& operator*=(const float2x2& m) noexcept { return *this = *this * m; }

	bool operator==(const float2x2& v) const noexcept { return memcmp(this, &v, sizeof(float) * 2 * 2) == 0; }
	bool operator!=(const float2x2& v) const noexcept { return memcmp(this, &v, sizeof(float) * 2 * 2) != 0; }

	static const float2x2 identity;
};

//**********************************************************************************************************************
struct float3x3
{
	float3 c0, c1, c2;

	explicit float3x3(float v = 0.0f) noexcept { this->c0 = v; this->c1 = v; this->c2 = v; }
	float3x3(const float3& c0, const float3& c1, const float3& c2) noexcept
	{
		this->c0 = c0; this->c1 = c1; this->c2 = c2;
	}
	float3x3(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1,
		float c0r2, float c1r2, float c2r2) noexcept
	{
		this->c0 = float3(c0r0, c0r1, c0r2);
		this->c1 = float3(c1r0, c1r1, c1r2);
		this->c2 = float3(c2r0, c2r1, c2r2);
	}
	
	float3& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((float3*)this)[i];
	}
	const float3& operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float3*)this)[i];
	}

	float3x3 operator*(float v) const noexcept { return float3x3(c0 * v, c1 * v, c2 * v); }
	float3x3 operator*(const float3x3& m) const noexcept
	{
		return float3x3(
			c0 * m.c0.x + c1 * m.c0.y + c2 * m.c0.z,
			c0 * m.c1.x + c1 * m.c1.y + c2 * m.c1.z,
			c0 * m.c2.x + c1 * m.c2.y + c2 * m.c2.z);
	}
	float3 operator*(const float3& v) const noexcept
	{
		return float3(
			c0.x * v.x + c1.x * v.y + c2.x * v.z,
			c0.y * v.x + c1.y * v.y + c2.y * v.z,
			c0.z * v.x + c1.z * v.y + c2.z * v.z);
	}
	float3x3& operator*=(const float3x3& m) noexcept { return *this = *this * m; }

	bool operator==(const float3x3& v) const noexcept { return memcmp(this, &v, sizeof(float) * 3 * 3) == 0; }
	bool operator!=(const float3x3& v) const noexcept { return memcmp(this, &v, sizeof(float) * 3 * 3) != 0; }

	static const float3x3 identity;
};

//**********************************************************************************************************************
struct float4x4
{
	float4 c0, c1, c2, c3;

	explicit float4x4(float v = 0.0f) noexcept { this->c0 = v; this->c1 = v; this->c2 = v; this->c3 = v; }
	float4x4(const float4& c0, const float4& c1, const float4& c2, const float4& c3) noexcept
	{
		this->c0 = c0; this->c1 = c1; this->c2 = c2; this->c3 = c3;
	}
	float4x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2,
		float c0r3, float c1r3, float c2r3, float c3r3) noexcept
	{
		this->c0 = float4(c0r0, c0r1, c0r2, c0r3);
		this->c1 = float4(c1r0, c1r1, c1r2, c1r3);
		this->c2 = float4(c2r0, c2r1, c2r2, c2r3);
		this->c3 = float4(c3r0, c3r1, c3r2, c3r3);
	}

	explicit operator float3x3() const noexcept { return float3x3((float3)c0, (float3)c1, (float3)c2); }
	explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }
		
	float4& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((float4*)this)[i];
	}
	const float4& operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float4*)this)[i];
	}

	float4x4 operator*(float v) const noexcept { return float4x4(c0 * v, c1 * v, c2 * v, c3 * v); }
	float4x4 operator*(const float4x4& m) const noexcept
	{
		return float4x4(
			c0 * m.c0.x + c1 * m.c0.y + c2 * m.c0.z + c3 * m.c0.w,
			c0 * m.c1.x + c1 * m.c1.y + c2 * m.c1.z + c3 * m.c1.w,
			c0 * m.c2.x + c1 * m.c2.y + c2 * m.c2.z + c3 * m.c2.w,
			c0 * m.c3.x + c1 * m.c3.y + c2 * m.c3.z + c3 * m.c3.w);
	}
	float4 operator*(const float4& v) const noexcept
	{
		return float4(
			c0.x * v.x + c1.x * v.y + c2.x * v.z + c3.x * v.w,
			c0.y * v.x + c1.y * v.y + c2.y * v.z + c3.y * v.w,
			c0.z * v.x + c1.z * v.y + c2.z * v.z + c3.z * v.w,
			c0.w * v.x + c1.w * v.y + c2.w * v.z + c3.w * v.w);
	}
	float4x4& operator*=(const float4x4& m) noexcept { return *this = *this * m; }

	bool operator==(const float4x4& v) const noexcept { return memcmp(this, &v, sizeof(float) * 4 * 4) == 0; }
	bool operator!=(const float4x4& v) const noexcept { return memcmp(this, &v, sizeof(float) * 4 * 4) != 0; }

	static const float4x4 identity;
};

//**********************************************************************************************************************
static float2 operator*(float2 v, const float2x2& m) noexcept
{
	return float2(
		m.c0.x * v.x + m.c1.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y);
}
static float2x2 transpose(const float2x2& m) noexcept
{
	return float2x2(
		m.c0.x, m.c0.y,
		m.c1.x, m.c1.y);
}
static float2x2 inverse(const float2x2& matrix) noexcept
{
	auto m = matrix;
	auto oneOverDeterminant = 1.0f / (m.c0.x * m.c1.y - m.c1.x * m.c0.y);
	return float2x2(m.c1.y * oneOverDeterminant, -m.c0.y * oneOverDeterminant,
		-m.c1.x * oneOverDeterminant, m.c0.x * oneOverDeterminant);
}

static float3 operator*(const float3& v, const float3x3& m) noexcept
{
	return float3(
		m.c0.x * v.x + m.c1.x * v.x + m.c2.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y + m.c2.y * v.y,
		m.c0.z * v.z + m.c1.z * v.z + m.c2.z * v.z);
}
static float3x3 transpose(const float3x3& m) noexcept
{
	return float3x3(
		m.c0.x, m.c0.y, m.c0.z,
		m.c1.x, m.c1.y, m.c1.z,
		m.c2.x, m.c2.y, m.c2.z);
}
static float3x3 inverse(const float3x3& matrix) noexcept
{
	auto m = matrix;
	auto oneOverDeterminant = 1.0f / (
		m.c0.x * (m.c1.y * m.c2.z - m.c2.y * m.c1.z)
		-m.c1.x * (m.c0.y * m.c2.z - m.c2.y * m.c0.z) +
		m.c2.x * (m.c0.y * m.c1.z - m.c1.y * m.c0.z));
	return float3x3(
		(m.c1.y * m.c2.z - m.c2.y * m.c1.z) * oneOverDeterminant,
		-(m.c0.y * m.c2.z - m.c2.y * m.c0.z) * oneOverDeterminant,
		(m.c0.y * m.c2.z - m.c1.y * m.c0.z) * oneOverDeterminant,
		-(m.c1.x * m.c2.z - m.c2.x * m.c1.z) * oneOverDeterminant,
		(m.c0.x * m.c2.z - m.c2.x * m.c0.z) * oneOverDeterminant,
		-(m.c0.x * m.c2.z - m.c1.x * m.c0.z) * oneOverDeterminant,
		(m.c1.x * m.c2.y - m.c2.x * m.c1.y) * oneOverDeterminant,
		-(m.c0.x * m.c2.y - m.c2.x * m.c0.y) * oneOverDeterminant,
		(m.c0.x * m.c2.y - m.c1.x * m.c0.y) * oneOverDeterminant);
}

//**********************************************************************************************************************
static float4 operator*(const float4& v, const float4x4& m) noexcept
{
	return float4(
		m.c0.x * v.x + m.c1.x * v.x + m.c2.x * v.x + m.c3.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y + m.c2.y * v.y + m.c3.y * v.y,
		m.c0.z * v.z + m.c1.z * v.z + m.c2.z * v.z + m.c3.z * v.z,
		m.c0.w * v.w + m.c1.w * v.w + m.c2.w * v.w + m.c3.w * v.w);
}
static float4x4 transpose(const float4x4& m) noexcept
{
	return float4x4(
		m.c0.x, m.c0.y, m.c0.z, m.c0.w,
		m.c1.x, m.c1.y, m.c1.z, m.c1.w,
		m.c2.x, m.c2.y, m.c2.z, m.c2.w,
		m.c3.x, m.c3.y, m.c3.z, m.c3.w);
}
static float4x4 inverse(const float4x4& matrix) noexcept
{
	auto m = matrix;
	auto c00 = m.c2.z * m.c3.w - m.c3.z * m.c2.w;
	auto c02 = m.c1.z * m.c3.w - m.c3.z * m.c1.w;
	auto c03 = m.c1.z * m.c2.w - m.c2.z * m.c1.w;
	auto c04 = m.c2.y * m.c3.w - m.c3.y * m.c2.w;
	auto c06 = m.c1.y * m.c3.w - m.c3.y * m.c1.w;
	auto c07 = m.c1.y * m.c2.w - m.c2.y * m.c1.w;
	auto c08 = m.c2.y * m.c3.z - m.c3.y * m.c2.z;
	auto c10 = m.c1.y * m.c3.z - m.c3.y * m.c1.z;
	auto c11 = m.c1.y * m.c2.z - m.c2.y * m.c1.z;
	auto c12 = m.c2.x * m.c3.w - m.c3.x * m.c2.w;
	auto c14 = m.c1.x * m.c3.w - m.c3.x * m.c1.w;
	auto c15 = m.c1.x * m.c2.w - m.c2.x * m.c1.w;
	auto c16 = m.c2.x * m.c3.z - m.c3.x * m.c2.z;
	auto c18 = m.c1.x * m.c3.z - m.c3.x * m.c1.z;
	auto c19 = m.c1.x * m.c2.z - m.c2.x * m.c1.z;
	auto c20 = m.c2.x * m.c3.y - m.c3.x * m.c2.y;
	auto c22 = m.c1.x * m.c3.y - m.c3.x * m.c1.y;
	auto c23 = m.c1.x * m.c2.y - m.c2.x * m.c1.y;

	float4 f0(c00, c00, c02, c03);
	float4 f1(c04, c04, c06, c07);
	float4 f2(c08, c08, c10, c11);
	float4 f3(c12, c12, c14, c15);
	float4 f4(c16, c16, c18, c19);
	float4 f5(c20, c20, c22, c23);

	float4 v0(m.c1.x, m.c0.x, m.c0.x, m.c0.x);
	float4 v1(m.c1.y, m.c0.y, m.c0.y, m.c0.y);
	float4 v2(m.c1.z, m.c0.z, m.c0.z, m.c0.z);
	float4 v3(m.c1.w, m.c0.w, m.c0.w, m.c0.w);

	float4 i0(v1 * f0 - v2 * f1 + v3 * f2);
	float4 i1(v0 * f0 - v2 * f3 + v3 * f4);
	float4 i2(v0 * f1 - v1 * f3 + v3 * f5);
	float4 i3(v0 * f2 - v1 * f4 + v2 * f5);

	float4 sA( 1.0f, -1.0f,  1.0f, -1.0f);
	float4 sB(-1.0f,  1.0f, -1.0f,  1.0f);
	float4x4 i(i0 * sA, i1 * sB, i2 * sA, i3 * sB);
	float4 r0(i.c0.x, i.c1.x, i.c2.x, i.c3.x);
	float4 d0(m.c0 * r0);
	auto d1 = (d0.x + d0.y) + (d0.z + d0.w);
	return i * (1.0f / d1);
}

//**********************************************************************************************************************
static float4x4 translate(const float4x4& m, const float3& t) noexcept
{
	return float4x4(m.c0, m.c1, m.c2, m.c0 * t.x + m.c1 * t.y + m.c2 * t.z + m.c3);
}
static float4x4 translate(const float3& t) noexcept
{
	return float4x4(
		1.0f, 0.0f, 0.0f, t.x,
		0.0f, 1.0f, 0.0f, t.y,
		0.0f, 0.0f, 1.0f, t.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}
static float3 getTranslation(const float4x4& m) noexcept
{
	return float3(m.c3.x, m.c3.y, m.c3.z);
}
static void setTranslation(float4x4& m, const float3& t) noexcept
{
	m.c3.x = t.x; m.c3.y = t.y; m.c3.z = t.z;
}

static float4x4 scale(const float4x4& m, const float3& s) noexcept
{
	return float4x4(m.c0 * s.x, m.c1 * s.y, m.c2 * s.z, m.c3);
}
static float4x4 scale(const float3& s) noexcept
{
	return float4x4(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
static float3 extractScale(const float4x4& m) noexcept
{
	return float3(length((float3)m.c0), length((float3)m.c1), length((float3)m.c2));
}
static float2 extractScale2(const float4x4& m) noexcept
{
	return float2(length((float3)m.c0), length((float3)m.c1));
}

//**********************************************************************************************************************
static float4x4 rotate(const quat& q) noexcept
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
static float4x4 rotate(const float3& lookFrom,
	const float3& lookTo, const float3& up = float3::top) noexcept
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
static float4x4 extractRotation(const float4x4& m) noexcept
{
	auto invScale = 1.0f / extractScale(m);
	auto c0 = (float3)m.c0 * invScale.x;
	auto c1 = (float3)m.c1 * invScale.y;
	auto c2 = (float3)m.c2 * invScale.z;

	return float4x4(float4(c0, 0.0f), float4(c1, 0.0f), float4(c2, 0.0f), float4(0.0f, 0.0f, 0.0f, 1.0f));
}

static float4x4 calcModel(const float3& position, const quat& rotation, const float3& scale) noexcept
{
	return translate(position) * rotate(normalize(rotation)) * math::scale(scale);
}

//**********************************************************************************************************************
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

	switch(biggestIndex)
	{
	case 0: return quat((m.c1.z - m.c2.y) * mult, (m.c2.x - m.c0.z) * mult, (m.c0.y - m.c1.x) * mult, biggestVal);
	case 1: return quat(biggestVal, (m.c0.y + m.c1.x) * mult, (m.c2.x + m.c0.z) * mult, (m.c1.z - m.c2.y) * mult);
	case 2: return quat((m.c0.y + m.c1.x) * mult, biggestVal, (m.c1.z + m.c2.y) * mult, (m.c2.x - m.c0.z) * mult);
	case 3: return quat((m.c2.x + m.c0.z) * mult, (m.c1.z + m.c2.y) * mult, biggestVal, (m.c0.y - m.c1.x) * mult);
	default: abort();
	}
}
static quat extractQuat(const float4x4& m) noexcept
{
	return extractQuat((float3x3)m);
}

//**********************************************************************************************************************
// These projections are fixed for the Vulkan NDC space.
// http://matthewwellings.com/blog/the-new-vulkan-coordinate-system/
//**********************************************************************************************************************

//**********************************************************************************************************************
// Infinite Reversed Z Perspective Projection
static float4x4 calcPerspProjInfRevZ(float fieldOfView, float aspectRatio, float nearPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);

	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, nearPlane,
		0.0f, 0.0f, 1.0f, 0.0f);
}
// Reversed Z Perspective Projection
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
// Common Perspective Projection
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

// Reversed Z Orthographic Projection
static float4x4 calcOrthoProjRevZ(float2 width, float2 height, float2 depth) noexcept
{
	return float4x4(
		2.0f / (width.y - width.x), 0.0f, 0.0f, -(width.y + width.x) / (width.y - width.x),
		0.0f, -2.0f / (height.y - height.x), 0.0f, (height.y + height.x) / (height.y - height.x),
		0.0f, 0.0f, 1.0f / (depth.x - depth.y), -depth.y / (depth.x - depth.y),
		0.0f, 0.0f, 0.0f, 1.0f);
}
// Common Orthographic Projection
static float4x4 calcOrthoProj(float2 width, float2 height, float2 depth) noexcept
{
	return float4x4(
		2.0f / (width.y - width.x), 0.0f, 0.0f, -(width.y + width.x) / (width.y - width.x),
		0.0f, -2.0f / (height.y - height.x), 0.0f, (height.y + height.x) / (height.y - height.x),
		0.0f, 0.0f, 1.0f / (depth.y - depth.x), -depth.x / (depth.y - depth.x),
		0.0f, 0.0f, 0.0f, 1.0f);
}

//**********************************************************************************************************************
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

static quat lookAtQuat(const float3& direction, const float3& up = float3::top) noexcept
{
	auto right = cross(up, direction);
	auto c0 = right * (1.0f / std::sqrt(std::max(0.00001f, dot(right, right))));
	auto c1 = cross(right, c0);
	auto m = float3x3(c0, c1, direction);
	return extractQuat(m);
}

} // namespace math