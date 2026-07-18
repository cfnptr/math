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
 * @brief Common unsigned integer 8 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/types.hpp"

#include <string>
#include <algorithm>
#include <cassert>
#include <cstring>

namespace math
{

using namespace std;

/**
 * @brief A 2-component vector of 8-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] byte2
{
	uint8 x; /**< First vector component. */
	uint8 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 8-bit unsigned integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit byte2(uint8 xy = 0u) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 8-bit unsigned integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr byte2(uint8 x, uint8 y) noexcept : x(x), y(y) { }

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint8& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((uint8*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint8 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((uint8*)this)[i];
	}

	//******************************************************************************************************************
	constexpr byte2 operator+(byte2 v) const noexcept { return byte2(x + v.x, y + v.y); }
	constexpr byte2 operator-(byte2 v) const noexcept { return byte2(x - v.x, y - v.y); }
	constexpr byte2 operator*(byte2 v) const noexcept { return byte2(x * v.x, y * v.y); }
	constexpr byte2 operator/(byte2 v) const noexcept { return byte2(x / v.x, y / v.y); }
	constexpr byte2 operator%(byte2 v) const noexcept { return byte2(x % v.x, y % v.y); }
	constexpr byte2 operator&(byte2 v) const noexcept { return byte2(x & v.x, y & v.y); }
	constexpr byte2 operator|(byte2 v) const noexcept { return byte2(x | v.x, y | v.y); }
	constexpr byte2 operator^(byte2 v) const noexcept { return byte2(x ^ v.x, y ^ v.y); }
	constexpr byte2 operator>>(byte2 v) const noexcept { return byte2(x >> v.x, y >> v.y); }
	constexpr byte2 operator<<(byte2 v) const noexcept { return byte2(x << v.x, y << v.y); }
	constexpr byte2 operator+(uint8 n) const noexcept { return byte2(x + n, y + n); }
	constexpr byte2 operator-(uint8 n) const noexcept { return byte2(x - n, y - n); }
	constexpr byte2 operator*(uint8 n) const noexcept { return byte2(x * n, y * n); }
	constexpr byte2 operator/(uint8 n) const noexcept { return byte2(x / n, y / n); }
	constexpr byte2 operator%(uint8 n) const noexcept { return byte2(x % n, y % n); }
	constexpr byte2 operator&(uint8 n) const noexcept { return byte2(x & n, y & n); }
	constexpr byte2 operator|(uint8 n) const noexcept { return byte2(x | n, y | n); }
	constexpr byte2 operator^(uint8 n) const noexcept { return byte2(x ^ n, y ^ n); }
	constexpr byte2 operator>>(uint8 n) const noexcept { return byte2(x >> n, y >> n); }
	constexpr byte2 operator<<(uint8 n) const noexcept { return byte2(x << n, y << n); }
	constexpr byte2 operator-() const noexcept { return byte2(-x, -y); }
	constexpr byte2 operator!() const noexcept { return byte2(!x, !y); }
	constexpr byte2 operator~() const noexcept { return byte2(~x, ~y); }
	byte2& operator+=(byte2 v) noexcept { x += v.x; y += v.y; return *this; }
	byte2& operator-=(byte2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	byte2& operator*=(byte2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	byte2& operator/=(byte2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	byte2& operator%=(byte2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	byte2& operator&=(byte2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	byte2& operator|=(byte2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	byte2& operator^=(byte2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	byte2& operator>>=(byte2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	byte2& operator<<=(byte2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	byte2& operator+=(uint8 n) noexcept { x += n; y += n; return *this; }
	byte2& operator-=(uint8 n) noexcept { x -= n; y -= n; return *this; }
	byte2& operator*=(uint8 n) noexcept { x *= n; y *= n; return *this; }
	byte2& operator/=(uint8 n) noexcept { x /= n; y /= n; return *this; }
	byte2& operator%=(uint8 n) noexcept { x %= n; y %= n; return *this; }
	byte2& operator&=(uint8 n) noexcept { x &= n; y &= n; return *this; }
	byte2& operator|=(uint8 n) noexcept { x |= n; y |= n; return *this; }
	byte2& operator^=(uint8 n) noexcept { x ^= n; y ^= n; return *this; }
	byte2& operator>>=(uint8 n) noexcept { x >>= n; y >>= n; return *this; }
	byte2& operator<<=(uint8 n) noexcept { x <<= n; y <<= n; return *this; }
	byte2& operator=(uint8 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(byte2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(byte2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr byte2 operator<(byte2 v) const noexcept
	{
		return byte2(x < v.x ? UINT8_MAX : 0, y < v.y ? UINT8_MAX : 0);
	}
	constexpr byte2 operator>(byte2 v) const noexcept
	{
		return byte2(x > v.x ? UINT8_MAX : 0, y > v.y ? UINT8_MAX : 0);
	}
	constexpr byte2 operator<=(byte2 v) const noexcept
	{
		return byte2(x <= v.x ? UINT8_MAX : 0, y <= v.y ? UINT8_MAX : 0);
	}
	constexpr byte2 operator>=(byte2 v) const noexcept
	{
		return byte2(x >= v.x ? UINT8_MAX : 0, y >= v.y ? UINT8_MAX : 0);
	}
	constexpr bool operator==(uint8 n) const noexcept { return *this == byte2(n); }
	constexpr bool operator!=(uint8 n) const noexcept { return *this != byte2(n); }
	constexpr byte2 operator<(uint8 n) const noexcept { return *this < byte2(n); }
	constexpr byte2 operator>(uint8 n) const noexcept { return *this > byte2(n); }
	constexpr byte2 operator<=(uint8 n) const noexcept { return *this <= byte2(n); }
	constexpr byte2 operator>=(uint8 n) const noexcept { return *this >= byte2(n); }

	static const byte2 zero, one, max;
};

inline const byte2 byte2::zero = byte2(0u);
inline const byte2 byte2::one = byte2(1u);
inline const byte2 byte2::max = byte2(UINT8_MAX);

/***********************************************************************************************************************
 * @brief A 3-component vector of 8-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] byte3
{
	uint8 x; /**< First vector component. */
	uint8 y; /**< Second vector component. */
	uint8 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 8-bit unsigned integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit byte3(uint8 xyz = 0u) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 8-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr byte3(uint8 x, uint8 y, uint8 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 8-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr byte3(byte2 xy, uint8 z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 8-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr byte3(uint8 x, byte2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint8& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((uint8*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint8 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((uint8*)this)[i];
	}

	constexpr explicit operator byte2() const noexcept { return byte2(x, y); }

	//******************************************************************************************************************
	constexpr byte3 operator+(byte3 v) const noexcept { return byte3(x + v.x, y + v.y, z + v.z); }
	constexpr byte3 operator-(byte3 v) const noexcept { return byte3(x - v.x, y - v.y, z - v.z); }
	constexpr byte3 operator*(byte3 v) const noexcept { return byte3(x * v.x, y * v.y, z * v.z); }
	constexpr byte3 operator/(byte3 v) const noexcept { return byte3(x / v.x, y / v.y, z / v.z); }
	constexpr byte3 operator%(byte3 v) const noexcept { return byte3(x % v.x, y % v.y, z % v.z); }
	constexpr byte3 operator&(byte3 v) const noexcept { return byte3(x & v.x, y & v.y, z & v.z); }
	constexpr byte3 operator|(byte3 v) const noexcept { return byte3(x | v.x, y | v.y, z | v.z); }
	constexpr byte3 operator^(byte3 v) const noexcept { return byte3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr byte3 operator>>(byte3 v) const noexcept { return byte3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr byte3 operator<<(byte3 v) const noexcept { return byte3(x << v.x, y << v.y, z << v.z); }
	constexpr byte3 operator+(uint8 n) const noexcept { return byte3(x + n, y + n, z + n); }
	constexpr byte3 operator-(uint8 n) const noexcept { return byte3(x - n, y - n, z - n); }
	constexpr byte3 operator*(uint8 n) const noexcept { return byte3(x * n, y * n, z * n); }
	constexpr byte3 operator/(uint8 n) const noexcept { return byte3(x / n, y / n, z / n); }
	constexpr byte3 operator%(uint8 n) const noexcept { return byte3(x % n, y % n, z % n); }
	constexpr byte3 operator&(uint8 n) const noexcept { return byte3(x & n, y & n, z & n); }
	constexpr byte3 operator|(uint8 n) const noexcept { return byte3(x | n, y | n, z | n); }
	constexpr byte3 operator^(uint8 n) const noexcept { return byte3(x ^ n, y ^ n, z ^ n); }
	constexpr byte3 operator>>(uint8 n) const noexcept { return byte3(x >> n, y >> n, z >> n); }
	constexpr byte3 operator<<(uint8 n) const noexcept { return byte3(x << n, y << n, z << n); }
	constexpr byte3 operator-() const noexcept { return byte3(-x, -y, -z); }
	constexpr byte3 operator!() const noexcept { return byte3(!x, !y, !z); }
	byte3 operator~() const noexcept { return byte3(~x, ~y, ~z); }
	byte3& operator+=(byte3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	byte3& operator-=(byte3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	byte3& operator*=(byte3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	byte3& operator/=(byte3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	byte3& operator%=(byte3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	byte3& operator&=(byte3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	byte3& operator|=(byte3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	byte3& operator^=(byte3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	byte3& operator>>=(byte3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	byte3& operator<<=(byte3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	byte3& operator+=(uint8 n) noexcept { x += n; y += n; z += n; return *this; }
	byte3& operator-=(uint8 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	byte3& operator*=(uint8 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	byte3& operator/=(uint8 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	byte3& operator%=(uint8 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	byte3& operator&=(uint8 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	byte3& operator|=(uint8 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	byte3& operator^=(uint8 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	byte3& operator>>=(uint8 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	byte3& operator<<=(uint8 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	byte3& operator=(uint8 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(byte3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(byte3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr byte3 operator<(byte3 v) const noexcept
	{
		return byte3(x < v.x ? UINT8_MAX : 0, y < v.y ? UINT8_MAX : 0, z < v.z ? UINT8_MAX : 0);
	}
	constexpr byte3 operator>(byte3 v) const noexcept
	{
		return byte3(x > v.x ? UINT8_MAX : 0, y > v.y ? UINT8_MAX : 0, z > v.z ? UINT8_MAX : 0);
	}
	constexpr byte3 operator<=(byte3 v) const noexcept
	{
		return byte3(x <= v.x ? UINT8_MAX : 0, y <= v.y ? UINT8_MAX : 0, z <= v.z ? UINT8_MAX : 0);
	}
	constexpr byte3 operator>=(byte3 v) const noexcept
	{
		return byte3(x >= v.x ? UINT8_MAX : 0, y >= v.y ? UINT8_MAX : 0, z >= v.z ? UINT8_MAX : 0);
	}
	constexpr bool operator==(uint8 n) const noexcept { return *this == byte3(n); }
	constexpr bool operator!=(uint8 n) const noexcept { return *this != byte3(n); }
	constexpr byte3 operator<(uint8 n) const noexcept { return *this < byte3(n); }
	constexpr byte3 operator>(uint8 n) const noexcept { return *this > byte3(n); }
	constexpr byte3 operator<=(uint8 n) const noexcept { return *this <= byte3(n); }
	constexpr byte3 operator>=(uint8 n) const noexcept { return *this >= byte3(n); }

	static const byte3 zero, one, max;
};

inline const byte3 byte3::zero = byte3(0u);
inline const byte3 byte3::one = byte3(1u);
inline const byte3 byte3::max = byte3(UINT8_MAX);

/***********************************************************************************************************************
 * @brief A 4-component vector of 8-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] byte4
{
	uint8 x; /**< First vector component. */
	uint8 y; /**< Second vector component. */
	uint8 z; /**< Third vector component. */
	uint8 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit byte4(uint8 xyzw = 0u) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr byte4(uint8 x, uint8 y, uint8 z, uint8 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr byte4(byte2 xy, uint8 z, uint8 w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr byte4(uint8 x, byte2 yz, uint8 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr byte4(uint8 x, uint8 y, byte2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr byte4(byte2 xy, byte2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr byte4(byte3 xyz, uint8 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector component value
	 */
	constexpr byte4(uint8 x, byte3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint8& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((uint8*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint8 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((uint8*)this)[i];
	}

	constexpr explicit operator byte3() const noexcept { return byte3(x, y, z); }
	constexpr explicit operator byte2() const noexcept { return byte2(x, y); }

	//******************************************************************************************************************
	constexpr byte4 operator+(byte4 v) const noexcept { return byte4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr byte4 operator-(byte4 v) const noexcept { return byte4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr byte4 operator*(byte4 v) const noexcept { return byte4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr byte4 operator/(byte4 v) const noexcept { return byte4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr byte4 operator%(byte4 v) const noexcept { return byte4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr byte4 operator&(byte4 v) const noexcept { return byte4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr byte4 operator|(byte4 v) const noexcept { return byte4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr byte4 operator^(byte4 v) const noexcept { return byte4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr byte4 operator>>(byte4 v) const noexcept { return byte4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr byte4 operator<<(byte4 v) const noexcept { return byte4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr byte4 operator+(uint8 n) const noexcept { return byte4(x + n, y + n, z + n, w + n); }
	constexpr byte4 operator-(uint8 n) const noexcept { return byte4(x - n, y - n, z - n, w - n); }
	constexpr byte4 operator*(uint8 n) const noexcept { return byte4(x * n, y * n, z * n, w * n); }
	constexpr byte4 operator/(uint8 n) const noexcept { return byte4(x / n, y / n, z / n, w / n); }
	constexpr byte4 operator%(uint8 n) const noexcept { return byte4(x % n, y % n, z % n, w % n); }
	constexpr byte4 operator&(uint8 n) const noexcept { return byte4(x & n, y & n, z & n, w & n); }
	constexpr byte4 operator|(uint8 n) const noexcept { return byte4(x | n, y | n, z | n, w | n); }
	constexpr byte4 operator^(uint8 n) const noexcept { return byte4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr byte4 operator>>(uint8 n) const noexcept { return byte4(x >> n, y >> n, z >> n, w >> n); }
	constexpr byte4 operator<<(uint8 n) const noexcept { return byte4(x << n, y << n, z << n, w << n); }
	constexpr byte4 operator-() const noexcept { return byte4(-x, -y, -z, -w); }
	constexpr byte4 operator!() const noexcept { return byte4(!x, !y, !z, !w); }
	constexpr byte4 operator~() const noexcept { return byte4(~x, ~y, ~z, ~w); }
	byte4& operator+=(byte4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	byte4& operator-=(byte4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	byte4& operator*=(byte4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	byte4& operator/=(byte4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	byte4& operator%=(byte4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	byte4& operator&=(byte4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	byte4& operator|=(byte4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	byte4& operator^=(byte4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	byte4& operator>>=(byte4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	byte4& operator<<=(byte4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	byte4& operator+=(uint8 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	byte4& operator-=(uint8 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	byte4& operator*=(uint8 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	byte4& operator/=(uint8 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	byte4& operator%=(uint8 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	byte4& operator&=(uint8 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	byte4& operator|=(uint8 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	byte4& operator^=(uint8 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	byte4& operator>>=(uint8 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	byte4& operator<<=(uint8 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	byte4& operator=(uint8 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(byte4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(byte4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr byte4 operator<(byte4 v) const noexcept
	{
		return byte4(x < v.x ? UINT8_MAX : 0, y < v.y ? UINT8_MAX : 0, 
			z < v.z ? UINT8_MAX : 0, w < v.w ? UINT8_MAX : 0);
	}
	constexpr byte4 operator>(byte4 v) const noexcept
	{
		return byte4(x > v.x ? UINT8_MAX : 0, y > v.y ? UINT8_MAX : 0, 
			z > v.z ? UINT8_MAX : 0, w > v.w ? UINT8_MAX : 0);
	}
	constexpr byte4 operator<=(byte4 v) const noexcept
	{
		return byte4(x <= v.x ? UINT8_MAX : 0, y <= v.y ? UINT8_MAX : 0, 
			z <= v.z ? UINT8_MAX : 0, w <= v.w ? UINT8_MAX : 0);
	}
	constexpr byte4 operator>=(byte4 v) const noexcept
	{
		return byte4(x >= v.x ? UINT8_MAX : 0, y >= v.y ? UINT8_MAX : 0, 
			z >= v.z ? UINT8_MAX : 0, w >= v.w ? UINT8_MAX : 0);
	}
	constexpr bool operator==(uint8 n) const noexcept { return *this == byte4(n); }
	constexpr bool operator!=(uint8 n) const noexcept { return *this != byte4(n); }
	constexpr byte4 operator<(uint8 n) const noexcept { return *this < byte4(n); }
	constexpr byte4 operator>(uint8 n) const noexcept { return *this > byte4(n); }
	constexpr byte4 operator<=(uint8 n) const noexcept { return *this <= byte4(n); }
	constexpr byte4 operator>=(uint8 n) const noexcept { return *this >= byte4(n); }

	static const byte4 zero, one, max;
};

inline const byte4 byte4::zero = byte4(0u);
inline const byte4 byte4::one = byte4(1u);
inline const byte4 byte4::max = byte4(UINT8_MAX);

//**********************************************************************************************************************
static constexpr byte2 operator+(uint8 n, byte2 v) noexcept { return byte2(n) + v; }
static constexpr byte2 operator-(uint8 n, byte2 v) noexcept { return byte2(n) - v; }
static constexpr byte2 operator*(uint8 n, byte2 v) noexcept { return byte2(n) * v; }
static constexpr byte2 operator/(uint8 n, byte2 v) noexcept { return byte2(n) / v; }
static constexpr byte2 operator%(uint8 n, byte2 v) noexcept { return byte2(n) % v; }
static constexpr byte2 operator&(uint8 n, byte2 v) noexcept { return byte2(n) & v; }
static constexpr byte2 operator|(uint8 n, byte2 v) noexcept { return byte2(n) | v; }
static constexpr byte2 operator^(uint8 n, byte2 v) noexcept { return byte2(n) ^ v; }
static constexpr byte2 operator>>(uint8 n, byte2 v) noexcept { return byte2(n) >> v; }
static constexpr byte2 operator<<(uint8 n, byte2 v) noexcept { return byte2(n) << v; }
static constexpr bool operator==(uint8 n, byte2 v) noexcept { return byte2(n) == v; }
static constexpr bool operator!=(uint8 n, byte2 v) noexcept { return byte2(n) != v; }
static constexpr byte2 operator<(uint8 n, byte2 v) noexcept { return byte2(n) < v; }
static constexpr byte2 operator>(uint8 n, byte2 v) noexcept { return byte2(n) > v; }
static constexpr byte2 operator<=(uint8 n, byte2 v) noexcept { return byte2(n) <= v; }
static constexpr byte2 operator>=(uint8 n, byte2 v) noexcept { return byte2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(byte2 v) { return to_string(v.x) + " " + to_string(v.y); }

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (2bits)
 */
static constexpr uint8 getTrues(byte2 v) noexcept
{
	return (v.x >> 7u) | ((v.y >> 7u) << 1u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(byte2 v) noexcept { return (v.x & v.y) == UINT8_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(byte2 v) noexcept { return (v.x | v.y) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(byte2 v) noexcept { return v.x | v.y; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(byte2 v) noexcept { return (v.x & v.y) != UINT8_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte2 equal(byte2 a, byte2 b) noexcept
{
	return byte2(a.x == b.x ? UINT8_MAX : 0, a.y == b.y ? UINT8_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte2 notEqual(byte2 a, byte2 b) noexcept
{
	return byte2(a.x != b.x ? UINT8_MAX : 0, a.y != b.y ? UINT8_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(byte2 a, byte2 b) noexcept { return *((const uint16*)&a) < *((const uint16*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr byte2 select(byte2 c, byte2 t, byte2 f) noexcept
{
	return byte2(c.x & 0x80u ? t.x : f.x, c.y & 0x80u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr byte2 min(byte2 a, byte2 b) noexcept
{
	return byte2(std::min(a.x, b.x), std::min(a.y, b.y));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr byte2 max(byte2 a, byte2 b) noexcept
{
	return byte2(std::max(a.x, b.x), std::max(a.y, b.y));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr byte2 min(byte2 a, byte2 b, byte2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr byte2 max(byte2 a, byte2 b, byte2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr byte2 clamp(byte2 v, byte2 min, byte2 max) noexcept
{
	return byte2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr byte3 operator+(uint8 n, byte3 v) noexcept { return byte3(n) + v; }
static constexpr byte3 operator-(uint8 n, byte3 v) noexcept { return byte3(n) - v; }
static constexpr byte3 operator*(uint8 n, byte3 v) noexcept { return byte3(n) * v; }
static constexpr byte3 operator/(uint8 n, byte3 v) noexcept { return byte3(n) / v; }
static constexpr byte3 operator%(uint8 n, byte3 v) noexcept { return byte3(n) % v; }
static constexpr byte3 operator&(uint8 n, byte3 v) noexcept { return byte3(n) & v; }
static constexpr byte3 operator|(uint8 n, byte3 v) noexcept { return byte3(n) | v; }
static constexpr byte3 operator^(uint8 n, byte3 v) noexcept { return byte3(n) ^ v; }
static constexpr byte3 operator>>(uint8 n, byte3 v) noexcept { return byte3(n) >> v; }
static constexpr byte3 operator<<(uint8 n, byte3 v) noexcept { return byte3(n) << v; }
static constexpr bool operator==(uint8 n, byte3 v) noexcept { return byte3(n) == v; }
static constexpr bool operator!=(uint8 n, byte3 v) noexcept { return byte3(n) != v; }
static constexpr byte3 operator<(uint8 n, byte3 v) noexcept { return byte3(n) < v; }
static constexpr byte3 operator>(uint8 n, byte3 v) noexcept { return byte3(n) > v; }
static constexpr byte3 operator<=(uint8 n, byte3 v) noexcept { return byte3(n) <= v; }
static constexpr byte3 operator>=(uint8 n, byte3 v) noexcept { return byte3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(byte3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (3bits)
 */
static constexpr uint8 getTrues(byte3 v) noexcept
{
	return (v.x >> 7u) | ((v.y >> 7u) << 1u) | ((v.z >> 7u) << 2u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(byte3 v) noexcept { return (v.x & v.y & v.z) == UINT8_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(byte3 v) noexcept { return (v.x | v.y | v.z) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(byte3 v) noexcept { return v.x | v.y | v.z; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(byte3 v) noexcept { return (v.x & v.y & v.z) != UINT8_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte3 equal(byte3 a, byte3 b) noexcept
{
	return byte3(a.x == b.x ? UINT8_MAX : 0, a.y == b.y ? UINT8_MAX : 0, a.z == b.z ? UINT8_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte3 notEqual(byte3 a, byte3 b) noexcept
{
	return byte3(a.x != b.x ? UINT8_MAX : 0, a.y != b.y ? UINT8_MAX : 0, a.z != b.z ? UINT8_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const byte3& a, const byte3& b) noexcept { return memcmp(&a, &b, sizeof(byte3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr byte3 select(byte3 c, byte3 t, byte3 f) noexcept
{
	return byte3(c.x & 0x80u ? t.x : f.x, c.y & 0x80u ? t.y : f.y, c.z & 0x80u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr byte3 min(byte3 a, byte3 b) noexcept
{
	return byte3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr byte3 max(byte3 a, byte3 b) noexcept
{
	return byte3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr byte3 min(byte3 a, byte3 b, byte3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr byte3 max(byte3 a, byte3 b, byte3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr byte3 clamp(byte3 v, byte3 min, byte3 max) noexcept
{
	return byte3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr byte4 operator+(uint8 n, const byte4& v) noexcept { return byte4(n) + v; }
static constexpr byte4 operator-(uint8 n, const byte4& v) noexcept { return byte4(n) - v; }
static constexpr byte4 operator*(uint8 n, const byte4& v) noexcept { return byte4(n) * v; }
static constexpr byte4 operator/(uint8 n, const byte4& v) noexcept { return byte4(n) / v; }
static constexpr byte4 operator%(uint8 n, const byte4& v) noexcept { return byte4(n) % v; }
static constexpr byte4 operator&(uint8 n, const byte4& v) noexcept { return byte4(n) & v; }
static constexpr byte4 operator|(uint8 n, const byte4& v) noexcept { return byte4(n) | v; }
static constexpr byte4 operator^(uint8 n, const byte4& v) noexcept { return byte4(n) ^ v; }
static constexpr byte4 operator>>(uint8 n, const byte4& v) noexcept { return byte4(n) >> v; }
static constexpr byte4 operator<<(uint8 n, const byte4& v) noexcept { return byte4(n) << v; }
static constexpr bool operator==(uint8 n, const byte4& v) noexcept { return byte4(n) == v; }
static constexpr bool operator!=(uint8 n, const byte4& v) noexcept { return byte4(n) != v; }
static constexpr byte4 operator<(uint8 n, const byte4& v) noexcept { return byte4(n) < v; }
static constexpr byte4 operator>(uint8 n, const byte4& v) noexcept { return byte4(n) > v; }
static constexpr byte4 operator<=(uint8 n, const byte4& v) noexcept { return byte4(n) <= v; }
static constexpr byte4 operator>=(uint8 n, const byte4& v) noexcept { return byte4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(byte4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (4bits)
 */
static constexpr uint8 getTrues(byte4 v) noexcept
{
	return (v.x >> 7u) | ((v.y >> 7u) << 1u) | ((v.z >> 7u) << 2u) | ((v.w >> 7u) << 3u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(byte4 v) noexcept { return (v.x & v.y & v.z & v.w) == UINT8_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(byte4 v) noexcept { return (v.x | v.y | v.z | v.w) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(byte4 v) noexcept { return v.x | v.y | v.z | v.w; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(byte4 v) noexcept { return (v.x & v.y & v.z & v.w) != UINT8_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte4 equal(byte4 a, byte4 b) noexcept
{
	return byte4(a.x == b.x ? UINT8_MAX : 0, a.y == b.y ? UINT8_MAX : 0, 
		a.z == b.z ? UINT8_MAX : 0, a.w == b.w ? UINT8_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte4 notEqual(byte4 a, byte4 b) noexcept
{
	return byte4(a.x != b.x ? UINT8_MAX : 0, a.y != b.y ? UINT8_MAX : 0, 
		a.z != b.z ? UINT8_MAX : 0, a.w != b.w ? UINT8_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const byte4& a, const byte4& b) noexcept
{
	return *((const uint32*)&a) < *((const uint32*)&b);
}

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr byte4 select(byte4 c, byte4 t, byte4 f) noexcept
{
	return byte4(c.x & 0x80u ? t.x : f.x, c.y & 0x80u ? t.y : f.y, c.z & 0x80u ? t.z : f.z, c.w & 0x80u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr byte4 min(byte4 a, byte4 b) noexcept
{
	return byte4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr byte4 max(byte4 a, byte4 b) noexcept
{
	return byte4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr byte4 min(byte4 a, byte4 b, byte4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr byte4 max(byte4 a, byte4 b, byte4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr byte4 clamp(byte4 v, byte4 min, byte4 max) noexcept
{
	return byte4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math