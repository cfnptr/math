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
 * @brief Common vector functions.
 * 
 * @details
 * Vector is a mathematical concept used to represent points, positions, directions, velocities, sizes, colors, and 
 * forces in 2D and 3D space. For example, a 3D vector might represent an object's position relative to the origin or a 
 * direction of motion. Vectors are essential for operations like transformations, lighting, and physics calculations.
 */

#pragma once
#include "math/types.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

#define NOMINMAX
#include <algorithm>

#include <string>
#include <cassert>
#include <cstring>
#include <stdexcept>

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
 * @brief Floating point 2 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct float2
{
	float x; /**< First vector component. */
	float y; /**< Second vector component. */

	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target value for all vector components
	 */
	explicit float2(float xy = 0.0f) noexcept { this->x = xy; this->y = xy; }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	float2(float x, float y) noexcept { this->x = x; this->y = y; }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target signed integer vector value
	 */
	float2(int2 xy) noexcept { this->x = (float)xy.x; this->y = (float)xy.y; }

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((float*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((float*)this)[i];
	}

	/**
	 * @brief Returns first and second vector components as int. (xy)
	 */
	explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first vector component as int. (x)
	 */
	explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first vector component. (x)
	 */
	explicit operator float() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y); }

	float2 operator+(float2 v) const noexcept { return float2(x + v.x, y + v.y); }
	float2 operator-(float2 v) const noexcept { return float2(x - v.x, y - v.y); }
	float2 operator*(float2 v) const noexcept { return float2(x * v.x, y * v.y); }
	float2 operator/(float2 v) const noexcept { return float2(x / v.x, y / v.y); }
	float2 operator-() const noexcept { return float2(-x, -y); }
	float2& operator+=(float2 v) noexcept { x += v.x; y += v.y; return *this; }
	float2& operator-=(float2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	float2& operator*=(float2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	float2& operator/=(float2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	float2& operator+=(float n) noexcept { x += n; y += n; return *this; }
	float2& operator-=(float n) noexcept { x -= n; y -= n; return *this; }
	float2& operator*=(float n) noexcept { x *= n; y *= n; return *this; }
	float2& operator/=(float n) noexcept { x /= n; y /= n; return *this; }
	float2& operator=(float n) noexcept { x = n; y = n; return *this; }
	bool operator==(float2 v) const noexcept { return *((int64*)this) == *((int64*)&v); }
	bool operator!=(float2 v) const noexcept { return *((int64*)this) != *((int64*)&v); }
	bool operator<(float2 v) const noexcept { return x < v.x && y < v.y; }
	bool operator>(float2 v) const noexcept { return x > v.x && y > v.y; }
	bool operator<=(float2 v) const noexcept { return x <= v.x && y <= v.y; }
	bool operator>=(float2 v) const noexcept { return x >= v.x && y >= v.y; }

	static const float2 zero, one, minusOne, left, right, bottom, top;
};

inline const float2 float2::zero = float2(0.0f);
inline const float2 float2::one = float2(1.0f);
inline const float2 float2::minusOne = float2(-1.0f);
inline const float2 float2::left = float2(-1.0f, 0.0f);
inline const float2 float2::right = float2(1.0f, 0.0f);
inline const float2 float2::bottom = float2(0.0f, -1.0f);
inline const float2 float2::top = float2(0.0f, 1.0f);

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
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator int2() const noexcept { return int2(x, y); }
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
 * @brief Floating point 3 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct float3
{
	float x; /**< First vector component. */
	float y; /**< Second vector component. */
	float z; /**< Third vector component. */

	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param xyz target value for all vector components
	 */
	explicit float3(float xyz = 0.0f) noexcept { this->x = xyz; this->y = xyz; this->z = xyz; }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	float3(float x, float y, float z) noexcept { this->x = x; this->y = y; this->z = z; }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 */
	float3(float2 xy, float z) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 */
	float3(float x, float2 yz) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param[in] xyz target signed integer vector value
	 */
	float3(const int3& xyz) noexcept { this->x = (float)xyz.x; this->y = (float)xyz.y; this->z = (float)xyz.z; }

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((float*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float*)this)[i];
	}

	/**
	 * @brief Returns first, second and third vector components as int. (xyz)
	 */
	explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	/**
	 * @brief Returns first and second vector components as int. (xy)
	 */
	explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first vector component as int. (x)
	 */
	explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator float2() const noexcept { return float2(x, y); }
	/**
	 * @brief Returns first vector component. (x)
	 */
	explicit operator float() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y) + " " + to_string(z); }

	float3 operator+(const float3& v) const noexcept { return float3(x + v.x, y + v.y, z + v.z); }
	float3 operator-(const float3& v) const noexcept { return float3(x - v.x, y - v.y, z - v.z); }
	float3 operator*(const float3& v) const noexcept { return float3(x * v.x, y * v.y, z * v.z); }
	float3 operator/(const float3& v) const noexcept { return float3(x / v.x, y / v.y, z / v.z); }
	float3 operator-() const noexcept { return float3(-x, -y, -z); }
	float3& operator+=(const float3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	float3& operator-=(const float3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	float3& operator*=(const float3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	float3& operator/=(const float3& v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	float3& operator+=(float n) noexcept { x += n; y += n; z += n; return *this; }
	float3& operator-=(float n) noexcept { x -= n; y -= n; z -= n; return *this; }
	float3& operator*=(float n) noexcept { x *= n; y *= n; z *= n; return *this; }
	float3& operator/=(float n) noexcept { x /= n; y /= n; z /= n; return *this; }
	float3& operator=(float n) noexcept { x = n; y = n; z = n; return *this; }
	bool operator==(const float3& v) const noexcept { return memcmp(this, &v, sizeof(float) * 3) == 0; }
	bool operator!=(const float3& v) const noexcept { return memcmp(this, &v, sizeof(float) * 3) != 0; }
	bool operator<(const float3& v) const noexcept { return x < v.x && y < v.y && z < v.z; }
	bool operator>(const float3& v) const noexcept { return x > v.x && y > v.y && z > v.z; }
	bool operator<=(const float3& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z; }
	bool operator>=(const float3& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z; }

	static const float3 zero, one, minusOne, left, right, bottom, top, back, front;
};

inline const float3 float3::zero = float3(0.0f);
inline const float3 float3::one = float3(1.0f);
inline const float3 float3::minusOne = float3(-1.0f);
inline const float3 float3::left = float3(-1.0f, 0.0f, 0.0f);
inline const float3 float3::right = float3(1.0f, 0.0f, 0.0f);
inline const float3 float3::bottom = float3(0.0f, -1.0f, 0.0f);
inline const float3 float3::top = float3(0.0f, 1.0f, 0.0f);
inline const float3 float3::back = float3(0.0f, 0.0f, -1.0f);
inline const float3 float3::front = float3(0.0f, 0.0f, 1.0f);

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
	 * @brief Returns first, second and third vector components. (xyz)
	 */
	explicit operator int3() const noexcept { return int3(x, y, z); }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator int2() const noexcept { return int2(x, y); }
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

/***********************************************************************************************************************
 * @brief Floating point 4 component vector structure.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct float4
{
	float x; /**< First vector component. */
	float y; /**< Second vector component. */
	float z; /**< Third vector component. */
	float w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param xyzw target value for all vector components
	 */
	explicit float4(float xyzw = 0.0f) noexcept { this->x = xyzw; this->y = xyzw; this->z = xyzw; this->w = xyzw; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	float4(float x, float y, float z, float w) noexcept { this->x = x; this->y = y; this->z = z; this->w = w;}
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	float4(float2 xy, float z, float w) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; this->w = w; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 * @param w fourth vector component value
	 */
	float4(float x, float2 yz, float w) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; this->w = w; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector components value
	 */
	float4(float x, float y, float2 zw) noexcept { this->x = x; this->y = y; this->z = zw.x; this->w = zw.y; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param zw third and fourth vector components value
	 */
	float4(float2 xy, float2 zw) noexcept { this->x = xy.x; this->y = xy.y; this->z = zw.x; this->w = zw.y; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param[in] xyz first, second and third vector components value
	 * @param w fourth vector component value
	 */
	float4(const float3& xyz, float w) noexcept { this->x = xyz.x; this->y = xyz.y; this->z = xyz.z; this->w = w; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector components value
	 */
	float4(float x, const float3& yzw) noexcept { this->x = x; this->y = yzw.x; this->z = yzw.y; this->w = yzw.z; }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param[in] xyzw target signed integer vector value
	 */
	float4(const int4& xyzw) noexcept
	{
		this->x = (float)xyzw.x; this->y = (float)xyzw.y; this->z = (float)xyzw.z; this->w = (float)xyzw.w;
	}

	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((float*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	float operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float*)this)[i];
	}

	/**
	 * @brief Returns first, second, third and fourth vector components as int. (xyzw)
	 */
	explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	/**
	 * @brief Returns first, second and third vector components as int. (xyz)
	 */
	explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	/**
	 * @brief Returns first and second vector components as int. (xy)
	 */
	explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first vector component as int. (x)
	 */
	explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first, second and third vector components. (xyz)
	 */
	explicit operator float3() const noexcept { return float3(x, y, z); }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	explicit operator float2() const noexcept { return float2(x, y); }
	/**
	 * @brief Returns first vector component. (x)
	 */
	explicit operator float() const noexcept { return x; }
	/**
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept
	{
		return to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(w);
	}

	float4 operator+(const float4& v) const noexcept { return float4(x + v.x, y + v.y, z + v.z, w + v.w); }
	float4 operator-(const float4& v) const noexcept { return float4(x - v.x, y - v.y, z - v.z, w - v.w); }
	float4 operator*(const float4& v) const noexcept { return float4(x * v.x, y * v.y, z * v.z, w * v.w); }
	float4 operator/(const float4& v) const noexcept { return float4(x / v.x, y / v.y, z / v.z, w / v.w); }
	float4 operator-() const noexcept { return float4(-x, -y, -z, -w); }
	float4& operator+=(const float4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	float4& operator-=(const float4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	float4& operator*=(const float4& v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	float4& operator/=(const float4& v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	float4& operator+=(float n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	float4& operator-=(float n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	float4& operator*=(float n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	float4& operator/=(float n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	float4& operator=(float n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	bool operator==(const float4& v) const noexcept { return memcmp(this, &v, sizeof(float) * 4) == 0; }
	bool operator!=(const float4& v) const noexcept { return memcmp(this, &v, sizeof(float) * 4) != 0; }
	bool operator<(const float4& v) const noexcept { return x < v.x && y < v.y && z < v.z && w < v.w; }
	bool operator>(const float4& v) const noexcept { return x > v.x && y > v.y && z > v.z && w > v.w; }
	bool operator<=(const float4& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z && w <= v.w; }
	bool operator>=(const float4& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z && w >= v.w; }

	static const float4 zero, one, minusOne;
};

inline const float4 float4::zero = float4(0.0f);
inline const float4 float4::one = float4(1.0f);
inline const float4 float4::minusOne = float4(-1.0f);

//**********************************************************************************************************************
static float2 operator+(float2 v, float n) noexcept { return float2(v.x + n, v.y + n); }
static float2 operator-(float2 v, float n) noexcept { return float2(v.x - n, v.y - n); }
static float2 operator*(float2 v, float n) noexcept { return float2(v.x * n, v.y * n); }
static float2 operator/(float2 v, float n) noexcept { return float2(v.x / n, v.y / n); }
static bool operator==(float2 v, float n) noexcept { return v == float2(n); }
static bool operator!=(float2 v, float n) noexcept { return v != float2(n); }
static bool operator<(float2 v, float n) noexcept { return v < float2(n); }
static bool operator>(float2 v, float n) noexcept { return v > float2(n); }
static bool operator<=(float2 v, float n) noexcept { return v <= float2(n); }
static bool operator>=(float2 v, float n) noexcept { return v >= float2(n); }

static float2 operator+(float n, float2 v) noexcept { return float2(n + v.x, n + v.y); }
static float2 operator-(float n, float2 v) noexcept { return float2(n - v.x, n - v.y); }
static float2 operator*(float n, float2 v) noexcept { return float2(n * v.x, n * v.y); }
static float2 operator/(float n, float2 v) noexcept { return float2(n / v.x, n / v.y); }
static bool operator==(float n, float2 v) noexcept { return float2(n) == v; }
static bool operator!=(float n, float2 v) noexcept { return float2(n) != v; }
static bool operator<(float n, float2 v) noexcept { return float2(n) < v; }
static bool operator>(float n, float2 v) noexcept { return float2(n) > v; }
static bool operator<=(float n, float2 v) noexcept { return float2(n) <= v; }
static bool operator>=(float n, float2 v) noexcept { return float2(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b secong vector to binary compare
 */
static bool isBinaryLess(float2 a, float2 b) noexcept { return *((const int64*)&a) < *((const int64*)&b); }

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
static float3 operator+(const float3& v, float n) noexcept { return float3(v.x + n, v.y + n, v.z + n); }
static float3 operator-(const float3& v, float n) noexcept { return float3(v.x - n, v.y - n, v.z - n); }
static float3 operator*(const float3& v, float n) noexcept { return float3(v.x * n, v.y * n, v.z * n); }
static float3 operator/(const float3& v, float n) noexcept { return float3(v.x / n, v.y / n, v.z / n); }
static bool operator==(const float3& v, float n) noexcept { return v == float3(n); }
static bool operator!=(const float3& v, float n) noexcept { return v != float3(n); }
static bool operator<(const float3& v, float n) noexcept { return v < float3(n); }
static bool operator>(const float3& v, float n) noexcept { return v > float3(n); }
static bool operator<=(const float3& v, float n) noexcept { return v <= float3(n); }
static bool operator>=(const float3& v, float n) noexcept { return v >= float3(n); }

static float3 operator+(float n, const float3& v) noexcept { return float3(n + v.x, n + v.y, n + v.z); }
static float3 operator-(float n, const float3& v) noexcept { return float3(n - v.x, n - v.y, n - v.z); }
static float3 operator*(float n, const float3& v) noexcept { return float3(n * v.x, n * v.y, n * v.z); }
static float3 operator/(float n, const float3& v) noexcept { return float3(n / v.x, n / v.y, n / v.z); }
static bool operator==(float n, const float3& v) noexcept { return float3(n) == v; }
static bool operator!=(float n, const float3& v) noexcept { return float3(n) != v; }
static bool operator<(float n, const float3& v) noexcept { return float3(n) < v; }
static bool operator>(float n, const float3& v) noexcept { return float3(n) > v; }
static bool operator<=(float n, const float3& v) noexcept { return float3(n) <= v; }
static bool operator>=(float n, const float3& v) noexcept { return float3(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const float3& a, const float3& b) noexcept { return memcmp(&a, &b, sizeof(float) * 3) < 0; }

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
static float4 operator+(const float4& v, float n) noexcept { return float4(v.x + n, v.y + n, v.z + n, v.w + n); }
static float4 operator-(const float4& v, float n) noexcept { return float4(v.x - n, v.y - n, v.z - n, v.w - n); }
static float4 operator*(const float4& v, float n) noexcept { return float4(v.x * n, v.y * n, v.z * n, v.w * n); }
static float4 operator/(const float4& v, float n) noexcept { return float4(v.x / n, v.y / n, v.z / n, v.w / n); }
static bool operator==(const float4& v, float n) noexcept { return v == float4(n); }
static bool operator!=(const float4& v, float n) noexcept { return v != float4(n); }
static bool operator<(const float4& v, float n) noexcept { return v < float4(n); }
static bool operator>(const float4& v, float n) noexcept { return v > float4(n); }
static bool operator<=(const float4& v, float n) noexcept { return v <= float4(n); }
static bool operator>=(const float4& v, float n) noexcept { return v >= float4(n); }

static float4 operator+(float n, const float4& v) noexcept { return float4(n + v.x, n + v.y, n + v.z, n + v.w); }
static float4 operator-(float n, const float4& v) noexcept { return float4(n - v.x, n - v.y, n - v.z, n - v.w); }
static float4 operator*(float n, const float4& v) noexcept { return float4(n * v.x, n * v.y, n * v.z, n * v.w); }
static float4 operator/(float n, const float4& v) noexcept { return float4(n / v.x, n / v.y, n / v.z, n / v.w); }
static bool operator==(float n, const float4& v) noexcept { return float4(n) == v; }
static bool operator!=(float n, const float4& v) noexcept { return float4(n) != v; }
static bool operator<(float n, const float4& v) noexcept { return float4(n) < v; }
static bool operator>(float n, const float4& v) noexcept { return float4(n) > v; }
static bool operator<=(float n, const float4& v) noexcept { return float4(n) <= v; }
static bool operator>=(float n, const float4& v) noexcept { return float4(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const float4& a, const float4& b) noexcept { return memcmp(&a, &b, sizeof(float) * 4) < 0; }

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

} // namespace math