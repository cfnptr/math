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
 * @brief Common signed integer 8 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/byte.hpp"

namespace math
{

/**
 * @brief A 2-component vector of 8-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] sbyte2
{
	int8 x; /**< First vector component. */
	int8 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 8-bit signed integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit sbyte2(int8 xy = 0) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 8-bit signed integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr sbyte2(int8 x, int8 y) noexcept : x(x), y(y) { }

	constexpr sbyte2(byte4 xy) noexcept : x((int8)xy.x), y((int8)xy.y) { }
	constexpr sbyte2(byte3 xy) noexcept : x((int8)xy.x), y((int8)xy.y) { }
	constexpr sbyte2(byte2 xy) noexcept : x((int8)xy.x), y((int8)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int8& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((int8*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int8 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((int8*)this)[i];
	}

	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr sbyte2 operator+(sbyte2 v) const noexcept { return sbyte2(x + v.x, y + v.y); }
	constexpr sbyte2 operator-(sbyte2 v) const noexcept { return sbyte2(x - v.x, y - v.y); }
	constexpr sbyte2 operator*(sbyte2 v) const noexcept { return sbyte2(x * v.x, y * v.y); }
	constexpr sbyte2 operator/(sbyte2 v) const noexcept { return sbyte2(x / v.x, y / v.y); }
	constexpr sbyte2 operator%(sbyte2 v) const noexcept { return sbyte2(x % v.x, y % v.y); }
	constexpr sbyte2 operator&(sbyte2 v) const noexcept { return sbyte2(x & v.x, y & v.y); }
	constexpr sbyte2 operator|(sbyte2 v) const noexcept { return sbyte2(x | v.x, y | v.y); }
	constexpr sbyte2 operator^(sbyte2 v) const noexcept { return sbyte2(x ^ v.x, y ^ v.y); }
	constexpr sbyte2 operator>>(sbyte2 v) const noexcept { return sbyte2(x >> v.x, y >> v.y); }
	constexpr sbyte2 operator<<(sbyte2 v) const noexcept { return sbyte2(x << v.x, y << v.y); }
	constexpr sbyte2 operator+(int8 n) const noexcept { return sbyte2(x + n, y + n); }
	constexpr sbyte2 operator-(int8 n) const noexcept { return sbyte2(x - n, y - n); }
	constexpr sbyte2 operator*(int8 n) const noexcept { return sbyte2(x * n, y * n); }
	constexpr sbyte2 operator/(int8 n) const noexcept { return sbyte2(x / n, y / n); }
	constexpr sbyte2 operator%(int8 n) const noexcept { return sbyte2(x % n, y % n); }
	constexpr sbyte2 operator&(int8 n) const noexcept { return sbyte2(x & n, y & n); }
	constexpr sbyte2 operator|(int8 n) const noexcept { return sbyte2(x | n, y | n); }
	constexpr sbyte2 operator^(int8 n) const noexcept { return sbyte2(x ^ n, y ^ n); }
	constexpr sbyte2 operator>>(int8 n) const noexcept { return sbyte2(x >> n, y >> n); }
	constexpr sbyte2 operator<<(int8 n) const noexcept { return sbyte2(x << n, y << n); }
	constexpr sbyte2 operator-() const noexcept { return sbyte2(-x, -y); }
	constexpr sbyte2 operator!() const noexcept { return sbyte2(!x, !y); }
	constexpr sbyte2 operator~() const noexcept { return sbyte2(~x, ~y); }
	sbyte2& operator+=(sbyte2 v) noexcept { x += v.x; y += v.y; return *this; }
	sbyte2& operator-=(sbyte2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	sbyte2& operator*=(sbyte2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	sbyte2& operator/=(sbyte2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	sbyte2& operator%=(sbyte2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	sbyte2& operator&=(sbyte2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	sbyte2& operator|=(sbyte2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	sbyte2& operator^=(sbyte2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	sbyte2& operator>>=(sbyte2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	sbyte2& operator<<=(sbyte2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	sbyte2& operator+=(int8 n) noexcept { x += n; y += n; return *this; }
	sbyte2& operator-=(int8 n) noexcept { x -= n; y -= n; return *this; }
	sbyte2& operator*=(int8 n) noexcept { x *= n; y *= n; return *this; }
	sbyte2& operator/=(int8 n) noexcept { x /= n; y /= n; return *this; }
	sbyte2& operator%=(int8 n) noexcept { x %= n; y %= n; return *this; }
	sbyte2& operator&=(int8 n) noexcept { x &= n; y &= n; return *this; }
	sbyte2& operator|=(int8 n) noexcept { x |= n; y |= n; return *this; }
	sbyte2& operator^=(int8 n) noexcept { x ^= n; y ^= n; return *this; }
	sbyte2& operator>>=(int8 n) noexcept { x >>= n; y >>= n; return *this; }
	sbyte2& operator<<=(int8 n) noexcept { x <<= n; y <<= n; return *this; }
	sbyte2& operator=(int8 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(sbyte2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(sbyte2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr byte2 operator<(sbyte2 v) const noexcept
	{
		return byte2(x < v.x ? UINT8_MAX : 0, y < v.y ? UINT8_MAX : 0);
	}
	constexpr byte2 operator>(sbyte2 v) const noexcept
	{
		return byte2(x > v.x ? UINT8_MAX : 0, y > v.y ? UINT8_MAX : 0);
	}
	constexpr byte2 operator<=(sbyte2 v) const noexcept
	{
		return byte2(x <= v.x ? UINT8_MAX : 0, y <= v.y ? UINT8_MAX : 0);
	}
	constexpr byte2 operator>=(sbyte2 v) const noexcept
	{
		return byte2(x >= v.x ? UINT8_MAX : 0, y >= v.y ? UINT8_MAX : 0);
	}
	constexpr bool operator==(int8 n) const noexcept { return *this == sbyte2(n); }
	constexpr bool operator!=(int8 n) const noexcept { return *this != sbyte2(n); }
	constexpr byte2 operator<(int8 n) const noexcept { return *this < sbyte2(n); }
	constexpr byte2 operator>(int8 n) const noexcept { return *this > sbyte2(n); }
	constexpr byte2 operator<=(int8 n) const noexcept { return *this <= sbyte2(n); }
	constexpr byte2 operator>=(int8 n) const noexcept { return *this >= sbyte2(n); }

	static const sbyte2 zero, one, minusOne, min, max, left, right, bottom, top;
};

inline const sbyte2 sbyte2::zero = sbyte2(0);
inline const sbyte2 sbyte2::one = sbyte2(1);
inline const sbyte2 sbyte2::minusOne = sbyte2(-1);
inline const sbyte2 sbyte2::min = sbyte2(INT8_MIN);
inline const sbyte2 sbyte2::max = sbyte2(INT8_MAX);
inline const sbyte2 sbyte2::left = sbyte2(-1, 0);
inline const sbyte2 sbyte2::right = sbyte2(1, 0);
inline const sbyte2 sbyte2::bottom = sbyte2(0, -1);
inline const sbyte2 sbyte2::top = sbyte2(0, 1);

/***********************************************************************************************************************
 * @brief A 3-component vector of 8-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] sbyte3
{
	int8 x; /**< First vector component. */
	int8 y; /**< Second vector component. */
	int8 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 8-bit signed integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit sbyte3(int8 xyz = 0) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 8-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr sbyte3(int8 x, int8 y, int8 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 8-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr sbyte3(sbyte2 xy, int8 z) noexcept : x(xy.x), y(xy.y), z(x) { }
	/**
	 * @brief Creates a new 3-component vector of 8-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr sbyte3(int8 x, sbyte2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	constexpr sbyte3(byte4 xyz) noexcept : x((int8)xyz.x), y((int8)xyz.y), z((int8)xyz.z) { }
	constexpr sbyte3(byte3 xyz) noexcept : x((int8)xyz.x), y((int8)xyz.y), z((int8)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int8& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((int8*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int8 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((int8*)this)[i];
	}

	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2(x, y); }

	//******************************************************************************************************************
	constexpr sbyte3 operator+(sbyte3 v) const noexcept { return sbyte3(x + v.x, y + v.y, z + v.z); }
	constexpr sbyte3 operator-(sbyte3 v) const noexcept { return sbyte3(x - v.x, y - v.y, z - v.z); }
	constexpr sbyte3 operator*(sbyte3 v) const noexcept { return sbyte3(x * v.x, y * v.y, z * v.z); }
	constexpr sbyte3 operator/(sbyte3 v) const noexcept { return sbyte3(x / v.x, y / v.y, z / v.z); }
	constexpr sbyte3 operator%(sbyte3 v) const noexcept { return sbyte3(x % v.x, y % v.y, z % v.z); }
	constexpr sbyte3 operator&(sbyte3 v) const noexcept { return sbyte3(x & v.x, y & v.y, z & v.z); }
	constexpr sbyte3 operator|(sbyte3 v) const noexcept { return sbyte3(x | v.x, y | v.y, z | v.z); }
	constexpr sbyte3 operator^(sbyte3 v) const noexcept { return sbyte3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr sbyte3 operator>>(sbyte3 v) const noexcept { return sbyte3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr sbyte3 operator<<(sbyte3 v) const noexcept { return sbyte3(x << v.x, y << v.y, z << v.z); }
	constexpr sbyte3 operator+(int8 n) const noexcept { return sbyte3(x + n, y + n, z + n); }
	constexpr sbyte3 operator-(int8 n) const noexcept { return sbyte3(x - n, y - n, z - n); }
	constexpr sbyte3 operator*(int8 n) const noexcept { return sbyte3(x * n, y * n, z * n); }
	constexpr sbyte3 operator/(int8 n) const noexcept { return sbyte3(x / n, y / n, z / n); }
	constexpr sbyte3 operator%(int8 n) const noexcept { return sbyte3(x % n, y % n, z % n); }
	constexpr sbyte3 operator&(int8 n) const noexcept { return sbyte3(x & n, y & n, z & n); }
	constexpr sbyte3 operator|(int8 n) const noexcept { return sbyte3(x | n, y | n, z | n); }
	constexpr sbyte3 operator^(int8 n) const noexcept { return sbyte3(x ^ n, y ^ n, z ^ n); }
	constexpr sbyte3 operator>>(int8 n) const noexcept { return sbyte3(x >> n, y >> n, z >> n); }
	constexpr sbyte3 operator<<(int8 n) const noexcept { return sbyte3(x << n, y << n, z << n); }
	constexpr sbyte3 operator-() const noexcept { return sbyte3(-x, -y, -z); }
	constexpr sbyte3 operator!() const noexcept { return sbyte3(!x, !y, !z); }
	constexpr sbyte3 operator~() const noexcept { return sbyte3(~x, ~y, ~z); }
	sbyte3& operator+=(sbyte3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	sbyte3& operator-=(sbyte3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	sbyte3& operator*=(sbyte3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	sbyte3& operator/=(sbyte3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	sbyte3& operator%=(sbyte3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	sbyte3& operator&=(sbyte3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	sbyte3& operator|=(sbyte3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	sbyte3& operator^=(sbyte3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	sbyte3& operator>>=(sbyte3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	sbyte3& operator<<=(sbyte3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	sbyte3& operator+=(int8 n) noexcept { x += n; y += n; z += n; return *this; }
	sbyte3& operator-=(int8 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	sbyte3& operator*=(int8 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	sbyte3& operator/=(int8 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	sbyte3& operator%=(int8 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	sbyte3& operator&=(int8 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	sbyte3& operator|=(int8 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	sbyte3& operator^=(int8 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	sbyte3& operator>>=(int8 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	sbyte3& operator<<=(int8 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	sbyte3& operator=(int8 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(sbyte3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(sbyte3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr byte3 operator<(sbyte3 v) const noexcept
	{
		return byte3(x < v.x ? UINT8_MAX : 0, y < v.y ? UINT8_MAX : 0, z < v.z ? UINT8_MAX : 0);
	}
	constexpr byte3 operator>(sbyte3 v) const noexcept
	{
		return byte3(x > v.x ? UINT8_MAX : 0, y > v.y ? UINT8_MAX : 0, z > v.z ? UINT8_MAX : 0);
	}
	constexpr byte3 operator<=(sbyte3 v) const noexcept
	{
		return byte3(x <= v.x ? UINT8_MAX : 0, y <= v.y ? UINT8_MAX : 0, z <= v.z ? UINT8_MAX : 0);
	}
	constexpr byte3 operator>=(sbyte3 v) const noexcept
	{
		return byte3(x >= v.x ? UINT8_MAX : 0, y >= v.y ? UINT8_MAX : 0, z >= v.z ? UINT8_MAX : 0);
	}
	constexpr bool operator==(int8 n) const noexcept { return *this == sbyte3(n); }
	constexpr bool operator!=(int8 n) const noexcept { return *this != sbyte3(n); }
	constexpr byte3 operator<(int8 n) const noexcept { return *this < sbyte3(n); }
	constexpr byte3 operator>(int8 n) const noexcept { return *this > sbyte3(n); }
	constexpr byte3 operator<=(int8 n) const noexcept { return *this <= sbyte3(n); }
	constexpr byte3 operator>=(int8 n) const noexcept { return *this >= sbyte3(n); }

	static const sbyte3 zero, one, minusOne, min, max, left, right, bottom, top, back, front;
};

inline const sbyte3 sbyte3::zero = sbyte3(0);
inline const sbyte3 sbyte3::one = sbyte3(1);
inline const sbyte3 sbyte3::minusOne = sbyte3(-1);
inline const sbyte3 sbyte3::min = sbyte3(INT8_MIN);
inline const sbyte3 sbyte3::max = sbyte3(INT8_MAX);
inline const sbyte3 sbyte3::left = sbyte3(-1, 0, 0);
inline const sbyte3 sbyte3::right = sbyte3(1, 0, 0);
inline const sbyte3 sbyte3::bottom = sbyte3(0, -1, 0);
inline const sbyte3 sbyte3::top = sbyte3(0, 1, 0);
inline const sbyte3 sbyte3::back = sbyte3(0, 0, -1);
inline const sbyte3 sbyte3::front = sbyte3(0, 0, 1);

/***********************************************************************************************************************
 * @brief A 4-component vector of 8-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] sbyte4
{
	int8 x; /**< First vector component. */
	int8 y; /**< Second vector component. */
	int8 z; /**< Third vector component. */
	int8 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit sbyte4(int8 xyzw = 0) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr sbyte4(int8 x, int8 y, int8 z, int8 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr sbyte4(sbyte2 xy, int8 z, int8 w) noexcept: x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr sbyte4(int8 x, sbyte2 yz, int8 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr sbyte4(int8 x, int8 y, sbyte2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr sbyte4(sbyte2 xy, sbyte2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr sbyte4(sbyte3 xyz, int8 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 8-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector component value
	 */
	constexpr sbyte4(int8 x, sbyte3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	constexpr sbyte4(byte4 xyzw) noexcept : x((int8)xyzw.x), y((int8)xyzw.y), z((int8)xyzw.z), w((int8)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int8& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((int8*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int8 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((int8*)this)[i];
	}

	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3(x, y, z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2(x, y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr sbyte4 operator+(sbyte4 v) const noexcept { return sbyte4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr sbyte4 operator-(sbyte4 v) const noexcept { return sbyte4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr sbyte4 operator*(sbyte4 v) const noexcept { return sbyte4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr sbyte4 operator/(sbyte4 v) const noexcept { return sbyte4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr sbyte4 operator%(sbyte4 v) const noexcept { return sbyte4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr sbyte4 operator&(sbyte4 v) const noexcept { return sbyte4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr sbyte4 operator|(sbyte4 v) const noexcept { return sbyte4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr sbyte4 operator^(sbyte4 v) const noexcept { return sbyte4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr sbyte4 operator>>(sbyte4 v) const noexcept { return sbyte4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr sbyte4 operator<<(sbyte4 v) const noexcept { return sbyte4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr sbyte4 operator+(int8 n) const noexcept { return sbyte4(x + n, y + n, z + n, w + n); }
	constexpr sbyte4 operator-(int8 n) const noexcept { return sbyte4(x - n, y - n, z - n, w - n); }
	constexpr sbyte4 operator*(int8 n) const noexcept { return sbyte4(x * n, y * n, z * n, w * n); }
	constexpr sbyte4 operator/(int8 n) const noexcept { return sbyte4(x / n, y / n, z / n, w / n); }
	constexpr sbyte4 operator%(int8 n) const noexcept { return sbyte4(x % n, y % n, z % n, w % n); }
	constexpr sbyte4 operator&(int8 n) const noexcept { return sbyte4(x & n, y & n, z & n, w & n); }
	constexpr sbyte4 operator|(int8 n) const noexcept { return sbyte4(x | n, y | n, z | n, w | n); }
	constexpr sbyte4 operator^(int8 n) const noexcept { return sbyte4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr sbyte4 operator>>(int8 n) const noexcept { return sbyte4(x >> n, y >> n, z >> n, w >> n); }
	constexpr sbyte4 operator<<(int8 n) const noexcept { return sbyte4(x << n, y << n, z << n, w << n); }
	constexpr sbyte4 operator-() const noexcept { return sbyte4(-x, -y, -z, -w); }
	constexpr sbyte4 operator!() const noexcept { return sbyte4(!x, !y, !z, !w); }
	constexpr sbyte4 operator~() const noexcept { return sbyte4(~x, ~y, ~z, ~w); }
	sbyte4& operator+=(sbyte4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	sbyte4& operator-=(sbyte4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	sbyte4& operator*=(sbyte4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	sbyte4& operator/=(sbyte4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	sbyte4& operator%=(sbyte4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	sbyte4& operator&=(sbyte4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	sbyte4& operator|=(sbyte4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	sbyte4& operator^=(sbyte4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	sbyte4& operator>>=(sbyte4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	sbyte4& operator<<=(sbyte4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	sbyte4& operator+=(int8 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	sbyte4& operator-=(int8 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	sbyte4& operator*=(int8 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	sbyte4& operator/=(int8 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	sbyte4& operator%=(int8 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	sbyte4& operator&=(int8 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	sbyte4& operator|=(int8 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	sbyte4& operator^=(int8 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	sbyte4& operator>>=(int8 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	sbyte4& operator<<=(int8 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	sbyte4& operator=(int8 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(sbyte4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(sbyte4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr byte4 operator<(sbyte4 v) const noexcept
	{
		return byte4(x < v.x ? UINT8_MAX : 0, y < v.y ? UINT8_MAX : 0, 
			z < v.z ? UINT8_MAX : 0, w < v.w ? UINT8_MAX : 0);
	}
	constexpr byte4 operator>(sbyte4 v) const noexcept
	{
		return byte4(x > v.x ? UINT8_MAX : 0, y > v.y ? UINT8_MAX : 0, 
			z > v.z ? UINT8_MAX : 0, w > v.w ? UINT8_MAX : 0);
	}
	constexpr byte4 operator<=(sbyte4 v) const noexcept
	{
		return byte4(x <= v.x ? UINT8_MAX : 0, y <= v.y ? UINT8_MAX : 0, 
			z <= v.z ? UINT8_MAX : 0, w <= v.w ? UINT8_MAX : 0);
	}
	constexpr byte4 operator>=(sbyte4 v) const noexcept
	{
		return byte4(x >= v.x ? UINT8_MAX : 0, y >= v.y ? UINT8_MAX : 0, 
			z >= v.z ? UINT8_MAX : 0, w >= v.w ? UINT8_MAX : 0);
	}
	constexpr bool operator==(int8 n) const noexcept { return *this == sbyte4(n); }
	constexpr bool operator!=(int8 n) const noexcept { return *this != sbyte4(n); }
	constexpr byte4 operator<(int8 n) const noexcept { return *this < sbyte4(n); }
	constexpr byte4 operator>(int8 n) const noexcept { return *this > sbyte4(n); }
	constexpr byte4 operator<=(int8 n) const noexcept { return *this <= sbyte4(n); }
	constexpr byte4 operator>=(int8 n) const noexcept { return *this >= sbyte4(n); }

	static const sbyte4 zero, one, minusOne, min, max;
};

inline const sbyte4 sbyte4::zero = sbyte4(0);
inline const sbyte4 sbyte4::one = sbyte4(1);
inline const sbyte4 sbyte4::minusOne = sbyte4(-1);
inline const sbyte4 sbyte4::min = sbyte4(INT8_MIN);
inline const sbyte4 sbyte4::max = sbyte4(INT8_MAX);

//**********************************************************************************************************************
static constexpr sbyte2 operator+(int8 n, sbyte2 v) noexcept { return sbyte2(n) + v; }
static constexpr sbyte2 operator-(int8 n, sbyte2 v) noexcept { return sbyte2(n) - v; }
static constexpr sbyte2 operator*(int8 n, sbyte2 v) noexcept { return sbyte2(n) * v; }
static constexpr sbyte2 operator/(int8 n, sbyte2 v) noexcept { return sbyte2(n) / v; }
static constexpr sbyte2 operator%(int8 n, sbyte2 v) noexcept { return sbyte2(n) % v; }
static constexpr sbyte2 operator&(int8 n, sbyte2 v) noexcept { return sbyte2(n) & v; }
static constexpr sbyte2 operator|(int8 n, sbyte2 v) noexcept { return sbyte2(n) | v; }
static constexpr sbyte2 operator^(int8 n, sbyte2 v) noexcept { return sbyte2(n) ^ v; }
static constexpr sbyte2 operator>>(int8 n, sbyte2 v) noexcept { return sbyte2(n) >> v; }
static constexpr sbyte2 operator<<(int8 n, sbyte2 v) noexcept { return sbyte2(n) << v; }
static constexpr bool operator==(int8 n, sbyte2 v) noexcept { return sbyte2(n) == v; }
static constexpr bool operator!=(int8 n, sbyte2 v) noexcept { return sbyte2(n) != v; }
static constexpr byte2 operator<(int8 n, sbyte2 v) noexcept { return sbyte2(n) < v; }
static constexpr byte2 operator>(int8 n, sbyte2 v) noexcept { return sbyte2(n) > v; }
static constexpr byte2 operator<=(int8 n, sbyte2 v) noexcept { return sbyte2(n) <= v; }
static constexpr byte2 operator>=(int8 n, sbyte2 v) noexcept { return sbyte2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(sbyte2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte2 equal(sbyte2 a, sbyte2 b) noexcept
{
	return byte2(a.x == b.x ? UINT8_MAX : 0, a.y == b.y ? UINT8_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte2 notEqual(sbyte2 a, sbyte2 b) noexcept
{
	return byte2(a.x != b.x ? UINT8_MAX : 0, a.y != b.y ? UINT8_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(sbyte2 a, sbyte2 b) noexcept { return *((const int16*)&a) < *((const int16*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr sbyte2 select(byte2 c, sbyte2 t, sbyte2 f) noexcept
{
	return sbyte2(c.x & 0x80u ? t.x : f.x, c.y & 0x80u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr sbyte2 min(sbyte2 a, sbyte2 b) noexcept { return sbyte2(std::min(a.x, b.x), std::min(a.y, b.y)); }
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr sbyte2 max(sbyte2 a, sbyte2 b) noexcept { return sbyte2(std::max(a.x, b.x), std::max(a.y, b.y)); }
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr sbyte2 min(sbyte2 a, sbyte2 b, sbyte2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr sbyte2 max(sbyte2 a, sbyte2 b, sbyte2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr sbyte2 clamp(sbyte2 v, sbyte2 min, sbyte2 max) noexcept
{
	return sbyte2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr sbyte3 operator+(int8 n, sbyte3 v) noexcept { return sbyte3(n) + v; }
static constexpr sbyte3 operator-(int8 n, sbyte3 v) noexcept { return sbyte3(n) - v; }
static constexpr sbyte3 operator*(int8 n, sbyte3 v) noexcept { return sbyte3(n) * v; }
static constexpr sbyte3 operator/(int8 n, sbyte3 v) noexcept { return sbyte3(n) / v; }
static constexpr sbyte3 operator%(int8 n, sbyte3 v) noexcept { return sbyte3(n) % v; }
static constexpr sbyte3 operator&(int8 n, sbyte3 v) noexcept { return sbyte3(n) & v; }
static constexpr sbyte3 operator|(int8 n, sbyte3 v) noexcept { return sbyte3(n) | v; }
static constexpr sbyte3 operator^(int8 n, sbyte3 v) noexcept { return sbyte3(n) ^ v; }
static constexpr sbyte3 operator>>(int8 n, sbyte3 v) noexcept { return sbyte3(n) >> v; }
static constexpr sbyte3 operator<<(int8 n, sbyte3 v) noexcept { return sbyte3(n) << v; }
static constexpr bool operator==(int8 n, sbyte3 v) noexcept { return sbyte3(n) == v; }
static constexpr bool operator!=(int8 n, sbyte3 v) noexcept { return sbyte3(n) != v; }
static constexpr byte3 operator<(int8 n, sbyte3 v) noexcept { return sbyte3(n) < v; }
static constexpr byte3 operator>(int8 n, sbyte3 v) noexcept { return sbyte3(n) > v; }
static constexpr byte3 operator<=(int8 n, sbyte3 v) noexcept { return sbyte3(n) <= v; }
static constexpr byte3 operator>=(int8 n, sbyte3 v) noexcept { return sbyte3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(sbyte3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte3 equal(sbyte3 a, sbyte3 b) noexcept
{
	return byte3(a.x == b.x ? UINT8_MAX : 0, a.y == b.y ? UINT8_MAX : 0, a.z == b.z ? UINT8_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte3 notEqual(sbyte3 a, sbyte3 b) noexcept
{
	return byte3(a.x != b.x ? UINT8_MAX : 0, a.y != b.y ? UINT8_MAX : 0, a.z != b.z ? UINT8_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const sbyte3& a, const sbyte3& b) noexcept { return memcmp(&a, &b, sizeof(sbyte3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr sbyte3 select(byte3 c, sbyte3 t, sbyte3 f) noexcept
{
	return sbyte3(c.x & 0x80u ? t.x : f.x, c.y & 0x80u ? t.y : f.y, c.z & 0x80u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr sbyte3 min(sbyte3 a, sbyte3 b) noexcept
{
	return sbyte3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr sbyte3 max(sbyte3 a, sbyte3 b) noexcept
{
	return sbyte3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr sbyte3 min(sbyte3 a, sbyte3 b, sbyte3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr sbyte3 max(sbyte3 a, sbyte3 b, sbyte3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr sbyte3 clamp(sbyte3 v, sbyte3 min, sbyte3 max) noexcept
{
	return sbyte3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr sbyte4 operator+(int8 n, sbyte4 v) noexcept { return sbyte4(n) + v; }
static constexpr sbyte4 operator-(int8 n, sbyte4 v) noexcept { return sbyte4(n) - v; }
static constexpr sbyte4 operator*(int8 n, sbyte4 v) noexcept { return sbyte4(n) * v; }
static constexpr sbyte4 operator/(int8 n, sbyte4 v) noexcept { return sbyte4(n) / v; }
static constexpr sbyte4 operator%(int8 n, sbyte4 v) noexcept { return sbyte4(n) % v; }
static constexpr sbyte4 operator&(int8 n, sbyte4 v) noexcept { return sbyte4(n) & v; }
static constexpr sbyte4 operator|(int8 n, sbyte4 v) noexcept { return sbyte4(n) | v; }
static constexpr sbyte4 operator^(int8 n, sbyte4 v) noexcept { return sbyte4(n) ^ v; }
static constexpr sbyte4 operator>>(int8 n, sbyte4 v) noexcept { return sbyte4(n) >> v; }
static constexpr sbyte4 operator<<(int8 n, sbyte4 v) noexcept { return sbyte4(n) << v; }
static constexpr bool operator==(int8 n, sbyte4 v) noexcept { return sbyte4(n) == v; }
static constexpr bool operator!=(int8 n, sbyte4 v) noexcept { return sbyte4(n) != v; }
static constexpr byte4 operator<(int8 n, sbyte4 v) noexcept { return sbyte4(n) < v; }
static constexpr byte4 operator>(int8 n, sbyte4 v) noexcept { return sbyte4(n) > v; }
static constexpr byte4 operator<=(int8 n, sbyte4 v) noexcept { return sbyte4(n) <= v; }
static constexpr byte4 operator>=(int8 n, sbyte4 v) noexcept { return sbyte4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(sbyte4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static byte4 equal(sbyte4 a, sbyte4 b) noexcept
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
static byte4 notEqual(sbyte4 a, sbyte4 b) noexcept
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
static bool isBinaryLess(const sbyte4& a, const sbyte4& b) noexcept { return *((const int32*)&a) < *((const int32*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr sbyte4 select(byte4 c, sbyte4 t, sbyte4 f) noexcept
{
	return sbyte4(c.x & 0x80u ? t.x : f.x, c.y & 0x80u ? t.y : f.y, c.z & 0x80u ? t.z : f.z, c.w & 0x80u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr sbyte4 min(sbyte4 a, sbyte4 b) noexcept
{
	return sbyte4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr sbyte4 max(sbyte4 a, sbyte4 b) noexcept
{
	return sbyte4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr sbyte4 min(sbyte4 a, sbyte4 b, sbyte4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr sbyte4 max(sbyte4 a, sbyte4 b, sbyte4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr sbyte4 clamp(sbyte4 v, sbyte4 min, sbyte4 max) noexcept
{
	return sbyte4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math