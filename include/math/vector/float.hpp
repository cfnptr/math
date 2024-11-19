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
 * @brief Common floating point vector functions.
 * @details Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/common.hpp"
#include "math/vector/int.hpp"

namespace math
{

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
	constexpr explicit float2(float xy = 0.0f) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr float2(float x, float y) noexcept : x(x), y(y) { }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target unsigned integer vector value
	 */
	constexpr float2(uint2 xy) noexcept : x((float)xy.x), y((float)xy.y) { }
	/**
	 * @brief Creates a new floating point 2 component vector structure.
	 * @param xy target signed integer vector value
	 */
	constexpr float2(int2 xy) noexcept : x((float)xy.x), y((float)xy.y) { }

	/*******************************************************************************************************************
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
	 * @brief Returns first and second vector components as uint. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first and second vector components as int. (xy)
	 */
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first vector component as uint. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component as int. (x)
	 */
	constexpr explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first vector component. (x)
	 */
	constexpr explicit operator float() const noexcept { return x; }

	/*******************************************************************************************************************
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y); }

	constexpr float2 operator+(float2 v) const noexcept { return float2(x + v.x, y + v.y); }
	constexpr float2 operator-(float2 v) const noexcept { return float2(x - v.x, y - v.y); }
	constexpr float2 operator*(float2 v) const noexcept { return float2(x * v.x, y * v.y); }
	constexpr float2 operator/(float2 v) const noexcept { return float2(x / v.x, y / v.y); }
	constexpr float2 operator-() const noexcept { return float2(-x, -y); }
	float2& operator+=(float2 v) noexcept { x += v.x; y += v.y; return *this; }
	float2& operator-=(float2 v) noexcept { x -= v.x; y -= v.y; return *this; }
	float2& operator*=(float2 v) noexcept { x *= v.x; y *= v.y; return *this; }
	float2& operator/=(float2 v) noexcept { x /= v.x; y /= v.y; return *this; }
	float2& operator+=(float n) noexcept { x += n; y += n; return *this; }
	float2& operator-=(float n) noexcept { x -= n; y -= n; return *this; }
	float2& operator*=(float n) noexcept { x *= n; y *= n; return *this; }
	float2& operator/=(float n) noexcept { x /= n; y /= n; return *this; }
	float2& operator=(float n) noexcept { x = n; y = n; return *this; }
	constexpr bool operator==(float2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(float2 v) const noexcept { return x != v.x || y != v.y; }
	constexpr bool operator<(float2 v) const noexcept { return x < v.x && y < v.y; }
	constexpr bool operator>(float2 v) const noexcept { return x > v.x && y > v.y; }
	constexpr bool operator<=(float2 v) const noexcept { return x <= v.x && y <= v.y; }
	constexpr bool operator>=(float2 v) const noexcept { return x >= v.x && y >= v.y; }

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
	constexpr explicit float3(float xyz = 0.0f) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr float3(float x, float y, float z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 */
	constexpr float3(float2 xy, float z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 */
	constexpr float3(float x, float2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param[in] xyz target unsigned integer vector value
	 */
	constexpr float3(const uint3& xyz) noexcept : x((float)xyz.x), y((float)xyz.y), z((float)xyz.z) { }
	/**
	 * @brief Creates a new floating point 3 component vector structure.
	 * @param[in] xyz target signed integer vector value
	 */
	constexpr float3(const int3& xyz) noexcept : x((float)xyz.x), y((float)xyz.y), z((float)xyz.z) { }

	/*******************************************************************************************************************
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
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	/**
	 * @brief Returns first, second and third vector components as uint. (xyz)
	 */
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	/**
	 * @brief Returns first and second vector components as int. (xy)
	 */
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first and second vector components as uint. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first vector component as uint. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component as int. (x)
	 */
	constexpr explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	constexpr explicit operator float2() const noexcept { return float2(x, y); }
	/**
	 * @brief Returns first vector component. (x)
	 */
	constexpr explicit operator float() const noexcept { return x; }

	/*******************************************************************************************************************
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept { return to_string(x) + " " + to_string(y) + " " + to_string(z); }

	constexpr float3 operator+(const float3& v) const noexcept { return float3(x + v.x, y + v.y, z + v.z); }
	constexpr float3 operator-(const float3& v) const noexcept { return float3(x - v.x, y - v.y, z - v.z); }
	constexpr float3 operator*(const float3& v) const noexcept { return float3(x * v.x, y * v.y, z * v.z); }
	constexpr float3 operator/(const float3& v) const noexcept { return float3(x / v.x, y / v.y, z / v.z); }
	constexpr float3 operator-() const noexcept { return float3(-x, -y, -z); }
	float3& operator+=(const float3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
	float3& operator-=(const float3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
	float3& operator*=(const float3& v) noexcept { x *= v.x; y *= v.y; z *= v.z; return *this; }
	float3& operator/=(const float3& v) noexcept { x /= v.x; y /= v.y; z /= v.z; return *this; }
	float3& operator+=(float n) noexcept { x += n; y += n; z += n; return *this; }
	float3& operator-=(float n) noexcept { x -= n; y -= n; z -= n; return *this; }
	float3& operator*=(float n) noexcept { x *= n; y *= n; z *= n; return *this; }
	float3& operator/=(float n) noexcept { x /= n; y /= n; z /= n; return *this; }
	float3& operator=(float n) noexcept { x = n; y = n; z = n; return *this; }
	constexpr bool operator==(const float3& v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(const float3& v) const noexcept { return x != v.x || y != v.y || z != v.z; }
	constexpr bool operator<(const float3& v) const noexcept { return x < v.x && y < v.y && z < v.z; }
	constexpr bool operator>(const float3& v) const noexcept { return x > v.x && y > v.y && z > v.z; }
	constexpr bool operator<=(const float3& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z; }
	constexpr bool operator>=(const float3& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z; }

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
	constexpr explicit float4(float xyzw = 0.0f) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr float4(float x, float y, float z, float w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr float4(float2 xy, float z, float w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector components value
	 * @param w fourth vector component value
	 */
	constexpr float4(float x, float2 yz, float w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector components value
	 */
	constexpr float4(float x, float y, float2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param xy first and second vector components value
	 * @param zw third and fourth vector components value
	 */
	constexpr float4(float2 xy, float2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param[in] xyz first, second and third vector components value
	 * @param w fourth vector component value
	 */
	constexpr float4(const float3& xyz, float w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 *
	 * @param x first vector component value
	 * @param[in] yzw second, third and fourth vector components value
	 */
	constexpr float4(float x, const float3& yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param[in] xyzw target unsigned integer vector value
	 */
	constexpr float4(const uint4& xyzw) noexcept :
		x((float)xyzw.x), y((float)xyzw.y), z((float)xyzw.z), w((float)xyzw.w) { }
	/**
	 * @brief Creates a new floating point 4 component vector structure.
	 * @param[in] xyzw target signed integer vector value
	 */
	constexpr float4(const int4& xyzw) noexcept :
		x((float)xyzw.x), y((float)xyzw.y), z((float)xyzw.z), w((float)xyzw.w) { }

	/*******************************************************************************************************************
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
	 * @brief Returns first, second, third and fourth vector components as uint. (xyzw)
	 */
	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	/**
	 * @brief Returns first, second, third and fourth vector components as int. (xyzw)
	 */
	constexpr explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	/**
	 * @brief Returns first, second and third vector components as int. (xyz)
	 */
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	/**
	 * @brief Returns first, second and third vector components as uint. (xyz)
	 */
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	/**
	 * @brief Returns first and second vector components as int. (xy)
	 */
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	/**
	 * @brief Returns first and second vector components as uint. (xy)
	 */
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	/**
	 * @brief Returns first vector component as uint. (x)
	 */
	constexpr explicit operator uint32() const noexcept { return (uint32)x; }
	/**
	 * @brief Returns first vector component as int. (x)
	 */
	constexpr explicit operator int32() const noexcept { return (int32)x; }
	/**
	 * @brief Returns first, second and third vector components. (xyz)
	 */
	constexpr explicit operator float3() const noexcept { return float3(x, y, z); }
	/**
	 * @brief Returns first and second vector components. (xy)
	 */
	constexpr explicit operator float2() const noexcept { return float2(x, y); }
	/**
	 * @brief Returns first vector component. (x)
	 */
	constexpr explicit operator float() const noexcept { return x; }

	/*******************************************************************************************************************
	 * @brief Converts vector to the string. (space separated)
	 */
	string toString() const noexcept
	{
		return to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(w);
	}

	constexpr float4 operator+(const float4& v) const noexcept { return float4(x + v.x, y + v.y, z + v.z, w + v.w); }
	constexpr float4 operator-(const float4& v) const noexcept { return float4(x - v.x, y - v.y, z - v.z, w - v.w); }
	constexpr float4 operator*(const float4& v) const noexcept { return float4(x * v.x, y * v.y, z * v.z, w * v.w); }
	constexpr float4 operator/(const float4& v) const noexcept { return float4(x / v.x, y / v.y, z / v.z, w / v.w); }
	constexpr float4 operator-() const noexcept { return float4(-x, -y, -z, -w); }
	float4& operator+=(const float4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	float4& operator-=(const float4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	float4& operator*=(const float4& v) noexcept { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	float4& operator/=(const float4& v) noexcept { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	float4& operator+=(float n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	float4& operator-=(float n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	float4& operator*=(float n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	float4& operator/=(float n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	float4& operator=(float n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	constexpr bool operator==(const float4& v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(const float4& v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }
	constexpr bool operator<(const float4& v) const noexcept { return x < v.x && y < v.y && z < v.z && w < v.w; }
	constexpr bool operator>(const float4& v) const noexcept { return x > v.x && y > v.y && z > v.z && w > v.w; }
	constexpr bool operator<=(const float4& v) const noexcept { return x <= v.x && y <= v.y && z <= v.z && w <= v.w; }
	constexpr bool operator>=(const float4& v) const noexcept { return x >= v.x && y >= v.y && z >= v.z && w >= v.w; }

	static const float4 zero, one, minusOne;
};

inline const float4 float4::zero = float4(0.0f);
inline const float4 float4::one = float4(1.0f);
inline const float4 float4::minusOne = float4(-1.0f);

//**********************************************************************************************************************
static constexpr float2 operator+(float2 v, float n) noexcept { return float2(v.x + n, v.y + n); }
static constexpr float2 operator-(float2 v, float n) noexcept { return float2(v.x - n, v.y - n); }
static constexpr float2 operator*(float2 v, float n) noexcept { return float2(v.x * n, v.y * n); }
static constexpr float2 operator/(float2 v, float n) noexcept { return float2(v.x / n, v.y / n); }
static constexpr bool operator==(float2 v, float n) noexcept { return v == float2(n); }
static constexpr bool operator!=(float2 v, float n) noexcept { return v != float2(n); }
static constexpr bool operator<(float2 v, float n) noexcept { return v < float2(n); }
static constexpr bool operator>(float2 v, float n) noexcept { return v > float2(n); }
static constexpr bool operator<=(float2 v, float n) noexcept { return v <= float2(n); }
static constexpr bool operator>=(float2 v, float n) noexcept { return v >= float2(n); }

static constexpr float2 operator+(float n, float2 v) noexcept { return float2(n + v.x, n + v.y); }
static constexpr float2 operator-(float n, float2 v) noexcept { return float2(n - v.x, n - v.y); }
static constexpr float2 operator*(float n, float2 v) noexcept { return float2(n * v.x, n * v.y); }
static constexpr float2 operator/(float n, float2 v) noexcept { return float2(n / v.x, n / v.y); }
static constexpr bool operator==(float n, float2 v) noexcept { return float2(n) == v; }
static constexpr bool operator!=(float n, float2 v) noexcept { return float2(n) != v; }
static constexpr bool operator<(float n, float2 v) noexcept { return float2(n) < v; }
static constexpr bool operator>(float n, float2 v) noexcept { return float2(n) > v; }
static constexpr bool operator<=(float n, float2 v) noexcept { return float2(n) <= v; }
static constexpr bool operator>=(float n, float2 v) noexcept { return float2(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param a first vector to binary compare
 * @param b secong vector to binary compare
 */
static bool isBinaryLess(float2 a, float2 b) noexcept { return *((const int64*)&a) < *((const int64*)&b); }

//**********************************************************************************************************************
static constexpr float3 operator+(const float3& v, float n) noexcept { return float3(v.x + n, v.y + n, v.z + n); }
static constexpr float3 operator-(const float3& v, float n) noexcept { return float3(v.x - n, v.y - n, v.z - n); }
static constexpr float3 operator*(const float3& v, float n) noexcept { return float3(v.x * n, v.y * n, v.z * n); }
static constexpr float3 operator/(const float3& v, float n) noexcept { return float3(v.x / n, v.y / n, v.z / n); }
static constexpr bool operator==(const float3& v, float n) noexcept { return v == float3(n); }
static constexpr bool operator!=(const float3& v, float n) noexcept { return v != float3(n); }
static constexpr bool operator<(const float3& v, float n) noexcept { return v < float3(n); }
static constexpr bool operator>(const float3& v, float n) noexcept { return v > float3(n); }
static constexpr bool operator<=(const float3& v, float n) noexcept { return v <= float3(n); }
static constexpr bool operator>=(const float3& v, float n) noexcept { return v >= float3(n); }

static constexpr float3 operator+(float n, const float3& v) noexcept { return float3(n + v.x, n + v.y, n + v.z); }
static constexpr float3 operator-(float n, const float3& v) noexcept { return float3(n - v.x, n - v.y, n - v.z); }
static constexpr float3 operator*(float n, const float3& v) noexcept { return float3(n * v.x, n * v.y, n * v.z); }
static constexpr float3 operator/(float n, const float3& v) noexcept { return float3(n / v.x, n / v.y, n / v.z); }
static constexpr bool operator==(float n, const float3& v) noexcept { return float3(n) == v; }
static constexpr bool operator!=(float n, const float3& v) noexcept { return float3(n) != v; }
static constexpr bool operator<(float n, const float3& v) noexcept { return float3(n) < v; }
static constexpr bool operator>(float n, const float3& v) noexcept { return float3(n) > v; }
static constexpr bool operator<=(float n, const float3& v) noexcept { return float3(n) <= v; }
static constexpr bool operator>=(float n, const float3& v) noexcept { return float3(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const float3& a, const float3& b) noexcept { return memcmp(&a, &b, sizeof(float) * 3) < 0; }

//**********************************************************************************************************************
static constexpr float4 operator+(const float4& v, float n) noexcept { return float4(v.x + n, v.y + n, v.z + n, v.w + n); }
static constexpr float4 operator-(const float4& v, float n) noexcept { return float4(v.x - n, v.y - n, v.z - n, v.w - n); }
static constexpr float4 operator*(const float4& v, float n) noexcept { return float4(v.x * n, v.y * n, v.z * n, v.w * n); }
static constexpr float4 operator/(const float4& v, float n) noexcept { return float4(v.x / n, v.y / n, v.z / n, v.w / n); }
static constexpr bool operator==(const float4& v, float n) noexcept { return v == float4(n); }
static constexpr bool operator!=(const float4& v, float n) noexcept { return v != float4(n); }
static constexpr bool operator<(const float4& v, float n) noexcept { return v < float4(n); }
static constexpr bool operator>(const float4& v, float n) noexcept { return v > float4(n); }
static constexpr bool operator<=(const float4& v, float n) noexcept { return v <= float4(n); }
static constexpr bool operator>=(const float4& v, float n) noexcept { return v >= float4(n); }

static constexpr float4 operator+(float n, const float4& v) noexcept { return float4(n + v.x, n + v.y, n + v.z, n + v.w); }
static constexpr float4 operator-(float n, const float4& v) noexcept { return float4(n - v.x, n - v.y, n - v.z, n - v.w); }
static constexpr float4 operator*(float n, const float4& v) noexcept { return float4(n * v.x, n * v.y, n * v.z, n * v.w); }
static constexpr float4 operator/(float n, const float4& v) noexcept { return float4(n / v.x, n / v.y, n / v.z, n / v.w); }
static constexpr bool operator==(float n, const float4& v) noexcept { return float4(n) == v; }
static constexpr bool operator!=(float n, const float4& v) noexcept { return float4(n) != v; }
static constexpr bool operator<(float n, const float4& v) noexcept { return float4(n) < v; }
static constexpr bool operator>(float n, const float4& v) noexcept { return float4(n) > v; }
static constexpr bool operator<=(float n, const float4& v) noexcept { return float4(n) <= v; }
static constexpr bool operator>=(float n, const float4& v) noexcept { return float4(n) >= v; }

/**
 * @brief Returns true if first vector binary representation is less than the second.
 *
 * @param[in] a first vector to binary compare
 * @param[in] b secong vector to binary compare
 */
static bool isBinaryLess(const float4& a, const float4& b) noexcept { return memcmp(&a, &b, sizeof(float) * 4) < 0; }

//**********************************************************************************************************************
// TODO: possibly add more specific math functions like remquo, sph_neumann or dFdx.

static constexpr float2 min(float2 a, float2 b) noexcept { return float2(std::min(a.x, b.x), std::min(a.y, b.y)); }
static constexpr float2 max(float2 a, float2 b) noexcept { return float2(std::max(a.x, b.x), std::max(a.y, b.y)); }
static constexpr float2 min(float2 a, float2 b, float2 c) noexcept { return min(min(a, b), c); }
static constexpr float2 max(float2 a, float2 b, float2 c) noexcept { return max(max(a, b), c); }
static float2 abs(float2 v) noexcept { return float2(std::abs(v.x), std::abs(v.y)); }
static float2 mod(float2 a, float2 b) noexcept { return float2(std::fmod(a.x, b.x), std::fmod(a.y, b.y)); }
static float2 fma(float2 a, float2 b, float2 c) noexcept
{
	return float2(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y));
}
static float2 ceil(float2 v) noexcept { return float2(std::ceil(v.x), std::ceil(v.y)); }
static float2 floor(float2 v) noexcept { return float2(std::floor(v.x), std::floor(v.y)); }
static float2 trunc(float2 v) noexcept { return float2(std::trunc(v.x), std::trunc(v.y)); }
static float2 round(float2 v) noexcept { return float2(std::round(v.x), std::round(v.y)); }
static float2 sign(float2 v) noexcept { return float2(sign(v.x), sign(v.y)); }
static float2 exp(float2 v) noexcept { return float2(std::exp(v.x), std::exp(v.y)); }
static float2 exp2(float2 v) noexcept { return float2(std::exp2(v.x), std::exp2(v.y)); }
static float2 expm1(float2 v) noexcept { return float2(std::expm1(v.x), std::expm1(v.y)); }
static float2 log(float2 v) noexcept { return float2(std::log(v.x), std::log(v.y)); }
static float2 log10(float2 v) noexcept { return float2(std::log10(v.x), std::log10(v.y)); }
static float2 log2(float2 v) noexcept { return float2(std::log2(v.x), std::log2(v.y)); }
static float2 log1p(float2 v) noexcept { return float2(std::log1p(v.x), std::log1p(v.y)); }
static float2 pow(float2 a, float2 b) noexcept { return float2(std::pow(a.x, b.x), std::pow(a.y, b.y)); }
static float2 sqrt(float2 v) noexcept { return float2(std::sqrt(v.x), std::sqrt(v.y)); }
static float2 cbrt(float2 v) noexcept { return float2(std::cbrt(v.x), std::cbrt(v.y)); }
static float2 sin(float2 v) noexcept { return float2(std::sin(v.x), std::sin(v.y)); }
static float2 cos(float2 v) noexcept { return float2(std::cos(v.x), std::cos(v.y)); }
static float2 tan(float2 v) noexcept { return float2(std::tan(v.x), std::tan(v.y)); }
static float2 asin(float2 v) noexcept { return float2(std::asin(v.x), std::asin(v.y)); }
static float2 acos(float2 v) noexcept { return float2(std::acos(v.x), std::acos(v.y)); }
static float2 atan(float2 v) noexcept { return float2(std::atan(v.x), std::atan(v.y)); }
static float2 atan(float2 a, float2 b) noexcept { return float2(std::atan2(a.x, b.x), std::atan2(a.y, b.y)); }
static float2 sinh(float2 v) noexcept { return float2(std::sinh(v.x), std::sinh(v.y)); }
static float2 cosh(float2 v) noexcept { return float2(std::cosh(v.x), std::cosh(v.y)); }
static float2 tanh(float2 v) noexcept { return float2(std::tanh(v.x), std::tanh(v.y)); }
static float2 asinh(float2 v) noexcept { return float2(std::asinh(v.x), std::asinh(v.y)); }
static float2 acosh(float2 v) noexcept { return float2(std::acosh(v.x), std::acosh(v.y)); }
static float2 atanh(float2 v) noexcept { return float2(std::atanh(v.x), std::atanh(v.y)); }

static constexpr float2 clamp(float2 v, float2 min, float2 max) noexcept
{
	return float2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
}
static float2 repeat(float2 v) noexcept { return float2(repeat(v.x), repeat(v.y)); }
static constexpr float dot(float2 a, float2 b) noexcept { return a.x * b.x + a.y * b.y; }
static float length(float2 v) noexcept { return std::sqrt(dot(v, v)); }
static constexpr float length2(float2 v) noexcept { return dot(v, v); }
static float distance(float2 a, float2 b) noexcept { return length(a - b); }
static constexpr float distance2(float2 a, float2 b) noexcept { return length2(a - b); }
static float2 normalize(float2 v) noexcept
{
	auto l = length(v);
	assert(l > 0.0f);
	return v * (1.0f / l);
}
static float2 lerp(float2 a, float2 b, float t) noexcept
{
	assert(t >= 0.0f);
	assert(t <= 1.0f);
	return a * (1.0f - t) + b * t;
}
static float2 lerpDelta(float2 a, float2 b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}
static float2 gain(float2 x, float2 k) noexcept
{
	auto a = float2(0.5f) * pow(2.0f * ((x < 0.5f) ? x : 1.0f - x), k);
	return (x < 0.5f) ? a : 1.0f - a;
}

//**********************************************************************************************************************
static constexpr float3 min(const float3& a, const float3& b) noexcept
{
	return float3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z));
}
static constexpr float3 max(const float3& a, const float3& b) noexcept
{
	return float3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z));
}
static constexpr float3 min(const float3& a, const float3& b, const float3& c) noexcept { return min(min(a, b), c); }
static constexpr float3 max(const float3& a, const float3& b, const float3& c) noexcept { return max(max(a, b), c); }
static float3 abs(const float3& v) noexcept { return float3(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
static float3 mod(const float3& a, const float3& b) noexcept
{
	return float3(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z));
}
static float3 fma(const float3& a, const float3& b, const float3& c) noexcept
{
	return float3(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y), std::fma(a.z, b.z, c.z));
}
static float3 ceil(const float3& v) noexcept { return float3(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); }
static float3 floor(const float3& v) noexcept { return float3(std::floor(v.x), std::floor(v.y), std::floor(v.z)); }
static float3 trunc(const float3& v) noexcept { return float3(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z)); }
static float3 round(const float3& v) noexcept { return float3(std::round(v.x), std::round(v.y), std::round(v.z)); }
static float3 sign(const float3& v) noexcept { return float3(sign(v.x), sign(v.y), sign(v.z)); }
static float3 exp(const float3& v) noexcept { return float3(std::exp(v.x), std::exp(v.y), std::exp(v.z)); }
static float3 exp2(const float3& v) noexcept { return float3(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z)); }
static float3 expm1(const float3& v) noexcept { return float3(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z)); }
static float3 log(const float3& v) noexcept { return float3(std::log(v.x), std::log(v.y), std::log(v.z)); }
static float3 log10(const float3& v) noexcept { return float3(std::log10(v.x), std::log10(v.y), std::log10(v.z)); }
static float3 log2(const float3& v) noexcept { return float3(std::log2(v.x), std::log2(v.y), std::log2(v.z)); }
static float3 log1p(const float3& v) noexcept { return float3(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z)); }
static float3 pow(const float3& a, const float3& b) noexcept
{
	return float3(std::pow(a.x, b.x), std::pow(a.y, b.y), std::pow(a.z, b.z));
}
static float3 sqrt(const float3& v) noexcept { return float3(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z)); }
static float3 cbrt(const float3& v) noexcept { return float3(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z)); }
static float3 sin(const float3& v) noexcept { return float3(std::sin(v.x), std::sin(v.y), std::sin(v.z)); }
static float3 cos(const float3& v) noexcept { return float3(std::cos(v.x), std::cos(v.y), std::cos(v.z)); }
static float3 tan(const float3& v) noexcept { return float3(std::tan(v.x), std::tan(v.y), std::tan(v.z)); }
static float3 asin(const float3& v) noexcept { return float3(std::asin(v.x), std::asin(v.y), std::asin(v.z)); }
static float3 acos(const float3& v) noexcept { return float3(std::acos(v.x), std::acos(v.y), std::acos(v.z)); }
static float3 atan(const float3& v) noexcept { return float3(std::atan(v.x), std::atan(v.y), std::atan(v.z)); }
static float3 atan(const float3& a, const float3& b) noexcept
{
	return float3(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z));
}
static float3 sinh(const float3& v) noexcept { return float3(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z)); }
static float3 cosh(const float3& v) noexcept { return float3(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z)); }
static float3 tanh(const float3& v) noexcept { return float3(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z)); }
static float3 asinh(const float3& v) noexcept { return float3(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z)); }
static float3 acosh(const float3& v) noexcept { return float3(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z)); }
static float3 atanh(const float3& v) noexcept { return float3(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z)); }

static constexpr float3 clamp(const float3& v, const float3& min, const float3& max) noexcept
{
	return float3(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z));
}
static float3 repeat(const float3& v) noexcept { return float3(repeat(v.x), repeat(v.y), repeat(v.z)); }
static constexpr float dot(const float3& a, const float3& b) noexcept { return a.x * b.x + a.y * b.y + a.z * b.z; }
static constexpr float3 cross(const float3& a, const float3& b) noexcept
{
	return float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
static float length(const float3& v) noexcept { return std::sqrt(dot(v, v)); }
static constexpr float length2(const float3& v) noexcept { return dot(v, v); }
static float distance(const float3& a, const float3& b) noexcept { return length(a - b); }
static constexpr float distance2(const float3& a, const float3& b) noexcept { return length2(a - b); }
static float3 normalize(const float3& v) noexcept { return v * (1.0f / length(v)); }
static float3 lerp(const float3& a, const float3& b, float t) noexcept
{
	assert(t >= 0.0f);
	assert(t <= 1.0f);
	return a * (1.0f - t) + b * t;
}
static float3 lerpDelta(const float3& a, const float3& b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}
static float3 gain(const float3& x, const float3& k) noexcept
{
	auto a = float3(0.5f) * pow(2.0f * ((x < 0.5f) ? x : 1.0f - x), k);
	return (x < 0.5f) ? a : 1.0f - a;
}

//**********************************************************************************************************************
static constexpr float4 min(const float4& a, const float4& b) noexcept
{
	return float4(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w));
}
static constexpr float4 max(const float4& a, const float4& b) noexcept
{
	return float4(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w));
}
static constexpr float4 min(const float4& a, const float4& b, const float4& c) noexcept { return min(min(a, b), c); }
static constexpr float4 max(const float4& a, const float4& b, const float4& c) noexcept { return max(max(a, b), c); }
static float4 abs(const float4& v) noexcept
{
	return float4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w));
}
static float4 mod(const float4& a, const float4& b) noexcept
{
	return float4(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z), std::fmod(a.w, b.w));
}
static float4 fma(const float4& a, const float4& b, const float4& c) noexcept
{
	return float4(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y), std::fma(a.z, b.z, c.z), std::fma(a.w, b.w, c.w));
}
static float4 ceil(const float4& v) noexcept
{
	return float4(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w));
}
static float4 floor(const float4& v) noexcept
{
	return float4(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w));
}
static float4 trunc(const float4& v) noexcept
{
	return float4(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z), std::trunc(v.w));
}
static float4 round(const float4& v) noexcept
{
	return float4(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w));
}
static float4 sign(const float4& v) noexcept { return float4(sign(v.x), sign(v.y), sign(v.z), sign(v.w)); }
static float4 exp(const float4& v) noexcept
{
	return float4(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w));
}
static float4 exp2(const float4& v) noexcept
{
	return float4(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z), std::exp2(v.w));
}
static float4 expm1(const float4& v) noexcept
{
	return float4(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z), std::expm1(v.w));
}
static float4 log(const float4& v) noexcept
{
	return float4(std::log(v.x), std::log(v.y), std::log(v.z), std::log(v.w));
}
static float4 log10(const float4& v) noexcept
{
	return float4(std::log10(v.x), std::log10(v.y), std::log10(v.z), std::log10(v.w));
}
static float4 log2(const float4& v) noexcept
{
	return float4(std::log2(v.x), std::log2(v.y), std::log2(v.z), std::log2(v.w));
}
static float4 log1p(const float4& v) noexcept
{
	return float4(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z), std::log1p(v.w));
}
static float4 pow(const float4& a, const float4& b) noexcept
{
	return float4(std::pow(a.x, b.x), std::pow(a.y, b.y), std::pow(a.z, b.z), std::pow(a.w, b.w));
}
static float4 sqrt(const float4& v) noexcept
{
	return float4(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w));
}
static float4 cbrt(const float4& v) noexcept
{
	return float4(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z), std::cbrt(v.w));
}
static float4 sin(const float4& v) noexcept
{
	return float4(std::sin(v.x), std::sin(v.y), std::sin(v.z), std::sin(v.w));
}
static float4 cos(const float4& v) noexcept
{
	return float4(std::cos(v.x), std::cos(v.y), std::cos(v.z), std::cos(v.w));
}
static float4 tan(const float4& v) noexcept
{
	return float4(std::tan(v.x), std::tan(v.y), std::tan(v.z), std::tan(v.w));
}
static float4 asin(const float4& v) noexcept
{
	return float4(std::asin(v.x), std::asin(v.y), std::asin(v.z), std::asin(v.w));
}
static float4 acos(const float4& v) noexcept
{
	return float4(std::acos(v.x), std::acos(v.y), std::acos(v.z), std::acos(v.w));
}
static float4 atan(const float4& v) noexcept
{
	return float4(std::atan(v.x), std::atan(v.y), std::atan(v.z), std::atan(v.w));
}
static float4 atan(const float4& a, const float4& b) noexcept
{
	return float4(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z), std::atan2(a.w, b.w));
}
static float4 sinh(const float4& v) noexcept
{
	return float4(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z), std::sinh(v.w));
}
static float4 cosh(const float4& v) noexcept
{
	return float4(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z), std::cosh(v.w));
}
static float4 tanh(const float4& v) noexcept
{
	return float4(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z), std::tanh(v.w));
}
static float4 asinh(const float4& v) noexcept
{
	return float4(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z), std::asinh(v.w));
}
static float4 acosh(const float4& v) noexcept
{
	return float4(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z), std::acosh(v.w));
}
static float4 atanh(const float4& v) noexcept
{
	return float4(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z), std::atanh(v.w));
}

static float4 clamp(const float4& v, const float4& min, const float4& max) noexcept
{
	return float4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
		std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w));
}
static float4 repeat(const float4& v) noexcept { return float4(repeat(v.x), repeat(v.y), repeat(v.z), repeat(v.w)); }
static constexpr float dot(const float4& a, const float4& b) noexcept
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static float length(const float4& v) noexcept { return std::sqrt(dot(v, v)); }
static constexpr float length2(const float4& v) noexcept { return dot(v, v); }
static float distance(const float4& a, const float4& b) noexcept { return length(a - b); }
static constexpr float distance2(const float4& a, const float4& b) noexcept { return length2(a - b); }
static float4 normalize(const float4& v) noexcept
{
	auto l = length(v);
	assert(l > 0.0f);
	return v * (1.0f / l);
}
static float4 lerp(const float4& a, const float4& b, float t) noexcept
{
	assert(t >= 0.0f);
	assert(t <= 1.0f);
	return a * (1.0f - t) + b * t;
}
static float4 lerpDelta(const float4& a, const float4& b, float f, float dt) noexcept
{
	return a + (1.0f - std::pow(f, dt)) * (b - a);
}
static float4 gain(const float4& x, const float4& k) noexcept
{
	auto a = float4(0.5f) * pow(2.0f * ((x < 0.5f) ? x : 1.0f - x), k);
	return (x < 0.5f) ? a : 1.0f - a;
}

} // namespace math