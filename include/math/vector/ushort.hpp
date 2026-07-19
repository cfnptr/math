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
 * @brief Common unsigned integer 16 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/sbyte.hpp"

namespace math
{

using namespace std;

/**
 * @brief A 2-component vector of 16-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] ushort2
{
	uint16 x; /**< First vector component. */
	uint16 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 16-bit unsigned integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit ushort2(uint16 xy = 0u) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 16-bit unsigned integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr ushort2(uint16 x, uint16 y) noexcept : x(x), y(y) { }

	constexpr ushort2(sbyte2 xy) noexcept : x((uint16)xy.x), y((uint16)xy.y) { }
	constexpr ushort2(byte2 xy) noexcept : x((uint16)xy.x), y((uint16)xy.y) { }

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint16& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((uint16*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint16 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((uint16*)this)[i];
	}

	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr ushort2 operator+(ushort2 v) const noexcept { return ushort2(x + v.x, y + v.y); }
	constexpr ushort2 operator-(ushort2 v) const noexcept { return ushort2(x - v.x, y - v.y); }
	constexpr ushort2 operator*(ushort2 v) const noexcept { return ushort2(x * v.x, y * v.y); }
	constexpr ushort2 operator/(ushort2 v) const noexcept { return ushort2(x / v.x, y / v.y); }
	constexpr ushort2 operator%(ushort2 v) const noexcept { return ushort2(x % v.x, y % v.y); }
	constexpr ushort2 operator&(ushort2 v) const noexcept { return ushort2(x & v.x, y & v.y); }
	constexpr ushort2 operator|(ushort2 v) const noexcept { return ushort2(x | v.x, y | v.y); }
	constexpr ushort2 operator^(ushort2 v) const noexcept { return ushort2(x ^ v.x, y ^ v.y); }
	constexpr ushort2 operator>>(ushort2 v) const noexcept { return ushort2(x >> v.x, y >> v.y); }
	constexpr ushort2 operator<<(ushort2 v) const noexcept { return ushort2(x << v.x, y << v.y); }
	constexpr ushort2 operator+(uint16 n) const noexcept { return ushort2(x + n, y + n); }
	constexpr ushort2 operator-(uint16 n) const noexcept { return ushort2(x - n, y - n); }
	constexpr ushort2 operator*(uint16 n) const noexcept { return ushort2(x * n, y * n); }
	constexpr ushort2 operator/(uint16 n) const noexcept { return ushort2(x / n, y / n); }
	constexpr ushort2 operator%(uint16 n) const noexcept { return ushort2(x % n, y % n); }
	constexpr ushort2 operator&(uint16 n) const noexcept { return ushort2(x & n, y & n); }
	constexpr ushort2 operator|(uint16 n) const noexcept { return ushort2(x | n, y | n); }
	constexpr ushort2 operator^(uint16 n) const noexcept { return ushort2(x ^ n, y ^ n); }
	constexpr ushort2 operator>>(uint16 n) const noexcept { return ushort2(x >> n, y >> n); }
	constexpr ushort2 operator<<(uint16 n) const noexcept { return ushort2(x << n, y << n); }
	constexpr ushort2 operator-() const noexcept { return ushort2(-x, -y); }
	constexpr ushort2 operator!() const noexcept { return ushort2(!x, !y); }
	constexpr ushort2 operator~() const noexcept { return ushort2(~x, ~y); }
	ushort2& operator+=(ushort2 v) noexcept { x += v.x; y += v.y; return *this; }
	ushort2& operator-=(ushort2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	ushort2& operator*=(ushort2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	ushort2& operator/=(ushort2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	ushort2& operator%=(ushort2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	ushort2& operator&=(ushort2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	ushort2& operator|=(ushort2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	ushort2& operator^=(ushort2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	ushort2& operator>>=(ushort2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	ushort2& operator<<=(ushort2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	ushort2& operator+=(uint16 n) noexcept { x += n; y += n; return *this; }
	ushort2& operator-=(uint16 n) noexcept { x -= n; y -= n; return *this; }
	ushort2& operator*=(uint16 n) noexcept { x *= n; y *= n; return *this; }
	ushort2& operator/=(uint16 n) noexcept { x /= n; y /= n; return *this; }
	ushort2& operator%=(uint16 n) noexcept { x %= n; y %= n; return *this; }
	ushort2& operator&=(uint16 n) noexcept { x &= n; y &= n; return *this; }
	ushort2& operator|=(uint16 n) noexcept { x |= n; y |= n; return *this; }
	ushort2& operator^=(uint16 n) noexcept { x ^= n; y ^= n; return *this; }
	ushort2& operator>>=(uint16 n) noexcept { x >>= n; y >>= n; return *this; }
	ushort2& operator<<=(uint16 n) noexcept { x <<= n; y <<= n; return *this; }
	ushort2& operator=(uint16 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(ushort2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(ushort2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr ushort2 operator<(ushort2 v) const noexcept
	{
		return ushort2(x < v.x ? UINT16_MAX : 0, y < v.y ? UINT16_MAX : 0);
	}
	constexpr ushort2 operator>(ushort2 v) const noexcept
	{
		return ushort2(x > v.x ? UINT16_MAX : 0, y > v.y ? UINT16_MAX : 0);
	}
	constexpr ushort2 operator<=(ushort2 v) const noexcept
	{
		return ushort2(x <= v.x ? UINT16_MAX : 0, y <= v.y ? UINT16_MAX : 0);
	}
	constexpr ushort2 operator>=(ushort2 v) const noexcept
	{
		return ushort2(x >= v.x ? UINT16_MAX : 0, y >= v.y ? UINT16_MAX : 0);
	}
	constexpr bool operator==(uint16 n) const noexcept { return *this == ushort2(n); }
	constexpr bool operator!=(uint16 n) const noexcept { return *this != ushort2(n); }
	constexpr ushort2 operator<(uint16 n) const noexcept { return *this < ushort2(n); }
	constexpr ushort2 operator>(uint16 n) const noexcept { return *this > ushort2(n); }
	constexpr ushort2 operator<=(uint16 n) const noexcept { return *this <= ushort2(n); }
	constexpr ushort2 operator>=(uint16 n) const noexcept { return *this >= ushort2(n); }

	static const ushort2 zero, one, max;
};

inline const ushort2 ushort2::zero = ushort2(0u);
inline const ushort2 ushort2::one = ushort2(1u);
inline const ushort2 ushort2::max = ushort2(UINT16_MAX);

/***********************************************************************************************************************
 * @brief A 3-component vector of 16-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] ushort3
{
	uint16 x; /**< First vector component. */
	uint16 y; /**< Second vector component. */
	uint16 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 16-bit unsigned integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit ushort3(uint16 xyz = 0u) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr ushort3(uint16 x, uint16 y, uint16 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr ushort3(ushort2 xy, uint16 z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr ushort3(uint16 x, ushort2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	constexpr ushort3(sbyte3 xyz) noexcept : x((uint16)xyz.x), y((uint16)xyz.y), z((uint16)xyz.z) { }
	constexpr ushort3(byte3 xyz) noexcept : x((uint16)xyz.x), y((uint16)xyz.y), z((uint16)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint16& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((uint16*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint16 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((uint16*)this)[i];
	}

	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator ushort2() const noexcept { return ushort2(x, y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr ushort3 operator+(ushort3 v) const noexcept { return ushort3(x + v.x, y + v.y, z + v.z); }
	constexpr ushort3 operator-(ushort3 v) const noexcept { return ushort3(x - v.x, y - v.y, z - v.z); }
	constexpr ushort3 operator*(ushort3 v) const noexcept { return ushort3(x * v.x, y * v.y, z * v.z); }
	constexpr ushort3 operator/(ushort3 v) const noexcept { return ushort3(x / v.x, y / v.y, z / v.z); }
	constexpr ushort3 operator%(ushort3 v) const noexcept { return ushort3(x % v.x, y % v.y, z % v.z); }
	constexpr ushort3 operator&(ushort3 v) const noexcept { return ushort3(x & v.x, y & v.y, z & v.z); }
	constexpr ushort3 operator|(ushort3 v) const noexcept { return ushort3(x | v.x, y | v.y, z | v.z); }
	constexpr ushort3 operator^(ushort3 v) const noexcept { return ushort3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr ushort3 operator>>(ushort3 v) const noexcept { return ushort3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr ushort3 operator<<(ushort3 v) const noexcept { return ushort3(x << v.x, y << v.y, z << v.z); }
	constexpr ushort3 operator+(uint16 n) const noexcept { return ushort3(x + n, y + n, z + n); }
	constexpr ushort3 operator-(uint16 n) const noexcept { return ushort3(x - n, y - n, z - n); }
	constexpr ushort3 operator*(uint16 n) const noexcept { return ushort3(x * n, y * n, z * n); }
	constexpr ushort3 operator/(uint16 n) const noexcept { return ushort3(x / n, y / n, z / n); }
	constexpr ushort3 operator%(uint16 n) const noexcept { return ushort3(x % n, y % n, z % n); }
	constexpr ushort3 operator&(uint16 n) const noexcept { return ushort3(x & n, y & n, z & n); }
	constexpr ushort3 operator|(uint16 n) const noexcept { return ushort3(x | n, y | n, z | n); }
	constexpr ushort3 operator^(uint16 n) const noexcept { return ushort3(x ^ n, y ^ n, z ^ n); }
	constexpr ushort3 operator>>(uint16 n) const noexcept { return ushort3(x >> n, y >> n, z >> n); }
	constexpr ushort3 operator<<(uint16 n) const noexcept { return ushort3(x << n, y << n, z << n); }
	constexpr ushort3 operator-() const noexcept { return ushort3(-x, -y, -z); }
	constexpr ushort3 operator!() const noexcept { return ushort3(!x, !y, !z); }
	ushort3 operator~() const noexcept { return ushort3(~x, ~y, ~z); }
	ushort3& operator+=(ushort3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	ushort3& operator-=(ushort3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	ushort3& operator*=(ushort3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	ushort3& operator/=(ushort3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	ushort3& operator%=(ushort3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	ushort3& operator&=(ushort3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	ushort3& operator|=(ushort3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	ushort3& operator^=(ushort3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	ushort3& operator>>=(ushort3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	ushort3& operator<<=(ushort3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	ushort3& operator+=(uint16 n) noexcept { x += n; y += n; z += n; return *this; }
	ushort3& operator-=(uint16 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	ushort3& operator*=(uint16 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	ushort3& operator/=(uint16 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	ushort3& operator%=(uint16 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	ushort3& operator&=(uint16 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	ushort3& operator|=(uint16 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	ushort3& operator^=(uint16 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	ushort3& operator>>=(uint16 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	ushort3& operator<<=(uint16 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	ushort3& operator=(uint16 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(ushort3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(ushort3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr ushort3 operator<(ushort3 v) const noexcept
	{
		return ushort3(x < v.x ? UINT16_MAX : 0, y < v.y ? UINT16_MAX : 0, z < v.z ? UINT16_MAX : 0);
	}
	constexpr ushort3 operator>(ushort3 v) const noexcept
	{
		return ushort3(x > v.x ? UINT16_MAX : 0, y > v.y ? UINT16_MAX : 0, z > v.z ? UINT16_MAX : 0);
	}
	constexpr ushort3 operator<=(ushort3 v) const noexcept
	{
		return ushort3(x <= v.x ? UINT16_MAX : 0, y <= v.y ? UINT16_MAX : 0, z <= v.z ? UINT16_MAX : 0);
	}
	constexpr ushort3 operator>=(ushort3 v) const noexcept
	{
		return ushort3(x >= v.x ? UINT16_MAX : 0, y >= v.y ? UINT16_MAX : 0, z >= v.z ? UINT16_MAX : 0);
	}
	constexpr bool operator==(uint16 n) const noexcept { return *this == ushort3(n); }
	constexpr bool operator!=(uint16 n) const noexcept { return *this != ushort3(n); }
	constexpr ushort3 operator<(uint16 n) const noexcept { return *this < ushort3(n); }
	constexpr ushort3 operator>(uint16 n) const noexcept { return *this > ushort3(n); }
	constexpr ushort3 operator<=(uint16 n) const noexcept { return *this <= ushort3(n); }
	constexpr ushort3 operator>=(uint16 n) const noexcept { return *this >= ushort3(n); }

	static const ushort3 zero, one, max;
};

inline const ushort3 ushort3::zero = ushort3(0u);
inline const ushort3 ushort3::one = ushort3(1u);
inline const ushort3 ushort3::max = ushort3(UINT16_MAX);

/***********************************************************************************************************************
 * @brief A 4-component vector of 16-bit unsigned integer values.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] ushort4
{
	uint16 x; /**< First vector component. */
	uint16 y; /**< Second vector component. */
	uint16 z; /**< Third vector component. */
	uint16 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit ushort4(uint16 xyzw = 0u) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ushort4(uint16 x, uint16 y, uint16 z, uint16 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ushort4(ushort2 xy, uint16 z, uint16 w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ushort4(uint16 x, ushort2 yz, uint16 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr ushort4(uint16 x, uint16 y, ushort2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr ushort4(ushort2 xy, ushort2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr ushort4(ushort3 xyz, uint16 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit unsigned integer values.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector component value
	 */
	constexpr ushort4(uint16 x, ushort3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	constexpr ushort4(sbyte4 xyzw) noexcept : x((uint16)xyzw.x), y((uint16)xyzw.y), z((uint16)xyzw.z), w((uint16)xyzw.w) { }
	constexpr ushort4(byte4 xyzw) noexcept : x((uint16)xyzw.x), y((uint16)xyzw.y), z((uint16)xyzw.z), w((uint16)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint16& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((uint16*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint16 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((uint16*)this)[i];
	}

	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator ushort3() const noexcept { return ushort3(x, y, z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator ushort2() const noexcept { return ushort2(x, y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr ushort4 operator+(ushort4 v) const noexcept { return ushort4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr ushort4 operator-(ushort4 v) const noexcept { return ushort4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr ushort4 operator*(ushort4 v) const noexcept { return ushort4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr ushort4 operator/(ushort4 v) const noexcept { return ushort4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr ushort4 operator%(ushort4 v) const noexcept { return ushort4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr ushort4 operator&(ushort4 v) const noexcept { return ushort4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr ushort4 operator|(ushort4 v) const noexcept { return ushort4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr ushort4 operator^(ushort4 v) const noexcept { return ushort4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr ushort4 operator>>(ushort4 v) const noexcept { return ushort4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr ushort4 operator<<(ushort4 v) const noexcept { return ushort4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr ushort4 operator+(uint16 n) const noexcept { return ushort4(x + n, y + n, z + n, w + n); }
	constexpr ushort4 operator-(uint16 n) const noexcept { return ushort4(x - n, y - n, z - n, w - n); }
	constexpr ushort4 operator*(uint16 n) const noexcept { return ushort4(x * n, y * n, z * n, w * n); }
	constexpr ushort4 operator/(uint16 n) const noexcept { return ushort4(x / n, y / n, z / n, w / n); }
	constexpr ushort4 operator%(uint16 n) const noexcept { return ushort4(x % n, y % n, z % n, w % n); }
	constexpr ushort4 operator&(uint16 n) const noexcept { return ushort4(x & n, y & n, z & n, w & n); }
	constexpr ushort4 operator|(uint16 n) const noexcept { return ushort4(x | n, y | n, z | n, w | n); }
	constexpr ushort4 operator^(uint16 n) const noexcept { return ushort4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr ushort4 operator>>(uint16 n) const noexcept { return ushort4(x >> n, y >> n, z >> n, w >> n); }
	constexpr ushort4 operator<<(uint16 n) const noexcept { return ushort4(x << n, y << n, z << n, w << n); }
	constexpr ushort4 operator-() const noexcept { return ushort4(-x, -y, -z, -w); }
	constexpr ushort4 operator!() const noexcept { return ushort4(!x, !y, !z, !w); }
	constexpr ushort4 operator~() const noexcept { return ushort4(~x, ~y, ~z, ~w); }
	ushort4& operator+=(ushort4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	ushort4& operator-=(ushort4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	ushort4& operator*=(ushort4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	ushort4& operator/=(ushort4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	ushort4& operator%=(ushort4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	ushort4& operator&=(ushort4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	ushort4& operator|=(ushort4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	ushort4& operator^=(ushort4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	ushort4& operator>>=(ushort4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	ushort4& operator<<=(ushort4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	ushort4& operator+=(uint16 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	ushort4& operator-=(uint16 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	ushort4& operator*=(uint16 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	ushort4& operator/=(uint16 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	ushort4& operator%=(uint16 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	ushort4& operator&=(uint16 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	ushort4& operator|=(uint16 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	ushort4& operator^=(uint16 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	ushort4& operator>>=(uint16 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	ushort4& operator<<=(uint16 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	ushort4& operator=(uint16 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(ushort4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(ushort4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr ushort4 operator<(ushort4 v) const noexcept
	{
		return ushort4(x < v.x ? UINT16_MAX : 0, y < v.y ? UINT16_MAX : 0, 
			z < v.z ? UINT16_MAX : 0, w < v.w ? UINT16_MAX : 0);
	}
	constexpr ushort4 operator>(ushort4 v) const noexcept
	{
		return ushort4(x > v.x ? UINT16_MAX : 0, y > v.y ? UINT16_MAX : 0, 
			z > v.z ? UINT16_MAX : 0, w > v.w ? UINT16_MAX : 0);
	}
	constexpr ushort4 operator<=(ushort4 v) const noexcept
	{
		return ushort4(x <= v.x ? UINT16_MAX : 0, y <= v.y ? UINT16_MAX : 0, 
			z <= v.z ? UINT16_MAX : 0, w <= v.w ? UINT16_MAX : 0);
	}
	constexpr ushort4 operator>=(ushort4 v) const noexcept
	{
		return ushort4(x >= v.x ? UINT16_MAX : 0, y >= v.y ? UINT16_MAX : 0, 
			z >= v.z ? UINT16_MAX : 0, w >= v.w ? UINT16_MAX : 0);
	}
	constexpr bool operator==(uint16 n) const noexcept { return *this == ushort4(n); }
	constexpr bool operator!=(uint16 n) const noexcept { return *this != ushort4(n); }
	constexpr ushort4 operator<(uint16 n) const noexcept { return *this < ushort4(n); }
	constexpr ushort4 operator>(uint16 n) const noexcept { return *this > ushort4(n); }
	constexpr ushort4 operator<=(uint16 n) const noexcept { return *this <= ushort4(n); }
	constexpr ushort4 operator>=(uint16 n) const noexcept { return *this >= ushort4(n); }

	static const ushort4 zero, one, max;
};

inline const ushort4 ushort4::zero = ushort4(0u);
inline const ushort4 ushort4::one = ushort4(1u);
inline const ushort4 ushort4::max = ushort4(UINT16_MAX);

//**********************************************************************************************************************
static constexpr ushort2 operator+(uint16 n, ushort2 v) noexcept { return ushort2(n) + v; }
static constexpr ushort2 operator-(uint16 n, ushort2 v) noexcept { return ushort2(n) - v; }
static constexpr ushort2 operator*(uint16 n, ushort2 v) noexcept { return ushort2(n) * v; }
static constexpr ushort2 operator/(uint16 n, ushort2 v) noexcept { return ushort2(n) / v; }
static constexpr ushort2 operator%(uint16 n, ushort2 v) noexcept { return ushort2(n) % v; }
static constexpr ushort2 operator&(uint16 n, ushort2 v) noexcept { return ushort2(n) & v; }
static constexpr ushort2 operator|(uint16 n, ushort2 v) noexcept { return ushort2(n) | v; }
static constexpr ushort2 operator^(uint16 n, ushort2 v) noexcept { return ushort2(n) ^ v; }
static constexpr ushort2 operator>>(uint16 n, ushort2 v) noexcept { return ushort2(n) >> v; }
static constexpr ushort2 operator<<(uint16 n, ushort2 v) noexcept { return ushort2(n) << v; }
static constexpr bool operator==(uint16 n, ushort2 v) noexcept { return ushort2(n) == v; }
static constexpr bool operator!=(uint16 n, ushort2 v) noexcept { return ushort2(n) != v; }
static constexpr ushort2 operator<(uint16 n, ushort2 v) noexcept { return ushort2(n) < v; }
static constexpr ushort2 operator>(uint16 n, ushort2 v) noexcept { return ushort2(n) > v; }
static constexpr ushort2 operator<=(uint16 n, ushort2 v) noexcept { return ushort2(n) <= v; }
static constexpr ushort2 operator>=(uint16 n, ushort2 v) noexcept { return ushort2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(ushort2 v) { return to_string(v.x) + " " + to_string(v.y); }

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (2bits)
 */
static constexpr uint16 getTrues(ushort2 v) noexcept
{
	return (v.x >> 15u) | ((v.y >> 15u) << 1u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(ushort2 v) noexcept { return (v.x & v.y) == UINT16_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(ushort2 v) noexcept { return (v.x | v.y) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(ushort2 v) noexcept { return v.x | v.y; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(ushort2 v) noexcept { return (v.x & v.y) != UINT16_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort2 equal(ushort2 a, ushort2 b) noexcept
{
	return ushort2(a.x == b.x ? UINT16_MAX : 0, a.y == b.y ? UINT16_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort2 notEqual(ushort2 a, ushort2 b) noexcept
{
	return ushort2(a.x != b.x ? UINT16_MAX : 0, a.y != b.y ? UINT16_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(ushort2 a, ushort2 b) noexcept { return *((const uint32*)&a) < *((const uint32*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr ushort2 select(ushort2 c, ushort2 t, ushort2 f) noexcept
{
	return ushort2(c.x & 0x8000u ? t.x : f.x, c.y & 0x8000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr ushort2 min(ushort2 a, ushort2 b) noexcept
{
	return ushort2(std::min(a.x, b.x), std::min(a.y, b.y));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr ushort2 max(ushort2 a, ushort2 b) noexcept
{
	return ushort2(std::max(a.x, b.x), std::max(a.y, b.y));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr ushort2 min(ushort2 a, ushort2 b, ushort2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr ushort2 max(ushort2 a, ushort2 b, ushort2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr ushort2 clamp(ushort2 v, ushort2 min, ushort2 max) noexcept
{
	return ushort2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr ushort3 operator+(uint16 n, ushort3 v) noexcept { return ushort3(n) + v; }
static constexpr ushort3 operator-(uint16 n, ushort3 v) noexcept { return ushort3(n) - v; }
static constexpr ushort3 operator*(uint16 n, ushort3 v) noexcept { return ushort3(n) * v; }
static constexpr ushort3 operator/(uint16 n, ushort3 v) noexcept { return ushort3(n) / v; }
static constexpr ushort3 operator%(uint16 n, ushort3 v) noexcept { return ushort3(n) % v; }
static constexpr ushort3 operator&(uint16 n, ushort3 v) noexcept { return ushort3(n) & v; }
static constexpr ushort3 operator|(uint16 n, ushort3 v) noexcept { return ushort3(n) | v; }
static constexpr ushort3 operator^(uint16 n, ushort3 v) noexcept { return ushort3(n) ^ v; }
static constexpr ushort3 operator>>(uint16 n, ushort3 v) noexcept { return ushort3(n) >> v; }
static constexpr ushort3 operator<<(uint16 n, ushort3 v) noexcept { return ushort3(n) << v; }
static constexpr bool operator==(uint16 n, ushort3 v) noexcept { return ushort3(n) == v; }
static constexpr bool operator!=(uint16 n, ushort3 v) noexcept { return ushort3(n) != v; }
static constexpr ushort3 operator<(uint16 n, ushort3 v) noexcept { return ushort3(n) < v; }
static constexpr ushort3 operator>(uint16 n, ushort3 v) noexcept { return ushort3(n) > v; }
static constexpr ushort3 operator<=(uint16 n, ushort3 v) noexcept { return ushort3(n) <= v; }
static constexpr ushort3 operator>=(uint16 n, ushort3 v) noexcept { return ushort3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(ushort3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (3bits)
 */
static constexpr uint16 getTrues(ushort3 v) noexcept
{
	return (v.x >> 15u) | ((v.y >> 15u) << 1u) | ((v.z >> 15u) << 2u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(ushort3 v) noexcept { return (v.x & v.y & v.z) == UINT16_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(ushort3 v) noexcept { return (v.x | v.y | v.z) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(ushort3 v) noexcept { return v.x | v.y | v.z; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(ushort3 v) noexcept { return (v.x & v.y & v.z) != UINT16_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort3 equal(ushort3 a, ushort3 b) noexcept
{
	return ushort3(a.x == b.x ? UINT16_MAX : 0, a.y == b.y ? UINT16_MAX : 0, a.z == b.z ? UINT16_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort3 notEqual(ushort3 a, ushort3 b) noexcept
{
	return ushort3(a.x != b.x ? UINT16_MAX : 0, a.y != b.y ? UINT16_MAX : 0, a.z != b.z ? UINT16_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const ushort3& a, const ushort3& b) noexcept { return memcmp(&a, &b, sizeof(ushort3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr ushort3 select(ushort3 c, ushort3 t, ushort3 f) noexcept
{
	return ushort3(c.x & 0x8000u ? t.x : f.x, c.y & 0x8000u ? t.y : f.y, c.z & 0x8000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr ushort3 min(ushort3 a, ushort3 b) noexcept
{
	return ushort3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr ushort3 max(ushort3 a, ushort3 b) noexcept
{
	return ushort3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr ushort3 min(ushort3 a, ushort3 b, ushort3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr ushort3 max(ushort3 a, ushort3 b, ushort3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr ushort3 clamp(ushort3 v, ushort3 min, ushort3 max) noexcept
{
	return ushort3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr ushort4 operator+(uint16 n, const ushort4& v) noexcept { return ushort4(n) + v; }
static constexpr ushort4 operator-(uint16 n, const ushort4& v) noexcept { return ushort4(n) - v; }
static constexpr ushort4 operator*(uint16 n, const ushort4& v) noexcept { return ushort4(n) * v; }
static constexpr ushort4 operator/(uint16 n, const ushort4& v) noexcept { return ushort4(n) / v; }
static constexpr ushort4 operator%(uint16 n, const ushort4& v) noexcept { return ushort4(n) % v; }
static constexpr ushort4 operator&(uint16 n, const ushort4& v) noexcept { return ushort4(n) & v; }
static constexpr ushort4 operator|(uint16 n, const ushort4& v) noexcept { return ushort4(n) | v; }
static constexpr ushort4 operator^(uint16 n, const ushort4& v) noexcept { return ushort4(n) ^ v; }
static constexpr ushort4 operator>>(uint16 n, const ushort4& v) noexcept { return ushort4(n) >> v; }
static constexpr ushort4 operator<<(uint16 n, const ushort4& v) noexcept { return ushort4(n) << v; }
static constexpr bool operator==(uint16 n, const ushort4& v) noexcept { return ushort4(n) == v; }
static constexpr bool operator!=(uint16 n, const ushort4& v) noexcept { return ushort4(n) != v; }
static constexpr ushort4 operator<(uint16 n, const ushort4& v) noexcept { return ushort4(n) < v; }
static constexpr ushort4 operator>(uint16 n, const ushort4& v) noexcept { return ushort4(n) > v; }
static constexpr ushort4 operator<=(uint16 n, const ushort4& v) noexcept { return ushort4(n) <= v; }
static constexpr ushort4 operator>=(uint16 n, const ushort4& v) noexcept { return ushort4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(ushort4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/***********************************************************************************************************************
 * @brief Returns mask of vector components set to true. (4bits)
 */
static constexpr uint16 getTrues(ushort4 v) noexcept
{
	return (v.x >> 15u) | ((v.y >> 15u) << 1u) | ((v.z >> 15u) << 2u) | ((v.w >> 15u) << 3u);
}
/**
 * @brief Returns true if all vector component bits are set true.
 */
static constexpr bool areAllTrue(ushort4 v) noexcept { return (v.x & v.y & v.z & v.w) == UINT16_MAX; }
/**
 * @brief Returns false if all vector component bits are set false.
 */
static constexpr bool areAllFalse(ushort4 v) noexcept { return (v.x | v.y | v.z | v.w) == 0; }
/**
 * @brief Returns true if any of vector component bits is set true.
 */
static constexpr bool areAnyTrue(ushort4 v) noexcept { return v.x | v.y | v.z | v.w; }
/**
 * @brief Returns false if any of vector component bits is set false.
 */
static constexpr bool areAnyFalse(ushort4 v) noexcept { return (v.x & v.y & v.z & v.w) != UINT16_MAX; }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort4 equal(ushort4 a, ushort4 b) noexcept
{
	return ushort4(a.x == b.x ? UINT16_MAX : 0, a.y == b.y ? UINT16_MAX : 0, 
		a.z == b.z ? UINT16_MAX : 0, a.w == b.w ? UINT16_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort4 notEqual(ushort4 a, ushort4 b) noexcept
{
	return ushort4(a.x != b.x ? UINT16_MAX : 0, a.y != b.y ? UINT16_MAX : 0, 
		a.z != b.z ? UINT16_MAX : 0, a.w != b.w ? UINT16_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const ushort4& a, const ushort4& b) noexcept
{
	return *((const uint64*)&a) < *((const uint64*)&b);
}

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr ushort4 select(ushort4 c, ushort4 t, ushort4 f) noexcept
{
	return ushort4(c.x & 0x8000u ? t.x : f.x, c.y & 0x8000u ? t.y : f.y, 
		c.z & 0x8000u ? t.z : f.z, c.w & 0x8000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr ushort4 min(ushort4 a, ushort4 b) noexcept
{
	return ushort4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr ushort4 max(ushort4 a, ushort4 b) noexcept
{
	return ushort4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr ushort4 min(ushort4 a, ushort4 b, ushort4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr ushort4 max(ushort4 a, ushort4 b, ushort4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr ushort4 clamp(ushort4 v, ushort4 min, ushort4 max) noexcept
{
	return ushort4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math