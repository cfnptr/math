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
 * @brief Common unsigned integer 64 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/int.hpp"

namespace math
{

using namespace std;

/**
 * @brief A 2-component vector of 64-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] ulong2
{
	uint64 x; /**< First vector component. */
	uint64 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 64-bit unsigned integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit ulong2(uint64 xy = 0u) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 64-bit unsigned integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr ulong2(uint64 x, uint64 y) noexcept : x(x), y(y) { }

	constexpr ulong2(int2 xy) noexcept : x((uint64)xy.x), y((uint64)xy.y) { }
	constexpr ulong2(uint2 xy) noexcept : x((uint64)xy.x), y((uint64)xy.y) { }
	constexpr ulong2(short2 xy) noexcept : x((uint64)xy.x), y((uint64)xy.y) { }
	constexpr ulong2(ushort2 xy) noexcept : x((uint64)xy.x), y((uint64)xy.y) { }
	constexpr ulong2(sbyte2 xy) noexcept : x((uint64)xy.x), y((uint64)xy.y) { }
	constexpr ulong2(byte2 xy) noexcept : x((uint64)xy.x), y((uint64)xy.y) { }

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint64& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((uint64*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint64 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((uint64*)this)[i];
	}

	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr ulong2 operator+(ulong2 v) const noexcept { return ulong2(x + v.x, y + v.y); }
	constexpr ulong2 operator-(ulong2 v) const noexcept { return ulong2(x - v.x, y - v.y); }
	constexpr ulong2 operator*(ulong2 v) const noexcept { return ulong2(x * v.x, y * v.y); }
	constexpr ulong2 operator/(ulong2 v) const noexcept { return ulong2(x / v.x, y / v.y); }
	constexpr ulong2 operator%(ulong2 v) const noexcept { return ulong2(x % v.x, y % v.y); }
	constexpr ulong2 operator&(ulong2 v) const noexcept { return ulong2(x & v.x, y & v.y); }
	constexpr ulong2 operator|(ulong2 v) const noexcept { return ulong2(x | v.x, y | v.y); }
	constexpr ulong2 operator^(ulong2 v) const noexcept { return ulong2(x ^ v.x, y ^ v.y); }
	constexpr ulong2 operator>>(ulong2 v) const noexcept { return ulong2(x >> v.x, y >> v.y); }
	constexpr ulong2 operator<<(ulong2 v) const noexcept { return ulong2(x << v.x, y << v.y); }
	constexpr ulong2 operator+(uint64 n) const noexcept { return ulong2(x + n, y + n); }
	constexpr ulong2 operator-(uint64 n) const noexcept { return ulong2(x - n, y - n); }
	constexpr ulong2 operator*(uint64 n) const noexcept { return ulong2(x * n, y * n); }
	constexpr ulong2 operator/(uint64 n) const noexcept { return ulong2(x / n, y / n); }
	constexpr ulong2 operator%(uint64 n) const noexcept { return ulong2(x % n, y % n); }
	constexpr ulong2 operator&(uint64 n) const noexcept { return ulong2(x & n, y & n); }
	constexpr ulong2 operator|(uint64 n) const noexcept { return ulong2(x | n, y | n); }
	constexpr ulong2 operator^(uint64 n) const noexcept { return ulong2(x ^ n, y ^ n); }
	constexpr ulong2 operator>>(uint64 n) const noexcept { return ulong2(x >> n, y >> n); }
	constexpr ulong2 operator<<(uint64 n) const noexcept { return ulong2(x << n, y << n); }
	constexpr ulong2 operator-() const noexcept { return ulong2(-x, -y); }
	constexpr ulong2 operator!() const noexcept { return ulong2(!x, !y); }
	constexpr ulong2 operator~() const noexcept { return ulong2(~x, ~y); }
	ulong2& operator+=(ulong2 v) noexcept { x += v.x; y += v.y; return *this; }
	ulong2& operator-=(ulong2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	ulong2& operator*=(ulong2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	ulong2& operator/=(ulong2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	ulong2& operator%=(ulong2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	ulong2& operator&=(ulong2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	ulong2& operator|=(ulong2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	ulong2& operator^=(ulong2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	ulong2& operator>>=(ulong2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	ulong2& operator<<=(ulong2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	ulong2& operator+=(uint64 n) noexcept { x += n; y += n; return *this; }
	ulong2& operator-=(uint64 n) noexcept { x -= n; y -= n; return *this; }
	ulong2& operator*=(uint64 n) noexcept { x *= n; y *= n; return *this; }
	ulong2& operator/=(uint64 n) noexcept { x /= n; y /= n; return *this; }
	ulong2& operator%=(uint64 n) noexcept { x %= n; y %= n; return *this; }
	ulong2& operator&=(uint64 n) noexcept { x &= n; y &= n; return *this; }
	ulong2& operator|=(uint64 n) noexcept { x |= n; y |= n; return *this; }
	ulong2& operator^=(uint64 n) noexcept { x ^= n; y ^= n; return *this; }
	ulong2& operator>>=(uint64 n) noexcept { x >>= n; y >>= n; return *this; }
	ulong2& operator<<=(uint64 n) noexcept { x <<= n; y <<= n; return *this; }
	ulong2& operator=(uint64 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(ulong2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(ulong2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr ulong2 operator<(ulong2 v) const noexcept
	{
		return ulong2(x < v.x ? UINT64_MAX : 0, y < v.y ? UINT64_MAX : 0);
	}
	constexpr ulong2 operator>(ulong2 v) const noexcept
	{
		return ulong2(x > v.x ? UINT64_MAX : 0, y > v.y ? UINT64_MAX : 0);
	}
	constexpr ulong2 operator<=(ulong2 v) const noexcept
	{
		return ulong2(x <= v.x ? UINT64_MAX : 0, y <= v.y ? UINT64_MAX : 0);
	}
	constexpr ulong2 operator>=(ulong2 v) const noexcept
	{
		return ulong2(x >= v.x ? UINT64_MAX : 0, y >= v.y ? UINT64_MAX : 0);
	}
	constexpr bool operator==(uint64 n) const noexcept { return *this == ulong2(n); }
	constexpr bool operator!=(uint64 n) const noexcept { return *this != ulong2(n); }
	constexpr ulong2 operator<(uint64 n) const noexcept { return *this < ulong2(n); }
	constexpr ulong2 operator>(uint64 n) const noexcept { return *this > ulong2(n); }
	constexpr ulong2 operator<=(uint64 n) const noexcept { return *this <= ulong2(n); }
	constexpr ulong2 operator>=(uint64 n) const noexcept { return *this >= ulong2(n); }

	static const ulong2 zero, one;
};

inline const ulong2 ulong2::zero = ulong2(0u);
inline const ulong2 ulong2::one = ulong2(1u);

/***********************************************************************************************************************
 * @brief A 3-component vector of 64-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] ulong3
{
	uint64 x; /**< First vector component. */
	uint64 y; /**< Second vector component. */
	uint64 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 64-bit unsigned integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit ulong3(uint64 xyz = 0u) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr ulong3(uint64 x, uint64 y, uint64 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr ulong3(ulong2 xy, uint64 z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 64-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr ulong3(uint64 x, ulong2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	constexpr ulong3(int3 xyz) noexcept : x((uint64)xyz.x), y((uint64)xyz.y), z((uint64)xyz.z) { }
	constexpr ulong3(uint3 xyz) noexcept : x((uint64)xyz.x), y((uint64)xyz.y), z((uint64)xyz.z) { }
	constexpr ulong3(short3 xyz) noexcept : x((uint64)xyz.x), y((uint64)xyz.y), z((uint64)xyz.z) { }
	constexpr ulong3(ushort3 xyz) noexcept : x((uint64)xyz.x), y((uint64)xyz.y), z((uint64)xyz.z) { }
	constexpr ulong3(sbyte3 xyz) noexcept : x((uint64)xyz.x), y((uint64)xyz.y), z((uint64)xyz.z) { }
	constexpr ulong3(byte3 xyz) noexcept : x((uint64)xyz.x), y((uint64)xyz.y), z((uint64)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint64& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((uint64*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint64 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((uint64*)this)[i];
	}

	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator ulong2() const noexcept { return ulong2(x, y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr ulong3 operator+(ulong3 v) const noexcept { return ulong3(x + v.x, y + v.y, z + v.z); }
	constexpr ulong3 operator-(ulong3 v) const noexcept { return ulong3(x - v.x, y - v.y, z - v.z); }
	constexpr ulong3 operator*(ulong3 v) const noexcept { return ulong3(x * v.x, y * v.y, z * v.z); }
	constexpr ulong3 operator/(ulong3 v) const noexcept { return ulong3(x / v.x, y / v.y, z / v.z); }
	constexpr ulong3 operator%(ulong3 v) const noexcept { return ulong3(x % v.x, y % v.y, z % v.z); }
	constexpr ulong3 operator&(ulong3 v) const noexcept { return ulong3(x & v.x, y & v.y, z & v.z); }
	constexpr ulong3 operator|(ulong3 v) const noexcept { return ulong3(x | v.x, y | v.y, z | v.z); }
	constexpr ulong3 operator^(ulong3 v) const noexcept { return ulong3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr ulong3 operator>>(ulong3 v) const noexcept { return ulong3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr ulong3 operator<<(ulong3 v) const noexcept { return ulong3(x << v.x, y << v.y, z << v.z); }
	constexpr ulong3 operator+(uint64 n) const noexcept { return ulong3(x + n, y + n, z + n); }
	constexpr ulong3 operator-(uint64 n) const noexcept { return ulong3(x - n, y - n, z - n); }
	constexpr ulong3 operator*(uint64 n) const noexcept { return ulong3(x * n, y * n, z * n); }
	constexpr ulong3 operator/(uint64 n) const noexcept { return ulong3(x / n, y / n, z / n); }
	constexpr ulong3 operator%(uint64 n) const noexcept { return ulong3(x % n, y % n, z % n); }
	constexpr ulong3 operator&(uint64 n) const noexcept { return ulong3(x & n, y & n, z & n); }
	constexpr ulong3 operator|(uint64 n) const noexcept { return ulong3(x | n, y | n, z | n); }
	constexpr ulong3 operator^(uint64 n) const noexcept { return ulong3(x ^ n, y ^ n, z ^ n); }
	constexpr ulong3 operator>>(uint64 n) const noexcept { return ulong3(x >> n, y >> n, z >> n); }
	constexpr ulong3 operator<<(uint64 n) const noexcept { return ulong3(x << n, y << n, z << n); }
	constexpr ulong3 operator-() const noexcept { return ulong3(-x, -y, -z); }
	constexpr ulong3 operator!() const noexcept { return ulong3(!x, !y, !z); }
	ulong3 operator~() const noexcept { return ulong3(~x, ~y, ~z); }
	ulong3& operator+=(ulong3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	ulong3& operator-=(ulong3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	ulong3& operator*=(ulong3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	ulong3& operator/=(ulong3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	ulong3& operator%=(ulong3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	ulong3& operator&=(ulong3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	ulong3& operator|=(ulong3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	ulong3& operator^=(ulong3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	ulong3& operator>>=(ulong3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	ulong3& operator<<=(ulong3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	ulong3& operator+=(uint64 n) noexcept { x += n; y += n; z += n; return *this; }
	ulong3& operator-=(uint64 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	ulong3& operator*=(uint64 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	ulong3& operator/=(uint64 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	ulong3& operator%=(uint64 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	ulong3& operator&=(uint64 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	ulong3& operator|=(uint64 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	ulong3& operator^=(uint64 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	ulong3& operator>>=(uint64 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	ulong3& operator<<=(uint64 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	ulong3& operator=(uint64 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(ulong3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(ulong3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr ulong3 operator<(ulong3 v) const noexcept
	{
		return ulong3(x < v.x ? UINT64_MAX : 0, y < v.y ? UINT64_MAX : 0, z < v.z ? UINT64_MAX : 0);
	}
	constexpr ulong3 operator>(ulong3 v) const noexcept
	{
		return ulong3(x > v.x ? UINT64_MAX : 0, y > v.y ? UINT64_MAX : 0, z > v.z ? UINT64_MAX : 0);
	}
	constexpr ulong3 operator<=(ulong3 v) const noexcept
	{
		return ulong3(x <= v.x ? UINT64_MAX : 0, y <= v.y ? UINT64_MAX : 0, z <= v.z ? UINT64_MAX : 0);
	}
	constexpr ulong3 operator>=(ulong3 v) const noexcept
	{
		return ulong3(x >= v.x ? UINT64_MAX : 0, y >= v.y ? UINT64_MAX : 0, z >= v.z ? UINT64_MAX : 0);
	}
	constexpr bool operator==(uint64 n) const noexcept { return *this == ulong3(n); }
	constexpr bool operator!=(uint64 n) const noexcept { return *this != ulong3(n); }
	constexpr ulong3 operator<(uint64 n) const noexcept { return *this < ulong3(n); }
	constexpr ulong3 operator>(uint64 n) const noexcept { return *this > ulong3(n); }
	constexpr ulong3 operator<=(uint64 n) const noexcept { return *this <= ulong3(n); }
	constexpr ulong3 operator>=(uint64 n) const noexcept { return *this >= ulong3(n); }

	static const ulong3 zero, one, max;
};

inline const ulong3 ulong3::zero = ulong3(0u);
inline const ulong3 ulong3::one = ulong3(1u);
inline const ulong3 ulong3::max = ulong3(UINT64_MAX);

/***********************************************************************************************************************
 * @brief A 4-component vector of 64-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] ulong4
{
	uint64 x; /**< First vector component. */
	uint64 y; /**< Second vector component. */
	uint64 z; /**< Third vector component. */
	uint64 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit ulong4(uint64 xyzw = 0u) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ulong4(uint64 x, uint64 y, uint64 z, uint64 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ulong4(ulong2 xy, uint64 z, uint64 w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ulong4(uint64 x, ulong2 yz, uint64 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr ulong4(uint64 x, uint64 y, ulong2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr ulong4(ulong2 xy, ulong2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ulong4(ulong3 xyz, uint64 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 64-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector component value
	 */
	constexpr ulong4(uint64 x, ulong3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	constexpr ulong4(int4 xyzw) noexcept : x((uint64)xyzw.x), y((uint64)xyzw.y), z((uint64)xyzw.z), w((uint64)xyzw.w) { }
	constexpr ulong4(uint4 xyzw) noexcept : x((uint64)xyzw.x), y((uint64)xyzw.y), z((uint64)xyzw.z), w((uint64)xyzw.w) { }
	constexpr ulong4(short4 xyzw) noexcept : x((uint64)xyzw.x), y((uint64)xyzw.y), z((uint64)xyzw.z), w((uint64)xyzw.w) { }
	constexpr ulong4(ushort4 xyzw) noexcept : x((uint64)xyzw.x), y((uint64)xyzw.y), z((uint64)xyzw.z), w((uint64)xyzw.w) { }
	constexpr ulong4(sbyte4 xyzw) noexcept : x((uint64)xyzw.x), y((uint64)xyzw.y), z((uint64)xyzw.z), w((uint64)xyzw.w) { }
	constexpr ulong4(byte4 xyzw) noexcept : x((uint64)xyzw.x), y((uint64)xyzw.y), z((uint64)xyzw.z), w((uint64)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint64& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((uint64*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint64 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((uint64*)this)[i];
	}

	constexpr explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	constexpr explicit operator short4() const noexcept { return short4((int16)x, (int16)y, (int16)z, (int16)w); }
	constexpr explicit operator ushort4() const noexcept { return ushort4((uint16)x, (uint16)y, (uint16)z, (uint16)w); }
	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator ulong3() const noexcept { return ulong3(x, y, z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator ulong2() const noexcept { return ulong2(x, y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr ulong4 operator+(ulong4 v) const noexcept { return ulong4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr ulong4 operator-(ulong4 v) const noexcept { return ulong4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr ulong4 operator*(ulong4 v) const noexcept { return ulong4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr ulong4 operator/(ulong4 v) const noexcept { return ulong4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr ulong4 operator%(ulong4 v) const noexcept { return ulong4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr ulong4 operator&(ulong4 v) const noexcept { return ulong4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr ulong4 operator|(ulong4 v) const noexcept { return ulong4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr ulong4 operator^(ulong4 v) const noexcept { return ulong4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr ulong4 operator>>(ulong4 v) const noexcept { return ulong4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr ulong4 operator<<(ulong4 v) const noexcept { return ulong4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr ulong4 operator+(uint64 n) const noexcept { return ulong4(x + n, y + n, z + n, w + n); }
	constexpr ulong4 operator-(uint64 n) const noexcept { return ulong4(x - n, y - n, z - n, w - n); }
	constexpr ulong4 operator*(uint64 n) const noexcept { return ulong4(x * n, y * n, z * n, w * n); }
	constexpr ulong4 operator/(uint64 n) const noexcept { return ulong4(x / n, y / n, z / n, w / n); }
	constexpr ulong4 operator%(uint64 n) const noexcept { return ulong4(x % n, y % n, z % n, w % n); }
	constexpr ulong4 operator&(uint64 n) const noexcept { return ulong4(x & n, y & n, z & n, w & n); }
	constexpr ulong4 operator|(uint64 n) const noexcept { return ulong4(x | n, y | n, z | n, w | n); }
	constexpr ulong4 operator^(uint64 n) const noexcept { return ulong4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr ulong4 operator>>(uint64 n) const noexcept { return ulong4(x >> n, y >> n, z >> n, w >> n); }
	constexpr ulong4 operator<<(uint64 n) const noexcept { return ulong4(x << n, y << n, z << n, w << n); }
	constexpr ulong4 operator-() const noexcept { return ulong4(-x, -y, -z, -w); }
	constexpr ulong4 operator!() const noexcept { return ulong4(!x, !y, !z, !w); }
	constexpr ulong4 operator~() const noexcept { return ulong4(~x, ~y, ~z, ~w); }
	ulong4& operator+=(ulong4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	ulong4& operator-=(ulong4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	ulong4& operator*=(ulong4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	ulong4& operator/=(ulong4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	ulong4& operator%=(ulong4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	ulong4& operator&=(ulong4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	ulong4& operator|=(ulong4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	ulong4& operator^=(ulong4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	ulong4& operator>>=(ulong4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	ulong4& operator<<=(ulong4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	ulong4& operator+=(uint64 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	ulong4& operator-=(uint64 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	ulong4& operator*=(uint64 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	ulong4& operator/=(uint64 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	ulong4& operator%=(uint64 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	ulong4& operator&=(uint64 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	ulong4& operator|=(uint64 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	ulong4& operator^=(uint64 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	ulong4& operator>>=(uint64 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	ulong4& operator<<=(uint64 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	ulong4& operator=(uint64 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(ulong4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(ulong4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr ulong4 operator<(ulong4 v) const noexcept
	{
		return ulong4(x < v.x ? UINT64_MAX : 0, y < v.y ? UINT64_MAX : 0, 
			z < v.z ? UINT64_MAX : 0, w < v.w ? UINT64_MAX : 0);
	}
	constexpr ulong4 operator>(ulong4 v) const noexcept
	{
		return ulong4(x > v.x ? UINT64_MAX : 0, y > v.y ? UINT64_MAX : 0, 
			z > v.z ? UINT64_MAX : 0, w > v.w ? UINT64_MAX : 0);
	}
	constexpr ulong4 operator<=(ulong4 v) const noexcept
	{
		return ulong4(x <= v.x ? UINT64_MAX : 0, y <= v.y ? UINT64_MAX : 0, 
			z <= v.z ? UINT64_MAX : 0, w <= v.w ? UINT64_MAX : 0);
	}
	constexpr ulong4 operator>=(ulong4 v) const noexcept
	{
		return ulong4(x >= v.x ? UINT64_MAX : 0, y >= v.y ? UINT64_MAX : 0, 
			z >= v.z ? UINT64_MAX : 0, w >= v.w ? UINT64_MAX : 0);
	}
	constexpr bool operator==(uint64 n) const noexcept { return *this == ulong4(n); }
	constexpr bool operator!=(uint64 n) const noexcept { return *this != ulong4(n); }
	constexpr ulong4 operator<(uint64 n) const noexcept { return *this < ulong4(n); }
	constexpr ulong4 operator>(uint64 n) const noexcept { return *this > ulong4(n); }
	constexpr ulong4 operator<=(uint64 n) const noexcept { return *this <= ulong4(n); }
	constexpr ulong4 operator>=(uint64 n) const noexcept { return *this >= ulong4(n); }

	static const ulong4 zero, one, max;
};

inline const ulong4 ulong4::zero = ulong4(0u);
inline const ulong4 ulong4::one = ulong4(1u);
inline const ulong4 ulong4::max = ulong4(UINT64_MAX);

//**********************************************************************************************************************
static constexpr ulong2 operator+(uint64 n, ulong2 v) noexcept { return ulong2(n) + v; }
static constexpr ulong2 operator-(uint64 n, ulong2 v) noexcept { return ulong2(n) - v; }
static constexpr ulong2 operator*(uint64 n, ulong2 v) noexcept { return ulong2(n) * v; }
static constexpr ulong2 operator/(uint64 n, ulong2 v) noexcept { return ulong2(n) / v; }
static constexpr ulong2 operator%(uint64 n, ulong2 v) noexcept { return ulong2(n) % v; }
static constexpr ulong2 operator&(uint64 n, ulong2 v) noexcept { return ulong2(n) & v; }
static constexpr ulong2 operator|(uint64 n, ulong2 v) noexcept { return ulong2(n) | v; }
static constexpr ulong2 operator^(uint64 n, ulong2 v) noexcept { return ulong2(n) ^ v; }
static constexpr ulong2 operator>>(uint64 n, ulong2 v) noexcept { return ulong2(n) >> v; }
static constexpr ulong2 operator<<(uint64 n, ulong2 v) noexcept { return ulong2(n) << v; }
static constexpr bool operator==(uint64 n, ulong2 v) noexcept { return ulong2(n) == v; }
static constexpr bool operator!=(uint64 n, ulong2 v) noexcept { return ulong2(n) != v; }
static constexpr ulong2 operator<(uint64 n, ulong2 v) noexcept { return ulong2(n) < v; }
static constexpr ulong2 operator>(uint64 n, ulong2 v) noexcept { return ulong2(n) > v; }
static constexpr ulong2 operator<=(uint64 n, ulong2 v) noexcept { return ulong2(n) <= v; }
static constexpr ulong2 operator>=(uint64 n, ulong2 v) noexcept { return ulong2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(ulong2 v) { return to_string(v.x) + " " + to_string(v.y); }

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (2bits)
 */
static constexpr uint64 getTrues(ulong2 v) noexcept
{
	return (v.x >> 63u) | ((v.y >> 63u) << 1u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(ulong2 v) noexcept { return (v.x & v.y) == UINT64_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(ulong2 v) noexcept { return (v.x | v.y) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(ulong2 v) noexcept { return v.x | v.y; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(ulong2 v) noexcept { return (v.x & v.y) != UINT64_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong2 equal(ulong2 a, ulong2 b) noexcept
{
	return ulong2(a.x == b.x ? UINT64_MAX : 0, a.y == b.y ? UINT64_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong2 notEqual(ulong2 a, ulong2 b) noexcept
{
	return ulong2(a.x != b.x ? UINT64_MAX : 0, a.y != b.y ? UINT64_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(ulong2 a, ulong2 b) noexcept { return memcmp(&a, &b, sizeof(ulong2)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr ulong2 select(ulong2 c, ulong2 t, ulong2 f) noexcept
{
	return ulong2(c.x & 0x8000000000000000u ? t.x : f.x, c.y & 0x8000000000000000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr ulong2 min(ulong2 a, ulong2 b) noexcept
{
	return ulong2(std::min(a.x, b.x), std::min(a.y, b.y));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr ulong2 max(ulong2 a, ulong2 b) noexcept
{
	return ulong2(std::max(a.x, b.x), std::max(a.y, b.y));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr ulong2 min(ulong2 a, ulong2 b, ulong2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr ulong2 max(ulong2 a, ulong2 b, ulong2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr ulong2 clamp(ulong2 v, ulong2 min, ulong2 max) noexcept
{
	return ulong2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr ulong3 operator+(uint64 n, ulong3 v) noexcept { return ulong3(n) + v; }
static constexpr ulong3 operator-(uint64 n, ulong3 v) noexcept { return ulong3(n) - v; }
static constexpr ulong3 operator*(uint64 n, ulong3 v) noexcept { return ulong3(n) * v; }
static constexpr ulong3 operator/(uint64 n, ulong3 v) noexcept { return ulong3(n) / v; }
static constexpr ulong3 operator%(uint64 n, ulong3 v) noexcept { return ulong3(n) % v; }
static constexpr ulong3 operator&(uint64 n, ulong3 v) noexcept { return ulong3(n) & v; }
static constexpr ulong3 operator|(uint64 n, ulong3 v) noexcept { return ulong3(n) | v; }
static constexpr ulong3 operator^(uint64 n, ulong3 v) noexcept { return ulong3(n) ^ v; }
static constexpr ulong3 operator>>(uint64 n, ulong3 v) noexcept { return ulong3(n) >> v; }
static constexpr ulong3 operator<<(uint64 n, ulong3 v) noexcept { return ulong3(n) << v; }
static constexpr bool operator==(uint64 n, ulong3 v) noexcept { return ulong3(n) == v; }
static constexpr bool operator!=(uint64 n, ulong3 v) noexcept { return ulong3(n) != v; }
static constexpr ulong3 operator<(uint64 n, ulong3 v) noexcept { return ulong3(n) < v; }
static constexpr ulong3 operator>(uint64 n, ulong3 v) noexcept { return ulong3(n) > v; }
static constexpr ulong3 operator<=(uint64 n, ulong3 v) noexcept { return ulong3(n) <= v; }
static constexpr ulong3 operator>=(uint64 n, ulong3 v) noexcept { return ulong3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(ulong3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (3bits)
 */
static constexpr uint64 getTrues(ulong3 v) noexcept
{
	return (v.x >> 63u) | ((v.y >> 63u) << 1u) | ((v.z >> 63u) << 2u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(ulong3 v) noexcept { return (v.x & v.y & v.z) == UINT64_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(ulong3 v) noexcept { return (v.x | v.y | v.z) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(ulong3 v) noexcept { return v.x | v.y | v.z; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(ulong3 v) noexcept { return (v.x & v.y & v.z) != UINT64_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong3 equal(ulong3 a, ulong3 b) noexcept
{
	return ulong3(a.x == b.x ? UINT64_MAX : 0, a.y == b.y ? UINT64_MAX : 0, a.z == b.z ? UINT64_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong3 notEqual(ulong3 a, ulong3 b) noexcept
{
	return ulong3(a.x != b.x ? UINT64_MAX : 0, a.y != b.y ? UINT64_MAX : 0, a.z != b.z ? UINT64_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const ulong3& a, const ulong3& b) noexcept { return memcmp(&a, &b, sizeof(ulong3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr ulong3 select(ulong3 c, ulong3 t, ulong3 f) noexcept
{
	return ulong3(c.x & 0x8000000000000000u ? t.x : f.x, 
		c.y & 0x8000000000000000u ? t.y : f.y, c.z & 0x8000000000000000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr ulong3 min(ulong3 a, ulong3 b) noexcept
{
	return ulong3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr ulong3 max(ulong3 a, ulong3 b) noexcept
{
	return ulong3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr ulong3 min(ulong3 a, ulong3 b, ulong3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr ulong3 max(ulong3 a, ulong3 b, ulong3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr ulong3 clamp(ulong3 v, ulong3 min, ulong3 max) noexcept
{
	return ulong3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr ulong4 operator+(uint64 n, const ulong4& v) noexcept { return ulong4(n) + v; }
static constexpr ulong4 operator-(uint64 n, const ulong4& v) noexcept { return ulong4(n) - v; }
static constexpr ulong4 operator*(uint64 n, const ulong4& v) noexcept { return ulong4(n) * v; }
static constexpr ulong4 operator/(uint64 n, const ulong4& v) noexcept { return ulong4(n) / v; }
static constexpr ulong4 operator%(uint64 n, const ulong4& v) noexcept { return ulong4(n) % v; }
static constexpr ulong4 operator&(uint64 n, const ulong4& v) noexcept { return ulong4(n) & v; }
static constexpr ulong4 operator|(uint64 n, const ulong4& v) noexcept { return ulong4(n) | v; }
static constexpr ulong4 operator^(uint64 n, const ulong4& v) noexcept { return ulong4(n) ^ v; }
static constexpr ulong4 operator>>(uint64 n, const ulong4& v) noexcept { return ulong4(n) >> v; }
static constexpr ulong4 operator<<(uint64 n, const ulong4& v) noexcept { return ulong4(n) << v; }
static constexpr bool operator==(uint64 n, const ulong4& v) noexcept { return ulong4(n) == v; }
static constexpr bool operator!=(uint64 n, const ulong4& v) noexcept { return ulong4(n) != v; }
static constexpr ulong4 operator<(uint64 n, const ulong4& v) noexcept { return ulong4(n) < v; }
static constexpr ulong4 operator>(uint64 n, const ulong4& v) noexcept { return ulong4(n) > v; }
static constexpr ulong4 operator<=(uint64 n, const ulong4& v) noexcept { return ulong4(n) <= v; }
static constexpr ulong4 operator>=(uint64 n, const ulong4& v) noexcept { return ulong4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(ulong4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (4bits)
 */
static constexpr uint64 getTrues(ulong4 v) noexcept
{
	return (v.x >> 63u) | ((v.y >> 63u) << 1u) | ((v.z >> 63u) << 2u) | ((v.w >> 63u) << 3u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(ulong4 v) noexcept { return (v.x & v.y & v.z & v.w) == UINT64_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(ulong4 v) noexcept { return (v.x | v.y | v.z | v.w) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(ulong4 v) noexcept { return v.x | v.y | v.z | v.w; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(ulong4 v) noexcept { return (v.x & v.y & v.z & v.w) != UINT64_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ulong4 equal(ulong4 a, ulong4 b) noexcept
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
static ulong4 notEqual(ulong4 a, ulong4 b) noexcept
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
static bool isBinaryLess(const ulong4& a, const ulong4& b) noexcept { return memcmp(&a, &b, sizeof(ulong4)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr ulong4 select(ulong4 c, ulong4 t, ulong4 f) noexcept
{
	return ulong4(c.x & 0x8000000000000000u ? t.x : f.x, c.y & 0x8000000000000000u ? t.y : f.y, 
		c.z & 0x8000000000000000u ? t.z : f.z, c.w & 0x8000000000000000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr ulong4 min(ulong4 a, ulong4 b) noexcept
{
	return ulong4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr ulong4 max(ulong4 a, ulong4 b) noexcept
{
	return ulong4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr ulong4 min(ulong4 a, ulong4 b, ulong4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr ulong4 max(ulong4 a, ulong4 b, ulong4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr ulong4 clamp(ulong4 v, ulong4 min, ulong4 max) noexcept
{
	return ulong4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math