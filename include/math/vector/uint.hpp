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
 * @brief Common unsigned integer vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/types.hpp"

#if _WIN32
#define _USE_MATH_DEFINES
#define NOMINMAX
#endif

#include <string>
#include <algorithm>

#include <cmath>
#include <cassert>
#include <cstring>

namespace math
{

using namespace std;

/**
 * @brief Unsigned integer 2 component vector structure.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] uint2
{
	uint32 x; /**< First vector component. */
	uint32 y; /**< Second vector component. */

	/**
	 * @brief Creates a new unsigned integer 2 component vector structure.
	 * @param xy target value for all vector components
	 */
	constexpr explicit uint2(uint32 xy = 0u) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new unsigned integer 2 component vector structure.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr uint2(uint32 x, uint32 y) noexcept : x(x), y(y) { }

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint32& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((uint32*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint32 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((uint32*)this)[i];
	}

	/**
	 * @brief Returns first vector component value. (x)
	 */
	constexpr explicit operator uint32() noexcept { return x; }

	//******************************************************************************************************************
	constexpr uint2 operator+(uint2 v) const noexcept { return uint2(x + v.x, y + v.y); }
	constexpr uint2 operator-(uint2 v) const noexcept { return uint2(x - v.x, y - v.y); }
	constexpr uint2 operator*(uint2 v) const noexcept { return uint2(x * v.x, y * v.y); }
	constexpr uint2 operator/(uint2 v) const noexcept { return uint2(x / v.x, y / v.y); }
	constexpr uint2 operator%(uint2 v) const noexcept { return uint2(x % v.x, y % v.y); }
	constexpr uint2 operator&(uint2 v) const noexcept { return uint2(x & v.x, y & v.y); }
	constexpr uint2 operator|(uint2 v) const noexcept { return uint2(x | v.x, y | v.y); }
	constexpr uint2 operator^(uint2 v) const noexcept { return uint2(x ^ v.x, y ^ v.y); }
	constexpr uint2 operator>>(uint2 v) const noexcept { return uint2(x >> v.x, y >> v.y); }
	constexpr uint2 operator<<(uint2 v) const noexcept { return uint2(x << v.x, y << v.y); }
	constexpr uint2 operator+(uint32 n) const noexcept { return uint2(x + n, y + n); }
	constexpr uint2 operator-(uint32 n) const noexcept { return uint2(x - n, y - n); }
	constexpr uint2 operator*(uint32 n) const noexcept { return uint2(x * n, y * n); }
	constexpr uint2 operator/(uint32 n) const noexcept { return uint2(x / n, y / n); }
	constexpr uint2 operator%(uint32 n) const noexcept { return uint2(x % n, y % n); }
	constexpr uint2 operator&(uint32 n) const noexcept { return uint2(x & n, y & n); }
	constexpr uint2 operator|(uint32 n) const noexcept { return uint2(x | n, y | n); }
	constexpr uint2 operator^(uint32 n) const noexcept { return uint2(x ^ n, y ^ n); }
	constexpr uint2 operator>>(uint32 n) const noexcept { return uint2(x >> n, y >> n); }
	constexpr uint2 operator<<(uint32 n) const noexcept { return uint2(x << n, y << n); }
	constexpr uint2 operator-() const noexcept { return uint2(-x, -y); }
	constexpr uint2 operator!() const noexcept { return uint2(!x, !y); }
	constexpr uint2 operator~() const noexcept { return uint2(~x, ~y); }
	uint2& operator+=(uint2 v) noexcept { x += v.x; y += v.y; return *this; }
	uint2& operator-=(uint2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	uint2& operator*=(uint2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	uint2& operator/=(uint2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	uint2& operator%=(uint2 v) noexcept { x %= v.x; y %= v.y; return *this; }
	uint2& operator&=(uint2 v) noexcept { x &= v.x; y &= v.y; return *this; }
	uint2& operator|=(uint2 v) noexcept { x |= v.x; y |= v.y; return *this; }
	uint2& operator^=(uint2 v) noexcept { x ^= v.x; y ^= v.y; return *this; }
	uint2& operator>>=(uint2 v) noexcept { x >>= v.x; y >>= v.y; return *this; }
	uint2& operator<<=(uint2 v) noexcept { x <<= v.x; y <<= v.y; return *this; }
	uint2& operator+=(uint32 n) noexcept { x += n; y += n; return *this; }
	uint2& operator-=(uint32 n) noexcept { x -= n; y -= n; return *this; }
	uint2& operator*=(uint32 n) noexcept { x *= n; y *= n; return *this; }
	uint2& operator/=(uint32 n) noexcept { x /= n; y /= n; return *this; }
	uint2& operator%=(uint32 n) noexcept { x %= n; y %= n; return *this; }
	uint2& operator&=(uint32 n) noexcept { x &= n; y &= n; return *this; }
	uint2& operator|=(uint32 n) noexcept { x |= n; y |= n; return *this; }
	uint2& operator^=(uint32 n) noexcept { x ^= n; y ^= n; return *this; }
	uint2& operator>>=(uint32 n) noexcept { x >>= n; y >>= n; return *this; }
	uint2& operator<<=(uint32 n) noexcept { x <<= n; y <<= n; return *this; }
	uint2& operator=(uint32 n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(uint2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(uint2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr uint2 operator<(uint2 v) const noexcept { return uint2(x < v.x, y < v.y); }
	constexpr uint2 operator>(uint2 v) const noexcept { return uint2(x > v.x, y > v.y); }
	constexpr uint2 operator<=(uint2 v) const noexcept { return uint2(x <= v.x, y <= v.y); }
	constexpr uint2 operator>=(uint2 v) const noexcept { return uint2(x >= v.x, y >= v.y); }
	constexpr bool operator==(uint32 n) const noexcept { return x == n && y == n; }
	constexpr bool operator!=(uint32 n) const noexcept { return x != n || y != n; }
	constexpr uint2 operator<(uint32 n) const noexcept { return uint2(x < n, y < n); }
	constexpr uint2 operator>(uint32 n) const noexcept { return uint2(x > n, y > n); }
	constexpr uint2 operator<=(uint32 n) const noexcept { return uint2(x <= n, y <= n); }
	constexpr uint2 operator>=(uint32 n) const noexcept { return uint2(x >= n, y >= n); }

	static const uint2 zero, one;
};

inline const uint2 uint2::zero = uint2(0u);
inline const uint2 uint2::one = uint2(1u);

/***********************************************************************************************************************
 * @brief Unsigned integer 3 component vector structure.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] uint3
{
	uint32 x; /**< First vector component. */
	uint32 y; /**< Second vector component. */
	uint32 z; /**< Third vector component. */

	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit uint3(uint32 xyz = 0u) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr uint3(uint32 x, uint32 y, uint32 z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 */
	constexpr uint3(uint2 xy, uint32 z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 */
	constexpr uint3(uint32 x, uint2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint32& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((uint32*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint32 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((uint32*)this)[i];
	}

	/**
	 * @brief Returns as 2 component unsigned integer vector. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2(x, y); }
	/**
	 * @brief Returns first vector component value. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return x; }

	//******************************************************************************************************************
	constexpr uint3 operator+(uint3 v) const noexcept { return uint3(x + v.x, y + v.y, z + v.z); }
	constexpr uint3 operator-(uint3 v) const noexcept { return uint3(x - v.x, y - v.y, z - v.z); }
	constexpr uint3 operator*(uint3 v) const noexcept { return uint3(x * v.x, y * v.y, z * v.z); }
	constexpr uint3 operator/(uint3 v) const noexcept { return uint3(x / v.x, y / v.y, z / v.z); }
	constexpr uint3 operator%(uint3 v) const noexcept { return uint3(x % v.x, y % v.y, z % v.z); }
	constexpr uint3 operator&(uint3 v) const noexcept { return uint3(x & v.x, y & v.y, z & v.z); }
	constexpr uint3 operator|(uint3 v) const noexcept { return uint3(x | v.x, y | v.y, z | v.z); }
	constexpr uint3 operator^(uint3 v) const noexcept { return uint3(x ^ v.x, y ^ v.y, z ^ v.z); }
	constexpr uint3 operator>>(uint3 v) const noexcept { return uint3(x >> v.x, y >> v.y, z >> v.z); }
	constexpr uint3 operator<<(uint3 v) const noexcept { return uint3(x << v.x, y << v.y, z << v.z); }
	constexpr uint3 operator+(uint32 n) const noexcept { return uint3(x + n, y + n, z + n); }
	constexpr uint3 operator-(uint32 n) const noexcept { return uint3(x - n, y - n, z - n); }
	constexpr uint3 operator*(uint32 n) const noexcept { return uint3(x * n, y * n, z * n); }
	constexpr uint3 operator/(uint32 n) const noexcept { return uint3(x / n, y / n, z / n); }
	constexpr uint3 operator%(uint32 n) const noexcept { return uint3(x % n, y % n, z % n); }
	constexpr uint3 operator&(uint32 n) const noexcept { return uint3(x & n, y & n, z & n); }
	constexpr uint3 operator|(uint32 n) const noexcept { return uint3(x | n, y | n, z | n); }
	constexpr uint3 operator^(uint32 n) const noexcept { return uint3(x ^ n, y ^ n, z ^ n); }
	constexpr uint3 operator>>(uint32 n) const noexcept { return uint3(x >> n, y >> n, z >> n); }
	constexpr uint3 operator<<(uint32 n) const noexcept { return uint3(x << n, y << n, z << n); }
	constexpr uint3 operator-() const noexcept { return uint3(-x, -y, -z); }
	constexpr uint3 operator!() const noexcept { return uint3(!x, !y, !z); }
	uint3 operator~() const noexcept { return uint3(~x, ~y, ~z); }
	uint3& operator+=(uint3 v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	uint3& operator-=(uint3 v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	uint3& operator*=(uint3 v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	uint3& operator/=(uint3 v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	uint3& operator%=(uint3 v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	uint3& operator&=(uint3 v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	uint3& operator|=(uint3 v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	uint3& operator^=(uint3 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	uint3& operator>>=(uint3 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	uint3& operator<<=(uint3 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
	uint3& operator+=(uint32 n) noexcept { x += n; y += n; z += n; return *this; }
	uint3& operator-=(uint32 n) noexcept { x -= n; y -= n; z -= n; return *this; }
	uint3& operator*=(uint32 n) noexcept { x *= n; y *= n; z *= n; return *this; }
	uint3& operator/=(uint32 n) noexcept { x /= n; y /= n; z /= n; return *this; }
	uint3& operator%=(uint32 n) noexcept { x %= n; y %= n; z %= n; return *this; }
	uint3& operator&=(uint32 n) noexcept { x &= n; y &= n; z &= n; return *this; }
	uint3& operator|=(uint32 n) noexcept { x |= n; y |= n; z |= n; return *this; }
	uint3& operator^=(uint32 n) noexcept { x ^= n; y ^= n; z ^= n; return *this; }
	uint3& operator>>=(uint32 n) noexcept { x >>= n; y >>= n; z >>= n; return *this; }
	uint3& operator<<=(uint32 n) noexcept { x <<= n; y <<= n; z <<= n; return *this; }
	uint3& operator=(uint32 n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(uint3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(uint3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr uint3 operator<(uint3 v) const noexcept { return uint3(x < v.x, y < v.y, z < v.z); }
	constexpr uint3 operator>(uint3 v) const noexcept { return uint3(x > v.x, y > v.y, z > v.z); }
	constexpr uint3 operator<=(uint3 v) const noexcept { return uint3(x <= v.x, y <= v.y, z <= v.z); }
	constexpr uint3 operator>=(uint3 v) const noexcept { return uint3(x >= v.x, y >= v.y, z >= v.z); }
	constexpr bool operator==(uint32 n) const noexcept { return x == n && y == n && z == n; }
	constexpr bool operator!=(uint32 n) const noexcept { return x != n || y != n || z != n; }
	constexpr uint3 operator<(uint32 n) const noexcept { return uint3(x < n, y < n, z < n); }
	constexpr uint3 operator>(uint32 n) const noexcept { return uint3(x > n, y > n, z > n); }
	constexpr uint3 operator<=(uint32 n) const noexcept { return uint3(x <= n, y <= n, z <= n); }
	constexpr uint3 operator>=(uint32 n) const noexcept { return uint3(x >= n, y >= n, z >= n); }

	static const uint3 zero, one;
};

inline const uint3 uint3::zero = uint3(0u);
inline const uint3 uint3::one = uint3(1u);

/***********************************************************************************************************************
 * @brief Unsigned integer 4 component vector structure.
 * @details Commonly used to represent: points, positions, etc.
 */
struct [[nodiscard]] uint4
{
	uint32 x; /**< First vector component. */
	uint32 y; /**< Second vector component. */
	uint32 z; /**< Third vector component. */
	uint32 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit uint4(uint32 xyzw = 0u) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr uint4(uint32 x, uint32 y, uint32 z, uint32 w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr uint4(uint2 xy, uint32 z, uint32 w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 * @param w fourth vector component value
	 */
	constexpr uint4(uint32 x, uint2 yz, uint32 w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector components value
	 */
	constexpr uint4(uint32 x, uint32 y, uint2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param zw third and fourth vector components value
	 */
	constexpr uint4(uint2 xy, uint2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param xyz first, second and third vector components value
	 * @param w fourth vector component value
	 */
	constexpr uint4(uint3 xyz, uint32 w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector components value
	 */
	constexpr uint4(uint32 x, uint3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint32& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((uint32*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	uint32 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((uint32*)this)[i];
	}

	/**
	 * @brief Returns as 3 component unsigned integer vector. (xyz)
	 */
	constexpr explicit operator uint3() const noexcept { return uint3(x, y, z); }
	/**
	 * @brief Returns as 2 component unsigned integer vector. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2(x, y); }
	/**
	 * @brief Returns first vector component value. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return x; }

	//******************************************************************************************************************
	constexpr uint4 operator+(uint4 v) const noexcept { return uint4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr uint4 operator-(uint4 v) const noexcept { return uint4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr uint4 operator*(uint4 v) const noexcept { return uint4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr uint4 operator/(uint4 v) const noexcept { return uint4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr uint4 operator%(uint4 v) const noexcept { return uint4(x % v.x, y % v.y, z % v.z, w % v.w); }
	constexpr uint4 operator&(uint4 v) const noexcept { return uint4(x & v.x, y & v.y, z & v.z, w & v.w); }
	constexpr uint4 operator|(uint4 v) const noexcept { return uint4(x | v.x, y | v.y, z | v.z, w | v.w); }
	constexpr uint4 operator^(uint4 v) const noexcept { return uint4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	constexpr uint4 operator>>(uint4 v) const noexcept { return uint4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	constexpr uint4 operator<<(uint4 v) const noexcept { return uint4(x << v.x, y << v.y, z << v.z, w << v.w); }
	constexpr uint4 operator+(uint32 n) const noexcept { return uint4(x + n, y + n, z + n, w + n); }
	constexpr uint4 operator-(uint32 n) const noexcept { return uint4(x - n, y - n, z - n, w - n); }
	constexpr uint4 operator*(uint32 n) const noexcept { return uint4(x * n, y * n, z * n, w * n); }
	constexpr uint4 operator/(uint32 n) const noexcept { return uint4(x / n, y / n, z / n, w / n); }
	constexpr uint4 operator%(uint32 n) const noexcept { return uint4(x % n, y % n, z % n, w % n); }
	constexpr uint4 operator&(uint32 n) const noexcept { return uint4(x & n, y & n, z & n, w & n); }
	constexpr uint4 operator|(uint32 n) const noexcept { return uint4(x | n, y | n, z | n, w | n); }
	constexpr uint4 operator^(uint32 n) const noexcept { return uint4(x ^ n, y ^ n, z ^ n, w ^ n); }
	constexpr uint4 operator>>(uint32 n) const noexcept { return uint4(x >> n, y >> n, z >> n, w >> n); }
	constexpr uint4 operator<<(uint32 n) const noexcept { return uint4(x << n, y << n, z << n, w << n); }
	constexpr uint4 operator-() const noexcept { return uint4(-x, -y, -z, -w); }
	constexpr uint4 operator!() const noexcept { return uint4(!x, !y, !z, !w); }
	constexpr uint4 operator~() const noexcept { return uint4(~x, ~y, ~z, ~w); }
	uint4& operator+=(uint4 v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	uint4& operator-=(uint4 v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	uint4& operator*=(uint4 v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	uint4& operator/=(uint4 v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	uint4& operator%=(uint4 v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	uint4& operator&=(uint4 v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	uint4& operator|=(uint4 v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	uint4& operator^=(uint4 v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	uint4& operator>>=(uint4 v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	uint4& operator<<=(uint4 v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	uint4& operator+=(uint32 n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	uint4& operator-=(uint32 n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	uint4& operator*=(uint32 n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	uint4& operator/=(uint32 n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	uint4& operator%=(uint32 n) noexcept { x %= n; y %= n; z %= n; w %= n; return *this; }
	uint4& operator&=(uint32 n) noexcept { x &= n; y &= n; z &= n; w &= n; return *this; }
	uint4& operator|=(uint32 n) noexcept { x |= n; y |= n; z |= n; w |= n; return *this; }
	uint4& operator^=(uint32 n) noexcept { x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	uint4& operator>>=(uint32 n) noexcept { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	uint4& operator<<=(uint32 n) noexcept { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	uint4& operator=(uint32 n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(uint4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(uint4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr uint4 operator<(uint4 v) const noexcept { return uint4(x < v.x, y < v.y, z < v.z, w < v.w); }
	constexpr uint4 operator>(uint4 v) const noexcept { return uint4(x > v.x, y > v.y, z > v.z, w > v.w); }
	constexpr uint4 operator<=(uint4 v) const noexcept { return uint4(x <= v.x, y <= v.y, z <= v.z, w <= v.w); }
	constexpr uint4 operator>=(uint4 v) const noexcept { return uint4(x >= v.x, y >= v.y, z >= v.z, w >= v.w); }
	constexpr bool operator==(uint32 n) const noexcept { return x == n && y == n && z == n && w == n; }
	constexpr bool operator!=(uint32 n) const noexcept { return x != n || y != n || z != n || w != n; }
	constexpr uint4 operator<(uint32 n) const noexcept { return uint4(x < n, y < n, z < n, w < n); }
	constexpr uint4 operator>(uint32 n) const noexcept { return uint4(x > n, y > n, z > n, w > n); }
	constexpr uint4 operator<=(uint32 n) const noexcept { return uint4(x <= n, y <= n, z <= n, w <= n); }
	constexpr uint4 operator>=(uint32 n) const noexcept { return uint4(x >= n, y >= n, z >= n, w >= n); }

	static const uint4 zero, one;
};

inline const uint4 uint4::zero = uint4(0u);
inline const uint4 uint4::one = uint4(1u);

//**********************************************************************************************************************
static constexpr uint2 operator+(uint32 n, uint2 v) noexcept { return uint2(n) + v; }
static constexpr uint2 operator-(uint32 n, uint2 v) noexcept { return uint2(n) - v; }
static constexpr uint2 operator*(uint32 n, uint2 v) noexcept { return uint2(n) * v; }
static constexpr uint2 operator/(uint32 n, uint2 v) noexcept { return uint2(n) / v; }
static constexpr uint2 operator%(uint32 n, uint2 v) noexcept { return uint2(n) % v; }
static constexpr uint2 operator&(uint32 n, uint2 v) noexcept { return uint2(n) & v; }
static constexpr uint2 operator|(uint32 n, uint2 v) noexcept { return uint2(n) | v; }
static constexpr uint2 operator^(uint32 n, uint2 v) noexcept { return uint2(n) ^ v; }
static constexpr uint2 operator>>(uint32 n, uint2 v) noexcept { return uint2(n) >> v; }
static constexpr uint2 operator<<(uint32 n, uint2 v) noexcept { return uint2(n) << v; }
static constexpr bool operator==(uint32 n, uint2 v) noexcept { return uint2(n) == v; }
static constexpr bool operator!=(uint32 n, uint2 v) noexcept { return uint2(n) != v; }
static constexpr uint2 operator<(uint32 n, uint2 v) noexcept { return uint2(n) < v; }
static constexpr uint2 operator>(uint32 n, uint2 v) noexcept { return uint2(n) > v; }
static constexpr uint2 operator<=(uint32 n, uint2 v) noexcept { return uint2(n) <= v; }
static constexpr uint2 operator>=(uint32 n, uint2 v) noexcept { return uint2(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(uint2 v) { return to_string(v.x) + " " + to_string(v.y); }

/**
 * @brief Returns true if all vector components are set true.
 */
static constexpr bool areAllTrue(uint2 v) noexcept { return v.x & v.y; }
/**
 * @brief Returns false if all vector components are set false.
 */
static constexpr bool areAllFalse(uint2 v) noexcept { return !(v.x | v.y); }
/**
 * @brief Returns true if any of vector components are set true.
 */
static constexpr bool areAnyTrue(uint2 v) noexcept { return v.x | v.y; }
/**
 * @brief Returns false if any of vector components are set false.
 */
static constexpr bool areAnyFalse(uint2 v) noexcept { return !(v.x & v.y); }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b second vector to binary compare
 */
static bool isBinaryLess(uint2 a, uint2 b) noexcept { return *((const uint64*)&a) < *((const uint64*)&b); }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr uint2 select(uint2 c, uint2 t, uint2 f) noexcept
{
	return uint2(c.x ? t.x : f.x, c.y ? t.y : f.y);
}

//**********************************************************************************************************************
static constexpr uint3 operator+(uint32 n, const uint3& v) noexcept { return uint3(n) + v; }
static constexpr uint3 operator-(uint32 n, const uint3& v) noexcept { return uint3(n) - v; }
static constexpr uint3 operator*(uint32 n, const uint3& v) noexcept { return uint3(n) * v; }
static constexpr uint3 operator/(uint32 n, const uint3& v) noexcept { return uint3(n) / v; }
static constexpr uint3 operator%(uint32 n, const uint3& v) noexcept { return uint3(n) % v; }
static constexpr uint3 operator&(uint32 n, const uint3& v) noexcept { return uint3(n) & v; }
static constexpr uint3 operator|(uint32 n, const uint3& v) noexcept { return uint3(n) | v; }
static constexpr uint3 operator^(uint32 n, const uint3& v) noexcept { return uint3(n) ^ v; }
static constexpr uint3 operator>>(uint32 n, const uint3& v) noexcept { return uint3(n) >> v; }
static constexpr uint3 operator<<(uint32 n, const uint3& v) noexcept { return uint3(n) << v; }
static constexpr bool operator==(uint32 n, const uint3& v) noexcept { return uint3(n) == v; }
static constexpr bool operator!=(uint32 n, const uint3& v) noexcept { return uint3(n) != v; }
static constexpr uint3 operator<(uint32 n, const uint3& v) noexcept { return uint3(n) < v; }
static constexpr uint3 operator>(uint32 n, const uint3& v) noexcept { return uint3(n) > v; }
static constexpr uint3 operator<=(uint32 n, const uint3& v) noexcept { return uint3(n) <= v; }
static constexpr uint3 operator>=(uint32 n, const uint3& v) noexcept { return uint3(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(uint3 v) { return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z); }

/**
 * @brief Returns true if all vector components are set true.
 */
static constexpr bool areAllTrue(uint3 v) noexcept { return v.x & v.y & v.z; }
/**
 * @brief Returns false if all vector components are set false.
 */
static constexpr bool areAllFalse(uint3 v) noexcept { return !(v.x | v.y | v.z); }
/**
 * @brief Returns true if any of vector components are set true.
 */
static constexpr bool areAnyTrue(uint3 v) noexcept { return v.x | v.y | v.z; }
/**
 * @brief Returns false if any of vector components are set false.
 */
static constexpr bool areAnyFalse(uint3 v) noexcept { return !(v.x & v.y & v.z); }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const uint3& a, const uint3& b) noexcept { return memcmp(&a, &b, sizeof(uint32) * 3) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param c control vector (contains is true or false)
 * @param t contains components for true condition
 * @param f contains components for false condition
 */
static constexpr uint3 select(uint3 c, uint3 t, uint3 f) noexcept
{
	return uint3(c.x ? t.x : f.x, c.y ? t.y : f.y, c.z ? t.z : f.z);
}

//**********************************************************************************************************************
static constexpr uint4 operator+(uint32 n, const uint4& v) noexcept { return uint4(n) + v; }
static constexpr uint4 operator-(uint32 n, const uint4& v) noexcept { return uint4(n) - v; }
static constexpr uint4 operator*(uint32 n, const uint4& v) noexcept { return uint4(n) * v; }
static constexpr uint4 operator/(uint32 n, const uint4& v) noexcept { return uint4(n) / v; }
static constexpr uint4 operator%(uint32 n, const uint4& v) noexcept { return uint4(n) % v; }
static constexpr uint4 operator&(uint32 n, const uint4& v) noexcept { return uint4(n) & v; }
static constexpr uint4 operator|(uint32 n, const uint4& v) noexcept { return uint4(n) | v; }
static constexpr uint4 operator^(uint32 n, const uint4& v) noexcept { return uint4(n) ^ v; }
static constexpr uint4 operator>>(uint32 n, const uint4& v) noexcept { return uint4(n) >> v; }
static constexpr uint4 operator<<(uint32 n, const uint4& v) noexcept { return uint4(n) << v; }
static constexpr bool operator==(uint32 n, const uint4& v) noexcept { return uint4(n) == v; }
static constexpr bool operator!=(uint32 n, const uint4& v) noexcept { return uint4(n) != v; }
static constexpr uint4 operator<(uint32 n, const uint4& v) noexcept { return uint4(n) < v; }
static constexpr uint4 operator>(uint32 n, const uint4& v) noexcept { return uint4(n) > v; }
static constexpr uint4 operator<=(uint32 n, const uint4& v) noexcept { return uint4(n) <= v; }
static constexpr uint4 operator>=(uint32 n, const uint4& v) noexcept { return uint4(n) >= v; }

/**
 * @brief Converts vector to the string. (space separated)
 * @param v target vector to convert
 */
static string toString(uint4 v)
{
	return to_string(v.x) + " " + to_string(v.y) + " " + to_string(v.z) + " " + to_string(v.w);
}

/**
 * @brief Returns true if all vector components are set true.
 */
static constexpr bool areAllTrue(uint4 v) noexcept { return v.x && v.y && v.z && v.w; }
/**
 * @brief Returns false if all vector components are set false.
 */
static constexpr bool areAllFalse(uint4 v) noexcept { return !(v.x || v.y || v.z || v.w); }
/**
 * @brief Returns true if any of vector components are set true.
 */
static constexpr bool areAnyTrue(uint4 v) noexcept { return v.x || v.y || v.z || v.w; }
/**
 * @brief Returns false if any of vector components are set false.
 */
static constexpr bool areAnyFalse(uint4 v) noexcept { return !(v.x && v.y && v.z && v.w); }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b second vector to binary compare
 */
static bool isBinaryLess(const uint4& a, const uint4& b) noexcept { return memcmp(&a, &b, sizeof(uint32) * 4) < 0; }

/**
 * @brief Selects between two vector components based on the control vector values.
 * 
 * @param[in] c control vector (contains is true or false)
 * @param[in] t contains components for true condition
 * @param[in] f contains components for false condition
 */
static constexpr uint4 select(uint4 c, uint4 t, uint4 f) noexcept
{
	return uint4(c.x ? t.x : f.x, c.y ? t.y : f.y, c.z ? t.z : f.z, c.w ? t.w : f.w);
}

//**********************************************************************************************************************
static constexpr uint2 min(uint2 a, uint2 b) noexcept { return uint2(std::min(a.x, b.x), std::min(a.y, b.y)); }
static constexpr uint2 max(uint2 a, uint2 b) noexcept { return uint2(std::max(a.x, b.x), std::max(a.y, b.y)); }
static constexpr uint2 min(uint2 a, uint2 b, uint2 c) noexcept { return min(min(a, b), c); }
static constexpr uint2 max(uint2 a, uint2 b, uint2 c) noexcept { return max(max(a, b), c); }
static constexpr uint2 clamp(uint2 v, uint2 min, uint2 max) noexcept
{
	return uint2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}
static constexpr uint32 dot(uint2 a, uint2 b) noexcept { return a.x * b.x + a.y * b.y; }
static constexpr uint32 length2(uint2 v) noexcept { return dot(v, v); }
static constexpr uint32 distance2(uint2 a, uint2 b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static constexpr uint3 min(uint3 a, uint3 b) noexcept
{
	return uint3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
static constexpr uint3 max(uint3 a, uint3 b) noexcept
{
	return uint3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
static constexpr uint3 min(const uint3& a, const uint3& b, const uint3& c) noexcept { return min(min(a, b), c); }
static constexpr uint3 max(const uint3& a, const uint3& b, const uint3& c) noexcept { return max(max(a, b), c); }
static constexpr uint3 clamp(uint3 v, uint3 min, uint3 max) noexcept
{
	return uint3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

static constexpr uint32 dot(uint3 a, uint3 b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
static constexpr uint32 length2(const uint3& v) noexcept { return dot(v, v); }
static constexpr uint32 distance2(const uint3& a, const uint3& b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static constexpr uint4 min(uint4 a, uint4 b) noexcept
{
	return uint4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
static constexpr uint4 max(uint4 a, uint4 b) noexcept
{
	return uint4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
static constexpr uint4 min(const uint4& a, const uint4& b, const uint4& c) noexcept { return min(min(a, b), c); }
static constexpr uint4 max(const uint4& a, const uint4& b, const uint4& c) noexcept { return max(max(a, b), c); }
static constexpr uint4 clamp(uint4 v, uint4 min, uint4 max) noexcept
{
	return uint4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}
static constexpr uint32 dot(uint4 a, uint4 b) noexcept
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static constexpr uint32 length2(const uint4& v) noexcept { return dot(v, v); }
static constexpr uint32 distance2(const uint4& a, const uint4& b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static uint8 calcMipCount(uint32 size) noexcept
{
	return (uint8)(std::floor(std::log2((float)size))) + 1u;
}
static uint8 calcMipCount(uint2 size) noexcept
{
	return (uint8)(std::floor(std::log2((float)std::max(size.x, size.y)))) + 1u;
}
static uint8 calcMipCount(uint3 size) noexcept
{
	return (uint8)(std::floor(std::log2((float)std::max(std::max(size.x, size.y), size.z)))) + 1u;
}

static uint32 calcSizeAtMip(uint32 sizeAt0, uint8 mip) noexcept
{
	return std::max(sizeAt0 / (uint32)std::exp2((float)mip), 1u);
}
static uint2 calcSizeAtMip(uint2 sizeAt0, uint8 mip) noexcept
{
	return max(sizeAt0 / (uint32)std::exp2((float)mip), uint2(1u));
}
static uint3 calcSizeAtMip(const uint3& sizeAt0, uint8 mip) noexcept
{
	return max(sizeAt0 / (uint32)std::exp2((float)mip), uint3(1u));
}

} // namespace math