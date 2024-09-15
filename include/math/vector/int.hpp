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
 * @brief Common signed integer vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector/uint.hpp"

namespace math
{

using namespace std;

/***********************************************************************************************************************
 * @brief Signed integer 2 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct int2
{
	int32 x; /**< First vector component. */
	int32 y; /**< Second vector component. */

	/**
	 * @brief Creates a new signed integer 2 component vector structure.
	 * @param xy target value for all vector components
	 */
	explicit int2(int32 xy = 0) noexcept { this->x = xy; this->y = xy; }
	/**
	 * @brief Creates a new signed integer 2 component vector structure.
	 * 
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	int2(int32 x, int32 y) noexcept { this->x = x; this->y = y; }
	/**
	 * @brief Creates a new signed integer 2 component vector structure.
	 * @param xy target unsigned integer vector value
	 */
	int2(uint2 xy) noexcept { this->x = (int32)xy.x; this->y = (int32)xy.y; }

	/**
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

	/**
	 * @brief Returns first and second vector components as uint. (xy)
	 */
	explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first vector component as uint. (x)
	 */
	explicit operator uint32() noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component. (x)
	 */
	explicit operator int32() noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y); }

	int2 operator+(int2 v) const noexcept { return int2(x + v.x, y + v.y); }
	int2 operator-(int2 v) const noexcept { return int2(x - v.x, y - v.y); }
	int2 operator*(int2 v) const noexcept { return int2(x * v.x, y * v.y); }
	int2 operator/(int2 v) const noexcept { return int2(x / v.x, y / v.y); }
	int2 operator%(int2 v) const noexcept { return int2(x % v.x, y % v.y); }
	int2 operator&(int2 v) const noexcept { return int2(x & v.x, y & v.y); }
	int2 operator|(int2 v) const noexcept { return int2(x | v.x, y | v.y); }
	int2 operator^(int2 v) const noexcept { return int2(x ^ v.x, y ^ v.y); }
	int2 operator>>(int2 v) const noexcept { return int2(x >> v.x, y >> v.y); }
	int2 operator<<(int2 v) const noexcept { return int2(x << v.x, y << v.y); }
	int2 operator-() const noexcept { return int2(-x, -y); }
	int2 operator!() const noexcept { return int2(!x, !y); }
	int2 operator~() const noexcept { return int2(~x, ~y); }
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
	bool operator==(int2 v) const noexcept { return *((int64*)this) == *((int64*)&v); }
	bool operator!=(int2 v) const noexcept { return *((int64*)this) != *((int64*)&v); }
	bool operator<(int2 v) const noexcept { return x < v.x && y < v.y; }
	bool operator>(int2 v) const noexcept { return x > v.x && y > v.y; }
	bool operator<=(int2 v) const noexcept { return x <= v.x && y <= v.y; }
	bool operator>=(int2 v) const noexcept { return x >= v.x && y >= v.y; }

	static const int2 zero, one, minusOne, left, right, bottom, top;
};

inline const int2 int2::zero = int2(0);
inline const int2 int2::one = int2(1);
inline const int2 int2::minusOne = int2(-1);
inline const int2 int2::left = int2(-1, 0);
inline const int2 int2::right = int2(1, 0);
inline const int2 int2::bottom = int2(0, -1);
inline const int2 int2::top = int2(0, 1);

/***********************************************************************************************************************
 * @brief Signed integer 3 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct int3
{
	int32 x; /**< First vector component. */
	int32 y; /**< Second vector component. */
	int32 z; /**< Third vector component. */

	/**
	 * @brief Creates a new signed integer 3 component vector structure.
	 * @param xyz target value for all vector components
	 */
	explicit int3(int32 xyz = 0) noexcept { this->x = xyz; this->y = xyz; this->z = xyz; }
	/**
	 * @brief Creates a new signed integer 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	int3(int32 x, int32 y, int32 z) noexcept { this->x = x; this->y = y; this->z = z; }
	/**
	 * @brief Creates a new signed integer 3 component vector structure.
	 *
	 * @param xy first and secind vector components value
	 * @param z third vector component value
	 */
	int3(int2 xy, int32 z) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; }
	/**
	 * @brief Creates a new signed integer 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 */
	int3(int32 x, int2 yz) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; }
	/**
	 * @brief Creates a new signed integer 3 component vector structure.
	 * @param[in] xyz target unsigned integer vector value
	 */
	int3(const uint3& xyz) noexcept { this->x = (int32)xyz.x; this->y = (int32)xyz.y; this->z = (int32)xyz.z; }

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

	/**
	 * @brief Returns first, second and third vector components as uint. (xyz)
	 */
	explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	/**
	 * @brief Returns first and second vector components as uint. (xy)
	 */
	explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator int2() const noexcept { return int2(x, y); }
	/**
	 * @brief Returns first vector component as uint. (xy)
	 */
	explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component. (xy)
	 */
	explicit operator int32() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y) + " " + to_string(z); }

	int3 operator+(const int3& v) const noexcept { return int3(x + v.x, y + v.y, z + v.z); }
	int3 operator-(const int3& v) const noexcept { return int3(x - v.x, y - v.y, z - v.z); }
	int3 operator*(const int3& v) const noexcept { return int3(x * v.x, y * v.y, z * v.z); }
	int3 operator/(const int3& v) const noexcept { return int3(x / v.x, y / v.y, z / v.z); }
	int3 operator%(const int3& v) const noexcept { return int3(x % v.x, y % v.y, z % v.z); }
	int3 operator&(const int3& v) const noexcept { return int3(x & v.x, y & v.y, z & v.z); }
	int3 operator|(const int3& v) const noexcept { return int3(x | v.x, y | v.y, z | v.z); }
	int3 operator^(const int3& v) const noexcept { return int3(x ^ v.x, y ^ v.y, z ^ v.z); }
	int3 operator>>(const int3& v) const noexcept { return int3(x >> v.x, y >> v.y, z >> v.z); }
	int3 operator<<(const int3& v) const noexcept { return int3(x << v.x, y << v.y, z << v.z); }
	int3 operator-() const noexcept { return int3(-x, -y, -z); }
	int3 operator!() const noexcept { return int3(!x, !y, !z); }
	int3 operator~() const noexcept { return int3(~x, ~y, ~z); }
	int3& operator+=(const int3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	int3& operator-=(const int3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	int3& operator*=(const int3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	int3& operator/=(const int3& v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	int3& operator%=(const int3& v) noexcept { x %= v.x; y %= v.y; z %= v.z; return *this; }
	int3& operator&=(const int3& v) noexcept { x &= v.x; y &= v.y; z &= v.z; return *this; }
	int3& operator|=(const int3& v) noexcept { x |= v.x; y |= v.y; z |= v.z; return *this; }
	int3& operator^=(const int3& v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	int3& operator>>=(const int3& v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	int3& operator<<=(const int3& v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
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
	bool operator==(const int3& v) const noexcept { return memcmp(this, &v, sizeof(int32) * 3) == 0; }
	bool operator!=(const int3& v) const noexcept { return memcmp(this, &v, sizeof(int32) * 3) != 0; }
	bool operator<(const int3& v) const noexcept {return x < v.x && y < v.y && z < v.z; }
	bool operator>(const int3& v) const noexcept {return x > v.x && y > v.y && z > v.z; }
	bool operator<=(const int3& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z; }
	bool operator>=(const int3& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z; }

	static const int3 zero, one, minusOne, left, right, bottom, top, back, front;
};

inline const int3 int3::zero = int3(0);
inline const int3 int3::one = int3(1);
inline const int3 int3::minusOne = int3(-1);
inline const int3 int3::left = int3(-1, 0, 0);
inline const int3 int3::right = int3(1, 0, 0);
inline const int3 int3::bottom = int3(0, -1, 0);
inline const int3 int3::top = int3(0, 1, 0);
inline const int3 int3::back = int3(0, 0, -1);
inline const int3 int3::front = int3(0, 0, 1);

/***********************************************************************************************************************
 * @brief Signed integer 4 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct int4
{
	int32 x; /**< First vector component. */
	int32 y; /**< Second vector component. */
	int32 z; /**< Third vector component. */
	int32 w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit int4(int32 xyzw = 0) noexcept { this->x = xyzw; this->y = xyzw; this->z = xyzw; this->w = xyzw; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	int4(int32 x, int32 y, int32 z, int32 w) noexcept { this->x = x; this->y = y; this->z = z; this->w = w;}
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	int4(int2 xy, int32 z, int32 w) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; this->w = w; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 * @param w fourth vector component value
	 */
	int4(int32 x, int2 yz, int32 w) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; this->w = w; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector components value
	 */
	int4(int32 x, int32 y, int2 zw) noexcept { this->x = x; this->y = y; this->z = zw.x; this->w = zw.y; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param zw third and fourth vector components value
	 */
	int4(int2 xy, int2 zw) noexcept { this->x = xy.x; this->y = xy.x; this->z = zw.x; this->w = zw.y; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param[in] xyz first, second and third vector components value
	 * @param w fourth vector component value
	 */
	int4(const int3& xyz, int32 w) noexcept { this->x = xyz.x; this->y = xyz.y; this->z = xyz.z; this->w = w; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector components value
	 */
	int4(int32 x, const int3& yzw) noexcept { this->x = x; this->y = yzw.x; this->z = yzw.y; this->w = yzw.z; }
	/**
	 * @brief Creates a new signed integer 4 component vector structure.
	 * @param[in] xyzw target unsigned integer vector value
	 */
	int4(const uint4& xyzw) noexcept
	{
		this->x = (int32)xyzw.x; this->y = (int32)xyzw.y; this->z = (int32)xyzw.z; this->w = (int32)xyzw.w;
	}

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

	/**
	 * @brief Returns first, second, third and fourth vector components as uint. (xyz)
	 */
	explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	/**
	 * @brief Returns first, second and third vector components as uint. (xyz)
	 */
	explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	/**
	 * @brief Returns first, second and third vector components. (xyz)
	 */
	explicit operator int3() const noexcept { return int3(x, y, z); }
	/**
	 * @brief Returns first and second vector components as uint. (xy)
	 */
	explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator int2() const noexcept { return int2(x, y); }
	/**
	 * @brief Returns first vector component as uint. (x)
	 */
	explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component. (x)
	 */
	explicit operator int32() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept
	{
		return to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(w);
	}

	int4 operator+(const int4& v) const noexcept { return int4(x + v.x, y + v.y, z + v.z, w + v.w); }
	int4 operator-(const int4& v) const noexcept { return int4(x - v.x, y - v.y, z - v.z, w - v.w); }
	int4 operator*(const int4& v) const noexcept { return int4(x * v.x, y * v.y, z * v.z, w * v.w); }
	int4 operator/(const int4& v) const noexcept { return int4(x / v.x, y / v.y, z / v.z, w / v.w); }
	int4 operator%(const int4& v) const noexcept { return int4(x % v.x, y % v.y, z % v.z, w % v.w); }
	int4 operator&(const int4& v) const noexcept { return int4(x & v.x, y & v.y, z & v.z, w & v.w); }
	int4 operator|(const int4& v) const noexcept { return int4(x | v.x, y | v.y, z | v.z, w | v.w); }
	int4 operator^(const int4& v) const noexcept { return int4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	int4 operator>>(const int4& v) const noexcept { return int4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	int4 operator<<(const int4& v) const noexcept { return int4(x << v.x, y << v.y, z << v.z, w << v.w); }
	int4 operator-() const noexcept { return int4(-x, -y, -z, -w); }
	int4 operator!() const noexcept { return int4(!x, !y, !z, !w); }
	int4 operator~() const noexcept { return int4(~x, ~y, ~z, ~w); }
	int4& operator+=(const int4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	int4& operator-=(const int4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	int4& operator*=(const int4& v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	int4& operator/=(const int4& v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	int4& operator%=(const int4& v) noexcept { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	int4& operator&=(const int4& v) noexcept { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	int4& operator|=(const int4& v) noexcept { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	int4& operator^=(const int4& v) noexcept { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	int4& operator>>=(const int4& v) noexcept { x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	int4& operator<<=(const int4& v) noexcept { x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
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
	bool operator==(const int4& v) const noexcept { return memcmp(this, &v, sizeof(int32) * 4) == 0; }
	bool operator!=(const int4& v) const noexcept { return memcmp(this, &v, sizeof(int32) * 4) != 0; }
	bool operator<(const int4& v) const noexcept { return x < v.x && y < v.y && z < v.z && w < v.w; }
	bool operator>(const int4& v) const noexcept { return x > v.x && y > v.y && z > v.z && w > v.w; }
	bool operator<=(const int4& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z && w <= v.w; }
	bool operator>=(const int4& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z && w >= v.w; }

	static const int4 zero, one, minusOne;
};

inline const int4 int4::zero = int4(0);
inline const int4 int4::one = int4(1);
inline const int4 int4::minusOne = int4(-1);

//**********************************************************************************************************************
static int2 operator+(int2 v, int32 n) noexcept { return int2(v.x + n, v.y + n); }
static int2 operator-(int2 v, int32 n) noexcept { return int2(v.x - n, v.y - n); }
static int2 operator*(int2 v, int32 n) noexcept { return int2(v.x * n, v.y * n); }
static int2 operator/(int2 v, int32 n) noexcept { return int2(v.x / n, v.y / n); }
static int2 operator%(int2 v, int32 n) noexcept { return int2(v.x % n, v.y % n); }
static int2 operator&(int2 v, int32 n) noexcept { return int2(v.x & n, v.y & n); }
static int2 operator|(int2 v, int32 n) noexcept { return int2(v.x | n, v.y | n); }
static int2 operator^(int2 v, int32 n) noexcept { return int2(v.x ^ n, v.y ^ n); }
static int2 operator>>(int2 v, int32 n) noexcept { return int2(v.x >> n, v.y >> n); }
static int2 operator<<(int2 v, int32 n) noexcept { return int2(v.x << n, v.y << n); }
static bool operator==(int2 v, int32 n) noexcept { return v == int2(n); }
static bool operator!=(int2 v, int32 n) noexcept { return v != int2(n); }
static bool operator<(int2 v, int32 n) noexcept { return v < int2(n); }
static bool operator>(int2 v, int32 n) noexcept { return v > int2(n); }
static bool operator<=(int2 v, int32 n) noexcept { return v <= int2(n); }
static bool operator>=(int2 v, int32 n) noexcept { return v >= int2(n); }

static int2 operator+(int32 n, int2 v) noexcept { return int2(n + v.x, n + v.y); }
static int2 operator-(int32 n, int2 v) noexcept { return int2(n - v.x, n - v.y); }
static int2 operator*(int32 n, int2 v) noexcept { return int2(n * v.x, n * v.y); }
static int2 operator/(int32 n, int2 v) noexcept { return int2(n / v.x, n / v.y); }
static int2 operator%(int32 n, int2 v) noexcept { return int2(n % v.x, n % v.y); }
static int2 operator&(int32 n, int2 v) noexcept { return int2(n & v.x, n & v.y); }
static int2 operator|(int32 n, int2 v) noexcept { return int2(n | v.x, n | v.y); }
static int2 operator^(int32 n, int2 v) noexcept { return int2(n ^ v.x, n ^ v.y); }
static int2 operator>>(int32 n, int2 v) noexcept { return int2(n >> v.x, n >> v.y); }
static int2 operator<<(int32 n, int2 v) noexcept { return int2(n << v.x, n << v.y); }
static bool operator==(int32 n, int2 v) noexcept { return int2(n) == v; }
static bool operator!=(int32 n, int2 v) noexcept { return int2(n) != v; }
static bool operator<(int32 n, int2 v) noexcept { return int2(n) < v; }
static bool operator>(int32 n, int2 v) noexcept { return int2(n) > v; }
static bool operator<=(int32 n, int2 v) noexcept { return int2(n) <= v; }
static bool operator>=(int32 n, int2 v) noexcept { return int2(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b secong vector to binary compare
 */
static bool isBinaryLess(int2 a, int2 b) noexcept { return *((const int64*)&a) < *((const int64*)&b); }

//**********************************************************************************************************************
static int3 operator+(const int3& v, int32 n) noexcept { return int3(v.x + n, v.y + n, v.z + n); }
static int3 operator-(const int3& v, int32 n) noexcept { return int3(v.x - n, v.y - n, v.z - n); }
static int3 operator*(const int3& v, int32 n) noexcept { return int3(v.x * n, v.y * n, v.z * n); }
static int3 operator/(const int3& v, int32 n) noexcept { return int3(v.x / n, v.y / n, v.z / n); }
static int3 operator%(const int3& v, int32 n) noexcept { return int3(v.x % n, v.y % n, v.z % n); }
static int3 operator&(const int3& v, int32 n) noexcept { return int3(v.x & n, v.y & n, v.z & n); }
static int3 operator|(const int3& v, int32 n) noexcept { return int3(v.x | n, v.y | n, v.z | n); }
static int3 operator^(const int3& v, int32 n) noexcept { return int3(v.x ^ n, v.y ^ n, v.z ^ n); }
static int3 operator>>(const int3& v, int32 n) noexcept { return int3(v.x >> n, v.y >> n, v.z >> n); }
static int3 operator<<(const int3& v, int32 n) noexcept { return int3(v.x << n, v.y << n, v.z << n); }
static bool operator==(const int3& v, int32 n) noexcept { return v == int3(n); }
static bool operator!=(const int3& v, int32 n) noexcept { return v != int3(n); }
static bool operator<(const int3& v, int32 n) noexcept { return v < int3(n); }
static bool operator>(const int3& v, int32 n) noexcept { return v > int3(n); }
static bool operator<=(const int3& v, int32 n) noexcept { return v <= int3(n); }
static bool operator>=(const int3& v, int32 n) noexcept { return v >= int3(n); }

static int3 operator+(int32 n, const int3& v) noexcept { return int3(n + v.x, n + v.y, n + v.z); }
static int3 operator-(int32 n, const int3& v) noexcept { return int3(n - v.x, n - v.y, n - v.z); }
static int3 operator*(int32 n, const int3& v) noexcept { return int3(n * v.x, n * v.y, n * v.z); }
static int3 operator/(int32 n, const int3& v) noexcept { return int3(n / v.x, n / v.y, n / v.z); }
static int3 operator%(int32 n, const int3& v) noexcept { return int3(n % v.x, n % v.y, n % v.z); }
static int3 operator&(int32 n, const int3& v) noexcept { return int3(n & v.x, n & v.y, n & v.z); }
static int3 operator|(int32 n, const int3& v) noexcept { return int3(n | v.x, n | v.y, n | v.z); }
static int3 operator^(int32 n, const int3& v) noexcept { return int3(n ^ v.x, n ^ v.y, n ^ v.z); }
static int3 operator>>(int32 n, const int3& v) noexcept { return int3(n >> v.x, n >> v.y, n >> v.z); }
static int3 operator<<(int32 n, const int3& v) noexcept { return int3(n << v.x, n << v.y, n << v.z); }
static bool operator==(int32 n, const int3& v) noexcept { return int3(n) == v; }
static bool operator!=(int32 n, const int3& v) noexcept { return int3(n) != v; }
static bool operator<(int32 n, const int3& v) noexcept { return int3(n) < v; }
static bool operator>(int32 n, const int3& v) noexcept { return int3(n) > v; }
static bool operator<=(int32 n, const int3& v) noexcept { return int3(n) <= v; }
static bool operator>=(int32 n, const int3& v) noexcept { return int3(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const int3& a, const int3& b) noexcept { return memcmp(&a, &b, sizeof(int32) * 3) < 0; }

//**********************************************************************************************************************
static int4 operator+(const int4& v, int32 n) noexcept { return int4(v.x + n, v.y + n, v.z + n, v.w + n); }
static int4 operator-(const int4& v, int32 n) noexcept { return int4(v.x - n, v.y - n, v.z - n, v.w - n); }
static int4 operator*(const int4& v, int32 n) noexcept { return int4(v.x * n, v.y * n, v.z * n, v.w * n); }
static int4 operator/(const int4& v, int32 n) noexcept { return int4(v.x / n, v.y / n, v.z / n, v.w / n); }
static int4 operator%(const int4& v, int32 n) noexcept { return int4(v.x % n, v.y % n, v.z % n, v.w % n); }
static int4 operator&(const int4& v, int32 n) noexcept { return int4(v.x & n, v.y & n, v.z & n, v.w & n); }
static int4 operator|(const int4& v, int32 n) noexcept { return int4(v.x | n, v.y | n, v.z | n, v.w | n); }
static int4 operator^(const int4& v, int32 n) noexcept { return int4(v.x ^ n, v.y ^ n, v.z ^ n, v.w ^ n); }
static int4 operator>>(const int4& v, int32 n) noexcept { return int4(v.x >> n, v.y >> n, v.z >> n, v.w >> n); }
static int4 operator<<(const int4& v, int32 n) noexcept { return int4(v.x << n, v.y << n, v.z << n, v.w << n); }
static bool operator==(const int4& v, int32 n) noexcept { return v == int4(n); }
static bool operator!=(const int4& v, int32 n) noexcept { return v != int4(n); }
static bool operator<(const int4& v, int32 n) noexcept { return v < int4(n); }
static bool operator>(const int4& v, int32 n) noexcept { return v > int4(n); }
static bool operator<=(const int4& v, int32 n) noexcept { return v <= int4(n); }
static bool operator>=(const int4& v, int32 n) noexcept { return v >= int4(n); }

static int4 operator+(int32 n, const int4& v) noexcept { return int4(n + v.x, n + v.y, n + v.z, n + v.w); }
static int4 operator-(int32 n, const int4& v) noexcept { return int4(n - v.x, n - v.y, n - v.z, n - v.w); }
static int4 operator*(int32 n, const int4& v) noexcept { return int4(n * v.x, n * v.y, n * v.z, n * v.w); }
static int4 operator/(int32 n, const int4& v) noexcept { return int4(n / v.x, n / v.y, n / v.z, n / v.w); }
static int4 operator%(int32 n, const int4& v) noexcept { return int4(n % v.x, n % v.y, n % v.z, n % v.w); }
static int4 operator&(int32 n, const int4& v) noexcept { return int4(n & v.x, n & v.y, n & v.z, n & v.w); }
static int4 operator|(int32 n, const int4& v) noexcept { return int4(n | v.x, n | v.y, n | v.z, n | v.w); }
static int4 operator^(int32 n, const int4& v) noexcept { return int4(n ^ v.x, n ^ v.y, n ^ v.z, n ^ v.w); }
static int4 operator>>(int32 n, const int4& v) noexcept { return int4(n >> v.x, n >> v.y, n >> v.z, n >> v.w); }
static int4 operator<<(int32 n, const int4& v) noexcept { return int4(n << v.x, n << v.y, n << v.z, n << v.w); }
static bool operator==(int32 n, const int4& v) noexcept { return int4(n) == v; }
static bool operator!=(int32 n, const int4& v) noexcept { return int4(n) != v; }
static bool operator<(int32 n, const int4& v) noexcept { return int4(n) < v; }
static bool operator>(int32 n, const int4& v) noexcept { return int4(n) > v; }
static bool operator<=(int32 n, const int4& v) noexcept { return int4(n) <= v; }
static bool operator>=(int32 n, const int4& v) noexcept { return int4(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const int4& a, const int4& b) noexcept { return memcmp(&a, &b, sizeof(int32) * 4) < 0; }

//**********************************************************************************************************************
static int2 min(int2 a, int2 b) noexcept { return int2(std::min(a.x, b.x), std::min(a.y, b.y)); }
static int2 max(int2 a, int2 b) noexcept { return int2(std::max(a.x, b.x), std::max(a.y, b.y)); }
static int2 min(int2 a, int2 b, int2 c) noexcept { return min(min(a, b), c); }
static int2 max(int2 a, int2 b, int2 c) noexcept { return max(max(a, b), c); }

static int2 clamp(int2 v, int2 min, int2 max) noexcept
{
	return int2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}
static int32 dot(int2 a, int2 b) noexcept { return a.x * b.x + a.y * b.y; }
static int32 length2(int2 v) noexcept { return dot(v, v); }
static int32 distance2(int2 a, int2 b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static int3 min(const int3& a, const int3& b) noexcept
{
	return int3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
static int3 max(const int3& a, const int3& b) noexcept
{
	return int3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
static int3 min(const int3& a, const int3& b, const int3& c) noexcept { return min(min(a, b), c); }
static int3 max(const int3& a, const int3& b, const int3& c) noexcept { return max(max(a, b), c); }
static int3 clamp(const int3& v, const int3& min, const int3& max) noexcept
{
	return int3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}

static int32 dot(const int3& a, const int3& b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
static int32 length2(const int3& v) noexcept { return dot(v, v); }
static int32 distance2(const int3& a, const int3& b) noexcept { return length2(a - b); }

//**********************************************************************************************************************
static int4 min(const int4& a, const int4& b) noexcept
{
	return int4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
static int4 max(const int4& a, const int4& b) noexcept
{
	return int4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
static int4 min(const int4& a, const int4& b, const int4& c) noexcept { return min(min(a, b), c); }
static int4 max(const int4& a, const int4& b, const int4& c) noexcept { return max(max(a, b), c); }

static int4 clamp(const int4& v, const int4& min, const int4& max) noexcept
{
	return int4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}
static int32 dot(const int4& a, const int4& b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
static int32 length2(const int4& v) noexcept { return dot(v, v); }
static int32 distance2(const int4& a, const int4& b) noexcept { return length2(a - b); }

} // namespace math