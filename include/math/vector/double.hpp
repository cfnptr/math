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
 * @brief Common floating point 64 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/float.hpp"

namespace math
{

/**
 * @brief A 2-component vector of 64-bit floating-point values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] double2
{
	double x; /**< First vector component. */
	double y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 64-bit floating-point values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit double2(double xy = 0.0) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr double2(double x, double y) noexcept : x(x), y(y) { }

	constexpr double2(float4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(float3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(float2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(half4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(half3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(half2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(long4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(long3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(long2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(ulong4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(ulong3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(ulong2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(int4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(int3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(int2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(uint4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(uint3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(uint2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(short4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(short3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(short2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(ushort4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(ushort3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(ushort2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(sbyte4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(sbyte3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(sbyte2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(byte4 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(byte3 xy) noexcept : x((double)xy.x), y((double)xy.y) { }
	constexpr double2(byte2 xy) noexcept : x((double)xy.x), y((double)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	double& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((double*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	double operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((double*)this)[i];
	}

	constexpr explicit operator float2() const noexcept { return float2((float)x, (float)y); }
	constexpr explicit operator half2() const noexcept { return half2((half)x, (half)y); }
	constexpr explicit operator long2() const noexcept { return long2((int64)x, (int64)y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr double2 operator+(double2 v) const noexcept { return double2(x + v.x, y + v.y); }
	constexpr double2 operator-(double2 v) const noexcept { return double2(x - v.x, y - v.y); }
	constexpr double2 operator*(double2 v) const noexcept { return double2(x * v.x, y * v.y); }
	constexpr double2 operator/(double2 v) const noexcept { return double2(x / v.x, y / v.y); }
	constexpr double2 operator+(double n) const noexcept { return double2(x + n, y + n); }
	constexpr double2 operator-(double n) const noexcept { return double2(x - n, y - n); }
	constexpr double2 operator*(double n) const noexcept { return double2(x * n, y * n); }
	constexpr double2 operator/(double n) const noexcept { return double2(x / n, y / n); }
	constexpr double2 operator-() const noexcept { return double2(-x, -y); }
	double2& operator+=(double2 v) noexcept { x += v.x; y += v.y; return *this; }
	double2& operator-=(double2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	double2& operator*=(double2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	double2& operator/=(double2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	double2& operator+=(double n) noexcept { x += n; y += n; return *this; }
	double2& operator-=(double n) noexcept { x -= n; y -= n; return *this; }
	double2& operator*=(double n) noexcept { x *= n; y *= n; return *this; }
	double2& operator/=(double n) noexcept { x /= n; y /= n; return *this; }
	double2& operator=(double n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(double2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(double2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr uint2 operator<(double2 v) const noexcept
	{
		return uint2(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator>(double2 v) const noexcept
	{
		return uint2(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator<=(double2 v) const noexcept
	{
		return uint2(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator>=(double2 v) const noexcept
	{
		return uint2(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0);
	}
	constexpr bool operator==(double n) const noexcept { return *this == double2(n); }
	constexpr bool operator!=(double n) const noexcept { return *this != double2(n); }
	constexpr uint2 operator<(double n) const noexcept { return *this < double2(n); }
	constexpr uint2 operator>(double n) const noexcept { return *this > double2(n); }
	constexpr uint2 operator<=(double n) const noexcept { return *this <= double2(n); }
	constexpr uint2 operator>=(double n) const noexcept { return *this >= double2(n); }

	static const double2 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top;
};

inline constexpr double2 double2::zero = double2(0.0);
inline constexpr double2 double2::one = double2(1.0);
inline constexpr double2 double2::minusOne = double2(-1.0);
inline constexpr double2 double2::min = double2(DBL_MIN);
inline constexpr double2 double2::minusMin = double2(-DBL_MIN);
inline constexpr double2 double2::max = double2(DBL_MAX);
inline constexpr double2 double2::minusMax = double2(-DBL_MAX);
inline constexpr double2 double2::epsilon = double2(DBL_EPSILON);
inline constexpr double2 double2::inf = double2(INFINITY);
inline constexpr double2 double2::minusInf = double2(-INFINITY);
inline constexpr double2 double2::nan = double2(NAN);
inline constexpr double2 double2::left = double2(-1.0, 0.0);
inline constexpr double2 double2::right = double2(1.0, 0.0);
inline constexpr double2 double2::bottom = double2(0.0, -1.0);
inline constexpr double2 double2::top = double2(0.0, 1.0);

/***********************************************************************************************************************
 * @brief A 3-component vector of 64-bit floating-point values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] double3
{
	double x; /**< First vector component. */
	double y; /**< Second vector component. */
	double z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 64-bit floating-point values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit double3(double xyz = 0.0) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr double3(double x, double y, double z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit floating-point values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr double3(double2 xy, double z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr double3(double x, double2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	constexpr double3(float4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(float3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(half4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(half3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(long4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(long3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(ulong4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(ulong3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(int4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(int3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(uint4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(uint3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(short4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(short3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(ushort4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(ushort3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(sbyte4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(sbyte3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(byte4 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }
	constexpr double3(byte3 xyz) noexcept : x((double)xyz.x), y((double)xyz.y), z((double)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	double& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((double*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	double operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((double*)this)[i];
	}

	constexpr explicit operator float3() const noexcept { return float3((float)x, (float)y, (float)z); }
	constexpr explicit operator half3() const noexcept { return half3((half)x, (half)y, (half)z); }
	constexpr explicit operator long3() const noexcept { return long3((int64)x, (int64)y, (int64)z); }
	constexpr explicit operator ulong3() const noexcept { return ulong3((uint64)x, (uint64)y, (uint64)z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator double2() const noexcept { return double2(x, y); }
	constexpr explicit operator float2() const noexcept { return float2((float)x, (float)y); }
	constexpr explicit operator half2() const noexcept { return half2((half)x, (half)y); }
	constexpr explicit operator long2() const noexcept { return long2((int64)x, (int64)y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr double3 operator+(double3 v) const noexcept { return double3(x + v.x, y + v.y, z + v.z); }
	constexpr double3 operator-(double3 v) const noexcept { return double3(x - v.x, y - v.y, z - v.z); }
	constexpr double3 operator*(double3 v) const noexcept { return double3(x * v.x, y * v.y, z * v.z); }
	constexpr double3 operator/(double3 v) const noexcept { return double3(x / v.x, y / v.y, z / v.z); }
	constexpr double3 operator+(double n) const noexcept { return double3(x + n, y + n, z + n); }
	constexpr double3 operator-(double n) const noexcept { return double3(x - n, y - n, z - n); }
	constexpr double3 operator*(double n) const noexcept { return double3(x * n, y * n, z * n); }
	constexpr double3 operator/(double n) const noexcept { return double3(x / n, y / n, z / n); }
	constexpr double3 operator-() const noexcept { return double3(-x, -y, -z); }
	double3& operator+=(double3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	double3& operator-=(double3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	double3& operator*=(double3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	double3& operator/=(double3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	double3& operator+=(double n) noexcept { x += n; y += n; z += n; return *this; }
	double3& operator-=(double n) noexcept { x -= n; y -= n; z -= n; return *this; }
	double3& operator*=(double n) noexcept { x *= n; y *= n; z *= n; return *this; }
	double3& operator/=(double n) noexcept { x /= n; y /= n; z /= n; return *this; }
	double3& operator=(double n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(double3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(double3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr uint3 operator<(double3 v) const noexcept
	{
		return uint3(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0, z < v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator>(double3 v) const noexcept
	{
		return uint3(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0, z > v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator<=(double3 v) const noexcept
	{
		return uint3(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0, z <= v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator>=(double3 v) const noexcept
	{
		return uint3(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0, z >= v.z ? UINT32_MAX : 0);
	}
	constexpr bool operator==(double n) const noexcept { return *this == double3(n); }
	constexpr bool operator!=(double n) const noexcept { return *this != double3(n); }
	constexpr uint3 operator<(double n) const noexcept { return *this < double3(n); }
	constexpr uint3 operator>(double n) const noexcept { return *this > double3(n); }
	constexpr uint3 operator<=(double n) const noexcept { return *this <= double3(n); }
	constexpr uint3 operator>=(double n) const noexcept { return *this >= double3(n); }

	static const double3 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top, back, front;
};

inline constexpr double3 double3::zero = double3(0.0);
inline constexpr double3 double3::one = double3(1.0);
inline constexpr double3 double3::minusOne = double3(-1.0);
inline constexpr double3 double3::min = double3(DBL_MIN);
inline constexpr double3 double3::minusMin = double3(-DBL_MIN);
inline constexpr double3 double3::max = double3(DBL_MAX);
inline constexpr double3 double3::minusMax = double3(-DBL_MAX);
inline constexpr double3 double3::epsilon = double3(DBL_EPSILON);
inline constexpr double3 double3::inf = double3(INFINITY);
inline constexpr double3 double3::minusInf = double3(-INFINITY);
inline constexpr double3 double3::nan = double3(NAN);
inline constexpr double3 double3::left = double3(-1.0, 0.0, 0.0);
inline constexpr double3 double3::right = double3(1.0, 0.0, 0.0);
inline constexpr double3 double3::bottom = double3(0.0, -1.0, 0.0);
inline constexpr double3 double3::top = double3(0.0, 1.0, 0.0);
inline constexpr double3 double3::back = double3(0.0, 0.0, -1.0);
inline constexpr double3 double3::front = double3(0.0, 0.0, 1.0);

/***********************************************************************************************************************
 * @brief A 4-component vector of 64-bit floating-point values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] double4
{
	double x; /**< First vector component. */
	double y; /**< Second vector component. */
	double z; /**< Third vector component. */
	double w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit double4(double xyzw = 0.0) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr double4(double x, double y, double z, double w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr double4(double2 xy, double z, double w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr double4(double x, double2 yz, double w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr double4(double x, double y, double2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr double4(double2 xy, double2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr double4(double3 xyz, double w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector component value
	 */
	constexpr double4(double x, double3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	constexpr double4(float4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(half4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(long4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(ulong4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(int4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(uint4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(short4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(ushort4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(sbyte4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }
	constexpr double4(byte4 xyzw) noexcept : x((double)xyzw.x), y((double)xyzw.y), z((double)xyzw.z), w((double)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	double& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((double*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	double operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((double*)this)[i];
	}

	constexpr explicit operator float4() const noexcept { return float4((float)x, (float)y, (float)z, (float)w); }
	constexpr explicit operator half4() const noexcept { return half4((half)x, (half)y, (half)z, (half)w); }
	constexpr explicit operator long4() const noexcept { return long4((int64)x, (int64)y, (int64)z, (int64)w); }
	constexpr explicit operator ulong4() const noexcept { return ulong4((uint64)x, (uint64)y, (uint64)z, (uint64)w); }
	constexpr explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	constexpr explicit operator short4() const noexcept { return short4((int16)x, (int16)y, (int16)z, (int16)w); }
	constexpr explicit operator ushort4() const noexcept { return ushort4((uint16)x, (uint16)y, (uint16)z, (uint16)w); }
	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator double3() const noexcept { return double3(x, y, z); }
	constexpr explicit operator float3() const noexcept { return float3((float)x, (float)y, (float)z); }
	constexpr explicit operator half3() const noexcept { return half3((half)x, (half)y, (half)z); }
	constexpr explicit operator long3() const noexcept { return long3((int64)x, (int64)y, (int64)z); }
	constexpr explicit operator ulong3() const noexcept { return ulong3((uint64)x, (uint64)y, (uint64)z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator double2() const noexcept { return double2(x, y); }
	constexpr explicit operator float2() const noexcept { return float2((float)x, (float)y); }
	constexpr explicit operator half2() const noexcept { return half2((half)x, (half)y); }
	constexpr explicit operator long2() const noexcept { return long2((int64)x, (int64)y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr double4 operator+(double4 v) const noexcept { return double4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr double4 operator-(double4 v) const noexcept { return double4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr double4 operator*(double4 v) const noexcept { return double4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr double4 operator/(double4 v) const noexcept { return double4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr double4 operator+(double n) const noexcept { return double4(x + n, y + n, z + n, w + n); }
	constexpr double4 operator-(double n) const noexcept { return double4(x - n, y - n, z - n, w - n); }
	constexpr double4 operator*(double n) const noexcept { return double4(x * n, y * n, z * n, w * n); }
	constexpr double4 operator/(double n) const noexcept { return double4(x / n, y / n, z / n, w / n); }
	constexpr double4 operator-() const noexcept { return double4(-x, -y, -z, -w); }
	double4& operator+=(double4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	double4& operator-=(double4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	double4& operator*=(double4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	double4& operator/=(double4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	double4& operator+=(double n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	double4& operator-=(double n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	double4& operator*=(double n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	double4& operator/=(double n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	double4& operator=(double n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(double4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(double4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr uint4 operator<(double4 v) const noexcept
	{
		return uint4(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0, 
			z < v.z ? UINT32_MAX : 0, w < v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator>(double4 v) const noexcept
	{
		return uint4(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0, 
			z > v.z ? UINT32_MAX : 0, w > v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator<=(double4 v) const noexcept
	{
		return uint4(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0, 
			z <= v.z ? UINT32_MAX : 0, w <= v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator>=(double4 v) const noexcept
	{
		return uint4(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0, 
			z >= v.z ? UINT32_MAX : 0, w >= v.w ? UINT32_MAX : 0);
	}
	constexpr bool operator==(double n) const noexcept { return *this == double4(n); }
	constexpr bool operator!=(double n) const noexcept { return *this != double4(n); }
	constexpr uint4 operator<(double n) const noexcept { return *this < double4(n); }
	constexpr uint4 operator>(double n) const noexcept { return *this > double4(n); }
	constexpr uint4 operator<=(double n) const noexcept { return *this <= double4(n); }
	constexpr uint4 operator>=(double n) const noexcept { return *this >= double4(n); }

	static const double4 zero, one, minusOne, min, minusMin, max, minusMax, epsilon, inf, minusInf, nan;
};

inline constexpr double4 double4::zero = double4(0.0);
inline constexpr double4 double4::one = double4(1.0);
inline constexpr double4 double4::minusOne = double4(-1.0);
inline constexpr double4 double4::min = double4(DBL_MIN);
inline constexpr double4 double4::minusMin = double4(-DBL_MIN);
inline constexpr double4 double4::max = double4(DBL_MAX);
inline constexpr double4 double4::minusMax = double4(-DBL_MAX);
inline constexpr double4 double4::epsilon = double4(DBL_EPSILON);
inline constexpr double4 double4::inf = double4(INFINITY);
inline constexpr double4 double4::minusInf = double4(-INFINITY);
inline constexpr double4 double4::nan = double4(NAN);

//**********************************************************************************************************************
static constexpr double2 operator+(double n, double2 v) noexcept { return double2(n) + v; }
static constexpr double2 operator-(double n, double2 v) noexcept { return double2(n) - v; }
static constexpr double2 operator*(double n, double2 v) noexcept { return double2(n) * v; }
static constexpr double2 operator/(double n, double2 v) noexcept { return double2(n) / v; }
static constexpr bool operator==(double n, double2 v) noexcept { return double2(n) == v; }
static constexpr bool operator!=(double n, double2 v) noexcept { return double2(n) != v; }
static constexpr uint2 operator<(double n, double2 v) noexcept { return double2(n) < v; }
static constexpr uint2 operator>(double n, double2 v) noexcept { return double2(n) > v; }
static constexpr uint2 operator<=(double n, double2 v) noexcept { return double2(n) <= v; }
static constexpr uint2 operator>=(double n, double2 v) noexcept { return double2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(double2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint2 equal(double2 a, double2 b) noexcept
{
	return uint2(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint2 notEqual(double2 a, double2 b) noexcept
{
	return uint2(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(double2 a, double2 b) noexcept { return memcmp(&a, &b, sizeof(double2)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr double2 select(uint2 c, double2 t, double2 f) noexcept
{
	return double2(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr double2 min(double2 a, double2 b) noexcept { return double2(std::min(a.x, b.x), std::min(a.y, b.y)); }
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr double2 max(double2 a, double2 b) noexcept { return double2(std::max(a.x, b.x), std::max(a.y, b.y)); }
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr double2 min(double2 a, double2 b, double2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr double2 max(double2 a, double2 b, double2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values. (Inclusive range)
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr double2 clamp(double2 v, double2 min, double2 max) noexcept
{
	return double2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}
/**
 * @brief Clamps vector components between the 0.0 and 1.0. (Inclusive range)
 * @param v target vector to saturate
 */
static constexpr double2 saturate(double2 v) noexcept { return double2(saturate(v.x), saturate(v.y)); }

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first vector multiplier
 * @param mul2 second vector multiplier
 * @param add vector addend
 */
static double2 fma(double2 mul1, double2 mul2, double2 add) noexcept
{
	return double2(std::fma(mul1.x, mul2.x, add.x), std::fma(mul1.y, mul2.y, add.y));
}
/**
 * @brief Returns absolute value for each component of the vector.
 * @param v target vector
 */
static double2 abs(double2 v) noexcept { return double2(std::abs(v.x), std::abs(v.y)); }
/**
 * @brief Returns square root for each component of the vector.
 * @param v target vector
 */
static double2 sqrt(double2 v) noexcept { return double2(std::sqrt(v.x), std::sqrt(v.y)); }
/**
 * @brief Returns sign for each component of the vector.
 * @param v target vector
 */
static double2 sign(double2 v) noexcept { return double2(sign(v.x), sign(v.y)); }
/**
 * @brief Returns sign bits of the vector. (2 bits)
 * @param v target vector
 */
static uint32 signBits(double2 v) noexcept { return (std::signbit(v.x) ? 1u : 0u) | (std::signbit(v.y) ? 2u : 0u); }

/**
 * @brief Returns index of the highest vector component value.
 * @param v target vector
 */
static constexpr uint32 getHighest(double2 v) noexcept { return v.x > v.y ? 0 : 1; }
/**
 * @brief Returns index of the lowest vector component value.
 * @param v target vector
 */
static constexpr uint32 getLowest3(double2 v) noexcept { return v.x < v.y ? 0 : 1; }

/**
 * @brief Rounds each component of the vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target vector
 */
static double2 round(double2 v) noexcept { return double2(std::round(v.x), std::round(v.y)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target vector
 */
static double2 floor(double2 v) noexcept { return double2(std::floor(v.x), std::floor(v.y)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target vector
 */
static double2 ceil(double2 v) noexcept { return double2(std::ceil(v.x), std::ceil(v.y)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target vector
 */
static double2 trunc(double2 v) noexcept { return double2(std::trunc(v.x), std::trunc(v.y)); }

/***********************************************************************************************************************
 * @brief Returns dot product between two vector.
 * 
 * @param a first vector to dot
 * @param b second vector to dot
 */
static constexpr double dot(double2 a, double2 b) noexcept { return a.x * b.x + a.y * b.y; }

/**
 * @brief Returns squared length of the vector. (length ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * @param v target vector
 */
static constexpr double lengthSq(double2 v) noexcept { return dot(v, v); }
/**
 * @brief Returns length of the vector.
 * @param v target vector
 */
static double length(double2 v) noexcept { return std::sqrt(dot(v, v)); }

/**
 * @brief Returns squared distance between two points. (distance ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * 
 * @param a first point
 * @param b second point
 */
static constexpr double distanceSq(double2 a, double2 b) noexcept { return lengthSq(a - b); }
/**
 * @brief Returns distance between two points.
 * 
 * @param a first point
 * @param b second point
 */
static double distance(double2 a, double2 b) noexcept { return length(a - b); }
/**
 * @brief Returns true if two vectors are close with specified maximum squared distance. (maxDistance ^ 2)
 * 
 * @param a first vector
 * @param b second vector
 */
static constexpr bool isClose(double2 a, double2 b, double maxDistSq = 1.0e-28) noexcept
{
	return distanceSq(a, b) <= maxDistSq;
}

/**
 * @brief Returns normalized vector. (With length of 1.0)
 * @param v target vector to normalize
 */
static double2 normalize(double2 v) noexcept { return v * (1.0 / length(v)); }
/**
 * @brief Returns true if vector is normalized with specified tolerance.
 * 
 * @param v target vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized(double2 v, double tolerance = 1.0e-14) noexcept
{
	return std::abs(lengthSq(v) - 1.0) <= tolerance;
}
/**
 * @brief Returns true if any vector element is not a number.
 * @param v target vector to check
 */
static bool isNan(double2 v) noexcept { return isnan(v.x) || isnan(v.y); }

/**
 * @brief Remaps each component of vector to the 0.0 - 1.0 range.
 * @param v target vector
 */
static double2 repeat(double2 v) noexcept { return double2(repeat(v.x), repeat(v.y)); }

/**
 * @brief Linearly interpolates each component of the vector between a and b using t.
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static double2 lerp(double2 a, double2 b, double t) noexcept { return fma(double2(t), b, fma(double2(-t), a, a)); }
/**
 * @brief Linearly interpolates each component of the vector between a and b taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param dr target decay rate value
 * @param dt current delta time
 */
static double2 lerpDelta(double2 a, double2 b, double dr, double dt) noexcept { return lerp(b, a, std::exp(-dr * dt)); }

/**
 * @brief Computes the power of each component of base b raised to the corresponding exponent e.
 * 
 * @param b target base vector to raise
 * @param e exponent vector
 */
static double2 pow(double2 b, double2 e) noexcept { return double2(std::pow(b.x, e.x), std::pow(b.y, e.y)); }
/**
 * @brief Applies gain function for each component of the vector.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target vector to gain (0.0 - 1.0)
 * @param k gain factor
 */
static double2 gain(double2 x, double2 k) noexcept
{
	auto a = double2(0.5) * pow(2.0 * select(x < 0.5, x, 1.0 - x), k);
	return select(x < 0.5, a, 1.0 - a);
}

//**********************************************************************************************************************
static constexpr double3 operator+(double n, double3 v) noexcept { return double3(n) + v; }
static constexpr double3 operator-(double n, double3 v) noexcept { return double3(n) - v; }
static constexpr double3 operator*(double n, double3 v) noexcept { return double3(n) * v; }
static constexpr double3 operator/(double n, double3 v) noexcept { return double3(n) / v; }
static constexpr bool operator==(double n, double3 v) noexcept { return double3(n) == v; }
static constexpr bool operator!=(double n, double3 v) noexcept { return double3(n) != v; }
static constexpr uint3 operator<(double n, double3 v) noexcept { return double3(n) < v; }
static constexpr uint3 operator>(double n, double3 v) noexcept { return double3(n) > v; }
static constexpr uint3 operator<=(double n, double3 v) noexcept { return double3(n) <= v; }
static constexpr uint3 operator>=(double n, double3 v) noexcept { return double3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(double3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint3 equal(double3 a, double3 b) noexcept
{
	return uint3(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0, a.z == b.z ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint3 notEqual(double3 a, double3 b) noexcept
{
	return uint3(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0, a.z != b.z ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const double3& a, const double3& b) noexcept { return memcmp(&a, &b, sizeof(double3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr double3 select(uint3 c, double3 t, double3 f) noexcept
{
	return double3(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y, c.z & 0x80000000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr double3 min(double3 a, double3 b) noexcept
{
	return double3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr double3 max(double3 a, double3 b) noexcept
{
	return double3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr double3 min(double3 a, double3 b, double3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr double3 max(double3 a, double3 b, double3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values. (Inclusive range)
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr double3 clamp(double3 v, double3 min, double3 max) noexcept
{
	return double3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}
/**
 * @brief Clamps vector components between the 0.0 and 1.0. (Inclusive range)
 * @param v target vector to saturate
 */
static constexpr double3 saturate(double3 v) noexcept { return double3(saturate(v.x), saturate(v.y), saturate(v.z)); }

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first vector multiplier
 * @param mul2 second vector multiplier
 * @param add vector addend
 */
static double3 fma(double3 mul1, double3 mul2, double3 add) noexcept
{
	return double3(std::fma(mul1.x, mul2.x, add.x), std::fma(mul1.y, mul2.y, add.y), std::fma(mul1.z, mul2.z, add.z));
}
/**
 * @brief Returns absolute value for each component of the vector.
 * @param v target vector
 */
static double3 abs(double3 v) noexcept { return double3(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
/**
 * @brief Returns square root for each component of the vector.
 * @param v target vector
 */
static double3 sqrt(double3 v) noexcept { return double3(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z)); }
/**
 * @brief Returns sign for each component of the vector.
 * @param v target vector
 */
static double3 sign(double3 v) noexcept { return double3(sign(v.x), sign(v.y), sign(v.z)); }
/**
 * @brief Returns sign bits of the vector. (3 bits)
 * @param v target vector
 */
static uint32 signBits(double3 v) noexcept
{
	return (std::signbit(v.x) ? 1u : 0u) | (std::signbit(v.y) ? 2u : 0u) | (std::signbit(v.z) ? 4u : 0u);
}

/**
 * @brief Returns index of the highest vector component value.
 * @param v target vector
 */
static constexpr uint32 getHighest(double3 v) noexcept { return v.x > v.y ? (v.z > v.x ? 2 : 0) : (v.z > v.y ? 2 : 1); }
/**
 * @brief Returns index of the lowest vector component value.
 * @param v target vector
 */
static constexpr uint32 getLowest(double3 v) noexcept { return v.x < v.y ? (v.z < v.x ? 2 : 0) : (v.z < v.y ? 2 : 1); }

/**
 * @brief Rounds each component of the vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target vector
 */
static double3 round(double3 v) noexcept { return double3(std::round(v.x), std::round(v.y), std::round(v.z)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target vector
 */
static double3 floor(double3 v) noexcept { return double3(std::floor(v.x), std::floor(v.y), std::floor(v.z)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target vector
 */
static double3 ceil(double3 v) noexcept { return double3(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); }
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target vector
 */
static double3 trunc(double3 v) noexcept { return double3(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z)); }

/***********************************************************************************************************************
 * @brief Returns dot product between two vector.
 * 
 * @param a first vector to dot
 * @param b second vector to dot
 */
static constexpr double dot(double3 a, double3 b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
/**
 * @brief Returns cross product between two vector.
 * 
 * @param a first vector to cross
 * @param b second vector to cross
 */
static constexpr double3 cross(double3 a, double3 b) noexcept
{
	return double3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

/**
 * @brief Returns squared length of the vector. (length ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * @param v target vector
 */
static constexpr double lengthSq(double3 v) noexcept { return dot(v, v); }
/**
 * @brief Returns length of the vector.
 * @param v target vector
 */
static double length(double3 v) noexcept { return std::sqrt(dot(v, v)); }

/**
 * @brief Returns squared distance between two points. (distance ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * 
 * @param a first point
 * @param b second point
 */
static constexpr double distanceSq(double3 a, double3 b) noexcept { return lengthSq(a - b); }
/**
 * @brief Returns distance between two points.
 * 
 * @param a first point
 * @param b second point
 */
static double distance(double3 a, double3 b) noexcept { return length(a - b); }
/**
 * @brief Returns true if two vectors are close with specified maximum squared distance. (maxDistance ^ 2)
 * 
 * @param a first vector
 * @param b second vector
 */
static constexpr bool isClose(double3 a, double3 b, double maxDistSq = 1.0e-28) noexcept
{
	return distanceSq(a, b) <= maxDistSq;
}

/**
 * @brief Returns normalized vector. (With length of 1.0)
 * @param v target vector to normalize
 */
static double3 normalize(double3 v) noexcept { return v * (1.0 / length(v)); }
/**
 * @brief Returns true if vector is normalized with specified tolerance.
 * 
 * @param v target vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized(double3 v, double tolerance = 1.0e-14) noexcept
{
	return std::abs(lengthSq(v) - 1.0) <= tolerance;
}
/**
 * @brief Returns true if any vector element is not a number.
 * @param v target vector to check
 */
static bool isNan(double3 v) noexcept { return isnan(v.x) || isnan(v.y) || isnan(v.z); }

/**
 * @brief Remaps each component of vector to the 0.0 - 1.0 range.
 * @param v target vector
 */
static double3 repeat(double3 v) noexcept { return double3(repeat(v.x), repeat(v.y), repeat(v.z)); }

/**
 * @brief Linearly interpolates each component of the vector between a and b using t.
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static double3 lerp(double3 a, double3 b, double t) noexcept { return fma(double3(t), b, fma(double3(-t), a, a)); }
/**
 * @brief Linearly interpolates each component of the vector between a and b taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param dr target decay rate value
 * @param dt current delta time
 */
static double3 lerpDelta(double3 a, double3 b, double dr, double dt) noexcept { return lerp(b, a, std::exp(-dr * dt)); }

/**
 * @brief Computes the power of each component of base b raised to the corresponding exponent e.
 * 
 * @param b target base vector to raise
 * @param e exponent vector
 */
static double3 pow(double3 b, double3 e) noexcept
{
	return double3(std::pow(b.x, e.x), std::pow(b.y, e.y), std::pow(b.z, e.z));
}
/**
 * @brief Applies gain function for each component of the vector.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target vector to gain (0.0 - 1.0)
 * @param k gain factor
 */
static double3 gain(double3 x, double3 k) noexcept
{
	auto a = double3(0.5) * pow(2.0 * select(x < 0.5, x, 1.0 - x), k);
	return select(x < 0.5, a, 1.0 - a);
}

//**********************************************************************************************************************
static constexpr double4 operator+(double n, double4 v) noexcept { return double4(n) + v; }
static constexpr double4 operator-(double n, double4 v) noexcept { return double4(n) - v; }
static constexpr double4 operator*(double n, double4 v) noexcept { return double4(n) * v; }
static constexpr double4 operator/(double n, double4 v) noexcept { return double4(n) / v; }
static constexpr bool operator==(double n, double4 v) noexcept { return double4(n) == v; }
static constexpr bool operator!=(double n, double4 v) noexcept { return double4(n) != v; }
static constexpr uint4 operator<(double n, double4 v) noexcept { return double4(n) < v; }
static constexpr uint4 operator>(double n, double4 v) noexcept { return double4(n) > v; }
static constexpr uint4 operator<=(double n, double4 v) noexcept { return double4(n) <= v; }
static constexpr uint4 operator>=(double n, double4 v) noexcept { return double4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(double4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint4 equal(double4 a, double4 b) noexcept
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
static uint4 notEqual(double4 a, double4 b) noexcept
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
static bool isBinaryLess(const double4& a, const double4& b) noexcept { return memcmp(&a, &b, sizeof(double4)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr double4 select(uint4 c, double4 t, double4 f) noexcept
{
	return double4(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y, 
		c.z & 0x80000000u ? t.z : f.z, c.w & 0x80000000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr double4 min(double4 a, double4 b) noexcept
{
	return double4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr double4 max(double4 a, double4 b) noexcept
{
	return double4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr double4 min(double4 a, double4 b, double4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr double4 max(double4 a, double4 b, double4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values. (Inclusive range)
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr double4 clamp(double4 v, double4 min, double4 max) noexcept
{
	return double4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}
/**
 * @brief Clamps vector components between the 0.0 and 1.0. (Inclusive range)
 * @param v target vector to saturate
 */
static constexpr double4 saturate(double4 v) noexcept
{
	return double4(saturate(v.x), saturate(v.y), saturate(v.z), saturate(v.w));
}

/***********************************************************************************************************************
 * @brief Fused multiply add, calculates: mul1 * mul2 + add
 * 
 * @param mul1 first vector multiplier
 * @param mul2 second vector multiplier
 * @param add vector addend
 */
static double4 fma(double4 mul1, double4 mul2, double4 add) noexcept
{
	return double4(std::fma(mul1.x, mul2.x, add.x), std::fma(mul1.y, mul2.y, add.y), 
		std::fma(mul1.z, mul2.z, add.z), std::fma(mul1.w, mul2.w, add.w));
}
/**
 * @brief Returns absolute value for each component of the vector.
 * @param v target vector
 */
static double4 abs(double4 v) noexcept { return double4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }
/**
 * @brief Returns square root for each component of the vector.
 * @param v target vector
 */
static double4 sqrt(double4 v) noexcept
{
	return double4(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w));
}
/**
 * @brief Returns sign for each component of the vector.
 * @param v target vector
 */
static double4 sign(double4 v) noexcept { return double4(sign(v.x), sign(v.y), sign(v.z), sign(v.w)); }
/**
 * @brief Returns sign bits of the vector. (4 bits)
 * @param v target vector
 */
static uint32 signBits(double4 v) noexcept
{
	return (std::signbit(v.x) ? 1u : 0u) | (std::signbit(v.y) ? 2u : 0u) | 
		(std::signbit(v.z) ? 4u : 0u) | (std::signbit(v.w) ? 8u : 0u);
}

/**
 * @brief Rounds each component of the vector to nearest integer. (1.5 -> 2.0; -1.5 -> -2.0)
 * @param v target vector
 */
static double4 round(double4 v) noexcept
{
	return double4(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w));
}
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.7 -> -2.0)
 * @param v target vector
 */
static double4 floor(double4 v) noexcept
{
	return double4(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w));
}
/**
 * @brief Rounds each component of the vector to nearest integer. (1.4 -> 2.0; -1.4 -> -1.0)
 * @param v target vector
 */
static double4 ceil(double4 v) noexcept
{
	return double4(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w));
}
/**
 * @brief Rounds each component of the vector to nearest integer. (1.7 -> 1.0; -1.9 -> -1.0)
 * @param v target vector
 */
static double4 trunc(double4 v) noexcept
{
	return double4(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z), std::trunc(v.w));
}

/***********************************************************************************************************************
 * @brief Returns dot product between two vector.
 * 
 * @param a first vector to dot
 * @param b second vector to dot
 */
static constexpr double dot(double4 a, double4 b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }

/**
 * @brief Returns squared length of the vector. (length ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * @param v target vector
 */
static constexpr double lengthSq(double4 v) noexcept { return dot(v, v); }
/**
 * @brief Returns length of the vector.
 * @param v target vector
 */
static double length(double4 v) noexcept { return std::sqrt(dot(v, v)); }

/**
 * @brief Returns squared distance between two points. (distance ^ 2)
 * @note Faster to compute because we don't calculate square root.
 * 
 * @param a first point
 * @param b second point
 */
static constexpr double distanceSq(double4 a, double4 b) noexcept { return lengthSq(a - b); }
/**
 * @brief Returns distance between two points.
 * 
 * @param a first point
 * @param b second point
 */
static double distance(double4 a, double4 b) noexcept { return length(a - b); }
/**
 * @brief Returns true if two vectors are close with specified maximum squared distance. (maxDistance ^ 2)
 * 
 * @param a first vector
 * @param b second vector
 */
static constexpr bool isClose(double4 a, double4 b, double maxDistSq = 1.0e-28) noexcept
{
	return distanceSq(a, b) <= maxDistSq;
}

/**
 * @brief Returns normalized vector. (With length of 1.0)
 * @param v target vector to normalize
 */
static double4 normalize(double4 v) noexcept { return v * (1.0 / length(v)); }
/**
 * @brief Returns true if vector is normalized with specified tolerance.
 * 
 * @param v target vector to check
 * @param tolerance floating point precision tolerance
 */
static bool isNormalized(double4 v, double tolerance = 1.0e-14) noexcept
{
	return std::abs(lengthSq(v) - 1.0) <= tolerance;
}
/**
 * @brief Returns true if any vector element is not a number.
 * @param v target vector to check
 */
static bool isNan(double4 v) noexcept { return isnan(v.x) || isnan(v.y) || isnan(v.z) || isnan(v.w); }

/**
 * @brief Remaps each component of vector to the 0.0 - 1.0 range.
 * @param v target vector
 */
static double4 repeat(double4 v) noexcept { return double4(repeat(v.x), repeat(v.y), repeat(v.z), repeat(v.w)); }

/**
 * @brief Linearly interpolates each component of the vector between a and b using t.
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param t target interpolation value (0.0 - 1.0)
 */
static double4 lerp(double4 a, double4 b, double t) noexcept { return fma(double4(t), b, fma(double4(-t), a, a)); }
/**
 * @brief Linearly interpolates each component of the vector between a and b taking into account delta time.
 * @note Always use this function instead of basic lerp() when you have variable delta time!
 * 
 * @param a minimum vector (t == 0.0)
 * @param b maximum vector (t == 1.0)
 * @param dr target decay rate value
 * @param dt current delta time
 */
static double4 lerpDelta(double4 a, double4 b, double dr, double dt) noexcept  { return lerp(b, a, std::exp(-dr * dt)); }

/**
 * @brief Computes the power of each component of base b raised to the corresponding exponent e.
 * 
 * @param b target base vector to raise
 * @param e exponent vector
 */
static double4 pow(double4 b, double4 e) noexcept
{
	return double4(std::pow(b.x, e.x), std::pow(b.y, e.y), std::pow(b.z, e.z), std::pow(b.w, e.w));
}
/**
 * @brief Applies gain function for each component of the vector.
 * @note The function is symmetric when x == 0.5.
 * 
 * @param x target vector to gain (0.0 - 1.0)
 * @param k gain factor
 */
static double4 gain(double4 x, double4 k) noexcept
{
	auto a = double4(0.5) * pow(2.0 * select(x < 0.5, x, 1.0 - x), k);
	return select(x < 0.5, a, 1.0 - a);
}

//**********************************************************************************************************************
// TODO: possibly add more specific math functions like remquo, sph_neumann or dFdx.

static double2 mod(double2 a, double2 b) noexcept { return double2(std::fmod(a.x, b.x), std::fmod(a.y, b.y)); }
static double2 exp(double2 v) noexcept { return double2(std::exp(v.x), std::exp(v.y)); }
static double2 exp2(double2 v) noexcept { return double2(std::exp2(v.x), std::exp2(v.y)); }
static double2 expm1(double2 v) noexcept { return double2(std::expm1(v.x), std::expm1(v.y)); }
static double2 log(double2 v) noexcept { return double2(std::log(v.x), std::log(v.y)); }
static double2 log10(double2 v) noexcept { return double2(std::log10(v.x), std::log10(v.y)); }
static double2 log2(double2 v) noexcept { return double2(std::log2(v.x), std::log2(v.y)); }
static double2 log1p(double2 v) noexcept { return double2(std::log1p(v.x), std::log1p(v.y)); }
static double2 cbrt(double2 v) noexcept { return double2(std::cbrt(v.x), std::cbrt(v.y)); }
static double2 sin(double2 v) noexcept { return double2(std::sin(v.x), std::sin(v.y)); }
static double2 cos(double2 v) noexcept { return double2(std::cos(v.x), std::cos(v.y)); }
static double2 tan(double2 v) noexcept { return double2(std::tan(v.x), std::tan(v.y)); }
static double2 asin(double2 v) noexcept { return double2(std::asin(v.x), std::asin(v.y)); }
static double2 acos(double2 v) noexcept { return double2(std::acos(v.x), std::acos(v.y)); }
static double2 atan(double2 v) noexcept { return double2(std::atan(v.x), std::atan(v.y)); }
static double2 atan(double2 a, double2 b) noexcept { return double2(std::atan2(a.x, b.x), std::atan2(a.y, b.y)); }
static double2 sinh(double2 v) noexcept { return double2(std::sinh(v.x), std::sinh(v.y)); }
static double2 cosh(double2 v) noexcept { return double2(std::cosh(v.x), std::cosh(v.y)); }
static double2 tanh(double2 v) noexcept { return double2(std::tanh(v.x), std::tanh(v.y)); }
static double2 asinh(double2 v) noexcept { return double2(std::asinh(v.x), std::asinh(v.y)); }
static double2 acosh(double2 v) noexcept { return double2(std::acosh(v.x), std::acosh(v.y)); }
static double2 atanh(double2 v) noexcept { return double2(std::atanh(v.x), std::atanh(v.y)); }

//**********************************************************************************************************************
static double3 mod(double3 a, double3 b) noexcept
{
	return double3(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z));
}
static double3 exp(double3 v) noexcept { return double3(std::exp(v.x), std::exp(v.y), std::exp(v.z)); }
static double3 exp2(double3 v) noexcept { return double3(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z)); }
static double3 expm1(double3 v) noexcept { return double3(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z)); }
static double3 log(double3 v) noexcept { return double3(std::log(v.x), std::log(v.y), std::log(v.z)); }
static double3 log10(double3 v) noexcept { return double3(std::log10(v.x), std::log10(v.y), std::log10(v.z)); }
static double3 log2(double3 v) noexcept { return double3(std::log2(v.x), std::log2(v.y), std::log2(v.z)); }
static double3 log1p(double3 v) noexcept { return double3(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z)); }
static double3 cbrt(double3 v) noexcept { return double3(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z)); }
static double3 sin(double3 v) noexcept { return double3(std::sin(v.x), std::sin(v.y), std::sin(v.z)); }
static double3 cos(double3 v) noexcept { return double3(std::cos(v.x), std::cos(v.y), std::cos(v.z)); }
static double3 tan(double3 v) noexcept { return double3(std::tan(v.x), std::tan(v.y), std::tan(v.z)); }
static double3 asin(double3 v) noexcept { return double3(std::asin(v.x), std::asin(v.y), std::asin(v.z)); }
static double3 acos(double3 v) noexcept { return double3(std::acos(v.x), std::acos(v.y), std::acos(v.z)); }
static double3 atan(double3 v) noexcept { return double3(std::atan(v.x), std::atan(v.y), std::atan(v.z)); }
static double3 atan(double3 a, double3 b) noexcept
{
	return double3(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z));
}
static double3 sinh(double3 v) noexcept { return double3(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z)); }
static double3 cosh(double3 v) noexcept { return double3(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z)); }
static double3 tanh(double3 v) noexcept { return double3(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z)); }
static double3 asinh(double3 v) noexcept { return double3(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z)); }
static double3 acosh(double3 v) noexcept { return double3(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z)); }
static double3 atanh(double3 v) noexcept { return double3(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z)); }

//**********************************************************************************************************************
static double4 mod(double4 a, double4 b) noexcept
{
	return double4(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z), std::fmod(a.w, b.w));
}
static double4 exp(double4 v) noexcept
{
	return double4(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}
static double4 exp2(double4 v) noexcept
{
	return double4(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z), std::exp2(v.w));
}
static double4 expm1(double4 v) noexcept
{
	return double4(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z), std::expm1(v.w));
}
static double4 log(double4 v) noexcept
{
	return double4(std::log(v.x), std::log(v.y), std::log(v.z), std::log(v.w));
}
static double4 log10(double4 v) noexcept
{
	return double4(std::log10(v.x), std::log10(v.y), std::log10(v.z), std::log10(v.w));
}
static double4 log2(double4 v) noexcept
{
	return double4(std::log2(v.x), std::log2(v.y), std::log2(v.z), std::log2(v.w));
}
static double4 log1p(double4 v) noexcept
{
	return double4(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z), std::log1p(v.w));
}
static double4 cbrt(double4 v) noexcept
{
	return double4(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z), std::cbrt(v.w));
}
static double4 sin(double4 v) noexcept
{
	return double4(std::sin(v.x), std::sin(v.y), std::sin(v.z), std::sin(v.w));
}
static double4 cos(double4 v) noexcept
{
	return double4(std::cos(v.x), std::cos(v.y), std::cos(v.z), std::cos(v.w));
}
static double4 tan(double4 v) noexcept
{
	return double4(std::tan(v.x), std::tan(v.y), std::tan(v.z), std::tan(v.w));
}
static double4 asin(double4 v) noexcept
{
	return double4(std::asin(v.x), std::asin(v.y), std::asin(v.z), std::asin(v.w));
}
static double4 acos(double4 v) noexcept
{
	return double4(std::acos(v.x), std::acos(v.y), std::acos(v.z), std::acos(v.w));
}
static double4 atan(double4 v) noexcept
{
	return double4(std::atan(v.x), std::atan(v.y), std::atan(v.z), std::atan(v.w));
}
static double4 atan(double4 a, double4 b) noexcept
{
	return double4(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z), std::atan2(a.w, b.w));
}
static double4 sinh(double4 v) noexcept
{
	return double4(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z), std::sinh(v.w));
}
static double4 cosh(double4 v) noexcept
{
	return double4(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z), std::cosh(v.w));
}
static double4 tanh(double4 v) noexcept
{
	return double4(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z), std::tanh(v.w));
}
static double4 asinh(double4 v) noexcept
{
	return double4(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z), std::asinh(v.w));
}
static double4 acosh(double4 v) noexcept
{
	return double4(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z), std::acosh(v.w));
}
static double4 atanh(double4 v) noexcept
{
	return double4(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z), std::atanh(v.w));
}

} // namespace math