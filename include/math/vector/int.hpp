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
 * @brief Common signed integer 32 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/uint.hpp"

namespace math
{

/**
 * @brief A 2-component vector of 32-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] int2
{
	int32 x; /**< First vector component. */
	int32 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 32-bit signed integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit int2(int32 xy = 0) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 32-bit signed integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr int2(int32 x, int32 y) noexcept : x(x), y(y) { }

	constexpr int2(uint2 xy) noexcept : x((int32)xy.x), y((int32)xy.y) { }
	constexpr int2(short2 xy) noexcept : x((int32)xy.x), y((int32)xy.y) { }
	constexpr int2(ushort2 xy) noexcept : x((int32)xy.x), y((int32)xy.y) { }
	constexpr int2(sbyte2 xy) noexcept : x((int32)xy.x), y((int32)xy.y) { }
	constexpr int2(byte2 xy) noexcept : x((int32)xy.x), y((int32)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int32& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((int32*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int32 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((int32*)this)[i];
	}

	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr int2 operator+(int2 v) const noexcept { return int2(x + v.x, y + v.y); }
	constexpr int2 operator-(int2 v) const noexcept { return int2(x - v.x, y - v.y); }
	constexpr int2 operator*(int2 v) const noexcept { return int2(x * v.x, y * v.y); }
	constexpr int2 operator/(int2 v) const noexcept { return int2(x / v.x, y / v.y); }
	constexpr int2 operator%(int2 v) const noexcept { return int2(x % v.x, y % v.y); }
	constexpr int2 operator&(int2 v) const noexcept { return int2(x & v.x, y & v.y); }
	constexpr int2 operator|(int2 v) const noexcept { return int2(x | v.x, y | v.y); }
	constexpr int2 operator^(int2 v) const noexcept { return int2(x ^ v.x, y ^ v.y); }
	constexpr int2 operator>>(int2 v) const noexcept { return int2(x >> v.x, y >> v.y); }
	constexpr int2 operator<<(int2 v) const noexcept { return int2(x << v.x, y << v.y); }
	constexpr int2 operator+(int32 n) const noexcept { return int2(x + n, y + n); }
	constexpr int2 operator-(int32 n) const noexcept { return int2(x - n, y - n); }
	constexpr int2 operator*(int32 n) const noexcept { return int2(x * n, y * n); }
	constexpr int2 operator/(int32 n) const noexcept { return int2(x / n, y / n); }
	constexpr int2 operator%(int32 n) const noexcept { return int2(x % n, y % n); }
	constexpr int2 operator&(int32 n) const noexcept { return int2(x & n, y & n); }
	constexpr int2 operator|(int32 n) const noexcept { return int2(x | n, y | n); }
	constexpr int2 operator^(int32 n) const noexcept { return int2(x ^ n, y ^ n); }
	constexpr int2 operator>>(int32 n) const noexcept { return int2(x >> n, y >> n); }
	constexpr int2 operator<<(int32 n) const noexcept { return int2(x << n, y << n); }
	constexpr int2 operator-() const noexcept { return int2(-x, -y); }
	constexpr int2 operator!() const noexcept { return int2(!x, !y); }
	constexpr int2 operator~() const noexcept { return int2(~x, ~y); }
	int2& operator+=(int2 v) noexcept { x += v.x; y += v.y; return *this; }
	int2& operator-=(int2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	int2& operator*=(int2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	int2& operator/=(int2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	int2& operator%=(int2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	int2& operator&=(int2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	int2& operator|=(int2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	int2& operator^=(int2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	int2& operator>>=(int2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	int2& operator<<=(int2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	int2& operator+=(int32 n) noexcept { x += n; y += n; return *this; }
	int2& operator-=(int32 n) noexcept { x -= n; y -= n; return *this; }
	int2& operator*=(int32 n) noexcept { x *= n; y *= n; return *this; }
	int2& operator/=(int32 n) noexcept { x /= n; y /= n; return *this; }
	int2& operator%=(int32 n) noexcept { x %= n; y %= n; return *this; }
	int2& operator&=(int32 n) noexcept { x &= n; y &= n; return *this; }
	int2& operator|=(int32 n) noexcept { x |= n; y |= n; return *this; }
	int2& operator^=(int32 n) noexcept { x ^= n; y ^= n; return *this; }
	int2& operator>>=(int32 n) noexcept { x >>= n; y >>= n; return *this; }
	int2& operator<<=(int32 n) noexcept { x <<= n; y <<= n; return *this; }
	int2& operator=(int32 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(int2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(int2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr uint2 operator<(int2 v) const noexcept
	{
		return uint2(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator>(int2 v) const noexcept
	{
		return uint2(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator<=(int2 v) const noexcept
	{
		return uint2(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0);
	}
	constexpr uint2 operator>=(int2 v) const noexcept
	{
		return uint2(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0);
	}
	constexpr bool operator==(int32 n) const noexcept { return *this == int2(n); }
	constexpr bool operator!=(int32 n) const noexcept { return *this != int2(n); }
	constexpr uint2 operator<(int32 n) const noexcept { return *this < int2(n); }
	constexpr uint2 operator>(int32 n) const noexcept { return *this > int2(n); }
	constexpr uint2 operator<=(int32 n) const noexcept { return *this <= int2(n); }
	constexpr uint2 operator>=(int32 n) const noexcept { return *this >= int2(n); }

	static const int2 zero, one, minusOne, min, max, left, right, bottom, top;
};

inline const int2 int2::zero = int2(0);
inline const int2 int2::one = int2(1);
inline const int2 int2::minusOne = int2(-1);
inline const int2 int2::min = int2(INT32_MIN);
inline const int2 int2::max = int2(INT32_MAX);
inline const int2 int2::left = int2(-1, 0);
inline const int2 int2::right = int2(1, 0);
inline const int2 int2::bottom = int2(0, -1);
inline const int2 int2::top = int2(0, 1);

/***********************************************************************************************************************
 * @brief A 3-component vector of 32-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] int3
{
	int32 x; /**< First vector component. */
	int32 y; /**< Second vector component. */
	int32 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 32-bit signed integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit int3(int32 xyz = 0) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 32-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr int3(int32 x, int32 y, int32 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 32-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr int3(int2 xy, int32 z) noexcept : x(xy.x), y(xy.y), z(x) { }
	/**
	 * @brief Creates a new 3-component vector of 32-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr int3(int32 x, int2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	constexpr int3(uint3 xyz) noexcept : x((int32)xyz.x), y((int32)xyz.y), z((int32)xyz.z) { }
	constexpr int3(short3 xyz) noexcept : x((int32)xyz.x), y((int32)xyz.y), z((int32)xyz.z) { }
	constexpr int3(ushort3 xyz) noexcept : x((int32)xyz.x), y((int32)xyz.y), z((int32)xyz.z) { }
	constexpr int3(sbyte3 xyz) noexcept : x((int32)xyz.x), y((int32)xyz.y), z((int32)xyz.z) { }
	constexpr int3(byte3 xyz) noexcept : x((int32)xyz.x), y((int32)xyz.y), z((int32)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int32& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((int32*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int32 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((int32*)this)[i];
	}

	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator int2() const noexcept { return int2(x, y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr int3 operator+(int3 v) const noexcept { return int3(x + v.x, y + v.y, z + v.z); }
	constexpr int3 operator-(int3 v) const noexcept { return int3(x - v.x, y - v.y, z - v.z); }
	constexpr int3 operator*(int3 v) const noexcept { return int3(x * v.x, y * v.y, z * v.z); }
	constexpr int3 operator/(int3 v) const noexcept { return int3(x / v.x, y / v.y, z / v.z); }
	constexpr int3 operator%(int3 v) const noexcept { return int3(x % v.x, y % v.y, z % v.z); }
	constexpr int3 operator&(int3 v) const noexcept { return int3(x & v.x, y & v.y, z & v.z); }
	constexpr int3 operator|(int3 v) const noexcept { return int3(x | v.x, y | v.y, z | v.z); }
	constexpr int3 operator^(int3 v) const noexcept { return int3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr int3 operator>>(int3 v) const noexcept { return int3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr int3 operator<<(int3 v) const noexcept { return int3(x << v.x, y << v.y, z << v.z); }
	constexpr int3 operator+(int32 n) const noexcept { return int3(x + n, y + n, z + n); }
	constexpr int3 operator-(int32 n) const noexcept { return int3(x - n, y - n, z - n); }
	constexpr int3 operator*(int32 n) const noexcept { return int3(x * n, y * n, z * n); }
	constexpr int3 operator/(int32 n) const noexcept { return int3(x / n, y / n, z / n); }
	constexpr int3 operator%(int32 n) const noexcept { return int3(x % n, y % n, z % n); }
	constexpr int3 operator&(int32 n) const noexcept { return int3(x & n, y & n, z & n); }
	constexpr int3 operator|(int32 n) const noexcept { return int3(x | n, y | n, z | n); }
	constexpr int3 operator^(int32 n) const noexcept { return int3(x ^ n, y ^ n, z ^ n); }
	constexpr int3 operator>>(int32 n) const noexcept { return int3(x >> n, y >> n, z >> n); }
	constexpr int3 operator<<(int32 n) const noexcept { return int3(x << n, y << n, z << n); }
	constexpr int3 operator-() const noexcept { return int3(-x, -y, -z); }
	constexpr int3 operator!() const noexcept { return int3(!x, !y, !z); }
	constexpr int3 operator~() const noexcept { return int3(~x, ~y, ~z); }
	int3& operator+=(int3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	int3& operator-=(int3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	int3& operator*=(int3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	int3& operator/=(int3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	int3& operator%=(int3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	int3& operator&=(int3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	int3& operator|=(int3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	int3& operator^=(int3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	int3& operator>>=(int3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	int3& operator<<=(int3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	int3& operator+=(int32 n) noexcept { x += n; y += n; z += n; return *this; }
	int3& operator-=(int32 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	int3& operator*=(int32 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	int3& operator/=(int32 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	int3& operator%=(int32 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	int3& operator&=(int32 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	int3& operator|=(int32 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	int3& operator^=(int32 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	int3& operator>>=(int32 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	int3& operator<<=(int32 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	int3& operator=(int32 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(int3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(int3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr uint3 operator<(int3 v) const noexcept
	{
		return uint3(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0, z < v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator>(int3 v) const noexcept
	{
		return uint3(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0, z > v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator<=(int3 v) const noexcept
	{
		return uint3(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0, z <= v.z ? UINT32_MAX : 0);
	}
	constexpr uint3 operator>=(int3 v) const noexcept
	{
		return uint3(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0, z >= v.z ? UINT32_MAX : 0);
	}
	constexpr bool operator==(int32 n) const noexcept { return *this == int3(n); }
	constexpr bool operator!=(int32 n) const noexcept { return *this != int3(n); }
	constexpr uint3 operator<(int32 n) const noexcept { return *this < int3(n); }
	constexpr uint3 operator>(int32 n) const noexcept { return *this > int3(n); }
	constexpr uint3 operator<=(int32 n) const noexcept { return *this <= int3(n); }
	constexpr uint3 operator>=(int32 n) const noexcept { return *this >= int3(n); }

	static const int3 zero, one, minusOne, min, max, left, right, bottom, top, back, front;
};

inline const int3 int3::zero = int3(0);
inline const int3 int3::one = int3(1);
inline const int3 int3::minusOne = int3(-1);
inline const int3 int3::min = int3(INT32_MIN);
inline const int3 int3::max = int3(INT32_MAX);
inline const int3 int3::left = int3(-1, 0, 0);
inline const int3 int3::right = int3(1, 0, 0);
inline const int3 int3::bottom = int3(0, -1, 0);
inline const int3 int3::top = int3(0, 1, 0);
inline const int3 int3::back = int3(0, 0, -1);
inline const int3 int3::front = int3(0, 0, 1);

/***********************************************************************************************************************
 * @brief A 4-component vector of 32-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] int4
{
	int32 x; /**< First vector component. */
	int32 y; /**< Second vector component. */
	int32 z; /**< Third vector component. */
	int32 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit int4(int32 xyzw = 0) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr int4(int32 x, int32 y, int32 z, int32 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr int4(int2 xy, int32 z, int32 w) noexcept: x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr int4(int32 x, int2 yz, int32 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr int4(int32 x, int32 y, int2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr int4(int2 xy, int2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr int4(int3 xyz, int32 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 32-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector component value
	 */
	constexpr int4(int32 x, int3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	constexpr int4(uint4 xyzw) noexcept : x((int32)xyzw.x), y((int32)xyzw.y), z((int32)xyzw.z), w((int32)xyzw.w) { }
	constexpr int4(short4 xyzw) noexcept : x((int32)xyzw.x), y((int32)xyzw.y), z((int32)xyzw.z), w((int32)xyzw.w) { }
	constexpr int4(ushort4 xyzw) noexcept : x((int32)xyzw.x), y((int32)xyzw.y), z((int32)xyzw.z), w((int32)xyzw.w) { }
	constexpr int4(sbyte4 xyzw) noexcept : x((int32)xyzw.x), y((int32)xyzw.y), z((int32)xyzw.z), w((int32)xyzw.w) { }
	constexpr int4(byte4 xyzw) noexcept : x((int32)xyzw.x), y((int32)xyzw.y), z((int32)xyzw.z), w((int32)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int32& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((int32*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int32 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((int32*)this)[i];
	}

	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	constexpr explicit operator short4() const noexcept { return short4((int16)x, (int16)y, (int16)z, (int16)w); }
	constexpr explicit operator ushort4() const noexcept { return ushort4((uint16)x, (uint16)y, (uint16)z, (uint16)w); }
	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator int3() const noexcept { return int3(x, y, z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator int2() const noexcept { return int2(x, y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr int4 operator+(int4 v) const noexcept { return int4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr int4 operator-(int4 v) const noexcept { return int4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr int4 operator*(int4 v) const noexcept { return int4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr int4 operator/(int4 v) const noexcept { return int4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr int4 operator%(int4 v) const noexcept { return int4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr int4 operator&(int4 v) const noexcept { return int4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr int4 operator|(int4 v) const noexcept { return int4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr int4 operator^(int4 v) const noexcept { return int4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr int4 operator>>(int4 v) const noexcept { return int4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr int4 operator<<(int4 v) const noexcept { return int4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr int4 operator+(int32 n) const noexcept { return int4(x + n, y + n, z + n, w + n); }
	constexpr int4 operator-(int32 n) const noexcept { return int4(x - n, y - n, z - n, w - n); }
	constexpr int4 operator*(int32 n) const noexcept { return int4(x * n, y * n, z * n, w * n); }
	constexpr int4 operator/(int32 n) const noexcept { return int4(x / n, y / n, z / n, w / n); }
	constexpr int4 operator%(int32 n) const noexcept { return int4(x % n, y % n, z % n, w % n); }
	constexpr int4 operator&(int32 n) const noexcept { return int4(x & n, y & n, z & n, w & n); }
	constexpr int4 operator|(int32 n) const noexcept { return int4(x | n, y | n, z | n, w | n); }
	constexpr int4 operator^(int32 n) const noexcept { return int4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr int4 operator>>(int32 n) const noexcept { return int4(x >> n, y >> n, z >> n, w >> n); }
	constexpr int4 operator<<(int32 n) const noexcept { return int4(x << n, y << n, z << n, w << n); }
	constexpr int4 operator-() const noexcept { return int4(-x, -y, -z, -w); }
	constexpr int4 operator!() const noexcept { return int4(!x, !y, !z, !w); }
	constexpr int4 operator~() const noexcept { return int4(~x, ~y, ~z, ~w); }
	int4& operator+=(int4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	int4& operator-=(int4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	int4& operator*=(int4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	int4& operator/=(int4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	int4& operator%=(int4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	int4& operator&=(int4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	int4& operator|=(int4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	int4& operator^=(int4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	int4& operator>>=(int4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	int4& operator<<=(int4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	int4& operator+=(int32 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	int4& operator-=(int32 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	int4& operator*=(int32 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	int4& operator/=(int32 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	int4& operator%=(int32 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	int4& operator&=(int32 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	int4& operator|=(int32 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	int4& operator^=(int32 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	int4& operator>>=(int32 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	int4& operator<<=(int32 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	int4& operator=(int32 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(int4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(int4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr uint4 operator<(int4 v) const noexcept
	{
		return uint4(x < v.x ? UINT32_MAX : 0, y < v.y ? UINT32_MAX : 0, 
			z < v.z ? UINT32_MAX : 0, w < v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator>(int4 v) const noexcept
	{
		return uint4(x > v.x ? UINT32_MAX : 0, y > v.y ? UINT32_MAX : 0, 
			z > v.z ? UINT32_MAX : 0, w > v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator<=(int4 v) const noexcept
	{
		return uint4(x <= v.x ? UINT32_MAX : 0, y <= v.y ? UINT32_MAX : 0, 
			z <= v.z ? UINT32_MAX : 0, w <= v.w ? UINT32_MAX : 0);
	}
	constexpr uint4 operator>=(int4 v) const noexcept
	{
		return uint4(x >= v.x ? UINT32_MAX : 0, y >= v.y ? UINT32_MAX : 0, 
			z >= v.z ? UINT32_MAX : 0, w >= v.w ? UINT32_MAX : 0);
	}
	constexpr bool operator==(int32 n) const noexcept { return *this == int4(n); }
	constexpr bool operator!=(int32 n) const noexcept { return *this != int4(n); }
	constexpr uint4 operator<(int32 n) const noexcept { return *this < int4(n); }
	constexpr uint4 operator>(int32 n) const noexcept { return *this > int4(n); }
	constexpr uint4 operator<=(int32 n) const noexcept { return *this <= int4(n); }
	constexpr uint4 operator>=(int32 n) const noexcept { return *this >= int4(n); }

	static const int4 zero, one, minusOne, min, max;
};

inline const int4 int4::zero = int4(0);
inline const int4 int4::one = int4(1);
inline const int4 int4::minusOne = int4(-1);
inline const int4 int4::min = int4(INT32_MIN);
inline const int4 int4::max = int4(INT32_MAX);

//**********************************************************************************************************************
static constexpr int2 operator+(int32 n, int2 v) noexcept { return int2(n) + v; }
static constexpr int2 operator-(int32 n, int2 v) noexcept { return int2(n) - v; }
static constexpr int2 operator*(int32 n, int2 v) noexcept { return int2(n) * v; }
static constexpr int2 operator/(int32 n, int2 v) noexcept { return int2(n) / v; }
static constexpr int2 operator%(int32 n, int2 v) noexcept { return int2(n) % v; }
static constexpr int2 operator&(int32 n, int2 v) noexcept { return int2(n) & v; }
static constexpr int2 operator|(int32 n, int2 v) noexcept { return int2(n) | v; }
static constexpr int2 operator^(int32 n, int2 v) noexcept { return int2(n) ^ v; }
static constexpr int2 operator>>(int32 n, int2 v) noexcept { return int2(n) >> v; }
static constexpr int2 operator<<(int32 n, int2 v) noexcept { return int2(n) << v; }
static constexpr bool operator==(int32 n, int2 v) noexcept { return int2(n) == v; }
static constexpr bool operator!=(int32 n, int2 v) noexcept { return int2(n) != v; }
static constexpr uint2 operator<(int32 n, int2 v) noexcept { return int2(n) < v; }
static constexpr uint2 operator>(int32 n, int2 v) noexcept { return int2(n) > v; }
static constexpr uint2 operator<=(int32 n, int2 v) noexcept { return int2(n) <= v; }
static constexpr uint2 operator>=(int32 n, int2 v) noexcept { return int2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(int2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint2 equal(int2 a, int2 b) noexcept
{
	return uint2(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint2 notEqual(int2 a, int2 b) noexcept
{
	return uint2(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(int2 a, int2 b) noexcept { return *((const int64*)&a) < *((const int64*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr int2 select(uint2 c, int2 t, int2 f) noexcept
{
	return int2(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr int2 min(int2 a, int2 b) noexcept { return int2(std::min(a.x, b.x), std::min(a.y, b.y)); }
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr int2 max(int2 a, int2 b) noexcept { return int2(std::max(a.x, b.x), std::max(a.y, b.y)); }
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr int2 min(int2 a, int2 b, int2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr int2 max(int2 a, int2 b, int2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr int2 clamp(int2 v, int2 min, int2 max) noexcept
{
	return int2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr int3 operator+(int32 n, int3 v) noexcept { return int3(n) + v; }
static constexpr int3 operator-(int32 n, int3 v) noexcept { return int3(n) - v; }
static constexpr int3 operator*(int32 n, int3 v) noexcept { return int3(n) * v; }
static constexpr int3 operator/(int32 n, int3 v) noexcept { return int3(n) / v; }
static constexpr int3 operator%(int32 n, int3 v) noexcept { return int3(n) % v; }
static constexpr int3 operator&(int32 n, int3 v) noexcept { return int3(n) & v; }
static constexpr int3 operator|(int32 n, int3 v) noexcept { return int3(n) | v; }
static constexpr int3 operator^(int32 n, int3 v) noexcept { return int3(n) ^ v; }
static constexpr int3 operator>>(int32 n, int3 v) noexcept { return int3(n) >> v; }
static constexpr int3 operator<<(int32 n, int3 v) noexcept { return int3(n) << v; }
static constexpr bool operator==(int32 n, int3 v) noexcept { return int3(n) == v; }
static constexpr bool operator!=(int32 n, int3 v) noexcept { return int3(n) != v; }
static constexpr uint3 operator<(int32 n, int3 v) noexcept { return int3(n) < v; }
static constexpr uint3 operator>(int32 n, int3 v) noexcept { return int3(n) > v; }
static constexpr uint3 operator<=(int32 n, int3 v) noexcept { return int3(n) <= v; }
static constexpr uint3 operator>=(int32 n, int3 v) noexcept { return int3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(int3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint3 equal(int3 a, int3 b) noexcept
{
	return uint3(a.x == b.x ? UINT32_MAX : 0, a.y == b.y ? UINT32_MAX : 0, a.z == b.z ? UINT32_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint3 notEqual(int3 a, int3 b) noexcept
{
	return uint3(a.x != b.x ? UINT32_MAX : 0, a.y != b.y ? UINT32_MAX : 0, a.z != b.z ? UINT32_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const int3& a, const int3& b) noexcept { return memcmp(&a, &b, sizeof(int3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr int3 select(uint3 c, int3 t, int3 f) noexcept
{
	return int3(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y, c.z & 0x80000000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr int3 min(int3 a, int3 b) noexcept
{
	return int3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr int3 max(int3 a, int3 b) noexcept
{
	return int3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr int3 min(int3 a, int3 b, int3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr int3 max(int3 a, int3 b, int3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr int3 clamp(int3 v, int3 min, int3 max) noexcept
{
	return int3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr int4 operator+(int32 n, int4 v) noexcept { return int4(n) + v; }
static constexpr int4 operator-(int32 n, int4 v) noexcept { return int4(n) - v; }
static constexpr int4 operator*(int32 n, int4 v) noexcept { return int4(n) * v; }
static constexpr int4 operator/(int32 n, int4 v) noexcept { return int4(n) / v; }
static constexpr int4 operator%(int32 n, int4 v) noexcept { return int4(n) % v; }
static constexpr int4 operator&(int32 n, int4 v) noexcept { return int4(n) & v; }
static constexpr int4 operator|(int32 n, int4 v) noexcept { return int4(n) | v; }
static constexpr int4 operator^(int32 n, int4 v) noexcept { return int4(n) ^ v; }
static constexpr int4 operator>>(int32 n, int4 v) noexcept { return int4(n) >> v; }
static constexpr int4 operator<<(int32 n, int4 v) noexcept { return int4(n) << v; }
static constexpr bool operator==(int32 n, int4 v) noexcept { return int4(n) == v; }
static constexpr bool operator!=(int32 n, int4 v) noexcept { return int4(n) != v; }
static constexpr uint4 operator<(int32 n, int4 v) noexcept { return int4(n) < v; }
static constexpr uint4 operator>(int32 n, int4 v) noexcept { return int4(n) > v; }
static constexpr uint4 operator<=(int32 n, int4 v) noexcept { return int4(n) <= v; }
static constexpr uint4 operator>=(int32 n, int4 v) noexcept { return int4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(int4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static uint4 equal(int4 a, int4 b) noexcept
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
static uint4 notEqual(int4 a, int4 b) noexcept
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
static bool isBinaryLess(const int4& a, const int4& b) noexcept { return memcmp(&a, &b, sizeof(int4)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr int4 select(uint4 c, int4 t, int4 f) noexcept
{
	return int4(c.x & 0x80000000u ? t.x : f.x, c.y & 0x80000000u ? t.y : f.y, 
		c.z & 0x80000000u ? t.z : f.z, c.w & 0x80000000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr int4 min(int4 a, int4 b) noexcept
{
	return int4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr int4 max(int4 a, int4 b) noexcept
{
	return int4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr int4 min(int4 a, int4 b, int4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr int4 max(int4 a, int4 b, int4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr int4 clamp(int4 v, int4 min, int4 max) noexcept
{
	return int4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math