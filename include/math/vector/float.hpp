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
 * @brief Common floating point vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/common.hpp"
#include "math/vector/int.hpp"
#include <cfloat>

namespace math
{

/**
 * @brief Floating point 2 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] float2
{
	float x; /**< First vector component. */
	float y; /**< Second vector component. */

	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target value for all vector components
	 */
	constexpr explicit float2(float xy = 0.0f) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr float2(float x, float y) noexcept : x(x), y(y) { }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target unsigned integer vector value
	 */
	constexpr float2(uint2 xy) noexcept : x((float)xy.x), y((float)xy.y) { }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target signed integer vector value
	 */
	constexpr float2(int2 xy) noexcept : x((float)xy.x), y((float)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((float*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((float*)this)[i];
	}

	/**
	 * @brief Returns as 2 component unsigned integer vector. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns as 2 component signed integer vector. (xy)
	 */
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first vector component as unsigned integer. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component as signed integer. (x)
	 */
	constexpr explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first vector component value. (x)
	 */
	constexpr explicit operator float() const noexcept { return x; }

	//******************************************************************************************************************
	constexpr float2 operator+(float2 v) const noexcept { return float2(x + v.x, y + v.y); }
	constexpr float2 operator-(float2 v) const noexcept { return float2(x - v.x, y - v.y); }
	constexpr float2 operator*(float2 v) const noexcept { return float2(x * v.x, y * v.y); }
	constexpr float2 operator/(float2 v) const noexcept { return float2(x / v.x, y / v.y); }
	constexpr float2 operator+(float n) const noexcept { return float2(x + n, y + n); }
	constexpr float2 operator-(float n) const noexcept { return float2(x - n, y - n); }
	constexpr float2 operator*(float n) const noexcept { return float2(x * n, y * n); }
	constexpr float2 operator/(float n) const noexcept { return float2(x / n, y / n); }
	constexpr float2 operator-() const noexcept { return float2(-x, -y); }
	float2& operator+=(float2 v) noexcept { x += v.x; y += v.y; return *this; }
	float2& operator-=(float2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	float2& operator*=(float2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	float2& operator/=(float2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	float2& operator+=(float n) noexcept { x += n; y += n; return *this; }
	float2& operator-=(float n) noexcept { x -= n; y -= n; return *this; }
	float2& operator*=(float n) noexcept { x *= n; y *= n; return *this; }
	float2& operator/=(float n) noexcept { x /= n; y /= n; return *this; }
	float2& operator=(float n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(float2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(float2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr uint2 operator<(float2 v) const noexcept
	{
		return uint2(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator>(float2 v) const noexcept
	{
		return uint2(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator<=(float2 v) const noexcept
	{
		return uint2(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator>=(float2 v) const noexcept
	{
		return uint2(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0);
	}
	constexpr bool operator==(float n) const noexcept { return *this == float2(n); }
	constexpr bool operator!=(float n) const noexcept { return *this != float2(n); }
	constexpr uint2 operator<(float n) const noexcept { return *this < float2(n); }
	constexpr uint2 operator>(float n) const noexcept { return *this > float2(n); }
	constexpr uint2 operator<=(float n) const noexcept { return *this <= float2(n); }
	constexpr uint2 operator>=(float n) const noexcept { return *this >= float2(n); }

	static const float2 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top;
};

inline const float2 float2::zero = float2(0.0f);
inline const float2 float2::one = float2(1.0f);
inline const float2 float2::minusOne = float2(-1.0f);
inline const float2 float2::min = float2(FLT_MIN);
inline const float2 float2::minusMin = float2(-FLT_MIN);
inline const float2 float2::max = float2(FLT_MAX);
inline const float2 float2::minusMax = float2(-FLT_MAX);
inline const float2 float2::epsilon = float2(FLT_EPSILON);
inline const float2 float2::inf = float2(INFINITY);
inline const float2 float2::minusInf = float2(-INFINITY);
inline const float2 float2::nan = float2(NAN);
inline const float2 float2::left = float2(-1.0f, 0.0f);
inline const float2 float2::right = float2(1.0f, 0.0f);
inline const float2 float2::bottom = float2(0.0f, -1.0f);
inline const float2 float2::top = float2(0.0f, 1.0f);

/***********************************************************************************************************************
 * @brief Floating point 3 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] float3
{
	float x; /**< First vector component. */
	float y; /**< Second vector component. */
	float z; /**< Third vector component. */

	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit float3(float xyz = 0.0f) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr float3(float x, float y, float z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 */
	constexpr float3(float2 xy, float z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 */
	constexpr float3(float x, float2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param xyz target unsigned integer vector value
	 */
	constexpr float3(uint3 xyz) noexcept : x((float)xyz.x), y((float)xyz.y), z((float)xyz.z) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param xyz target signed integer vector value
	 */
	constexpr float3(int3 xyz) noexcept : x((float)xyz.x), y((float)xyz.y), z((float)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((float*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float*)this)[i];
	}

	/**
	 * @brief Returns as 3 component signed integer vector. (xyz)
	 */
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	/**
	 * @brief Returns as 3 component unsigned integer vector. (xyz)
	 */
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	/**
	 * @brief Returns as 2 component signed integer vector. (xy)
	 */
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns as 2 component unsigned integer vector. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first vector component as unsigned integer. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component as signed integer. (x)
	 */
	constexpr explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns as 2 component floating point vector. (xy)
	 */
	constexpr explicit operator float2() const noexcept { return float2(x, y); }
	/**
	 * @brief Returns first vector component value. (x)
	 */
	constexpr explicit operator float() const noexcept { return x; }

	//******************************************************************************************************************
	constexpr float3 operator+(float3 v) const noexcept { return float3(x + v.x, y + v.y, z + v.z); }
	constexpr float3 operator-(float3 v) const noexcept { return float3(x - v.x, y - v.y, z - v.z); }
	constexpr float3 operator*(float3 v) const noexcept { return float3(x * v.x, y * v.y, z * v.z); }
	constexpr float3 operator/(float3 v) const noexcept { return float3(x / v.x, y / v.y, z / v.z); }
	constexpr float3 operator+(float n) const noexcept { return float3(x + n, y + n, z + n); }
	constexpr float3 operator-(float n) const noexcept { return float3(x - n, y - n, z - n); }
	constexpr float3 operator*(float n) const noexcept { return float3(x * n, y * n, z * n); }
	constexpr float3 operator/(float n) const noexcept { return float3(x / n, y / n, z / n); }
	constexpr float3 operator-() const noexcept { return float3(-x, -y, -z); }
	float3& operator+=(float3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	float3& operator-=(float3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	float3& operator*=(float3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	float3& operator/=(float3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	float3& operator+=(float n) noexcept { x += n; y += n; z += n; return *this; }
	float3& operator-=(float n) noexcept { x -= n; y -= n; z -= n; return *this; }
	float3& operator*=(float n) noexcept { x *= n; y *= n; z *= n; return *this; }
	float3& operator/=(float n) noexcept { x /= n; y /= n; z /= n; return *this; }
	float3& operator=(float n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(float3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(float3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr uint3 operator<(float3 v) const noexcept
	{
		return uint3(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0, z < v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator>(float3 v) const noexcept
	{
		return uint3(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0, z > v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator<=(float3 v) const noexcept
	{
		return uint3(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0, z <= v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator>=(float3 v) const noexcept
	{
		return uint3(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0, z >= v.z ? UINT32_MAX : 0);
	}
	constexpr bool operator==(float n) const noexcept { return *this == float3(n); }
	constexpr bool operator!=(float n) const noexcept { return *this != float3(n); }
	constexpr uint3 operator<(float n) const noexcept { return *this < float3(n); }
	constexpr uint3 operator>(float n) const noexcept { return *this > float3(n); }
	constexpr uint3 operator<=(float n) const noexcept { return *this <= float3(n); }
	constexpr uint3 operator>=(float n) const noexcept { return *this >= float3(n); }

	static const float3 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top, back, front;
};

inline const float3 float3::zero = float3(0.0f);
inline const float3 float3::one = float3(1.0f);
inline const float3 float3::minusOne = float3(-1.0f);
inline const float3 float3::min = float3(FLT_MIN);
inline const float3 float3::minusMin = float3(-FLT_MIN);
inline const float3 float3::max = float3(FLT_MAX);
inline const float3 float3::minusMax = float3(-FLT_MAX);
inline const float3 float3::epsilon = float3(FLT_EPSILON);
inline const float3 float3::inf = float3(INFINITY);
inline const float3 float3::minusInf = float3(-INFINITY);
inline const float3 float3::nan = float3(NAN);
inline const float3 float3::left = float3(-1.0f, 0.0f, 0.0f);
inline const float3 float3::right = float3(1.0f, 0.0f, 0.0f);
inline const float3 float3::bottom = float3(0.0f, -1.0f, 0.0f);
inline const float3 float3::top = float3(0.0f, 1.0f, 0.0f);
inline const float3 float3::back = float3(0.0f, 0.0f, -1.0f);
inline const float3 float3::front = float3(0.0f, 0.0f, 1.0f);

/***********************************************************************************************************************
 * @brief Floating point 4 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] float4
{
	float x; /**< First vector component. */
	float y; /**< Second vector component. */
	float z; /**< Third vector component. */
	float w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit float4(float xyzw = 0.0f) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr float4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr float4(float2 xy, float z, float w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 * @param w fourth vector component value
	 */
	constexpr float4(float x, float2 yz, float w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector components value
	 */
	constexpr float4(float x, float y, float2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param zw third and fourth vector components value
	 */
	constexpr float4(float2 xy, float2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xyz first, second and third vector components value
	 * @param w fourth vector component value
	 */
	constexpr float4(float3 xyz, float w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector components value
	 */
	constexpr float4(float x, float3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param xyzw target unsigned integer vector value
	 */
	constexpr float4(uint4 xyzw) noexcept :
		x((float)xyzw.x), y((float)xyzw.y), z((float)xyzw.z), w((float)xyzw.w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param xyzw target signed integer vector value
	 */
	constexpr float4(int4 xyzw) noexcept :
		x((float)xyzw.x), y((float)xyzw.y), z((float)xyzw.z), w((float)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((float*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float*)this)[i];
	}

	/**
	 * @brief Returns as 4 component signed integer vector. (xyzw)
	 */
	constexpr explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	/**
	 * @brief Returns as 4 component unsigned integer vector. (xyzw)
	 */
	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	/**
	 * @brief Returns as 3 component signed integer vector. (xyz)
	 */
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	/**
	 * @brief Returns as 3 component unsigned integer vector. (xyz)
	 */
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	/**
	 * @brief Returns as 2 component signed integer vector. (xy)
	 */
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns as 2 component unsigned integer vector. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first vector component as unsigned integer. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component as signed integer. (x)
	 */
	constexpr explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns as 3 component floating point vector. (xyz)
	 */
	constexpr explicit operator float3() const noexcept { return float3(x, y, z); }
	/**
	 * @brief Returns as 2 component floating point vector. (xy)
	 */
	constexpr explicit operator float2() const noexcept { return float2(x, y); }
	/**
	 * @brief Returns first vector component value. (x)
	 */
	constexpr explicit operator float() const noexcept { return x; }

	//******************************************************************************************************************
	constexpr float4 operator+(float4 v) const noexcept { return float4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr float4 operator-(float4 v) const noexcept { return float4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr float4 operator*(float4 v) const noexcept { return float4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr float4 operator/(float4 v) const noexcept { return float4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr float4 operator+(float n) const noexcept { return float4(x + n, y + n, z + n, w + n); }
	constexpr float4 operator-(float n) const noexcept { return float4(x - n, y - n, z - n, w - n); }
	constexpr float4 operator*(float n) const noexcept { return float4(x * n, y * n, z * n, w * n); }
	constexpr float4 operator/(float n) const noexcept { return float4(x / n, y / n, z / n, w / n); }
	constexpr float4 operator-() const noexcept { return float4(-x, -y, -z, -w); }
	float4& operator+=(float4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	float4& operator-=(float4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	float4& operator*=(float4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	float4& operator/=(float4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	float4& operator+=(float n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	float4& operator-=(float n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	float4& operator*=(float n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	float4& operator/=(float n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	float4& operator=(float n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(float4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(float4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr uint4 operator<(float4 v) const noexcept
	{
		return uint4(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0, 
			z < v.z ? UINT32_MAX : 0, w < v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator>(float4 v) const noexcept
	{
		return uint4(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0, 
			z > v.z ? UINT32_MAX : 0, w > v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator<=(float4 v) const noexcept
	{
		return uint4(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0, 
			z <= v.z ? UINT32_MAX : 0, w <= v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator>=(float4 v) const noexcept
	{
		return uint4(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0, 
			z >= v.z ? UINT32_MAX : 0, w >= v.w ? UINT32_MAX : 0);
	}
	constexpr bool operator==(float n) const noexcept { return *this == float4(n); }
	constexpr bool operator!=(float n) const noexcept { return *this != float4(n); }
	constexpr uint4 operator<(float n) const noexcept { return *this < float4(n); }
	constexpr uint4 operator>(float n) const noexcept { return *this > float4(n); }
	constexpr uint4 operator<=(float n) const noexcept { return *this <= float4(n); }
	constexpr uint4 operator>=(float n) const noexcept { return *this >= float4(n); }

	static const float4 zero, one, minusOne, min, minusMin, max, minusMax, epsilon, inf, minusInf, nan;
};

inline const float4 float4::zero = float4(0.0f);
inline const float4 float4::one = float4(1.0f);
inline const float4 float4::minusOne = float4(-1.0f);
inline const float4 float4::min = float4(FLT_MIN);
inline const float4 float4::minusMin = float4(-FLT_MIN);
inline const float4 float4::max = float4(FLT_MAX);
inline const float4 float4::minusMax = float4(-FLT_MAX);
inline const float4 float4::epsilon = float4(FLT_EPSILON);
inline const float4 float4::inf = float4(INFINITY);
inline const float4 float4::minusInf = float4(-INFINITY);
inline const float4 float4::nan = float4(NAN);

//**********************************************************************************************************************
static constexpr float2 operator+(float n, float2 v) noexcept { return float2(n) + v; }
static constexpr float2 operator-(float n, float2 v) noexcept { return float2(n) - v; }
static constexpr float2 operator*(float n, float2 v) noexcept { return float2(n) * v; }
static constexpr float2 operator/(float n, float2 v) noexcept { return float2(n) / v; }
static constexpr bool operator==(float n, float2 v) noexcept { return float2(n) == v; }
static constexpr bool operator!=(float n, float2 v) noexcept { return float2(n) != v; }
static constexpr uint2 operator<(float n, float2 v) noexcept { return float2(n) < v; }
static constexpr uint2 operator>(float n, float2 v) noexcept { return float2(n) > v; }
static constexpr uint2 operator<=(float n, float2 v) noexcept { return float2(n) <= v; }
static constexpr uint2 operator>=(float n, float2 v) noexcept { return float2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(float2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint2 equal(float2 a, float4 b) noexcept
{
	return uint2(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint2 notEqual(float2 a, float4 b) noexcept
{
	return uint2(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(float2 a, float2 b) noexcept { return *((const int64*)&a) < *((const int64*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr float2 select(uint2 c, float2 t, float2 f) noexcept
{
	return float2(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr float2 min(float2 a, float2 b) noexcept { return float2(std::min(a.x, b.x), std::min(a.y, b.y)); }
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr float2 max(float2 a, float2 b) noexcept { return float2(std::max(a.x, b.x), std::max(a.y, b.y)); }
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr float2 min(float2 a, float2 b, float2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr float2 max(float2 a, float2 b, float2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr float2 clamp(float2 v, float2 min, float2 max) noexcept
{
	return float2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first vector multiplier
 * @param mul2 second vector multiplier
 * @param add vector addend
 */
static float2 fma(float2 mul1, float2 mul2, float2 add) noexcept
{
	return float2(std::fma(mul1.x, mul2.x, add.x), std::fma(mul1.y, mul2.y, add.y));
}
/**
 * @brief Returns absolute value for each component of the vector.
 * @param v target vector
 */
static float2 abs(float2 v) noexcept { return float2(std::abs(v.x), std::abs(v.y)); }
/**
 * @brief Returns square root for each component of the vector.
 * @param v target vector
 */
static float2 sqrt(float2 v) noexcept { return float2(std::sqrt(v.x), std::sqrt(v.y)); }
/**
 * @brief Returns sign for each component of the vector.
 * @param v target vector
 */
static float2 sign(float2 v) noexcept { return float2(sign(v.x), sign(v.y)); }
/**
 * @brief Returns sign bits of the vector. (2 bits)
 * @param v target vector
 */
static uint32 signBits(float2 v) noexcept { return (std::signbit(v.x) ? 1u : 0u) | (std::signbit(v.y) ? 2u : 0u); }

/**
 * @brief Rounds each component of the vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target vector
 */
static float2 round(float2 v) noexcept { return float2(std::round(v.x), std::round(v.y)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target vector
 */
static float2 floor(float2 v) noexcept { return float2(std::floor(v.x), std::floor(v.y)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target vector
 */
static float2 ceil(float2 v) noexcept { return float2(std::ceil(v.x), std::ceil(v.y)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target vector
 */
static float2 trunc(float2 v) noexcept { return float2(std::trunc(v.x), std::trunc(v.y)); }

/***********************************************************************************************************************
 * @brief Returns dot product between two vector.
 * 
 * @param a first vector to dot
 * @param b second vector to dot
 */
static constexpr float dot(float2 a, float2 b) noexcept { return a.x * b.x + a.y * b.y; }

/**
 * @brief Returns squared length of the vector. (length ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * @param v target vector
 */
static constexpr float lengthSq(float2 v) noexcept { return dot(v, v); }
/**
 * @brief Returns length of the vector.
 * @param v target vector
 */
static float length(float2 v) noexcept { return std::sqrt(dot(v, v)); }

/**
 * @brief Returns squared distance between two points. (distance ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * 
 * @param a first point
 * @param b second point
 */
static constexpr float distanceSq(float2 a, float2 b) noexcept { return lengthSq(a - b); }
/**
 * @brief Returns distance between two points.
 * 
 * @param a first point
 * @param b second point
 */
static float distance(float2 a, float2 b) noexcept { return length(a - b); }
/**
 * @brief Returns true if two vectors are close with specified maximum squared distance. (maxDistance ^ 2)
 * 
 * @param a first vector
 * @param b second vector
 */
static constexpr bool isClose(float2 a, float2 b, float maxDistSq = 1.0e-12f) noexcept
{
	return distanceSq(a, b) <= maxDistSq;
}

/**
 * @brief Returns normalized vector. (With length of 1.0f)
 * @param v target vector to normalize
 */
static float2 normalize(float2 v) noexcept { return v * (1.0f / length(v)); }
/**
 * @brief Returns true if vector is normalized with specified tolerance.
 * 
 * @param v target vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized(float2 v, float tolerance = 1.0e-6f) noexcept
{
	return std::abs(lengthSq(v) - 1.0f) <= tolerance;
}
/**
 * @brief Returns true if any vector element is not a number.
 * @param v target vector to check
 */
static bool isNan(float2 v) noexcept { return isnan(v.x) || isnan(v.y); }

/**
 * @brief Remaps each component of vector to the 0.0 - 1.0 range.
 * @param v target vector
 */
static float2 repeat(float2 v) noexcept { return float2(repeat(v.x), repeat(v.y)); }

/**
 * @brief Linearly interpolates each component of the vector between a and b using t.
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static float2 lerp(float2 a, float2 b, float t) noexcept { return a * (1.0f - t) + b * t; }
/**
 * @brief Linearly interpolates each component of the vector between a and b using t, taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 * @param dt current delta time
 */
static float2 lerpDelta(float2 a, float2 b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}

/**
 * @brief Computes the power of each component of base b raised to the corresponding exponent e.
 * 
 * @param b target base vector to raise
 * @param e exponent vector
 */
static float2 pow(float2 b, float2 e) noexcept { return float2(std::pow(b.x, e.x), std::pow(b.y, e.y)); }
/**
 * @brief Applies gain function for each component of the vector.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target vector to gain (0.0 - 1.0)
 * @param k gain factor
 */
static float2 gain(float2 x, float2 k) noexcept
{
	auto a = float2(0.5f) * pow(2.0f * select(x < 0.5f, x, 1.0f - x), k);
	return select(x < 0.5f, a, 1.0f - a);
}

//**********************************************************************************************************************
static constexpr float3 operator+(float n, float3 v) noexcept { return float3(n) + v; }
static constexpr float3 operator-(float n, float3 v) noexcept { return float3(n) - v; }
static constexpr float3 operator*(float n, float3 v) noexcept { return float3(n) * v; }
static constexpr float3 operator/(float n, float3 v) noexcept { return float3(n) / v; }
static constexpr bool operator==(float n, float3 v) noexcept { return float3(n) == v; }
static constexpr bool operator!=(float n, float3 v) noexcept { return float3(n) != v; }
static constexpr uint3 operator<(float n, float3 v) noexcept { return float3(n) < v; }
static constexpr uint3 operator>(float n, float3 v) noexcept { return float3(n) > v; }
static constexpr uint3 operator<=(float n, float3 v) noexcept { return float3(n) <= v; }
static constexpr uint3 operator>=(float n, float3 v) noexcept { return float3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(float3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint3 equal(float3 a, float3 b) noexcept
{
	return uint3(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0, a.z == b.z ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint3 notEqual(float3 a, float3 b) noexcept
{
	return uint3(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0, a.z != b.z ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const float3& a, const float3& b) noexcept { return memcmp(&a, &b, sizeof(float3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr float3 select(uint3 c, float3 t, float3 f) noexcept
{
	return float3(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y, c.z & 0x80000000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr float3 min(float3 a, float3 b) noexcept
{
	return float3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr float3 max(float3 a, float3 b) noexcept
{
	return float3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr float3 min(float3 a, float3 b, float3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr float3 max(float3 a, float3 b, float3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr float3 clamp(float3 v, float3 min, float3 max) noexcept
{
	return float3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first vector multiplier
 * @param mul2 second vector multiplier
 * @param add vector addend
 */
static float3 fma(float3 mul1, float3 mul2, float3 add) noexcept
{
	return float3(std::fma(mul1.x, mul2.x, add.x), std::fma(mul1.y, mul2.y, add.y), std::fma(mul1.z, mul2.z, add.z));
}
/**
 * @brief Returns absolute value for each component of the vector.
 * @param v target vector
 */
static float3 abs(float3 v) noexcept { return float3(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
/**
 * @brief Returns square root for each component of the vector.
 * @param v target vector
 */
static float3 sqrt(float3 v) noexcept { return float3(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z)); }
/**
 * @brief Returns sign for each component of the vector.
 * @param v target vector
 */
static float3 sign(float3 v) noexcept { return float3(sign(v.x), sign(v.y), sign(v.z)); }
/**
 * @brief Returns sign bits of the vector. (3 bits)
 * @param v target vector
 */
static uint32 signBits(float3 v) noexcept
{
	return (std::signbit(v.x) ? 1u : 0u) | (std::signbit(v.y) ? 2u : 0u) | (std::signbit(v.z) ? 4u : 0u);
}

/**
 * @brief Rounds each component of the vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target vector
 */
static float3 round(float3 v) noexcept { return float3(std::round(v.x), std::round(v.y), std::round(v.z)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target vector
 */
static float3 floor(float3 v) noexcept { return float3(std::floor(v.x), std::floor(v.y), std::floor(v.z)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target vector
 */
static float3 ceil(float3 v) noexcept { return float3(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target vector
 */
static float3 trunc(float3 v) noexcept { return float3(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z)); }

/***********************************************************************************************************************
 * @brief Returns dot product between two vector.
 * 
 * @param a first vector to dot
 * @param b second vector to dot
 */
static constexpr float dot(float3 a, float3 b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
/**
 * @brief Returns cross product between two vector.
 * 
 * @param a first vector to cross
 * @param b second vector to cross
 */
static constexpr float3 cross(float3 a, float3 b) noexcept
{
	return float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

/**
 * @brief Returns squared length of the vector. (length ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * @param v target vector
 */
static constexpr float lengthSq(float3 v) noexcept { return dot(v, v); }
/**
 * @brief Returns length of the vector.
 * @param v target vector
 */
static float length(float3 v) noexcept { return std::sqrt(dot(v, v)); }

/**
 * @brief Returns squared distance between two points. (distance ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * 
 * @param a first point
 * @param b second point
 */
static constexpr float distanceSq(float3 a, float3 b) noexcept { return lengthSq(a - b); }
/**
 * @brief Returns distance between two points.
 * 
 * @param a first point
 * @param b second point
 */
static float distance(float3 a, float3 b) noexcept { return length(a - b); }
/**
 * @brief Returns true if two vectors are close with specified maximum squared distance. (maxDistance ^ 2)
 * 
 * @param a first vector
 * @param b second vector
 */
static constexpr bool isClose(float3 a, float3 b, float maxDistSq = 1.0e-12f) noexcept
{
	return distanceSq(a, b) <= maxDistSq;
}

/**
 * @brief Returns normalized vector. (With length of 1.0f)
 * @param v target vector to normalize
 */
static float3 normalize(float3 v) noexcept { return v * (1.0f / length(v)); }
/**
 * @brief Returns true if vector is normalized with specified tolerance.
 * 
 * @param v target vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized(float3 v, float tolerance = 1.0e-6f) noexcept
{
	return std::abs(lengthSq(v) - 1.0f) <= tolerance;
}
/**
 * @brief Returns true if any vector element is not a number.
 * @param v target vector to check
 */
static bool isNan(float3 v) noexcept { return isnan(v.x) || isnan(v.y) || isnan(v.z); }

/**
 * @brief Remaps each component of vector to the 0.0 - 1.0 range.
 * @param v target vector
 */
static float3 repeat(float3 v) noexcept { return float3(repeat(v.x), repeat(v.y), repeat(v.z)); }

/**
 * @brief Linearly interpolates each component of the vector between a and b using t.
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static float3 lerp(float3 a, float3 b, float t) noexcept { return a * (1.0f - t) + b * t; }
/**
 * @brief Linearly interpolates each component of the vector between a and b using t, taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 * @param dt current delta time
 */
static float3 lerpDelta(float3 a, float3 b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}

/**
 * @brief Computes the power of each component of base b raised to the corresponding exponent e.
 * 
 * @param b target base vector to raise
 * @param e exponent vector
 */
static float3 pow(float3 b, float3 e) noexcept
{
	return float3(std::pow(b.x, e.x), std::pow(b.y, e.y), std::pow(b.z, e.z));
}
/**
 * @brief Applies gain function for each component of the vector.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target vector to gain (0.0 - 1.0)
 * @param k gain factor
 */
static float3 gain(float3 x, float3 k) noexcept
{
	auto a = float3(0.5f) * pow(2.0f * select(x < 0.5f, x, 1.0f - x), k);
	return select(x < 0.5f, a, 1.0f - a);
}

//**********************************************************************************************************************
static constexpr float4 operator+(float n, float4 v) noexcept { return float4(n) + v; }
static constexpr float4 operator-(float n, float4 v) noexcept { return float4(n) - v; }
static constexpr float4 operator*(float n, float4 v) noexcept { return float4(n) * v; }
static constexpr float4 operator/(float n, float4 v) noexcept { return float4(n) / v; }
static constexpr bool operator==(float n, float4 v) noexcept { return float4(n) == v; }
static constexpr bool operator!=(float n, float4 v) noexcept { return float4(n) != v; }
static constexpr uint4 operator<(float n, float4 v) noexcept { return float4(n) < v; }
static constexpr uint4 operator>(float n, float4 v) noexcept { return float4(n) > v; }
static constexpr uint4 operator<=(float n, float4 v) noexcept { return float4(n) <= v; }
static constexpr uint4 operator>=(float n, float4 v) noexcept { return float4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(float4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint4 equal(float4 a, float4 b) noexcept
{
	return uint4(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0, 
		a.z == b.z ? UINT32_MAX : 0, a.w == b.w ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint4 notEqual(float4 a, float4 b) noexcept
{
	return uint4(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0, 
		a.z != b.z ? UINT32_MAX : 0, a.w != b.w ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const float4& a, const float4& b) noexcept { return memcmp(&a, &b, sizeof(float4)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr float4 select(uint4 c, float4 t, float4 f) noexcept
{
	return float4(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y, 
		c.z & 0x80000000u ? t.z : f.z, c.w & 0x80000000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr float4 min(float4 a, float4 b) noexcept
{
	return float4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr float4 max(float4 a, float4 b) noexcept
{
	return float4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr float4 min(float4 a, float4 b, float4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr float4 max(float4 a, float4 b, float4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr float4 clamp(float4 v, float4 min, float4 max) noexcept
{
	return float4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first vector multiplier
 * @param mul2 second vector multiplier
 * @param add vector addend
 */
static float4 fma(float4 mul1, float4 mul2, float4 add) noexcept
{
	return float4(std::fma(mul1.x, mul2.x, add.x), std::fma(mul1.y, mul2.y, add.y), 
		std::fma(mul1.z, mul2.z, add.z), std::fma(mul1.w, mul2.w, add.w));
}
/**
 * @brief Returns absolute value for each component of the vector.
 * @param v target vector
 */
static float4 abs(float4 v) noexcept { return float4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }
/**
 * @brief Returns square root for each component of the vector.
 * @param v target vector
 */
static float4 sqrt(float4 v) noexcept
{
	return float4(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w));
}
/**
 * @brief Returns sign for each component of the vector.
 * @param v target vector
 */
static float4 sign(float4 v) noexcept { return float4(sign(v.x), sign(v.y), sign(v.z), sign(v.w)); }
/**
 * @brief Returns sign bits of the vector. (4 bits)
 * @param v target vector
 */
static uint32 signBits(float4 v) noexcept
{
	return (std::signbit(v.x) ? 1u : 0u) | (std::signbit(v.y) ? 2u : 0u) | 
		(std::signbit(v.z) ? 4u : 0u) | (std::signbit(v.w) ? 8u : 0u);
}

/**
 * @brief Rounds each component of the vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target vector
 */
static float4 round(float4 v) noexcept
{
	return float4(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w));
}
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target vector
 */
static float4 floor(float4 v) noexcept
{
	return float4(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w));
}
/**
 * @brief Rounds each component of the vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target vector
 */
static float4 ceil(float4 v) noexcept
{
	return float4(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w));
}
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target vector
 */
static float4 trunc(float4 v) noexcept
{
	return float4(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z), std::trunc(v.w));
}

/***********************************************************************************************************************
 * @brief Returns dot product between two vector.
 * 
 * @param a first vector to dot
 * @param b second vector to dot
 */
static constexpr float dot(float4 a, float4 b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

/**
 * @brief Returns squared length of the vector. (length ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * @param v target vector
 */
static constexpr float lengthSq(float4 v) noexcept { return dot(v, v); }
/**
 * @brief Returns length of the vector.
 * @param v target vector
 */
static float length(float4 v) noexcept { return std::sqrt(dot(v, v)); }

/**
 * @brief Returns squared distance between two points. (distance ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * 
 * @param a first point
 * @param b second point
 */
static constexpr float distanceSq(float4 a, float4 b) noexcept { return lengthSq(a - b); }
/**
 * @brief Returns distance between two points.
 * 
 * @param a first point
 * @param b second point
 */
static float distance(float4 a, float4 b) noexcept { return length(a - b); }
/**
 * @brief Returns true if two vectors are close with specified maximum squared distance. (maxDistance ^ 2)
 * 
 * @param a first vector
 * @param b second vector
 */
static constexpr bool isClose(float4 a, float4 b, float maxDistSq = 1.0e-12f) noexcept
{
	return distanceSq(a, b) <= maxDistSq;
}

/**
 * @brief Returns normalized vector. (With length of 1.0f)
 * @param v target vector to normalize
 */
static float4 normalize(float4 v) noexcept { return v * (1.0f / length(v)); }
/**
 * @brief Returns true if vector is normalized with specified tolerance.
 * 
 * @param v target vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized(float4 v, float tolerance = 1.0e-6f) noexcept
{
	return std::abs(lengthSq(v) - 1.0f) <= tolerance;
}
/**
 * @brief Returns true if any vector element is not a number.
 * @param v target vector to check
 */
static bool isNan(float4 v) noexcept { return isnan(v.x) || isnan(v.y) || isnan(v.z) || isnan(v.w); }

/**
 * @brief Remaps each component of vector to the 0.0 - 1.0 range.
 * @param v target vector
 */
static float4 repeat(float4 v) noexcept { return float4(repeat(v.x), repeat(v.y), repeat(v.z), repeat(v.w)); }

/**
 * @brief Linearly interpolates each component of the vector between a and b using t.
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static float4 lerp(float4 a, float4 b, float t) noexcept { return a * (1.0f - t) + b * t; }
/**
 * @brief Linearly interpolates each component of the vector between a and b using t, taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 * @param dt current delta time
 */
static float4 lerpDelta(float4 a, float4 b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}

/**
 * @brief Computes the power of each component of base b raised to the corresponding exponent e.
 * 
 * @param b target base vector to raise
 * @param e exponent vector
 */
static float4 pow(float4 b, float4 e) noexcept
{
	return float4(std::pow(b.x, e.x), std::pow(b.y, e.y), std::pow(b.z, e.z), std::pow(b.w, e.w));
}
/**
 * @brief Applies gain function for each component of the vector.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target vector to gain (0.0 - 1.0)
 * @param k gain factor
 */
static float4 gain(float4 x, float4 k) noexcept
{
	auto a = float4(0.5f) * pow(2.0f * select(x < 0.5f, x, 1.0f - x), k);
	return select(x < 0.5f, a, 1.0f - a);
}

//**********************************************************************************************************************
// TODO: possibly add more specific math functions like remquo, sph_neumann or dFdx.

static float2 mod(float2 a, float2 b) noexcept { return float2(std::fmod(a.x, b.x), std::fmod(a.y, b.y)); }
static float2 exp(float2 v) noexcept { return float2(std::exp(v.x), std::exp(v.y)); }
static float2 exp2(float2 v) noexcept { return float2(std::exp2(v.x), std::exp2(v.y)); }
static float2 expm1(float2 v) noexcept { return float2(std::expm1(v.x), std::expm1(v.y)); }
static float2 log(float2 v) noexcept { return float2(std::log(v.x), std::log(v.y)); }
static float2 log10(float2 v) noexcept { return float2(std::log10(v.x), std::log10(v.y)); }
static float2 log2(float2 v) noexcept { return float2(std::log2(v.x), std::log2(v.y)); }
static float2 log1p(float2 v) noexcept { return float2(std::log1p(v.x), std::log1p(v.y)); }
static float2 cbrt(float2 v) noexcept { return float2(std::cbrt(v.x), std::cbrt(v.y)); }
static float2 sin(float2 v) noexcept { return float2(std::sin(v.x), std::sin(v.y)); }
static float2 cos(float2 v) noexcept { return float2(std::cos(v.x), std::cos(v.y)); }
static float2 tan(float2 v) noexcept { return float2(std::tan(v.x), std::tan(v.y)); }
static float2 asin(float2 v) noexcept { return float2(std::asin(v.x), std::asin(v.y)); }
static float2 acos(float2 v) noexcept { return float2(std::acos(v.x), std::acos(v.y)); }
static float2 atan(float2 v) noexcept { return float2(std::atan(v.x), std::atan(v.y)); }
static float2 atan(float2 a, float2 b) noexcept { return float2(std::atan2(a.x, b.x), std::atan2(a.y, b.y)); }
static float2 sinh(float2 v) noexcept { return float2(std::sinh(v.x), std::sinh(v.y)); }
static float2 cosh(float2 v) noexcept { return float2(std::cosh(v.x), std::cosh(v.y)); }
static float2 tanh(float2 v) noexcept { return float2(std::tanh(v.x), std::tanh(v.y)); }
static float2 asinh(float2 v) noexcept { return float2(std::asinh(v.x), std::asinh(v.y)); }
static float2 acosh(float2 v) noexcept { return float2(std::acosh(v.x), std::acosh(v.y)); }
static float2 atanh(float2 v) noexcept { return float2(std::atanh(v.x), std::atanh(v.y)); }

//**********************************************************************************************************************
static float3 mod(float3 a, float3 b) noexcept
{
	return float3(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z));
}
static float3 exp(float3 v) noexcept { return float3(std::exp(v.x), std::exp(v.y), std::exp(v.z)); }
static float3 exp2(float3 v) noexcept { return float3(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z)); }
static float3 expm1(float3 v) noexcept { return float3(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z)); }
static float3 log(float3 v) noexcept { return float3(std::log(v.x), std::log(v.y), std::log(v.z)); }
static float3 log10(float3 v) noexcept { return float3(std::log10(v.x), std::log10(v.y), std::log10(v.z)); }
static float3 log2(float3 v) noexcept { return float3(std::log2(v.x), std::log2(v.y), std::log2(v.z)); }
static float3 log1p(float3 v) noexcept { return float3(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z)); }
static float3 cbrt(float3 v) noexcept { return float3(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z)); }
static float3 sin(float3 v) noexcept { return float3(std::sin(v.x), std::sin(v.y), std::sin(v.z)); }
static float3 cos(float3 v) noexcept { return float3(std::cos(v.x), std::cos(v.y), std::cos(v.z)); }
static float3 tan(float3 v) noexcept { return float3(std::tan(v.x), std::tan(v.y), std::tan(v.z)); }
static float3 asin(float3 v) noexcept { return float3(std::asin(v.x), std::asin(v.y), std::asin(v.z)); }
static float3 acos(float3 v) noexcept { return float3(std::acos(v.x), std::acos(v.y), std::acos(v.z)); }
static float3 atan(float3 v) noexcept { return float3(std::atan(v.x), std::atan(v.y), std::atan(v.z)); }
static float3 atan(float3 a, float3 b) noexcept
{
	return float3(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z));
}
static float3 sinh(float3 v) noexcept { return float3(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z)); }
static float3 cosh(float3 v) noexcept { return float3(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z)); }
static float3 tanh(float3 v) noexcept { return float3(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z)); }
static float3 asinh(float3 v) noexcept { return float3(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z)); }
static float3 acosh(float3 v) noexcept { return float3(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z)); }
static float3 atanh(float3 v) noexcept { return float3(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z)); }

//**********************************************************************************************************************
static float4 mod(float4 a, float4 b) noexcept
{
	return float4(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z), std::fmod(a.w, b.w));
}
static float4 exp(float4 v) noexcept
{
	return float4(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}
static float4 exp2(float4 v) noexcept
{
	return float4(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z), std::exp2(v.w));
}
static float4 expm1(float4 v) noexcept
{
	return float4(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z), std::expm1(v.w));
}
static float4 log(float4 v) noexcept
{
	return float4(std::log(v.x), std::log(v.y), std::log(v.z), std::log(v.w));
}
static float4 log10(float4 v) noexcept
{
	return float4(std::log10(v.x), std::log10(v.y), std::log10(v.z), std::log10(v.w));
}
static float4 log2(float4 v) noexcept
{
	return float4(std::log2(v.x), std::log2(v.y), std::log2(v.z), std::log2(v.w));
}
static float4 log1p(float4 v) noexcept
{
	return float4(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z), std::log1p(v.w));
}
static float4 cbrt(float4 v) noexcept
{
	return float4(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z), std::cbrt(v.w));
}
static float4 sin(float4 v) noexcept
{
	return float4(std::sin(v.x), std::sin(v.y), std::sin(v.z), std::sin(v.w));
}
static float4 cos(float4 v) noexcept
{
	return float4(std::cos(v.x), std::cos(v.y), std::cos(v.z), std::cos(v.w));
}
static float4 tan(float4 v) noexcept
{
	return float4(std::tan(v.x), std::tan(v.y), std::tan(v.z), std::tan(v.w));
}
static float4 asin(float4 v) noexcept
{
	return float4(std::asin(v.x), std::asin(v.y), std::asin(v.z), std::asin(v.w));
}
static float4 acos(float4 v) noexcept
{
	return float4(std::acos(v.x), std::acos(v.y), std::acos(v.z), std::acos(v.w));
}
static float4 atan(float4 v) noexcept
{
	return float4(std::atan(v.x), std::atan(v.y), std::atan(v.z), std::atan(v.w));
}
static float4 atan(float4 a, float4 b) noexcept
{
	return float4(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z), std::atan2(a.w, b.w));
}
static float4 sinh(float4 v) noexcept
{
	return float4(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z), std::sinh(v.w));
}
static float4 cosh(float4 v) noexcept
{
	return float4(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z), std::cosh(v.w));
}
static float4 tanh(float4 v) noexcept
{
	return float4(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z), std::tanh(v.w));
}
static float4 asinh(float4 v) noexcept
{
	return float4(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z), std::asinh(v.w));
}
static float4 acosh(float4 v) noexcept
{
	return float4(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z), std::acosh(v.w));
}
static float4 atanh(float4 v) noexcept
{
	return float4(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z), std::atanh(v.w));
}

} // namespace math