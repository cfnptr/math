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
 * @brief Common signed integer 64 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/int.hpp"
#include "math/vector/ulong.hpp"

namespace math
{

/**
 * @brief A 2-component vector of 64-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] long2
{
	int64 x; /**< First vector component. */
	int64 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit long2(int64 xy = 0) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr long2(int64 x, int64 y) noexcept : x(x), y(y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(ulong2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(int2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(uint2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(short2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(ushort2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(sbyte2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit signed integer values.
	 * @param xy first and second vector component value
	 */
	constexpr long2(byte2 xy) noexcept : x((int64)xy.x), y((int64)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int64& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((int64*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int64 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((int64*)this)[i];
	}

	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr long2 operator+(long2 v) const noexcept { return long2(x + v.x, y + v.y); }
	constexpr long2 operator-(long2 v) const noexcept { return long2(x - v.x, y - v.y); }
	constexpr long2 operator*(long2 v) const noexcept { return long2(x * v.x, y * v.y); }
	constexpr long2 operator/(long2 v) const noexcept { return long2(x / v.x, y / v.y); }
	constexpr long2 operator%(long2 v) const noexcept { return long2(x % v.x, y % v.y); }
	constexpr long2 operator&(long2 v) const noexcept { return long2(x & v.x, y & v.y); }
	constexpr long2 operator|(long2 v) const noexcept { return long2(x | v.x, y | v.y); }
	constexpr long2 operator^(long2 v) const noexcept { return long2(x ^ v.x, y ^ v.y); }
	constexpr long2 operator>>(long2 v) const noexcept { return long2(x >> v.x, y >> v.y); }
	constexpr long2 operator<<(long2 v) const noexcept { return long2(x << v.x, y << v.y); }
	constexpr long2 operator+(int64 n) const noexcept { return long2(x + n, y + n); }
	constexpr long2 operator-(int64 n) const noexcept { return long2(x - n, y - n); }
	constexpr long2 operator*(int64 n) const noexcept { return long2(x * n, y * n); }
	constexpr long2 operator/(int64 n) const noexcept { return long2(x / n, y / n); }
	constexpr long2 operator%(int64 n) const noexcept { return long2(x % n, y % n); }
	constexpr long2 operator&(int64 n) const noexcept { return long2(x & n, y & n); }
	constexpr long2 operator|(int64 n) const noexcept { return long2(x | n, y | n); }
	constexpr long2 operator^(int64 n) const noexcept { return long2(x ^ n, y ^ n); }
	constexpr long2 operator>>(int64 n) const noexcept { return long2(x >> n, y >> n); }
	constexpr long2 operator<<(int64 n) const noexcept { return long2(x << n, y << n); }
	constexpr long2 operator-() const noexcept { return long2(-x, -y); }
	constexpr long2 operator!() const noexcept { return long2(!x, !y); }
	constexpr long2 operator~() const noexcept { return long2(~x, ~y); }
	long2& operator+=(long2 v) noexcept { x += v.x; y += v.y; return *this; }
	long2& operator-=(long2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	long2& operator*=(long2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	long2& operator/=(long2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	long2& operator%=(long2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	long2& operator&=(long2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	long2& operator|=(long2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	long2& operator^=(long2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	long2& operator>>=(long2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	long2& operator<<=(long2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	long2& operator+=(int64 n) noexcept { x += n; y += n; return *this; }
	long2& operator-=(int64 n) noexcept { x -= n; y -= n; return *this; }
	long2& operator*=(int64 n) noexcept { x *= n; y *= n; return *this; }
	long2& operator/=(int64 n) noexcept { x /= n; y /= n; return *this; }
	long2& operator%=(int64 n) noexcept { x %= n; y %= n; return *this; }
	long2& operator&=(int64 n) noexcept { x &= n; y &= n; return *this; }
	long2& operator|=(int64 n) noexcept { x |= n; y |= n; return *this; }
	long2& operator^=(int64 n) noexcept { x ^= n; y ^= n; return *this; }
	long2& operator>>=(int64 n) noexcept { x >>= n; y >>= n; return *this; }
	long2& operator<<=(int64 n) noexcept { x <<= n; y <<= n; return *this; }
	long2& operator=(int64 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(long2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(long2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr ulong2 operator<(long2 v) const noexcept
	{
		return ulong2(x < v.x ? UINT64_MAX : 0, y < v.y ? UINT64_MAX : 0);
	}
	constexpr ulong2 operator>(long2 v) const noexcept
	{
		return ulong2(x > v.x ? UINT64_MAX : 0, y > v.y ? UINT64_MAX : 0);
	}
	constexpr ulong2 operator<=(long2 v) const noexcept
	{
		return ulong2(x <= v.x ? UINT64_MAX : 0, y <= v.y ? UINT64_MAX : 0);
	}
	constexpr ulong2 operator>=(long2 v) const noexcept
	{
		return ulong2(x >= v.x ? UINT64_MAX : 0, y >= v.y ? UINT64_MAX : 0);
	}
	constexpr bool operator==(int64 n) const noexcept { return *this == long2(n); }
	constexpr bool operator!=(int64 n) const noexcept { return *this != long2(n); }
	constexpr ulong2 operator<(int64 n) const noexcept { return *this < long2(n); }
	constexpr ulong2 operator>(int64 n) const noexcept { return *this > long2(n); }
	constexpr ulong2 operator<=(int64 n) const noexcept { return *this <= long2(n); }
	constexpr ulong2 operator>=(int64 n) const noexcept { return *this >= long2(n); }

	static const long2 zero, one, minusOne, min, max, left, right, bottom, top;
};

inline const long2 long2::zero = long2(0);
inline const long2 long2::one = long2(1);
inline const long2 long2::minusOne = long2(-1);
inline const long2 long2::min = long2(INT64_MIN);
inline const long2 long2::max = long2(INT64_MAX);
inline const long2 long2::left = long2(-1, 0);
inline const long2 long2::right = long2(1, 0);
inline const long2 long2::bottom = long2(0, -1);
inline const long2 long2::top = long2(0, 1);

/***********************************************************************************************************************
 * @brief A 3-component vector of 64-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] long3
{
	int64 x; /**< First vector component. */
	int64 y; /**< Second vector component. */
	int64 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit long3(int64 xyz = 0) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr long3(int64 x, int64 y, int64 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr long3(long2 xy, int64 z) noexcept : x(xy.x), y(xy.y), z(x) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr long3(int64 x, long2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(ulong3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(int3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(uint3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(short3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(ushort3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(sbyte3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit signed integer values.
	 * @param xyz first, second and third vector component value
	 */
	constexpr long3(byte3 xyz) noexcept : x((int64)xyz.x), y((int64)xyz.y), z((int64)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int64& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((int64*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int64 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((int64*)this)[i];
	}

	constexpr explicit operator ulong3() const noexcept { return ulong3((uint64)x, (uint64)y, (uint64)z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator long2() const noexcept { return long2(x, y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr long3 operator+(long3 v) const noexcept { return long3(x + v.x, y + v.y, z + v.z); }
	constexpr long3 operator-(long3 v) const noexcept { return long3(x - v.x, y - v.y, z - v.z); }
	constexpr long3 operator*(long3 v) const noexcept { return long3(x * v.x, y * v.y, z * v.z); }
	constexpr long3 operator/(long3 v) const noexcept { return long3(x / v.x, y / v.y, z / v.z); }
	constexpr long3 operator%(long3 v) const noexcept { return long3(x % v.x, y % v.y, z % v.z); }
	constexpr long3 operator&(long3 v) const noexcept { return long3(x & v.x, y & v.y, z & v.z); }
	constexpr long3 operator|(long3 v) const noexcept { return long3(x | v.x, y | v.y, z | v.z); }
	constexpr long3 operator^(long3 v) const noexcept { return long3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr long3 operator>>(long3 v) const noexcept { return long3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr long3 operator<<(long3 v) const noexcept { return long3(x << v.x, y << v.y, z << v.z); }
	constexpr long3 operator+(int64 n) const noexcept { return long3(x + n, y + n, z + n); }
	constexpr long3 operator-(int64 n) const noexcept { return long3(x - n, y - n, z - n); }
	constexpr long3 operator*(int64 n) const noexcept { return long3(x * n, y * n, z * n); }
	constexpr long3 operator/(int64 n) const noexcept { return long3(x / n, y / n, z / n); }
	constexpr long3 operator%(int64 n) const noexcept { return long3(x % n, y % n, z % n); }
	constexpr long3 operator&(int64 n) const noexcept { return long3(x & n, y & n, z & n); }
	constexpr long3 operator|(int64 n) const noexcept { return long3(x | n, y | n, z | n); }
	constexpr long3 operator^(int64 n) const noexcept { return long3(x ^ n, y ^ n, z ^ n); }
	constexpr long3 operator>>(int64 n) const noexcept { return long3(x >> n, y >> n, z >> n); }
	constexpr long3 operator<<(int64 n) const noexcept { return long3(x << n, y << n, z << n); }
	constexpr long3 operator-() const noexcept { return long3(-x, -y, -z); }
	constexpr long3 operator!() const noexcept { return long3(!x, !y, !z); }
	constexpr long3 operator~() const noexcept { return long3(~x, ~y, ~z); }
	long3& operator+=(long3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	long3& operator-=(long3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	long3& operator*=(long3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	long3& operator/=(long3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	long3& operator%=(long3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	long3& operator&=(long3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	long3& operator|=(long3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	long3& operator^=(long3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	long3& operator>>=(long3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	long3& operator<<=(long3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	long3& operator+=(int64 n) noexcept { x += n; y += n; z += n; return *this; }
	long3& operator-=(int64 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	long3& operator*=(int64 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	long3& operator/=(int64 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	long3& operator%=(int64 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	long3& operator&=(int64 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	long3& operator|=(int64 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	long3& operator^=(int64 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	long3& operator>>=(int64 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	long3& operator<<=(int64 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	long3& operator=(int64 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(long3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(long3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr ulong3 operator<(long3 v) const noexcept
	{
		return ulong3(x < v.x ? UINT64_MAX : 0, y < v.y ? UINT64_MAX : 0, z < v.z ? UINT64_MAX : 0);
	}
	constexpr ulong3 operator>(long3 v) const noexcept
	{
		return ulong3(x > v.x ? UINT64_MAX : 0, y > v.y ? UINT64_MAX : 0, z > v.z ? UINT64_MAX : 0);
	}
	constexpr ulong3 operator<=(long3 v) const noexcept
	{
		return ulong3(x <= v.x ? UINT64_MAX : 0, y <= v.y ? UINT64_MAX : 0, z <= v.z ? UINT64_MAX : 0);
	}
	constexpr ulong3 operator>=(long3 v) const noexcept
	{
		return ulong3(x >= v.x ? UINT64_MAX : 0, y >= v.y ? UINT64_MAX : 0, z >= v.z ? UINT64_MAX : 0);
	}
	constexpr bool operator==(int64 n) const noexcept { return *this == long3(n); }
	constexpr bool operator!=(int64 n) const noexcept { return *this != long3(n); }
	constexpr ulong3 operator<(int64 n) const noexcept { return *this < long3(n); }
	constexpr ulong3 operator>(int64 n) const noexcept { return *this > long3(n); }
	constexpr ulong3 operator<=(int64 n) const noexcept { return *this <= long3(n); }
	constexpr ulong3 operator>=(int64 n) const noexcept { return *this >= long3(n); }

	static const long3 zero, one, minusOne, min, max, left, right, bottom, top, back, front;
};

inline const long3 long3::zero = long3(0);
inline const long3 long3::one = long3(1);
inline const long3 long3::minusOne = long3(-1);
inline const long3 long3::min = long3(INT64_MIN);
inline const long3 long3::max = long3(INT64_MAX);
inline const long3 long3::left = long3(-1, 0, 0);
inline const long3 long3::right = long3(1, 0, 0);
inline const long3 long3::bottom = long3(0, -1, 0);
inline const long3 long3::top = long3(0, 1, 0);
inline const long3 long3::back = long3(0, 0, -1);
inline const long3 long3::front = long3(0, 0, 1);

/***********************************************************************************************************************
 * @brief A 4-component vector of 64-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] long4
{
	int64 x; /**< First vector component. */
	int64 y; /**< Second vector component. */
	int64 z; /**< Third vector component. */
	int64 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit long4(int64 xyzw = 0) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr long4(int64 x, int64 y, int64 z, int64 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr long4(long2 xy, int64 z, int64 w) noexcept: x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr long4(int64 x, long2 yz, int64 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr long4(int64 x, int64 y, long2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr long4(long2 xy, long2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr long4(long3 xyz, int64 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector component value
	 */
	constexpr long4(int64 x, long3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(ulong4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(int4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(uint4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(short4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(ushort4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(sbyte4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit signed integer values.
	 * @param xyzw first, second, third and fourth vector component value
	 */
	constexpr long4(byte4 xyzw) noexcept : x((int64)xyzw.x), y((int64)xyzw.y), z((int64)xyzw.z), w((int64)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int64& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((int64*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int64 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((int64*)this)[i];
	}

	constexpr explicit operator ulong4() const noexcept { return ulong4((uint64)x, (uint64)y, (uint64)z, (uint64)w); }
	constexpr explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	constexpr explicit operator short4() const noexcept { return short4((int16)x, (int16)y, (int16)z, (int16)w); }
	constexpr explicit operator ushort4() const noexcept { return ushort4((uint16)x, (uint16)y, (uint16)z, (uint16)w); }
	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator long3() const noexcept { return long3(x, y, z); }
	constexpr explicit operator ulong3() const noexcept { return ulong3((uint64)x, (uint64)y, (uint64)z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator long2() const noexcept { return long2(x, y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr long4 operator+(long4 v) const noexcept { return long4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr long4 operator-(long4 v) const noexcept { return long4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr long4 operator*(long4 v) const noexcept { return long4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr long4 operator/(long4 v) const noexcept { return long4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr long4 operator%(long4 v) const noexcept { return long4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr long4 operator&(long4 v) const noexcept { return long4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr long4 operator|(long4 v) const noexcept { return long4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr long4 operator^(long4 v) const noexcept { return long4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr long4 operator>>(long4 v) const noexcept { return long4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr long4 operator<<(long4 v) const noexcept { return long4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr long4 operator+(int64 n) const noexcept { return long4(x + n, y + n, z + n, w + n); }
	constexpr long4 operator-(int64 n) const noexcept { return long4(x - n, y - n, z - n, w - n); }
	constexpr long4 operator*(int64 n) const noexcept { return long4(x * n, y * n, z * n, w * n); }
	constexpr long4 operator/(int64 n) const noexcept { return long4(x / n, y / n, z / n, w / n); }
	constexpr long4 operator%(int64 n) const noexcept { return long4(x % n, y % n, z % n, w % n); }
	constexpr long4 operator&(int64 n) const noexcept { return long4(x & n, y & n, z & n, w & n); }
	constexpr long4 operator|(int64 n) const noexcept { return long4(x | n, y | n, z | n, w | n); }
	constexpr long4 operator^(int64 n) const noexcept { return long4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr long4 operator>>(int64 n) const noexcept { return long4(x >> n, y >> n, z >> n, w >> n); }
	constexpr long4 operator<<(int64 n) const noexcept { return long4(x << n, y << n, z << n, w << n); }
	constexpr long4 operator-() const noexcept { return long4(-x, -y, -z, -w); }
	constexpr long4 operator!() const noexcept { return long4(!x, !y, !z, !w); }
	constexpr long4 operator~() const noexcept { return long4(~x, ~y, ~z, ~w); }
	long4& operator+=(long4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	long4& operator-=(long4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	long4& operator*=(long4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	long4& operator/=(long4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	long4& operator%=(long4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	long4& operator&=(long4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	long4& operator|=(long4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	long4& operator^=(long4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	long4& operator>>=(long4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	long4& operator<<=(long4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	long4& operator+=(int64 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	long4& operator-=(int64 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	long4& operator*=(int64 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	long4& operator/=(int64 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	long4& operator%=(int64 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	long4& operator&=(int64 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	long4& operator|=(int64 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	long4& operator^=(int64 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	long4& operator>>=(int64 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	long4& operator<<=(int64 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	long4& operator=(int64 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(long4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(long4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr ulong4 operator<(long4 v) const noexcept
	{
		return ulong4(x < v.x ? UINT64_MAX : 0, y < v.y ? UINT64_MAX : 0, 
			z < v.z ? UINT64_MAX : 0, w < v.w ? UINT64_MAX : 0);
	}
	constexpr ulong4 operator>(long4 v) const noexcept
	{
		return ulong4(x > v.x ? UINT64_MAX : 0, y > v.y ? UINT64_MAX : 0, 
			z > v.z ? UINT64_MAX : 0, w > v.w ? UINT64_MAX : 0);
	}
	constexpr ulong4 operator<=(long4 v) const noexcept
	{
		return ulong4(x <= v.x ? UINT64_MAX : 0, y <= v.y ? UINT64_MAX : 0, 
			z <= v.z ? UINT64_MAX : 0, w <= v.w ? UINT64_MAX : 0);
	}
	constexpr ulong4 operator>=(long4 v) const noexcept
	{
		return ulong4(x >= v.x ? UINT64_MAX : 0, y >= v.y ? UINT64_MAX : 0, 
			z >= v.z ? UINT64_MAX : 0, w >= v.w ? UINT64_MAX : 0);
	}
	constexpr bool operator==(int64 n) const noexcept { return *this == long4(n); }
	constexpr bool operator!=(int64 n) const noexcept { return *this != long4(n); }
	constexpr ulong4 operator<(int64 n) const noexcept { return *this < long4(n); }
	constexpr ulong4 operator>(int64 n) const noexcept { return *this > long4(n); }
	constexpr ulong4 operator<=(int64 n) const noexcept { return *this <= long4(n); }
	constexpr ulong4 operator>=(int64 n) const noexcept { return *this >= long4(n); }

	static const long4 zero, one, minusOne, min, max;
};

inline const long4 long4::zero = long4(0);
inline const long4 long4::one = long4(1);
inline const long4 long4::minusOne = long4(-1);
inline const long4 long4::min = long4(INT64_MIN);
inline const long4 long4::max = long4(INT64_MAX);

//**********************************************************************************************************************
static constexpr long2 operator+(int64 n, long2 v) noexcept { return long2(n) + v; }
static constexpr long2 operator-(int64 n, long2 v) noexcept { return long2(n) - v; }
static constexpr long2 operator*(int64 n, long2 v) noexcept { return long2(n) * v; }
static constexpr long2 operator/(int64 n, long2 v) noexcept { return long2(n) / v; }
static constexpr long2 operator%(int64 n, long2 v) noexcept { return long2(n) % v; }
static constexpr long2 operator&(int64 n, long2 v) noexcept { return long2(n) & v; }
static constexpr long2 operator|(int64 n, long2 v) noexcept { return long2(n) | v; }
static constexpr long2 operator^(int64 n, long2 v) noexcept { return long2(n) ^ v; }
static constexpr long2 operator>>(int64 n, long2 v) noexcept { return long2(n) >> v; }
static constexpr long2 operator<<(int64 n, long2 v) noexcept { return long2(n) << v; }
static constexpr bool operator==(int64 n, long2 v) noexcept { return long2(n) == v; }
static constexpr bool operator!=(int64 n, long2 v) noexcept { return long2(n) != v; }
static constexpr ulong2 operator<(int64 n, long2 v) noexcept { return long2(n) < v; }
static constexpr ulong2 operator>(int64 n, long2 v) noexcept { return long2(n) > v; }
static constexpr ulong2 operator<=(int64 n, long2 v) noexcept { return long2(n) <= v; }
static constexpr ulong2 operator>=(int64 n, long2 v) noexcept { return long2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(long2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong2 equal(long2 a, long2 b) noexcept
{
	return ulong2(a.x == b.x ? UINT64_MAX : 0, a.y == b.y ? UINT64_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong2 notEqual(long2 a, long2 b) noexcept
{
	return ulong2(a.x != b.x ? UINT64_MAX : 0, a.y != b.y ? UINT64_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(long2 a, long2 b) noexcept { return memcmp(&a, &b, sizeof(long2)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr long2 select(ulong2 c, long2 t, long2 f) noexcept
{
	return long2(c.x & 0x8000000000000000u ? t.x : f.x, c.y & 0x8000000000000000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr long2 min(long2 a, long2 b) noexcept { return long2(std::min(a.x, b.x), std::min(a.y, b.y)); }
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr long2 max(long2 a, long2 b) noexcept { return long2(std::max(a.x, b.x), std::max(a.y, b.y)); }
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr long2 min(long2 a, long2 b, long2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr long2 max(long2 a, long2 b, long2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr long2 clamp(long2 v, long2 min, long2 max) noexcept
{
	return long2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr long3 operator+(int64 n, long3 v) noexcept { return long3(n) + v; }
static constexpr long3 operator-(int64 n, long3 v) noexcept { return long3(n) - v; }
static constexpr long3 operator*(int64 n, long3 v) noexcept { return long3(n) * v; }
static constexpr long3 operator/(int64 n, long3 v) noexcept { return long3(n) / v; }
static constexpr long3 operator%(int64 n, long3 v) noexcept { return long3(n) % v; }
static constexpr long3 operator&(int64 n, long3 v) noexcept { return long3(n) & v; }
static constexpr long3 operator|(int64 n, long3 v) noexcept { return long3(n) | v; }
static constexpr long3 operator^(int64 n, long3 v) noexcept { return long3(n) ^ v; }
static constexpr long3 operator>>(int64 n, long3 v) noexcept { return long3(n) >> v; }
static constexpr long3 operator<<(int64 n, long3 v) noexcept { return long3(n) << v; }
static constexpr bool operator==(int64 n, long3 v) noexcept { return long3(n) == v; }
static constexpr bool operator!=(int64 n, long3 v) noexcept { return long3(n) != v; }
static constexpr ulong3 operator<(int64 n, long3 v) noexcept { return long3(n) < v; }
static constexpr ulong3 operator>(int64 n, long3 v) noexcept { return long3(n) > v; }
static constexpr ulong3 operator<=(int64 n, long3 v) noexcept { return long3(n) <= v; }
static constexpr ulong3 operator>=(int64 n, long3 v) noexcept { return long3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(long3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong3 equal(long3 a, long3 b) noexcept
{
	return ulong3(a.x == b.x ? UINT64_MAX : 0, a.y == b.y ? UINT64_MAX : 0, a.z == b.z ? UINT64_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong3 notEqual(long3 a, long3 b) noexcept
{
	return ulong3(a.x != b.x ? UINT64_MAX : 0, a.y != b.y ? UINT64_MAX : 0, a.z != b.z ? UINT64_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const long3& a, const long3& b) noexcept { return memcmp(&a, &b, sizeof(long3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr long3 select(ulong3 c, long3 t, long3 f) noexcept
{
	return long3(c.x & 0x8000000000000000u ? t.x : f.x, 
		c.y & 0x8000000000000000u ? t.y : f.y, c.z & 0x8000000000000000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr long3 min(long3 a, long3 b) noexcept
{
	return long3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr long3 max(long3 a, long3 b) noexcept
{
	return long3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr long3 min(long3 a, long3 b, long3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr long3 max(long3 a, long3 b, long3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr long3 clamp(long3 v, long3 min, long3 max) noexcept
{
	return long3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr long4 operator+(int64 n, long4 v) noexcept { return long4(n) + v; }
static constexpr long4 operator-(int64 n, long4 v) noexcept { return long4(n) - v; }
static constexpr long4 operator*(int64 n, long4 v) noexcept { return long4(n) * v; }
static constexpr long4 operator/(int64 n, long4 v) noexcept { return long4(n) / v; }
static constexpr long4 operator%(int64 n, long4 v) noexcept { return long4(n) % v; }
static constexpr long4 operator&(int64 n, long4 v) noexcept { return long4(n) & v; }
static constexpr long4 operator|(int64 n, long4 v) noexcept { return long4(n) | v; }
static constexpr long4 operator^(int64 n, long4 v) noexcept { return long4(n) ^ v; }
static constexpr long4 operator>>(int64 n, long4 v) noexcept { return long4(n) >> v; }
static constexpr long4 operator<<(int64 n, long4 v) noexcept { return long4(n) << v; }
static constexpr bool operator==(int64 n, long4 v) noexcept { return long4(n) == v; }
static constexpr bool operator!=(int64 n, long4 v) noexcept { return long4(n) != v; }
static constexpr ulong4 operator<(int64 n, long4 v) noexcept { return long4(n) < v; }
static constexpr ulong4 operator>(int64 n, long4 v) noexcept { return long4(n) > v; }
static constexpr ulong4 operator<=(int64 n, long4 v) noexcept { return long4(n) <= v; }
static constexpr ulong4 operator>=(int64 n, long4 v) noexcept { return long4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(long4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong4 equal(long4 a, long4 b) noexcept
{
	return ulong4(a.x == b.x ? UINT64_MAX : 0, a.y == b.y ? UINT64_MAX : 0, 
		a.z == b.z ? UINT64_MAX : 0, a.w == b.w ? UINT64_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong4 notEqual(long4 a, long4 b) noexcept
{
	return ulong4(a.x != b.x ? UINT64_MAX : 0, a.y != b.y ? UINT64_MAX : 0, 
		a.z != b.z ? UINT64_MAX : 0, a.w != b.w ? UINT64_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const long4& a, const long4& b) noexcept { return memcmp(&a, &b, sizeof(long4)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr long4 select(ulong4 c, long4 t, long4 f) noexcept
{
	return long4(c.x & 0x8000000000000000u ? t.x : f.x, c.y & 0x8000000000000000u ? t.y : f.y, 
		c.z & 0x8000000000000000u ? t.z : f.z, c.w & 0x8000000000000000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr long4 min(long4 a, long4 b) noexcept
{
	return long4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr long4 max(long4 a, long4 b) noexcept
{
	return long4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr long4 min(long4 a, long4 b, long4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr long4 max(long4 a, long4 b, long4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr long4 clamp(long4 v, long4 min, long4 max) noexcept
{
	return long4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math