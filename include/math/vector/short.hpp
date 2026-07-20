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
 * @brief Common signed integer 16 bit vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/ushort.hpp"

namespace math
{

/**
 * @brief A 2-component vector of 16-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] short2
{
	int16 x; /**< First vector component. */
	int16 y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 16-bit signed integer values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit short2(int16 xy = 0) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 16-bit signed integer values.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr short2(int16 x, int16 y) noexcept : x(x), y(y) { }

	constexpr short2(ushort4 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(ushort3 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(ushort2 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(sbyte4 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(sbyte3 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(sbyte2 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(byte4 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(byte3 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }
	constexpr short2(byte2 xy) noexcept : x((int16)xy.x), y((int16)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int16& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((int16*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int16 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((int16*)this)[i];
	}

	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr short2 operator+(short2 v) const noexcept { return short2(x + v.x, y + v.y); }
	constexpr short2 operator-(short2 v) const noexcept { return short2(x - v.x, y - v.y); }
	constexpr short2 operator*(short2 v) const noexcept { return short2(x * v.x, y * v.y); }
	constexpr short2 operator/(short2 v) const noexcept { return short2(x / v.x, y / v.y); }
	constexpr short2 operator%(short2 v) const noexcept { return short2(x % v.x, y % v.y); }
	constexpr short2 operator&(short2 v) const noexcept { return short2(x & v.x, y & v.y); }
	constexpr short2 operator|(short2 v) const noexcept { return short2(x | v.x, y | v.y); }
	constexpr short2 operator^(short2 v) const noexcept { return short2(x ^ v.x, y ^ v.y); }
	constexpr short2 operator>>(short2 v) const noexcept { return short2(x >> v.x, y >> v.y); }
	constexpr short2 operator<<(short2 v) const noexcept { return short2(x << v.x, y << v.y); }
	constexpr short2 operator+(int16 n) const noexcept { return short2(x + n, y + n); }
	constexpr short2 operator-(int16 n) const noexcept { return short2(x - n, y - n); }
	constexpr short2 operator*(int16 n) const noexcept { return short2(x * n, y * n); }
	constexpr short2 operator/(int16 n) const noexcept { return short2(x / n, y / n); }
	constexpr short2 operator%(int16 n) const noexcept { return short2(x % n, y % n); }
	constexpr short2 operator&(int16 n) const noexcept { return short2(x & n, y & n); }
	constexpr short2 operator|(int16 n) const noexcept { return short2(x | n, y | n); }
	constexpr short2 operator^(int16 n) const noexcept { return short2(x ^ n, y ^ n); }
	constexpr short2 operator>>(int16 n) const noexcept { return short2(x >> n, y >> n); }
	constexpr short2 operator<<(int16 n) const noexcept { return short2(x << n, y << n); }
	constexpr short2 operator-() const noexcept { return short2(-x, -y); }
	constexpr short2 operator!() const noexcept { return short2(!x, !y); }
	constexpr short2 operator~() const noexcept { return short2(~x, ~y); }
	short2& operator+=(short2 v) noexcept { x += v.x; y += v.y; return *this; }
	short2& operator-=(short2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	short2& operator*=(short2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	short2& operator/=(short2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	short2& operator%=(short2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	short2& operator&=(short2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	short2& operator|=(short2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	short2& operator^=(short2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	short2& operator>>=(short2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	short2& operator<<=(short2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	short2& operator+=(int16 n) noexcept { x += n; y += n; return *this; }
	short2& operator-=(int16 n) noexcept { x -= n; y -= n; return *this; }
	short2& operator*=(int16 n) noexcept { x *= n; y *= n; return *this; }
	short2& operator/=(int16 n) noexcept { x /= n; y /= n; return *this; }
	short2& operator%=(int16 n) noexcept { x %= n; y %= n; return *this; }
	short2& operator&=(int16 n) noexcept { x &= n; y &= n; return *this; }
	short2& operator|=(int16 n) noexcept { x |= n; y |= n; return *this; }
	short2& operator^=(int16 n) noexcept { x ^= n; y ^= n; return *this; }
	short2& operator>>=(int16 n) noexcept { x >>= n; y >>= n; return *this; }
	short2& operator<<=(int16 n) noexcept { x <<= n; y <<= n; return *this; }
	short2& operator=(int16 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(short2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(short2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr ushort2 operator<(short2 v) const noexcept
	{
		return ushort2(x < v.x ? UINT16_MAX : 0, y < v.y ? UINT16_MAX : 0);
	}
	constexpr ushort2 operator>(short2 v) const noexcept
	{
		return ushort2(x > v.x ? UINT16_MAX : 0, y > v.y ? UINT16_MAX : 0);
	}
	constexpr ushort2 operator<=(short2 v) const noexcept
	{
		return ushort2(x <= v.x ? UINT16_MAX : 0, y <= v.y ? UINT16_MAX : 0);
	}
	constexpr ushort2 operator>=(short2 v) const noexcept
	{
		return ushort2(x >= v.x ? UINT16_MAX : 0, y >= v.y ? UINT16_MAX : 0);
	}
	constexpr bool operator==(int16 n) const noexcept { return *this == short2(n); }
	constexpr bool operator!=(int16 n) const noexcept { return *this != short2(n); }
	constexpr ushort2 operator<(int16 n) const noexcept { return *this < short2(n); }
	constexpr ushort2 operator>(int16 n) const noexcept { return *this > short2(n); }
	constexpr ushort2 operator<=(int16 n) const noexcept { return *this <= short2(n); }
	constexpr ushort2 operator>=(int16 n) const noexcept { return *this >= short2(n); }

	static const short2 zero, one, minusOne, min, max, left, right, bottom, top;
};

inline const short2 short2::zero = short2(0);
inline const short2 short2::one = short2(1);
inline const short2 short2::minusOne = short2(-1);
inline const short2 short2::min = short2(INT16_MIN);
inline const short2 short2::max = short2(INT16_MAX);
inline const short2 short2::left = short2(-1, 0);
inline const short2 short2::right = short2(1, 0);
inline const short2 short2::bottom = short2(0, -1);
inline const short2 short2::top = short2(0, 1);

/***********************************************************************************************************************
 * @brief A 3-component vector of 16-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] short3
{
	int16 x; /**< First vector component. */
	int16 y; /**< Second vector component. */
	int16 z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 16-bit signed integer values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit short3(int16 xyz = 0) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr short3(int16 x, int16 y, int16 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr short3(short2 xy, int16 z) noexcept : x(xy.x), y(xy.y), z(x) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr short3(int16 x, short2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	constexpr short3(ushort4 xyz) noexcept : x((int16)xyz.x), y((int16)xyz.y), z((int16)xyz.z) { }
	constexpr short3(ushort3 xyz) noexcept : x((int16)xyz.x), y((int16)xyz.y), z((int16)xyz.z) { }
	constexpr short3(sbyte4 xyz) noexcept : x((int16)xyz.x), y((int16)xyz.y), z((int16)xyz.z) { }
	constexpr short3(sbyte3 xyz) noexcept : x((int16)xyz.x), y((int16)xyz.y), z((int16)xyz.z) { }
	constexpr short3(byte4 xyz) noexcept : x((int16)xyz.x), y((int16)xyz.y), z((int16)xyz.z) { }
	constexpr short3(byte3 xyz) noexcept : x((int16)xyz.x), y((int16)xyz.y), z((int16)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int16& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((int16*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int16 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((int16*)this)[i];
	}

	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator short2() const noexcept { return short2(x, y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr short3 operator+(short3 v) const noexcept { return short3(x + v.x, y + v.y, z + v.z); }
	constexpr short3 operator-(short3 v) const noexcept { return short3(x - v.x, y - v.y, z - v.z); }
	constexpr short3 operator*(short3 v) const noexcept { return short3(x * v.x, y * v.y, z * v.z); }
	constexpr short3 operator/(short3 v) const noexcept { return short3(x / v.x, y / v.y, z / v.z); }
	constexpr short3 operator%(short3 v) const noexcept { return short3(x % v.x, y % v.y, z % v.z); }
	constexpr short3 operator&(short3 v) const noexcept { return short3(x & v.x, y & v.y, z & v.z); }
	constexpr short3 operator|(short3 v) const noexcept { return short3(x | v.x, y | v.y, z | v.z); }
	constexpr short3 operator^(short3 v) const noexcept { return short3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr short3 operator>>(short3 v) const noexcept { return short3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr short3 operator<<(short3 v) const noexcept { return short3(x << v.x, y << v.y, z << v.z); }
	constexpr short3 operator+(int16 n) const noexcept { return short3(x + n, y + n, z + n); }
	constexpr short3 operator-(int16 n) const noexcept { return short3(x - n, y - n, z - n); }
	constexpr short3 operator*(int16 n) const noexcept { return short3(x * n, y * n, z * n); }
	constexpr short3 operator/(int16 n) const noexcept { return short3(x / n, y / n, z / n); }
	constexpr short3 operator%(int16 n) const noexcept { return short3(x % n, y % n, z % n); }
	constexpr short3 operator&(int16 n) const noexcept { return short3(x & n, y & n, z & n); }
	constexpr short3 operator|(int16 n) const noexcept { return short3(x | n, y | n, z | n); }
	constexpr short3 operator^(int16 n) const noexcept { return short3(x ^ n, y ^ n, z ^ n); }
	constexpr short3 operator>>(int16 n) const noexcept { return short3(x >> n, y >> n, z >> n); }
	constexpr short3 operator<<(int16 n) const noexcept { return short3(x << n, y << n, z << n); }
	constexpr short3 operator-() const noexcept { return short3(-x, -y, -z); }
	constexpr short3 operator!() const noexcept { return short3(!x, !y, !z); }
	constexpr short3 operator~() const noexcept { return short3(~x, ~y, ~z); }
	short3& operator+=(short3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	short3& operator-=(short3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	short3& operator*=(short3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	short3& operator/=(short3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	short3& operator%=(short3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	short3& operator&=(short3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	short3& operator|=(short3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	short3& operator^=(short3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	short3& operator>>=(short3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	short3& operator<<=(short3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	short3& operator+=(int16 n) noexcept { x += n; y += n; z += n; return *this; }
	short3& operator-=(int16 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	short3& operator*=(int16 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	short3& operator/=(int16 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	short3& operator%=(int16 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	short3& operator&=(int16 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	short3& operator|=(int16 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	short3& operator^=(int16 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	short3& operator>>=(int16 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	short3& operator<<=(int16 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	short3& operator=(int16 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(short3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(short3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr ushort3 operator<(short3 v) const noexcept
	{
		return ushort3(x < v.x ? UINT16_MAX : 0, y < v.y ? UINT16_MAX : 0, z < v.z ? UINT16_MAX : 0);
	}
	constexpr ushort3 operator>(short3 v) const noexcept
	{
		return ushort3(x > v.x ? UINT16_MAX : 0, y > v.y ? UINT16_MAX : 0, z > v.z ? UINT16_MAX : 0);
	}
	constexpr ushort3 operator<=(short3 v) const noexcept
	{
		return ushort3(x <= v.x ? UINT16_MAX : 0, y <= v.y ? UINT16_MAX : 0, z <= v.z ? UINT16_MAX : 0);
	}
	constexpr ushort3 operator>=(short3 v) const noexcept
	{
		return ushort3(x >= v.x ? UINT16_MAX : 0, y >= v.y ? UINT16_MAX : 0, z >= v.z ? UINT16_MAX : 0);
	}
	constexpr bool operator==(int16 n) const noexcept { return *this == short3(n); }
	constexpr bool operator!=(int16 n) const noexcept { return *this != short3(n); }
	constexpr ushort3 operator<(int16 n) const noexcept { return *this < short3(n); }
	constexpr ushort3 operator>(int16 n) const noexcept { return *this > short3(n); }
	constexpr ushort3 operator<=(int16 n) const noexcept { return *this <= short3(n); }
	constexpr ushort3 operator>=(int16 n) const noexcept { return *this >= short3(n); }

	static const short3 zero, one, minusOne, min, max, left, right, bottom, top, back, front;
};

inline const short3 short3::zero = short3(0);
inline const short3 short3::one = short3(1);
inline const short3 short3::minusOne = short3(-1);
inline const short3 short3::min = short3(INT16_MIN);
inline const short3 short3::max = short3(INT16_MAX);
inline const short3 short3::left = short3(-1, 0, 0);
inline const short3 short3::right = short3(1, 0, 0);
inline const short3 short3::bottom = short3(0, -1, 0);
inline const short3 short3::top = short3(0, 1, 0);
inline const short3 short3::back = short3(0, 0, -1);
inline const short3 short3::front = short3(0, 0, 1);

/***********************************************************************************************************************
 * @brief A 4-component vector of 16-bit signed integer values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] short4
{
	int16 x; /**< First vector component. */
	int16 y; /**< Second vector component. */
	int16 z; /**< Third vector component. */
	int16 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit short4(int16 xyzw = 0) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr short4(int16 x, int16 y, int16 z, int16 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr short4(short2 xy, int16 z, int16 w) noexcept: x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr short4(int16 x, short2 yz, int16 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr short4(int16 x, int16 y, short2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr short4(short2 xy, short2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr short4(short3 xyz, int16 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit signed integer values.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector component value
	 */
	constexpr short4(int16 x, short3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	constexpr short4(ushort4 xyzw) noexcept : x((int16)xyzw.x), y((int16)xyzw.y), z((int16)xyzw.z), w((int16)xyzw.w) { }
	constexpr short4(sbyte4 xyzw) noexcept : x((int16)xyzw.x), y((int16)xyzw.y), z((int16)xyzw.z), w((int16)xyzw.w) { }
	constexpr short4(byte4 xyzw) noexcept : x((int16)xyzw.x), y((int16)xyzw.y), z((int16)xyzw.z), w((int16)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int16& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((int16*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	int16 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((int16*)this)[i];
	}

	constexpr explicit operator ushort4() const noexcept { return ushort4((uint16)x, (uint16)y, (uint16)z, (uint16)w); }
	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator short3() const noexcept { return short3(x, y, z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator short2() const noexcept { return short2(x, y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	//******************************************************************************************************************
	constexpr short4 operator+(short4 v) const noexcept { return short4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr short4 operator-(short4 v) const noexcept { return short4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr short4 operator*(short4 v) const noexcept { return short4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr short4 operator/(short4 v) const noexcept { return short4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr short4 operator%(short4 v) const noexcept { return short4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr short4 operator&(short4 v) const noexcept { return short4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr short4 operator|(short4 v) const noexcept { return short4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr short4 operator^(short4 v) const noexcept { return short4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr short4 operator>>(short4 v) const noexcept { return short4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr short4 operator<<(short4 v) const noexcept { return short4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr short4 operator+(int16 n) const noexcept { return short4(x + n, y + n, z + n, w + n); }
	constexpr short4 operator-(int16 n) const noexcept { return short4(x - n, y - n, z - n, w - n); }
	constexpr short4 operator*(int16 n) const noexcept { return short4(x * n, y * n, z * n, w * n); }
	constexpr short4 operator/(int16 n) const noexcept { return short4(x / n, y / n, z / n, w / n); }
	constexpr short4 operator%(int16 n) const noexcept { return short4(x % n, y % n, z % n, w % n); }
	constexpr short4 operator&(int16 n) const noexcept { return short4(x & n, y & n, z & n, w & n); }
	constexpr short4 operator|(int16 n) const noexcept { return short4(x | n, y | n, z | n, w | n); }
	constexpr short4 operator^(int16 n) const noexcept { return short4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr short4 operator>>(int16 n) const noexcept { return short4(x >> n, y >> n, z >> n, w >> n); }
	constexpr short4 operator<<(int16 n) const noexcept { return short4(x << n, y << n, z << n, w << n); }
	constexpr short4 operator-() const noexcept { return short4(-x, -y, -z, -w); }
	constexpr short4 operator!() const noexcept { return short4(!x, !y, !z, !w); }
	constexpr short4 operator~() const noexcept { return short4(~x, ~y, ~z, ~w); }
	short4& operator+=(short4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	short4& operator-=(short4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	short4& operator*=(short4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	short4& operator/=(short4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	short4& operator%=(short4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	short4& operator&=(short4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	short4& operator|=(short4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	short4& operator^=(short4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	short4& operator>>=(short4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	short4& operator<<=(short4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	short4& operator+=(int16 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	short4& operator-=(int16 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	short4& operator*=(int16 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	short4& operator/=(int16 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	short4& operator%=(int16 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	short4& operator&=(int16 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	short4& operator|=(int16 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	short4& operator^=(int16 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	short4& operator>>=(int16 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	short4& operator<<=(int16 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	short4& operator=(int16 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(short4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(short4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr ushort4 operator<(short4 v) const noexcept
	{
		return ushort4(x < v.x ? UINT16_MAX : 0, y < v.y ? UINT16_MAX : 0, 
			z < v.z ? UINT16_MAX : 0, w < v.w ? UINT16_MAX : 0);
	}
	constexpr ushort4 operator>(short4 v) const noexcept
	{
		return ushort4(x > v.x ? UINT16_MAX : 0, y > v.y ? UINT16_MAX : 0, 
			z > v.z ? UINT16_MAX : 0, w > v.w ? UINT16_MAX : 0);
	}
	constexpr ushort4 operator<=(short4 v) const noexcept
	{
		return ushort4(x <= v.x ? UINT16_MAX : 0, y <= v.y ? UINT16_MAX : 0, 
			z <= v.z ? UINT16_MAX : 0, w <= v.w ? UINT16_MAX : 0);
	}
	constexpr ushort4 operator>=(short4 v) const noexcept
	{
		return ushort4(x >= v.x ? UINT16_MAX : 0, y >= v.y ? UINT16_MAX : 0, 
			z >= v.z ? UINT16_MAX : 0, w >= v.w ? UINT16_MAX : 0);
	}
	constexpr bool operator==(int16 n) const noexcept { return *this == short4(n); }
	constexpr bool operator!=(int16 n) const noexcept { return *this != short4(n); }
	constexpr ushort4 operator<(int16 n) const noexcept { return *this < short4(n); }
	constexpr ushort4 operator>(int16 n) const noexcept { return *this > short4(n); }
	constexpr ushort4 operator<=(int16 n) const noexcept { return *this <= short4(n); }
	constexpr ushort4 operator>=(int16 n) const noexcept { return *this >= short4(n); }

	static const short4 zero, one, minusOne, min, max;
};

inline const short4 short4::zero = short4(0);
inline const short4 short4::one = short4(1);
inline const short4 short4::minusOne = short4(-1);
inline const short4 short4::min = short4(INT16_MIN);
inline const short4 short4::max = short4(INT16_MAX);

//**********************************************************************************************************************
static constexpr short2 operator+(int16 n, short2 v) noexcept { return short2(n) + v; }
static constexpr short2 operator-(int16 n, short2 v) noexcept { return short2(n) - v; }
static constexpr short2 operator*(int16 n, short2 v) noexcept { return short2(n) * v; }
static constexpr short2 operator/(int16 n, short2 v) noexcept { return short2(n) / v; }
static constexpr short2 operator%(int16 n, short2 v) noexcept { return short2(n) % v; }
static constexpr short2 operator&(int16 n, short2 v) noexcept { return short2(n) & v; }
static constexpr short2 operator|(int16 n, short2 v) noexcept { return short2(n) | v; }
static constexpr short2 operator^(int16 n, short2 v) noexcept { return short2(n) ^ v; }
static constexpr short2 operator>>(int16 n, short2 v) noexcept { return short2(n) >> v; }
static constexpr short2 operator<<(int16 n, short2 v) noexcept { return short2(n) << v; }
static constexpr bool operator==(int16 n, short2 v) noexcept { return short2(n) == v; }
static constexpr bool operator!=(int16 n, short2 v) noexcept { return short2(n) != v; }
static constexpr ushort2 operator<(int16 n, short2 v) noexcept { return short2(n) < v; }
static constexpr ushort2 operator>(int16 n, short2 v) noexcept { return short2(n) > v; }
static constexpr ushort2 operator<=(int16 n, short2 v) noexcept { return short2(n) <= v; }
static constexpr ushort2 operator>=(int16 n, short2 v) noexcept { return short2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(short2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort2 equal(short2 a, short2 b) noexcept
{
	return ushort2(a.x == b.x ? UINT16_MAX : 0, a.y == b.y ? UINT16_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort2 notEqual(short2 a, short2 b) noexcept
{
	return ushort2(a.x != b.x ? UINT16_MAX : 0, a.y != b.y ? UINT16_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(short2 a, short2 b) noexcept { return *((const int32*)&a) < *((const int32*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr short2 select(ushort2 c, short2 t, short2 f) noexcept
{
	return short2(c.x & 0x8000u ? t.x : f.x, c.y & 0x8000u ? t.y : f.y);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr short2 min(short2 a, short2 b) noexcept { return short2(std::min(a.x, b.x), std::min(a.y, b.y)); }
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr short2 max(short2 a, short2 b) noexcept { return short2(std::max(a.x, b.x), std::max(a.y, b.y)); }
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr short2 min(short2 a, short2 b, short2 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr short2 max(short2 a, short2 b, short2 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr short2 clamp(short2 v, short2 min, short2 max) noexcept
{
	return short2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}

//**********************************************************************************************************************
static constexpr short3 operator+(int16 n, short3 v) noexcept { return short3(n) + v; }
static constexpr short3 operator-(int16 n, short3 v) noexcept { return short3(n) - v; }
static constexpr short3 operator*(int16 n, short3 v) noexcept { return short3(n) * v; }
static constexpr short3 operator/(int16 n, short3 v) noexcept { return short3(n) / v; }
static constexpr short3 operator%(int16 n, short3 v) noexcept { return short3(n) % v; }
static constexpr short3 operator&(int16 n, short3 v) noexcept { return short3(n) & v; }
static constexpr short3 operator|(int16 n, short3 v) noexcept { return short3(n) | v; }
static constexpr short3 operator^(int16 n, short3 v) noexcept { return short3(n) ^ v; }
static constexpr short3 operator>>(int16 n, short3 v) noexcept { return short3(n) >> v; }
static constexpr short3 operator<<(int16 n, short3 v) noexcept { return short3(n) << v; }
static constexpr bool operator==(int16 n, short3 v) noexcept { return short3(n) == v; }
static constexpr bool operator!=(int16 n, short3 v) noexcept { return short3(n) != v; }
static constexpr ushort3 operator<(int16 n, short3 v) noexcept { return short3(n) < v; }
static constexpr ushort3 operator>(int16 n, short3 v) noexcept { return short3(n) > v; }
static constexpr ushort3 operator<=(int16 n, short3 v) noexcept { return short3(n) <= v; }
static constexpr ushort3 operator>=(int16 n, short3 v) noexcept { return short3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(short3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort3 equal(short3 a, short3 b) noexcept
{
	return ushort3(a.x == b.x ? UINT16_MAX : 0, a.y == b.y ? UINT16_MAX : 0, a.z == b.z ? UINT16_MAX : 0);
}
/**
 * @brief Compares two vectors component wise if they are not equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort3 notEqual(short3 a, short3 b) noexcept
{
	return ushort3(a.x != b.x ? UINT16_MAX : 0, a.y != b.y ? UINT16_MAX : 0, a.z != b.z ? UINT16_MAX : 0);
}

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const short3& a, const short3& b) noexcept { return memcmp(&a, &b, sizeof(short3)) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr short3 select(ushort3 c, short3 t, short3 f) noexcept
{
	return short3(c.x & 0x8000u ? t.x : f.x, c.y & 0x8000u ? t.y : f.y, c.z & 0x8000u ? t.z : f.z);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr short3 min(short3 a, short3 b) noexcept
{
	return short3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr short3 max(short3 a, short3 b) noexcept
{
	return short3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr short3 min(short3 a, short3 b, short3 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr short3 max(short3 a, short3 b, short3 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr short3 clamp(short3 v, short3 min, short3 max) noexcept
{
	return short3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

//**********************************************************************************************************************
static constexpr short4 operator+(int16 n, short4 v) noexcept { return short4(n) + v; }
static constexpr short4 operator-(int16 n, short4 v) noexcept { return short4(n) - v; }
static constexpr short4 operator*(int16 n, short4 v) noexcept { return short4(n) * v; }
static constexpr short4 operator/(int16 n, short4 v) noexcept { return short4(n) / v; }
static constexpr short4 operator%(int16 n, short4 v) noexcept { return short4(n) % v; }
static constexpr short4 operator&(int16 n, short4 v) noexcept { return short4(n) & v; }
static constexpr short4 operator|(int16 n, short4 v) noexcept { return short4(n) | v; }
static constexpr short4 operator^(int16 n, short4 v) noexcept { return short4(n) ^ v; }
static constexpr short4 operator>>(int16 n, short4 v) noexcept { return short4(n) >> v; }
static constexpr short4 operator<<(int16 n, short4 v) noexcept { return short4(n) << v; }
static constexpr bool operator==(int16 n, short4 v) noexcept { return short4(n) == v; }
static constexpr bool operator!=(int16 n, short4 v) noexcept { return short4(n) != v; }
static constexpr ushort4 operator<(int16 n, short4 v) noexcept { return short4(n) < v; }
static constexpr ushort4 operator>(int16 n, short4 v) noexcept { return short4(n) > v; }
static constexpr ushort4 operator<=(int16 n, short4 v) noexcept { return short4(n) <= v; }
static constexpr ushort4 operator>=(int16 n, short4 v) noexcept { return short4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(short4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Compares two vectors component wise if they are equal.
 *
 * @param a first vector to compare
 * @param b second vector to compare
 */
static ushort4 equal(short4 a, short4 b) noexcept
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
static ushort4 notEqual(short4 a, short4 b) noexcept
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
static bool isBinaryLess(const short4& a, const short4& b) noexcept { return *((const int64*)&a) < *((const int64*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr short4 select(ushort4 c, short4 t, short4 f) noexcept
{
	return short4(c.x & 0x8000u ? t.x : f.x, c.y & 0x8000u ? t.y : f.y, 
		c.z & 0x8000u ? t.z : f.z, c.w & 0x8000u ? t.w : f.w);
}

/***********************************************************************************************************************
 * @brief Returns minimum value for each component of two vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 */
static constexpr short4 min(short4 a, short4 b) noexcept
{
	return short4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
/**
 * @brief Returns maximum value for each component of two vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 */
static constexpr short4 max(short4 a, short4 b) noexcept
{
	return short4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
/**
 * @brief Returns minimum value for each component of three vectors.
 * 
 * @param a first vector to find minimum
 * @param b second vector to find minimum
 * @param c third vector to find minimum
 */
static constexpr short4 min(short4 a, short4 b, short4 c) noexcept { return min(min(a, b), c); }
/**
 * @brief Returns maximum value for each component of three vectors.
 * 
 * @param a first vector to find maximum
 * @param b second vector to find maximum
 * @param c third vector to find maximum
 */
static constexpr short4 max(short4 a, short4 b, short4 c) noexcept { return max(max(a, b), c); }

/**
 * @brief Clamps vector components between min and max values.
 * 
 * @param v target vector to clamp
 * @param min vector with minimum values
 * @param max vector with maximum values
 */
static constexpr short4 clamp(short4 v, short4 min, short4 max) noexcept
{
	return short4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}

} // namespace math