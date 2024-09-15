// Copyright 2022-2024 Nikita Fediuchin. All rights reserved.
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

/***********************************************************************************************************************
 * @brief Unsigned integer 2 component vector structure.
 * @details Commonly used to represent: points, positions, etc.
 */
struct uint2
{
	uint32 x; /**< First vector component. */
	uint32 y; /**< Second vector component. */

	/**
	 * @brief Creates a new unsigned integer 2 component vector structure.
	 * @param xy target value for all vector components
	 */
	explicit uint2(uint32 xy = 0u) noexcept { this->x = xy; this->y = xy; }
	/**
	 * @brief Creates a new unsigned integer 2 component vector structure.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	uint2(uint32 x, uint32 y) noexcept { this->x = x; this->y = y; }

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
	 * @brief Returns first vector component. (x)
	 */
	explicit operator uint32() noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y); }

	uint2 operator+(uint2 v) const noexcept { return uint2(x + v.x, y + v.y); }
	uint2 operator-(uint2 v) const noexcept { return uint2(x - v.x, y - v.y); }
	uint2 operator*(uint2 v) const noexcept { return uint2(x * v.x, y * v.y); }
	uint2 operator/(uint2 v) const noexcept { return uint2(x / v.x, y / v.y); }
	uint2 operator%(uint2 v) const noexcept { return uint2(x % v.x, y % v.y); }
	uint2 operator&(uint2 v) const noexcept { return uint2(x & v.x, y & v.y); }
	uint2 operator|(uint2 v) const noexcept { return uint2(x | v.x, y | v.y); }
	uint2 operator^(uint2 v) const noexcept { return uint2(x ^ v.x, y ^ v.y); }
	uint2 operator>>(uint2 v) const noexcept { return uint2(x >> v.x, y >> v.y); }
	uint2 operator<<(uint2 v) const noexcept { return uint2(x << v.x, y << v.y); }
	uint2 operator-() const noexcept { return uint2(-x, -y); }
	uint2 operator!() const noexcept { return uint2(!x, !y); }
	uint2 operator~() const noexcept { return uint2(~x, ~y); }
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
	bool operator==(uint2 v) const noexcept { return *((uint64*)this) == *((uint64*)&v); }
	bool operator!=(uint2 v) const noexcept { return *((uint64*)this) != *((uint64*)&v); }
	bool operator<(uint2 v) const noexcept { return x < v.x && y < v.y; }
	bool operator>(uint2 v) const noexcept { return x > v.x && y > v.y; }
	bool operator<=(uint2 v) const noexcept { return x <= v.x && y <= v.y; }
	bool operator>=(uint2 v) const noexcept { return x >= v.x && y >= v.y; }

	static const uint2 zero, one;
};

inline const uint2 uint2::zero = uint2(0u);
inline const uint2 uint2::one = uint2(1u);

/***********************************************************************************************************************
 * @brief Unsigned integer 3 component vector structure.
 * @details Commonly used to represent: points, positions, etc.
 */
struct uint3
{
	uint32 x; /**< First vector component. */
	uint32 y; /**< Second vector component. */
	uint32 z; /**< Third vector component. */

	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 * @param xyz target value for all vector components
	 */
	explicit uint3(uint32 xyz = 0u) noexcept { this->x = xyz; this->y = xyz; this->z = xyz; }
	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	uint3(uint32 x, uint32 y, uint32 z) noexcept { this->x = x; this->y = y; this->z = z; }
	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 *
	 * @param xy first and secind vector components value
	 * @param z third vector component value
	 */
	uint3(uint2 xy, uint32 z) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; }
	/**
	 * @brief Creates a new unsigned integer 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 */
	uint3(uint32 x, uint2 yz) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; }

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
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator uint2() const noexcept { return uint2(x, y); }
	/**
	 * @brief Returns first vector component. (xy)
	 */
	explicit operator uint32() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y) + " " + to_string(z); }

	uint3 operator+(const uint3& v) const noexcept { return uint3(x + v.x, y + v.y, z + v.z); }
	uint3 operator-(const uint3& v) const noexcept { return uint3(x - v.x, y - v.y, z - v.z); }
	uint3 operator*(const uint3& v) const noexcept { return uint3(x * v.x, y * v.y, z * v.z); }
	uint3 operator/(const uint3& v) const noexcept { return uint3(x / v.x, y / v.y, z / v.z); }
	uint3 operator%(const uint3& v) const noexcept { return uint3(x % v.x, y % v.y, z % v.z); }
	uint3 operator&(const uint3& v) const noexcept { return uint3(x & v.x, y & v.y, z & v.z); }
	uint3 operator|(const uint3& v) const noexcept { return uint3(x | v.x, y | v.y, z | v.z); }
	uint3 operator^(const uint3& v) const noexcept { return uint3(x ^ v.x, y ^ v.y, z ^ v.z); }
	uint3 operator>>(const uint3& v) const noexcept { return uint3(x >> v.x, y >> v.y, z >> v.z); }
	uint3 operator<<(const uint3& v) const noexcept { return uint3(x << v.x, y << v.y, z << v.z); }
	uint3 operator-() const noexcept { return uint3(-x, -y, -z); }
	uint3 operator!() const noexcept { return uint3(!x, !y, !z); }
	uint3 operator~() const noexcept { return uint3(~x, ~y, ~z); }
	uint3& operator+=(const uint3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	uint3& operator-=(const uint3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	uint3& operator*=(const uint3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	uint3& operator/=(const uint3& v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	uint3& operator%=(const uint3& v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	uint3& operator&=(const uint3& v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	uint3& operator|=(const uint3& v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	uint3& operator^=(const uint3& v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	uint3& operator>>=(const uint3& v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	uint3& operator<<=(const uint3& v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
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
	bool operator==(const uint3& v) const noexcept { return memcmp(this, &v, sizeof(uint32) * 3) == 0; }
	bool operator!=(const uint3& v) const noexcept { return memcmp(this, &v, sizeof(uint32) * 3) != 0; }
	bool operator<(const uint3& v) const noexcept {return x < v.x && y < v.y && z < v.z; }
	bool operator>(const uint3& v) const noexcept {return x > v.x && y > v.y && z > v.z; }
	bool operator<=(const uint3& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z; }
	bool operator>=(const uint3& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z; }

	static const uint3 zero, one;
};

inline const uint3 uint3::zero = uint3(0u);
inline const uint3 uint3::one = uint3(1u);

/***********************************************************************************************************************
 * @brief Unsigned integer 4 component vector structure.
 * @details Commonly used to represent: points, positions, etc.
 */
struct uint4
{
	uint32 x; /**< First vector component. */
	uint32 y; /**< Second vector component. */
	uint32 z; /**< Third vector component. */
	uint32 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit uint4(uint32 xyzw = 0u) noexcept { this->x = xyzw; this->y = xyzw; this->z = xyzw; this->w = xyzw; }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	uint4(uint32 x, uint32 y, uint32 z, uint32 w) noexcept { this->x = x; this->y = y; this->z = z; this->w = w;}
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	uint4(uint2 xy, uint32 z, uint32 w) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; this->w = w; }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 * @param w fourth vector component value
	 */
	uint4(uint32 x, uint2 yz, uint32 w) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; this->w = w; }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector components value
	 */
	uint4(uint32 x, uint32 y, uint2 zw) noexcept { this->x = x; this->y = y; this->z = zw.x; this->w = zw.y; }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param zw third and fourth vector components value
	 */
	uint4(uint2 xy, uint2 zw) noexcept { this->x = xy.x; this->y = xy.x; this->z = zw.x; this->w = zw.y; }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param[in] xyz first, second and third vector components value
	 * @param w fourth vector component value
	 */
	uint4(const uint3& xyz, uint32 w) noexcept { this->x = xyz.x; this->y = xyz.y; this->z = xyz.z; this->w = w; }
	/**
	 * @brief Creates a new unsigned integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector components value
	 */
	uint4(uint32 x, const uint3& yzw) noexcept { this->x = x; this->y = yzw.x; this->z = yzw.y; this->w = yzw.z; }

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
	 * @brief Returns first, second and third vector components. (xyz)
	 */
	explicit operator uint3() const noexcept { return uint3(x, y, z); }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator uint2() const noexcept { return uint2(x, y); }
	/**
	 * @brief Returns first vector component. (x)
	 */
	explicit operator uint32() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept
	{
		return to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(w);
	}

	uint4 operator+(const uint4& v) const noexcept { return uint4(x + v.x, y + v.y, z + v.z, w + v.w); }
	uint4 operator-(const uint4& v) const noexcept { return uint4(x - v.x, y - v.y, z - v.z, w - v.w); }
	uint4 operator*(const uint4& v) const noexcept { return uint4(x * v.x, y * v.y, z * v.z, w * v.w); }
	uint4 operator/(const uint4& v) const noexcept { return uint4(x / v.x, y / v.y, z / v.z, w / v.w); }
	uint4 operator%(const uint4& v) const noexcept { return uint4(x % v.x, y % v.y, z % v.z, w % v.w); }
	uint4 operator&(const uint4& v) const noexcept { return uint4(x & v.x, y & v.y, z & v.z, w & v.w); }
	uint4 operator|(const uint4& v) const noexcept { return uint4(x | v.x, y | v.y, z | v.z, w | v.w); }
	uint4 operator^(const uint4& v) const noexcept { return uint4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	uint4 operator>>(const uint4& v) const noexcept { return uint4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	uint4 operator<<(const uint4& v) const noexcept { return uint4(x << v.x, y << v.y, z << v.z, w << v.w); }
	uint4 operator-() const noexcept { return uint4(-x, -y, -z, -w); }
	uint4 operator!() const noexcept { return uint4(!x, !y, !z, !w); }
	uint4 operator~() const noexcept { return uint4(~x, ~y, ~z, ~w); }
	uint4& operator+=(const uint4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	uint4& operator-=(const uint4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	uint4& operator*=(const uint4& v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	uint4& operator/=(const uint4& v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	uint4& operator%=(const uint4& v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	uint4& operator&=(const uint4& v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	uint4& operator|=(const uint4& v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	uint4& operator^=(const uint4& v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	uint4& operator>>=(const uint4& v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	uint4& operator<<=(const uint4& v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
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
	bool operator==(const uint4& v) const noexcept { return memcmp(this, &v, sizeof(uint32) * 4) == 0; }
	bool operator!=(const uint4& v) const noexcept { return memcmp(this, &v, sizeof(uint32) * 4) != 0; }
	bool operator<(const uint4& v) const noexcept { return x < v.x && y < v.y && z < v.z && w < v.w; }
	bool operator>(const uint4& v) const noexcept { return x > v.x && y > v.y && z > v.z && w > v.w; }
	bool operator<=(const uint4& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z && w <= v.w; }
	bool operator>=(const uint4& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z && w >= v.w; }

	static const uint4 zero, one;
};

inline const uint4 uint4::zero = uint4(0u);
inline const uint4 uint4::one = uint4(1u);

//**********************************************************************************************************************
static uint2 operator+(uint2 v, uint32 n) noexcept { return uint2(v.x + n, v.y + n); }
static uint2 operator-(uint2 v, uint32 n) noexcept { return uint2(v.x - n, v.y - n); }
static uint2 operator*(uint2 v, uint32 n) noexcept { return uint2(v.x * n, v.y * n); }
static uint2 operator/(uint2 v, uint32 n) noexcept { return uint2(v.x / n, v.y / n); }
static uint2 operator%(uint2 v, uint32 n) noexcept { return uint2(v.x % n, v.y % n); }
static uint2 operator&(uint2 v, uint32 n) noexcept { return uint2(v.x & n, v.y & n); }
static uint2 operator|(uint2 v, uint32 n) noexcept { return uint2(v.x | n, v.y | n); }
static uint2 operator^(uint2 v, uint32 n) noexcept { return uint2(v.x ^ n, v.y ^ n); }
static uint2 operator>>(uint2 v, uint32 n) noexcept { return uint2(v.x >> n, v.y >> n); }
static uint2 operator<<(uint2 v, uint32 n) noexcept { return uint2(v.x << n, v.y << n); }
static bool operator==(uint2 v, uint32 n) noexcept { return v == uint2(n); }
static bool operator!=(uint2 v, uint32 n) noexcept { return v != uint2(n); }
static bool operator<(uint2 v, uint32 n) noexcept { return v < uint2(n); }
static bool operator>(uint2 v, uint32 n) noexcept { return v > uint2(n); }
static bool operator<=(uint2 v, uint32 n) noexcept { return v <= uint2(n); }
static bool operator>=(uint2 v, uint32 n) noexcept { return v >= uint2(n); }

static uint2 operator+(uint32 n, uint2 v) noexcept { return uint2(n + v.x, n + v.y); }
static uint2 operator-(uint32 n, uint2 v) noexcept { return uint2(n - v.x, n - v.y); }
static uint2 operator*(uint32 n, uint2 v) noexcept { return uint2(n * v.x, n * v.y); }
static uint2 operator/(uint32 n, uint2 v) noexcept { return uint2(n / v.x, n / v.y); }
static uint2 operator%(uint32 n, uint2 v) noexcept { return uint2(n % v.x, n % v.y); }
static uint2 operator&(uint32 n, uint2 v) noexcept { return uint2(n & v.x, n & v.y); }
static uint2 operator|(uint32 n, uint2 v) noexcept { return uint2(n | v.x, n | v.y); }
static uint2 operator^(uint32 n, uint2 v) noexcept { return uint2(n ^ v.x, n ^ v.y); }
static uint2 operator>>(uint32 n, uint2 v) noexcept { return uint2(n >> v.x, n >> v.y); }
static uint2 operator<<(uint32 n, uint2 v) noexcept { return uint2(n << v.x, n << v.y); }
static bool operator==(uint32 n, uint2 v) noexcept { return uint2(n) == v; }
static bool operator!=(uint32 n, uint2 v) noexcept { return uint2(n) != v; }
static bool operator<(uint32 n, uint2 v) noexcept { return uint2(n) < v; }
static bool operator>(uint32 n, uint2 v) noexcept { return uint2(n) > v; }
static bool operator<=(uint32 n, uint2 v) noexcept { return uint2(n) <= v; }
static bool operator>=(uint32 n, uint2 v) noexcept { return uint2(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b secong vector to binary compare
 */
static bool isBinaryLess(uint2 a, uint2 b) noexcept { return *((const uint64*)&a) < *((const uint64*)&b); }

//**********************************************************************************************************************
static uint3 operator+(const uint3& v, uint32 n) noexcept { return uint3(v.x + n, v.y + n, v.z + n); }
static uint3 operator-(const uint3& v, uint32 n) noexcept { return uint3(v.x - n, v.y - n, v.z - n); }
static uint3 operator*(const uint3& v, uint32 n) noexcept { return uint3(v.x * n, v.y * n, v.z * n); }
static uint3 operator/(const uint3& v, uint32 n) noexcept { return uint3(v.x / n, v.y / n, v.z / n); }
static uint3 operator%(const uint3& v, uint32 n) noexcept { return uint3(v.x % n, v.y % n, v.z % n); }
static uint3 operator&(const uint3& v, uint32 n) noexcept { return uint3(v.x & n, v.y & n, v.z & n); }
static uint3 operator|(const uint3& v, uint32 n) noexcept { return uint3(v.x | n, v.y | n, v.z | n); }
static uint3 operator^(const uint3& v, uint32 n) noexcept { return uint3(v.x ^ n, v.y ^ n, v.z ^ n); }
static uint3 operator>>(const uint3& v, uint32 n) noexcept { return uint3(v.x >> n, v.y >> n, v.z >> n); }
static uint3 operator<<(const uint3& v, uint32 n) noexcept { return uint3(v.x << n, v.y << n, v.z << n); }
static bool operator==(const uint3& v, uint32 n) noexcept { return v == uint3(n); }
static bool operator!=(const uint3& v, uint32 n) noexcept { return v != uint3(n); }
static bool operator<(const uint3& v, uint32 n) noexcept { return v < uint3(n); }
static bool operator>(const uint3& v, uint32 n) noexcept { return v > uint3(n); }
static bool operator<=(const uint3& v, uint32 n) noexcept { return v <= uint3(n); }
static bool operator>=(const uint3& v, uint32 n) noexcept { return v >= uint3(n); }

static uint3 operator+(uint32 n, const uint3& v) noexcept { return uint3(n + v.x, n + v.y, n + v.z); }
static uint3 operator-(uint32 n, const uint3& v) noexcept { return uint3(n - v.x, n - v.y, n - v.z); }
static uint3 operator*(uint32 n, const uint3& v) noexcept { return uint3(n * v.x, n * v.y, n * v.z); }
static uint3 operator/(uint32 n, const uint3& v) noexcept { return uint3(n / v.x, n / v.y, n / v.z); }
static uint3 operator%(uint32 n, const uint3& v) noexcept { return uint3(n % v.x, n % v.y, n % v.z); }
static uint3 operator&(uint32 n, const uint3& v) noexcept { return uint3(n & v.x, n & v.y, n & v.z); }
static uint3 operator|(uint32 n, const uint3& v) noexcept { return uint3(n | v.x, n | v.y, n | v.z); }
static uint3 operator^(uint32 n, const uint3& v) noexcept { return uint3(n ^ v.x, n ^ v.y, n ^ v.z); }
static uint3 operator>>(uint32 n, const uint3& v) noexcept { return uint3(n >> v.x, n >> v.y, n >> v.z); }
static uint3 operator<<(uint32 n, const uint3& v) noexcept { return uint3(n << v.x, n << v.y, n << v.z); }
static bool operator==(uint32 n, const uint3& v) noexcept { return uint3(n) == v; }
static bool operator!=(uint32 n, const uint3& v) noexcept { return uint3(n) != v; }
static bool operator<(uint32 n, const uint3& v) noexcept { return uint3(n) < v; }
static bool operator>(uint32 n, const uint3& v) noexcept { return uint3(n) > v; }
static bool operator<=(uint32 n, const uint3& v) noexcept { return uint3(n) <= v; }
static bool operator>=(uint32 n, const uint3& v) noexcept { return uint3(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const uint3& a, const uint3& b) noexcept { return memcmp(&a, &b, sizeof(uint32) * 3) < 0; }

//**********************************************************************************************************************
static uint4 operator+(const uint4& v, uint32 n) noexcept { return uint4(v.x + n, v.y + n, v.z + n, v.w + n); }
static uint4 operator-(const uint4& v, uint32 n) noexcept { return uint4(v.x - n, v.y - n, v.z - n, v.w - n); }
static uint4 operator*(const uint4& v, uint32 n) noexcept { return uint4(v.x * n, v.y * n, v.z * n, v.w * n); }
static uint4 operator/(const uint4& v, uint32 n) noexcept { return uint4(v.x / n, v.y / n, v.z / n, v.w / n); }
static uint4 operator%(const uint4& v, uint32 n) noexcept { return uint4(v.x % n, v.y % n, v.z % n, v.w % n); }
static uint4 operator&(const uint4& v, uint32 n) noexcept { return uint4(v.x & n, v.y & n, v.z & n, v.w & n); }
static uint4 operator|(const uint4& v, uint32 n) noexcept { return uint4(v.x | n, v.y | n, v.z | n, v.w | n); }
static uint4 operator^(const uint4& v, uint32 n) noexcept { return uint4(v.x ^ n, v.y ^ n, v.z ^ n, v.w ^ n); }
static uint4 operator>>(const uint4& v, uint32 n) noexcept { return uint4(v.x >> n, v.y >> n, v.z >> n, v.w >> n); }
static uint4 operator<<(const uint4& v, uint32 n) noexcept { return uint4(v.x << n, v.y << n, v.z << n, v.w << n); }
static bool operator==(const uint4& v, uint32 n) noexcept { return v == uint4(n); }
static bool operator!=(const uint4& v, uint32 n) noexcept { return v != uint4(n); }
static bool operator<(const uint4& v, uint32 n) noexcept { return v < uint4(n); }
static bool operator>(const uint4& v, uint32 n) noexcept { return v > uint4(n); }
static bool operator<=(const uint4& v, uint32 n) noexcept { return v <= uint4(n); }
static bool operator>=(const uint4& v, uint32 n) noexcept { return v >= uint4(n); }

static uint4 operator+(uint32 n, const uint4& v) noexcept { return uint4(n + v.x, n + v.y, n + v.z, n + v.w); }
static uint4 operator-(uint32 n, const uint4& v) noexcept { return uint4(n - v.x, n - v.y, n - v.z, n - v.w); }
static uint4 operator*(uint32 n, const uint4& v) noexcept { return uint4(n * v.x, n * v.y, n * v.z, n * v.w); }
static uint4 operator/(uint32 n, const uint4& v) noexcept { return uint4(n / v.x, n / v.y, n / v.z, n / v.w); }
static uint4 operator%(uint32 n, const uint4& v) noexcept { return uint4(n % v.x, n % v.y, n % v.z, n % v.w); }
static uint4 operator&(uint32 n, const uint4& v) noexcept { return uint4(n & v.x, n & v.y, n & v.z, n & v.w); }
static uint4 operator|(uint32 n, const uint4& v) noexcept { return uint4(n | v.x, n | v.y, n | v.z, n | v.w); }
static uint4 operator^(uint32 n, const uint4& v) noexcept { return uint4(n ^ v.x, n ^ v.y, n ^ v.z, n ^ v.w); }
static uint4 operator>>(uint32 n, const uint4& v) noexcept { return uint4(n >> v.x, n >> v.y, n >> v.z, n >> v.w); }
static uint4 operator<<(uint32 n, const uint4& v) noexcept { return uint4(n << v.x, n << v.y, n << v.z, n << v.w); }
static bool operator==(uint32 n, const uint4& v) noexcept { return uint4(n) == v; }
static bool operator!=(uint32 n, const uint4& v) noexcept { return uint4(n) != v; }
static bool operator<(uint32 n, const uint4& v) noexcept { return uint4(n) < v; }
static bool operator>(uint32 n, const uint4& v) noexcept { return uint4(n) > v; }
static bool operator<=(uint32 n, const uint4& v) noexcept { return uint4(n) <= v; }
static bool operator>=(uint32 n, const uint4& v) noexcept { return uint4(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const uint4& a, const uint4& b) noexcept { return memcmp(&a, &b, sizeof(uint32) * 4) < 0; }

//**********************************************************************************************************************
static uint2 min(uint2 a, uint2 b) noexcept { return uint2(std::min(a.x, b.x), std::min(a.y, b.y)); }
static uint2 max(uint2 a, uint2 b) noexcept { return uint2(std::max(a.x, b.x), std::max(a.y, b.y)); }
static uint2 min(uint2 a, uint2 b, uint2 c) noexcept { return min(min(a, b), c); }
static uint2 max(uint2 a, uint2 b, uint2 c) noexcept { return max(max(a, b), c); }

static uint2 clamp(uint2 v, uint2 min, uint2 max) noexcept
{
	return uint2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}
static uint32 dot(uint2 a, uint2 b) noexcept { return a.x * b.x + a.y * b.y; }
static uint32 length2(uint2 v) noexcept { return dot(v, v); }
static uint32 distance2(uint2 a, uint2 b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static uint3 min(const uint3& a, const uint3& b) noexcept
{
	return uint3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
static uint3 max(const uint3& a, const uint3& b) noexcept
{
	return uint3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
static uint3 min(const uint3& a, const uint3& b, const uint3& c) noexcept { return min(min(a, b), c); }
static uint3 max(const uint3& a, const uint3& b, const uint3& c) noexcept { return max(max(a, b), c); }
static uint3 clamp(const uint3& v, const uint3& min, const uint3& max) noexcept
{
	return uint3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

static uint32 dot(const uint3& a, const uint3& b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
static uint32 length2(const uint3& v) noexcept { return dot(v, v); }
static uint32 distance2(const uint3& a, const uint3& b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static uint4 min(const uint4& a, const uint4& b) noexcept
{
	return uint4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
static uint4 max(const uint4& a, const uint4& b) noexcept
{
	return uint4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
static uint4 min(const uint4& a, const uint4& b, const uint4& c) noexcept { return min(min(a, b), c); }
static uint4 max(const uint4& a, const uint4& b, const uint4& c) noexcept { return max(max(a, b), c); }

static uint4 clamp(const uint4& v, const uint4& min, const uint4& max) noexcept
{
	return uint4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}
static uint32 dot(const uint4& a, const uint4& b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
static uint32 length2(const uint4& v) noexcept { return dot(v, v); }
static uint32 distance2(const uint4& a, const uint4& b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static uint8 calcMipCount(uint32 size) noexcept
{
	return (uint8)(std::floor(std::log2((float)size))) + 1u;
}
static uint8 calcMipCount(uint2 size) noexcept
{
	return (uint8)(std::floor(std::log2((float)std::max(size.x, size.y)))) + 1u;
}
static uint8 calcMipCount(const uint3& size) noexcept
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