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

//------------------------------------------------------------------------------------------------------------
struct int2
{
	int32 x, y;

	explicit int2(int32 xy = 0) noexcept { this->x = xy; this->y = xy; }
	int2(int32 x, int32 y) noexcept { this->x = x; this->y = y; }

	int32& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((int32*)this)[i];
	}
	int32 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((int32*)this)[i];
	}

	explicit operator int32() noexcept { return x; }
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
	string toString() const noexcept { return to_string(x) + " " + to_string(y); }

	static const int2 left, right, bottom, top;
};

//------------------------------------------------------------------------------------------------------------
struct float2
{
	float x, y;

	explicit float2(float xy = 0.0f) noexcept { this->x = xy; this->y = xy; }
	float2(float x, float y) noexcept { this->x = x; this->y = y; }
	float2(int2 xy) noexcept { this->x = (float)xy.x; this->y = (float)xy.y; }

	float& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((float*)this)[i];
	}
	float operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((float*)this)[i];
	}

	explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	explicit operator int32() const noexcept { return (int32)x; }
	explicit operator float() const noexcept { return x; }
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
	string toString() const noexcept { return to_string(x) + " " + to_string(y); }

	static const float2 left, right, bottom, top;
};

//------------------------------------------------------------------------------------------------------------
struct int3
{
	int32 x, y, z;

	explicit int3(int32 xyz = 0) noexcept { this->x = xyz; this->y = xyz; this->z = xyz; }
	int3(int32 x, int32 y, int32 z) noexcept { this->x = x; this->y = y; this->z = z; }
	int3(int2 xy, int32 z) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; }
	int3(int32 x, int2 yz) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; }

	int32& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((int32*)this)[i];
	}
	int32 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((int32*)this)[i];
	}

//------------------------------------------------------------------------------------------------------------
	explicit operator int2() const noexcept { return int2(x, y); }
	explicit operator int32() const noexcept { return x; }
	int3 operator+(const int3& v) const noexcept {
		return int3(x + v.x, y + v.y, z + v.z); }
	int3 operator-(const int3& v) const noexcept {
		return int3(x - v.x, y - v.y, z - v.z); }
	int3 operator*(const int3& v) const noexcept {
		return int3(x * v.x, y * v.y, z * v.z); }
	int3 operator/(const int3& v) const noexcept {
		return int3(x / v.x, y / v.y, z / v.z); }
	int3 operator%(const int3& v) const noexcept {
		return int3(x % v.x, y % v.y, z % v.z); }
	int3 operator&(const int3& v) const noexcept {
		return int3(x & v.x, y & v.y, z & v.z); }
	int3 operator|(const int3& v) const noexcept {
		return int3(x | v.x, y | v.y, z | v.z); }
	int3 operator^(const int3& v) const noexcept {
		return int3(x ^ v.x, y ^ v.y, z ^ v.z); }
	int3 operator>>(const int3& v) const noexcept {
		return int3(x >> v.x, y >> v.y, z >> v.z); }
	int3 operator<<(const int3& v) const noexcept {
		return int3(x << v.x, y << v.y, z << v.z); }
	int3 operator-() const noexcept { return int3(-x, -y, -z); }
	int3 operator!() const noexcept { return int3(!x, !y, !z); }
	int3 operator~() const noexcept { return int3(~x, ~y, ~z); }
	int3& operator+=(const int3& v) noexcept {
		x += v.x; y += v.y; z += v.z; return *this; }
	int3& operator-=(const int3& v) noexcept {
		x -= v.x; y -= v.y; z -= v.z; return *this; }
	int3& operator*=(const int3& v) noexcept {
		x *= v.x; y *= v.y; z *= v.z; return *this; }
	int3& operator/=(const int3& v) noexcept {
		x /= v.x; y /= v.y; z /= v.z; return *this; }
	int3& operator%=(const int3& v) noexcept {
		x %= v.x; y %= v.y; z %= v.z; return *this; }
	int3& operator&=(const int3& v) noexcept {
		x &= v.x; y &= v.y; z &= v.z; return *this; }
	int3& operator|=(const int3& v) noexcept {
		x |= v.x; y |= v.y; z |= v.z; return *this; }
	int3& operator^=(const int3& v) noexcept {
		x ^= v.x; y ^= v.y; z ^= v.z; return *this; }
	int3& operator>>=(const int3& v) noexcept {
		x >>= v.x; y >>= v.y; z >>= v.z; return *this; }
	int3& operator<<=(const int3& v) noexcept {
		x <<= v.x; y <<= v.y; z <<= v.z; return *this; }
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
	bool operator==(const int3& v) const noexcept {
		return memcmp(this, &v, sizeof(int32) * 3) == 0; }
	bool operator!=(const int3& v) const noexcept {
		return memcmp(this, &v, sizeof(int32) * 3) != 0; }
	bool operator<(const int3& v) const noexcept {
		return x < v.x && y < v.y && z < v.z; }
	bool operator>(const int3& v) const noexcept {
		return x > v.x && y > v.y && z > v.z; }
	bool operator<=(const int3& v) const noexcept {
		return x <= v.x && y <= v.y && z <= v.z; }
	bool operator>=(const int3& v) const noexcept {
		return x >= v.x && y >= v.y && z >= v.z; }

	string toString() const noexcept {
		return to_string(x) + " " + to_string(y) + " " + to_string(z); }

	static const int3 left, right, bottom, top, back, front;
};

//------------------------------------------------------------------------------------------------------------
struct float3
{
	float x, y, z;

	explicit float3(float xyz = 0.0f) noexcept {
		this->x = xyz; this->y = xyz; this->z = xyz; }
	float3(float x, float y, float z) noexcept { this->x = x; this->y = y; this->z = z; }
	float3(float2 xy, float z) noexcept { this->x = xy.x; this->y = xy.y; this->z = z; }
	float3(float x, float2 yz) noexcept { this->x = x; this->y = yz.x; this->z = yz.y; }
	float3(const int3& xyz) noexcept {
		this->x = (float)xyz.x; this->y = (float)xyz.y; this->z = (float)xyz.z; }

	float& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((float*)this)[i];
	}
	float operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float*)this)[i];
	}

//------------------------------------------------------------------------------------------------------------
	explicit operator int3() const noexcept {
		return int3((int32)x, (int32)y, (int32)z); }
	explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	explicit operator int32() const noexcept { return (int32)x; }
	explicit operator float2() const noexcept { return float2(x, y); }
	explicit operator float() const noexcept { return x; }
	float3 operator+(const float3& v) const noexcept {
		return float3(x + v.x, y + v.y, z + v.z); }
	float3 operator-(const float3& v) const noexcept {
		return float3(x - v.x, y - v.y, z - v.z); }
	float3 operator*(const float3& v) const noexcept {
		return float3(x * v.x, y * v.y, z * v.z); }
	float3 operator/(const float3& v) const noexcept {
		return float3(x / v.x, y / v.y, z / v.z); }
	float3 operator-() const noexcept { return float3(-x, -y, -z); }
	float3& operator+=(const float3& v) noexcept {
		x += v.x; y += v.y; z += v.z; return *this; }
	float3& operator-=(const float3& v) noexcept {
		x -= v.x; y -= v.y; z -= v.z; return *this; }
	float3& operator*=(const float3& v) noexcept {
		x *= v.x; y *= v.y; z *= v.z; return *this; }
	float3& operator/=(const float3& v) noexcept {
		x /= v.x; y /= v.y; z /= v.z; return *this; }
	float3& operator+=(float n) noexcept { x += n; y += n; z += n; return *this; }
	float3& operator-=(float n) noexcept { x -= n; y -= n; z -= n; return *this; }
	float3& operator*=(float n) noexcept { x *= n; y *= n; z *= n; return *this; }
	float3& operator/=(float n) noexcept { x /= n; y /= n; z /= n; return *this; }
	float3& operator=(float n) noexcept { x = n; y = n; z = n; return *this; }
	bool operator==(const float3& v) const noexcept {
		return memcmp(this, &v, sizeof(float) * 3) == 0; }
	bool operator!=(const float3& v) const noexcept {
		return memcmp(this, &v, sizeof(float) * 3) != 0; }
	bool operator<(const float3& v) const noexcept {
		return x < v.x && y < v.y && z < v.z; }
	bool operator>(const float3& v) const noexcept {
		return x > v.x && y > v.y && z > v.z; }
	bool operator<=(const float3& v) const noexcept {
		return x <= v.x && y <= v.y && z <= v.z; }
	bool operator>=(const float3& v) const noexcept {
		return x >= v.x && y >= v.y && z >= v.z; }

	string toString() const noexcept {
		return to_string(x) + " " + to_string(y) + " " + to_string(z); }

	static const float3 left, right, bottom, top, back, front;
};

//------------------------------------------------------------------------------------------------------------
struct int4
{
	int32 x, y, z, w;

	explicit int4(int32 xyzw = 0) noexcept {
		this->x = xyzw; this->y = xyzw; this->z = xyzw; this->w = xyzw; }
	int4(int32 x, int32 y, int32 z, int32 w) noexcept {
		this->x = x; this->y = y; this->z = z; this->w = w;}
	int4(int2 xy, int32 z, int32 w) noexcept {
		this->x = xy.x; this->y = xy.y; this->z = z; this->w = w; }
	int4(int32 x, int2 yz, int32 w) noexcept {
		this->x = x; this->y = yz.x; this->z = yz.y; this->w = w; }
	int4(int32 x, int32 y, int2 zw) noexcept {
		this->x = x; this->y = y; this->z = zw.x; this->w = zw.y; }
	int4(int2 xy, int2 zw) noexcept {
		this->x = xy.x; this->y = xy.x; this->z = zw.x; this->w = zw.y; }
	int4(const int3& xyz, int32 w) noexcept {
		this->x = xyz.x; this->y = xyz.y; this->z = xyz.z; this->w = w; }
	int4(int32 x, const int3& yzw) noexcept {
		this->x = x; this->y = yzw.x; this->z = yzw.y; this->w = yzw.z; }

	int32& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((int32*)this)[i];
	}
	int32 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((int32*)this)[i];
	}

//------------------------------------------------------------------------------------------------------------
	explicit operator int3() const noexcept { return int3(x, y, z); }
	explicit operator int2() const noexcept { return int2(x, y); }
	explicit operator int32() const noexcept { return x; }
	int4 operator+(const int4& v) const noexcept { 
		return int4(x + v.x, y + v.y, z + v.z, w + v.w); }
	int4 operator-(const int4& v) const noexcept { 
		return int4(x - v.x, y - v.y, z - v.z, w - v.w); }
	int4 operator*(const int4& v) const noexcept { 
		return int4(x * v.x, y * v.y, z * v.z, w * v.w); }
	int4 operator/(const int4& v) const noexcept { 
		return int4(x / v.x, y / v.y, z / v.z, w / v.w); }
	int4 operator%(const int4& v) const noexcept { 
		return int4(x % v.x, y % v.y, z % v.z, w % v.w); }
	int4 operator&(const int4& v) const noexcept {
		return int4(x & v.x, y & v.y, z & v.z, w & v.w); }
	int4 operator|(const int4& v) const noexcept {
		return int4(x | v.x, y | v.y, z | v.z, w | v.w); }
	int4 operator^(const int4& v) const noexcept {
		return int4(x ^ v.x, y ^ v.y, z ^ v.z, w ^ v.w); }
	int4 operator>>(const int4& v) const noexcept {
		return int4(x >> v.x, y >> v.y, z >> v.z, w >> v.w); }
	int4 operator<<(const int4& v) const noexcept {
		return int4(x << v.x, y << v.y, z << v.z, w << v.w); }
	int4 operator-() const noexcept { return int4(-x, -y, -z, -w); }
	int4 operator!() const noexcept { return int4(!x, !y, !z, !w); }
	int4 operator~() const noexcept { return int4(~x, ~y, ~z, ~w); }
	int4& operator+=(const int4& v) noexcept {
		x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	int4& operator-=(const int4& v) noexcept {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	int4& operator*=(const int4& v) noexcept {
		x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	int4& operator/=(const int4& v) noexcept {
		x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	int4& operator%=(const int4& v) noexcept {
		x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	int4& operator&=(const int4& v) noexcept {
		x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	int4& operator|=(const int4& v) noexcept {
		x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	int4& operator^=(const int4& v) noexcept {
		x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }
	int4& operator>>=(const int4& v) noexcept {
		x >>= v.x; y >>= v.y; z >>= v.z; w >>= v.w; return *this; }
	int4& operator<<=(const int4& v) noexcept {
		x <<= v.x; y <<= v.y; z <<= v.z; w <<= v.w; return *this; }
	int4& operator+=(int32 n) noexcept {
		x += n; y += n; z += n; w += n; return *this; }
	int4& operator-=(int32 n) noexcept {
		x -= n; y -= n; z -= n; w -= n; return *this; }
	int4& operator*=(int32 n) noexcept {
		x *= n; y *= n; z *= n; w *= n; return *this; }
	int4& operator/=(int32 n) noexcept {
		x /= n; y /= n; z /= n; w /= n; return *this; }
	int4& operator%=(int32 n) noexcept {
		x %= n; y %= n; z %= n; w %= n; return *this; }
	int4& operator&=(int32 n) noexcept {
		x &= n; y &= n; z &= n; w &= n; return *this; }
	int4& operator|=(int32 n) noexcept {
		x |= n; y |= n; z |= n; w |= n; return *this; }
	int4& operator^=(int32 n) noexcept {
		x ^= n; y ^= n; z ^= n; w ^= n; return *this; }
	int4& operator>>=(int32 n) noexcept {
		x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	int4& operator<<=(int32 n) noexcept {
		x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	int4& operator=(int32 n) noexcept {
		x = n; y = n; z = n; w = n; return *this; }
	bool operator==(const int4& v) const noexcept {
		return memcmp(this, &v, sizeof(int32) * 4) == 0; }
	bool operator!=(const int4& v) const noexcept {
		return memcmp(this, &v, sizeof(int32) * 4) != 0; }
	bool operator<(const int4& v) const noexcept {
		return x < v.x && y < v.y && z < v.z && w < v.w; }
	bool operator>(const int4& v) const noexcept {
		return x > v.x && y > v.y && z > v.z && w > v.w; }
	bool operator<=(const int4& v) const noexcept {
		return x <= v.x && y <= v.y && z <= v.z && w <= v.w; }
	bool operator>=(const int4& v) const noexcept {
		return x >= v.x && y >= v.y && z >= v.z && w >= v.w; }
	
	string toString() const noexcept
	{
		return to_string(x) + " " + to_string(y) + " " +
			to_string(z) + " " + to_string(w);
	}
};

//------------------------------------------------------------------------------------------------------------
struct float4
{
	float x, y, z, w;

	explicit float4(float xyzw = 0.0f) noexcept {
		this->x = xyzw; this->y = xyzw; this->z = xyzw; this->w = xyzw; }
	float4(float x, float y, float z, float w) noexcept {
		this->x = x; this->y = y; this->z = z; this->w = w;}
	float4(float2 xy, float z, float w) noexcept {
		this->x = xy.x; this->y = xy.y; this->z = z; this->w = w; }
	float4(float x, float2 yz, float w) noexcept {
		this->x = x; this->y = yz.x; this->z = yz.y; this->w = w; }
	float4(float x, float y, float2 zw) noexcept {
		this->x = x; this->y = y; this->z = zw.x; this->w = zw.y; }
	float4(float2 xy, float2 zw) noexcept {
		this->x = xy.x; this->y = xy.x; this->z = zw.x; this->w = zw.y; }
	float4(const float3& xyz, float w) noexcept {
		this->x = xyz.x; this->y = xyz.y; this->z = xyz.z; this->w = w; }
	float4(float x, const float3& yzw) noexcept {
		this->x = x; this->y = yzw.x; this->z = yzw.y; this->w = yzw.z; }
	float4(const int4& xyzw) noexcept {
		this->x = (float)xyzw.x; this->y = (float)xyzw.y;
		this->z = (float)xyzw.z; this->w = (float)xyzw.w; }

	float& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((float*)this)[i];
	}
	float operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float*)this)[i];
	}

//------------------------------------------------------------------------------------------------------------
	explicit operator int4() const noexcept {
		return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	explicit operator int3() const noexcept {
		return int3((int32)x, (int32)y, (int32)z); }
	explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	explicit operator int32() const noexcept { return (int32)x; }
	explicit operator float3() const noexcept { return float3(x, y, z); }
	explicit operator float2() const noexcept { return float2(x, y); }
	explicit operator float() const noexcept { return x; }
	float4 operator+(const float4& v) const noexcept {
		return float4(x + v.x, y + v.y, z + v.z, w + v.w); }
	float4 operator-(const float4& v) const noexcept {
		return float4(x - v.x, y - v.y, z - v.z, w - v.w); }
	float4 operator*(const float4& v) const noexcept {
		return float4(x * v.x, y * v.y, z * v.z, w * v.w); }
	float4 operator/(const float4& v) const noexcept {
		return float4(x / v.x, y / v.y, z / v.z, w / v.w); }
	float4 operator-() const noexcept { return float4(-x, -y, -z, -w); }
	float4& operator+=(const float4& v) noexcept {
		x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	float4& operator-=(const float4& v) noexcept {
		x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	float4& operator*=(const float4& v) noexcept {
		x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	float4& operator/=(const float4& v) noexcept {
		x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	float4& operator+=(float n) noexcept { x += n; y += n; z += n; w += n; return *this; }
	float4& operator-=(float n) noexcept { x -= n; y -= n; z -= n; w -= n; return *this; }
	float4& operator*=(float n) noexcept { x *= n; y *= n; z *= n; w *= n; return *this; }
	float4& operator/=(float n) noexcept { x /= n; y /= n; z /= n; w /= n; return *this; }
	float4& operator=(float n) noexcept { x = n; y = n; z = n; w = n; return *this; }
	bool operator==(const float4& v) const noexcept {
		return memcmp(this, &v, sizeof(float) * 4) == 0; }
	bool operator!=(const float4& v) const noexcept {
		return memcmp(this, &v, sizeof(float) * 4) != 0; }
	bool operator<(const float4& v) const noexcept {
		return x < v.x && y < v.y && z < v.z && w < v.w; }
	bool operator>(const float4& v) const noexcept {
		return x > v.x && y > v.y && z > v.z && w > v.w; }
	bool operator<=(const float4& v) const noexcept {
		return x <= v.x && y <= v.y && z <= v.z && w <= v.w; }
	bool operator>=(const float4& v) const noexcept {
		return x >= v.x && y >= v.y && z >= v.z && w >= v.w; }
		
	string toString() const noexcept
	{
		return to_string(x) + " " + to_string(y) + " " +
			to_string(z) + " " + to_string(w);
	}
};

//------------------------------------------------------------------------------------------------------------
static float min(float a, float b, float c) { return std::min(std::min(a, b), c); }
static float max(float a, float b, float c) { return std::max(std::max(a, b), c); }
static int32 min(int32 a, int32 b, int32 c) { return std::min(std::min(a, b), c); }
static int32 max(int32 a, int32 b, int32 c) { return std::max(std::max(a, b), c); }

static float repeat(float v) noexcept
{
    if (v < 0.0f)
		return 1.0f - std::fmod(-v, 1.0f);
    if (v >= 1.0f)
		return std::fmod(v, 1.0f);
	return v;
}
static float sign(float v) noexcept
{
	if (v == 0.0f)
		return 0.0f;
	return std::signbit(v) ? -1.0f : 1.0f;
}
static float lerp(float a, float b, float t) noexcept
{
	assert(t >= 0.0f);
	assert(t <= 1.0f);
	return a + t * (b - a);
}

//--------------------------------------------------------------------------------------------------
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

// TODO: possibly add more specific math functions like remquo, sph_neumann or dFdx.
//------------------------------------------------------------------------------------------------------------
static float2 abs(float2 v) noexcept {
	return float2(std::abs(v.x), std::abs(v.y)); }
static float2 mod(float2 a, float2 b) noexcept {
	return float2(std::fmod(a.x, b.x), std::fmod(a.y, b.y)); }
static float2 fma(float2 a, float2 b, float2 c) noexcept {
	return float2(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y)); }
static float2 max(float2 a, float2 b) noexcept {
	return float2(std::max(a.x, b.x), std::max(a.y, b.y)); }
static float2 max(float2 a, float2 b, float2 c)
	noexcept { return max(max(a, b), c); }
static float2 min(float2 a, float2 b) noexcept {
	return float2(std::min(a.x, b.x), std::min(a.y, b.y)); }
static float2 min(float2 a, float2 b, float2 c)
	noexcept { return min(min(a, b), c); }
static float2 clamp(float2 v, float2 min, float2 max) noexcept {
	return float2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y)); }
static float2 ceil(float2 v) noexcept {
	return float2(std::ceil(v.x), std::ceil(v.y)); }
static float2 floor(float2 v) noexcept {
	return float2(std::floor(v.x), std::floor(v.y)); }
static float2 trunc(float2 v) noexcept {
	return float2(std::trunc(v.x), std::trunc(v.y)); }
static float2 round(float2 v) noexcept {
	return float2(std::round(v.x), std::round(v.y)); }
static float2 repeat(float2 v) noexcept {
	return float2(repeat(v.x), repeat(v.y)); }
static float2 sign(float2 v) noexcept {
	return float2(sign(v.x), sign(v.y)); }

//------------------------------------------------------------------------------------------------------------
static float2 exp(float2 v) noexcept {
	return float2(std::exp(v.x), std::exp(v.y)); }
static float2 exp2(float2 v) noexcept {
	return float2(std::exp2(v.x), std::exp2(v.y)); }
static float2 expm1(float2 v) noexcept {
	return float2(std::expm1(v.x), std::expm1(v.y)); }
static float2 log(float2 v) noexcept {
	return float2(std::log(v.x), std::log(v.y)); }
static float2 log10(float2 v) noexcept {
	return float2(std::log10(v.x), std::log10(v.y)); }
static float2 log2(float2 v) noexcept {
	return float2(std::log2(v.x), std::log2(v.y)); }
static float2 log1p(float2 v) noexcept {
	return float2(std::log1p(v.x), std::log1p(v.y)); }
static float2 pow(float2 a, float2 b) noexcept {
	return float2(std::pow(a.x, b.x), std::pow(a.y, b.y)); }
static float2 sqrt(float2 v) noexcept {
	return float2(std::sqrt(v.x), std::sqrt(v.y)); }
static float2 cbrt(float2 v) noexcept {
	return float2(std::cbrt(v.x), std::cbrt(v.y)); }

//------------------------------------------------------------------------------------------------------------
static float2 sin(float2 v) noexcept {
	return float2(std::sin(v.x), std::sin(v.y)); }
static float2 cos(float2 v) noexcept {
	return float2(std::cos(v.x), std::cos(v.y)); }
static float2 tan(float2 v) noexcept {
	return float2(std::tan(v.x), std::tan(v.y)); }
static float2 asin(float2 v) noexcept {
	return float2(std::asin(v.x), std::asin(v.y)); }
static float2 acos(float2 v) noexcept {
	return float2(std::acos(v.x), std::acos(v.y)); }
static float2 atan(float2 v) noexcept {
	return float2(std::atan(v.x), std::atan(v.y)); }
static float2 atan(float2 a, float2 b) noexcept {
	return float2(std::atan2(a.x, b.x), std::atan2(a.y, b.y)); }
static float2 sinh(float2 v) noexcept {
	return float2(std::sinh(v.x), std::sinh(v.y)); }
static float2 cosh(float2 v) noexcept {
	return float2(std::cosh(v.x), std::cosh(v.y)); }
static float2 tanh(float2 v) noexcept {
	return float2(std::tanh(v.x), std::tanh(v.y)); }
static float2 asinh(float2 v) noexcept {
	return float2(std::asinh(v.x), std::asinh(v.y)); }
static float2 acosh(float2 v) noexcept {
	return float2(std::acosh(v.x), std::acosh(v.y)); }
static float2 atanh(float2 v) noexcept {
	return float2(std::atanh(v.x), std::atanh(v.y)); }

//------------------------------------------------------------------------------------------------------------
static float dot(float2 a, float2 b) noexcept { return a.x * b.x + a.y * b.y; }
static float length(float2 v) noexcept { return std::sqrt(dot(v, v)); }
static float length2(float2 v) noexcept { return dot(v, v); }
static float distance(float2 a, float2 b) noexcept { return length(a - b); }
static float distance2(float2 a, float2 b) noexcept { return length2(a - b); }

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

static bool isBinaryLess(float2 a, float2 b) noexcept {
	return *((const int64*)&a) < *((const int64*)&b); }

//------------------------------------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------------------------------------
static int2 max(int2 a, int2 b) noexcept {
	return int2(std::max(a.x, b.x), std::max(a.y, b.y)); }
static int2 max(int2 a, int2 b, int2 c)
	noexcept { return max(max(a, b), c); }
static int2 min(int2 a, int2 b) noexcept {
	return int2(std::min(a.x, b.x), std::min(a.y, b.y)); }
static int2 min(int2 a, int2 b, int2 c)
	noexcept { return min(min(a, b), c); }
static int2 clamp(int2 v, int2 min, int2 max) noexcept {
	return int2(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y)); }

static int32 dot(int2 a, int2 b) noexcept { return a.x * b.x + a.y * b.y; }
static int32 length2(int2 v) noexcept { return dot(v, v); }
static int32 distance2(int2 a, int2 b) noexcept { return length2(a - b); }

static bool isBinaryLess(int2 a, int2 b) noexcept {
	return *((const int64*)&a) < *((const int64*)&b); }

//------------------------------------------------------------------------------------------------------------
static float3 operator+(const float3& v, float n) noexcept {
	return float3(v.x + n, v.y + n, v.z + n); }
static float3 operator-(const float3& v, float n) noexcept {
	return float3(v.x - n, v.y - n, v.z - n); }
static float3 operator*(const float3& v, float n) noexcept {
	return float3(v.x * n, v.y * n, v.z * n); }
static float3 operator/(const float3& v, float n) noexcept {
	return float3(v.x / n, v.y / n, v.z / n); }
static bool operator==(const float3& v, float n) noexcept { return v == float3(n); }
static bool operator!=(const float3& v, float n) noexcept { return v != float3(n); }
static bool operator<(const float3& v, float n) noexcept { return v < float3(n); }
static bool operator>(const float3& v, float n) noexcept { return v > float3(n); }
static bool operator<=(const float3& v, float n) noexcept { return v <= float3(n); }
static bool operator>=(const float3& v, float n) noexcept { return v >= float3(n); }

static float3 operator+(float n, const float3& v) noexcept {
	return float3(n + v.x, n + v.y, n + v.z); }
static float3 operator-(float n, const float3& v) noexcept {
	return float3(n - v.x, n - v.y, n - v.z); }
static float3 operator*(float n, const float3& v) noexcept {
	return float3(n * v.x, n * v.y, n * v.z); }
static float3 operator/(float n, const float3& v) noexcept {
	return float3(n / v.x, n / v.y, n / v.z); }
static bool operator==(float n, const float3& v) noexcept { return float3(n) == v; }
static bool operator!=(float n, const float3& v) noexcept { return float3(n) != v; }
static bool operator<(float n, const float3& v) noexcept { return float3(n) < v; }
static bool operator>(float n, const float3& v) noexcept { return float3(n) > v; }
static bool operator<=(float n, const float3& v) noexcept { return float3(n) <= v; }
static bool operator>=(float n, const float3& v) noexcept { return float3(n) >= v; }

//------------------------------------------------------------------------------------------------------------
static float3 abs(const float3& v) noexcept {
	return float3(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
static float3 mod(const float3& a, const float3& b) noexcept {
	return float3(std::fmod(a.x, b.x), std::fmod(a.y, b.y), std::fmod(a.z, b.z)); }
static float3 fma(const float3& a, const float3& b, const float3& c) noexcept {
	return float3(std::fma(a.x, b.x, c.x), 
	std::fma(a.y, b.y, c.y), std::fma(a.z, b.z, c.z)); }
static float3 max(const float3& a, const float3& b) noexcept {
	return float3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); }
static float3 max(const float3& a, const float3& b, const float3& c)
	noexcept { return max(max(a, b), c); }
static float3 min(const float3& a, const float3& b) noexcept {
	return float3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); }
static float3 min(const float3& a, const float3& b, const float3& c)
	noexcept { return min(min(a, b), c); }
static float3 clamp(const float3& v, const float3& min, const float3& max) noexcept {
	return float3(std::clamp(v.x, min.x, max.x),
	std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z)); }
static float3 ceil(const float3& v) noexcept {
	return float3(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); }
static float3 floor(const float3& v) noexcept {
	return float3(std::floor(v.x), std::floor(v.y), std::floor(v.z)); }
static float3 trunc(const float3& v) noexcept {
	return float3(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z)); }
static float3 round(const float3& v) noexcept {
	return float3(std::round(v.x), std::round(v.y), std::round(v.z)); }
static float3 repeat(const float3& v) noexcept {
	return float3(repeat(v.x), repeat(v.y), repeat(v.z)); }
static float3 sign(const float3& v) noexcept {
	return float3(sign(v.x), sign(v.y), sign(v.z)); }

//------------------------------------------------------------------------------------------------------------
static float3 exp(const float3& v) noexcept { 
	return float3(std::exp(v.x), std::exp(v.y), std::exp(v.z)); }
static float3 exp2(const float3& v) noexcept {
	return float3(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z)); }
static float3 expm1(const float3& v) noexcept {
	return float3(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z)); }
static float3 log(const float3& v) noexcept {
	return float3(std::log(v.x), std::log(v.y), std::log(v.z)); }
static float3 log10(const float3& v) noexcept {
	return float3(std::log10(v.x), std::log10(v.y), std::log10(v.z)); }
static float3 log2(const float3& v) noexcept {
	return float3(std::log2(v.x), std::log2(v.y), std::log2(v.z)); }
static float3 log1p(const float3& v) noexcept {
	return float3(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z)); }
static float3 pow(const float3& a, const float3& b) noexcept {
	return float3(std::pow(a.x, b.x), std::pow(a.y, b.y), std::pow(a.z, b.z)); }
static float3 sqrt(const float3& v) noexcept {
	return float3(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z)); }
static float3 cbrt(const float3& v) noexcept {
	return float3(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z)); }

//------------------------------------------------------------------------------------------------------------
static float3 sin(const float3& v) noexcept {
	return float3(std::sin(v.x), std::sin(v.y), std::sin(v.z)); }
static float3 cos(const float3& v) noexcept {
	return float3(std::cos(v.x), std::cos(v.y), std::cos(v.z)); }
static float3 tan(const float3& v) noexcept {
	return float3(std::tan(v.x), std::tan(v.y), std::tan(v.z)); }
static float3 asin(const float3& v) noexcept {
	return float3(std::asin(v.x), std::asin(v.y), std::asin(v.z)); }
static float3 acos(const float3& v) noexcept {
	return float3(std::acos(v.x), std::acos(v.y), std::acos(v.z)); }
static float3 atan(const float3& v) noexcept {
	return float3(std::atan(v.x), std::atan(v.y), std::atan(v.z)); }
static float3 atan(const float3& a, const float3& b) noexcept {
	return float3(std::atan2(a.x, b.x), std::atan2(a.y, b.y), std::atan2(a.z, b.z)); }
static float3 sinh(const float3& v) noexcept {
	return float3(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z)); }
static float3 cosh(const float3& v) noexcept {
	return float3(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z)); }
static float3 tanh(const float3& v) noexcept {
	return float3(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z)); }
static float3 asinh(const float3& v) noexcept {
	return float3(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z)); }
static float3 acosh(const float3& v) noexcept {
	return float3(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z)); }
static float3 atanh(const float3& v) noexcept {
	return float3(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z)); }

//------------------------------------------------------------------------------------------------------------
static float dot(const float3& a, const float3& b) noexcept {
	return a.x * b.x + a.y * b.y + a.z * b.z; }
static float3 cross(const float3& a, const float3& b) noexcept {
	return float3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x); }
static float length(const float3& v) noexcept { return std::sqrt(dot(v, v)); }
static float length2(const float3& v) noexcept { return dot(v, v); }
static float distance(const float3& a, const float3& b) noexcept { return length(a - b); }
static float distance2(const float3& a, const float3& b) noexcept { return length2(a - b); }

static float3 normalize(const float3& v) noexcept
{
	auto l = length(v);
	assert(l > 0.0f);
	return v * (1.0f / l);
}
static float3 lerp(const float3& a, const float3& b, float t) noexcept
{
	assert(t >= 0.0f);
	assert(t <= 1.0f);
	return a * (1.0f - t) + b * t;
}

static bool isBinaryLess(const float3& a, const float3& b) noexcept {
	return memcmp(&a, &b, sizeof(float) * 3) < 0; }

//------------------------------------------------------------------------------------------------------------
static int3 operator+(const int3& v, int32 n) noexcept {
	return int3(v.x + n, v.y + n, v.z + n); }
static int3 operator-(const int3& v, int32 n) noexcept {
	return int3(v.x - n, v.y - n, v.z - n); }
static int3 operator*(const int3& v, int32 n) noexcept {
	return int3(v.x * n, v.y * n, v.z * n); }
static int3 operator/(const int3& v, int32 n) noexcept {
	return int3(v.x / n, v.y / n, v.z / n); }
static int3 operator%(const int3& v, int32 n) noexcept {
	return int3(v.x % n, v.y % n, v.z % n); }
static int3 operator&(const int3& v, int32 n) noexcept {
	return int3(v.x & n, v.y & n, v.z & n); }
static int3 operator|(const int3& v, int32 n) noexcept {
	return int3(v.x | n, v.y | n, v.z | n); }
static int3 operator^(const int3& v, int32 n) noexcept {
	return int3(v.x ^ n, v.y ^ n, v.z ^ n); }
static int3 operator>>(const int3& v, int32 n) noexcept {
	return int3(v.x >> n, v.y >> n, v.z >> n); }
static int3 operator<<(const int3& v, int32 n) noexcept {
	return int3(v.x << n, v.y << n, v.z << n); }
static bool operator==(const int3& v, int32 n) noexcept { return v == int3(n); }
static bool operator!=(const int3& v, int32 n) noexcept { return v != int3(n); }
static bool operator<(const int3& v, int32 n) noexcept { return v < int3(n); }
static bool operator>(const int3& v, int32 n) noexcept { return v > int3(n); }
static bool operator<=(const int3& v, int32 n) noexcept { return v <= int3(n); }
static bool operator>=(const int3& v, int32 n) noexcept { return v >= int3(n); }

static int3 operator+(int32 n, const int3& v) noexcept {
	return int3(n + v.x, n + v.y, n + v.z); }
static int3 operator-(int32 n, const int3& v) noexcept {
	return int3(n - v.x, n - v.y, n - v.z); }
static int3 operator*(int32 n, const int3& v) noexcept {
	return int3(n * v.x, n * v.y, n * v.z); }
static int3 operator/(int32 n, const int3& v) noexcept {
	return int3(n / v.x, n / v.y, n / v.z); }
static int3 operator%(int32 n, const int3& v) noexcept {
	return int3(n % v.x, n % v.y, n % v.z); }
static int3 operator&(int32 n, const int3& v) noexcept {
	return int3(n & v.x, n & v.y, n & v.z); }
static int3 operator|(int32 n, const int3& v) noexcept {
	return int3(n | v.x, n | v.y, n | v.z); }
static int3 operator^(int32 n, const int3& v) noexcept {
	return int3(n ^ v.x, n ^ v.y, n ^ v.z); }
static int3 operator>>(int32 n, const int3& v) noexcept {
	return int3(n >> v.x, n >> v.y, n >> v.z); }
static int3 operator<<(int32 n, const int3& v) noexcept {
	return int3(n << v.x, n << v.y, n << v.z); }
static bool operator==(int32 n, const int3& v) noexcept { return int3(n) == v; }
static bool operator!=(int32 n, const int3& v) noexcept { return int3(n) != v; }
static bool operator<(int32 n, const int3& v) noexcept { return int3(n) < v; }
static bool operator>(int32 n, const int3& v) noexcept { return int3(n) > v; }
static bool operator<=(int32 n, const int3& v) noexcept { return int3(n) <= v; }
static bool operator>=(int32 n, const int3& v) noexcept { return int3(n) >= v; }

//------------------------------------------------------------------------------------------------------------
static int3 max(const int3& a, const int3& b) noexcept {
	return int3(std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z)); }
static int3 max(const int3& a, const int3& b, const int3& c)
	noexcept { return max(max(a, b), c); }
static int3 min(const int3& a, const int3& b) noexcept {
	return int3(std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z)); }
static int3 min(const int3& a, const int3& b, const int3& c)
	noexcept { return min(min(a, b), c); }
static int3 clamp(const int3& v, const int3& min, const int3& max) noexcept {
	return int3(std::clamp(v.x, min.x, max.x),
	std::clamp(v.y, min.y, max.y), std::clamp(v.z, min.z, max.z)); }

static int32 dot(const int3& a, const int3& b) noexcept {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
static int32 length2(const int3& v) noexcept { return dot(v, v); }
static int32 distance2(const int3& a, const int3& b) noexcept { return length2(a - b); }

static bool isBinaryLess(const int3& a, const int3& b) noexcept {
	return memcmp(&a, &b, sizeof(int32) * 3) < 0; }

//------------------------------------------------------------------------------------------------------------
static float4 operator+(const float4& v, float n) noexcept {
	return float4(v.x + n, v.y + n, v.z + n, v.w + n); }
static float4 operator-(const float4& v, float n) noexcept {
	return float4(v.x - n, v.y - n, v.z - n, v.w - n); }
static float4 operator*(const float4& v, float n) noexcept {
	return float4(v.x * n, v.y * n, v.z * n, v.w * n); }
static float4 operator/(const float4& v, float n) noexcept {
	return float4(v.x / n, v.y / n, v.z / n, v.w / n); }
static bool operator==(const float4& v, float n) noexcept { return v == float4(n); }
static bool operator!=(const float4& v, float n) noexcept { return v != float4(n); }
static bool operator<(const float4& v, float n) noexcept { return v < float4(n); }
static bool operator>(const float4& v, float n) noexcept { return v > float4(n); }
static bool operator<=(const float4& v, float n) noexcept { return v <= float4(n); }
static bool operator>=(const float4& v, float n) noexcept { return v >= float4(n); }

static float4 operator+(float n, const float4& v) noexcept {
	return float4(n + v.x, n + v.y, n + v.z, n + v.w); }
static float4 operator-(float n, const float4& v) noexcept {
	return float4(n - v.x, n - v.y, n - v.z, n - v.w); }
static float4 operator*(float n, const float4& v) noexcept {
	return float4(n * v.x, n * v.y, n * v.z, n * v.w); }
static float4 operator/(float n, const float4& v) noexcept {
	return float4(n / v.x, n / v.y, n / v.z, n / v.w); }
static bool operator==(float n, const float4& v) noexcept { return float4(n) == v; }
static bool operator!=(float n, const float4& v) noexcept { return float4(n) != v; }
static bool operator<(float n, const float4& v) noexcept { return float4(n) < v; }
static bool operator>(float n, const float4& v) noexcept { return float4(n) > v; }
static bool operator<=(float n, const float4& v) noexcept { return float4(n) <= v; }
static bool operator>=(float n, const float4& v) noexcept { return float4(n) >= v; }

//------------------------------------------------------------------------------------------------------------
static float4 abs(const float4& v) noexcept {
	return float4(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }
static float4 mod(const float4& a, const float4& b) noexcept {
	return float4(std::fmod(a.x, b.x), std::fmod(a.y, b.y),
	std::fmod(a.z, b.z), std::fmod(a.w, b.w)); }
static float4 fma(const float4& a, const float4& b, const float4& c) noexcept {
	return float4(std::fma(a.x, b.x, c.x), std::fma(a.y, b.y, c.y),
	std::fma(a.z, b.z, c.z), std::fma(a.w, b.w, c.w)); }
static float4 max(const float4& a, const float4& b) noexcept {
	return float4(std::max(a.x, b.x), std::max(a.y, b.y),
	std::max(a.z, b.z), std::max(a.w, b.w)); }
static float4 max(const float4& a, const float4& b, const float4& c)
	noexcept { return max(max(a, b), c); }
static float4 min(const float4& a, const float4& b) noexcept {
	return float4(std::min(a.x, b.x), std::min(a.y, b.y),
	std::min(a.z, b.z), std::min(a.w, b.w)); }
static float4 min(const float4& a, const float4& b, const float4& c)
	noexcept { return min(min(a, b), c); }
static float4 clamp(const float4& v, const float4& min, const float4& max) noexcept {
	return float4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
	std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w)); }
static float4 ceil(const float4& v) noexcept {
	return float4(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w)); }
static float4 floor(const float4& v) noexcept {
	return float4(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w)); }
static float4 trunc(const float4& v) noexcept {
	return float4(std::trunc(v.x), std::trunc(v.y), std::trunc(v.z), std::trunc(v.w)); }
static float4 round(const float4& v) noexcept {
	return float4(std::round(v.x), std::round(v.y), std::round(v.z), std::round(v.w)); }
static float4 repeat(const float4& v) noexcept {
	return float4(repeat(v.x), repeat(v.y), repeat(v.z), repeat(v.w)); }
static float4 sign(const float4& v) noexcept {
	return float4(sign(v.x), sign(v.y), sign(v.z), sign(v.w)); }

//------------------------------------------------------------------------------------------------------------
static float4 exp(const float4& v) noexcept { 
	return float4(std::exp(v.x), std::exp(v.y), std::exp(v.z), std::exp(v.w)); }
static float4 exp2(const float4& v) noexcept {
	return float4(std::exp2(v.x), std::exp2(v.y), std::exp2(v.z), std::exp2(v.w)); }
static float4 expm1(const float4& v) noexcept {
	return float4(std::expm1(v.x), std::expm1(v.y), std::expm1(v.z), std::expm1(v.w)); }
static float4 log(const float4& v) noexcept {
	return float4(std::log(v.x), std::log(v.y), std::log(v.z), std::log(v.w)); }
static float4 log10(const float4& v) noexcept {
	return float4(std::log10(v.x), std::log10(v.y), std::log10(v.z), std::log10(v.w)); }
static float4 log2(const float4& v) noexcept {
	return float4(std::log2(v.x), std::log2(v.y), std::log2(v.z), std::log2(v.w)); }
static float4 log1p(const float4& v) noexcept {
	return float4(std::log1p(v.x), std::log1p(v.y), std::log1p(v.z), std::log1p(v.w)); }
static float4 pow(const float4& a, const float4& b) noexcept {
	return float4(std::pow(a.x, b.x), std::pow(a.y, b.y),
	std::pow(a.z, b.z), std::pow(a.w, b.w)); }
static float4 sqrt(const float4& v) noexcept {
	return float4(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w)); }
static float4 cbrt(const float4& v) noexcept {
	return float4(std::cbrt(v.x), std::cbrt(v.y), std::cbrt(v.z), std::cbrt(v.w)); }

//------------------------------------------------------------------------------------------------------------
static float4 sin(const float4& v) noexcept {
	return float4(std::sin(v.x), std::sin(v.y), std::sin(v.z), std::sin(v.w)); }
static float4 cos(const float4& v) noexcept {
	return float4(std::cos(v.x), std::cos(v.y), std::cos(v.z), std::cos(v.w)); }
static float4 tan(const float4& v) noexcept {
	return float4(std::tan(v.x), std::tan(v.y), std::tan(v.z), std::tan(v.w)); }
static float4 asin(const float4& v) noexcept {
	return float4(std::asin(v.x), std::asin(v.y), std::asin(v.z), std::asin(v.w)); }
static float4 acos(const float4& v) noexcept {
	return float4(std::acos(v.x), std::acos(v.y), std::acos(v.z), std::acos(v.w)); }
static float4 atan(const float4& v) noexcept {
	return float4(std::atan(v.x), std::atan(v.y), std::atan(v.z), std::atan(v.w)); }
static float4 atan(const float4& a, const float4& b) noexcept {
	return float4(std::atan2(a.x, b.x), std::atan2(a.y, b.y),
	std::atan2(a.z, b.z), std::atan2(a.w, b.w)); }
static float4 sinh(const float4& v) noexcept {
	return float4(std::sinh(v.x), std::sinh(v.y), std::sinh(v.z), std::sinh(v.w)); }
static float4 cosh(const float4& v) noexcept {
	return float4(std::cosh(v.x), std::cosh(v.y), std::cosh(v.z), std::cosh(v.w)); }
static float4 tanh(const float4& v) noexcept {
	return float4(std::tanh(v.x), std::tanh(v.y), std::tanh(v.z), std::tanh(v.w)); }
static float4 asinh(const float4& v) noexcept {
	return float4(std::asinh(v.x), std::asinh(v.y), std::asinh(v.z), std::asinh(v.w)); }
static float4 acosh(const float4& v) noexcept {
	return float4(std::acosh(v.x), std::acosh(v.y), std::acosh(v.z), std::acosh(v.w)); }
static float4 atanh(const float4& v) noexcept {
	return float4(std::atanh(v.x), std::atanh(v.y), std::atanh(v.z), std::atanh(v.w)); }

//------------------------------------------------------------------------------------------------------------
static float dot(const float4& a, const float4& b) noexcept {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
static float length(const float4& v) noexcept { return std::sqrt(dot(v, v)); }
static float length2(const float4& v) noexcept { return dot(v, v); }
static float distance(const float4& a, const float4& b) noexcept { return length(a - b); }
static float distance2(const float4& a, const float4& b) noexcept { return length2(a - b); }

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

static bool isBinaryLess(const float4& a, const float4& b) noexcept {
	return memcmp(&a, &b, sizeof(float) * 4) < 0; }

//------------------------------------------------------------------------------------------------------------
static int4 operator+(const int4& v, int32 n) noexcept {
	return int4(v.x + n, v.y + n, v.z + n, v.w + n); }
static int4 operator-(const int4& v, int32 n) noexcept {
	return int4(v.x - n, v.y - n, v.z - n, v.w - n); }
static int4 operator*(const int4& v, int32 n) noexcept {
	return int4(v.x * n, v.y * n, v.z * n, v.w * n); }
static int4 operator/(const int4& v, int32 n) noexcept {
	return int4(v.x / n, v.y / n, v.z / n, v.w / n); }
static int4 operator%(const int4& v, int32 n) noexcept {
	return int4(v.x % n, v.y % n, v.z % n, v.w % n); }
static int4 operator&(const int4& v, int32 n) noexcept {
	return int4(v.x & n, v.y & n, v.z & n, v.w & n); }
static int4 operator|(const int4& v, int32 n) noexcept {
	return int4(v.x | n, v.y | n, v.z | n, v.w | n); }
static int4 operator^(const int4& v, int32 n) noexcept {
	return int4(v.x ^ n, v.y ^ n, v.z ^ n, v.w ^ n); }
static int4 operator>>(const int4& v, int32 n) noexcept {
	return int4(v.x >> n, v.y >> n, v.z >> n, v.w >> n); }
static int4 operator<<(const int4& v, int32 n) noexcept {
	return int4(v.x << n, v.y << n, v.z << n, v.w << n); }
static bool operator==(const int4& v, int32 n) noexcept { return v == int4(n); }
static bool operator!=(const int4& v, int32 n) noexcept { return v != int4(n); }
static bool operator<(const int4& v, int32 n) noexcept { return v < int4(n); }
static bool operator>(const int4& v, int32 n) noexcept { return v > int4(n); }
static bool operator<=(const int4& v, int32 n) noexcept { return v <= int4(n); }
static bool operator>=(const int4& v, int32 n) noexcept { return v >= int4(n); }

static int4 operator+(int32 n, const int4& v) noexcept {
	return int4(n + v.x, n + v.y, n + v.z, n + v.w); }
static int4 operator-(int32 n, const int4& v) noexcept {
	return int4(n - v.x, n - v.y, n - v.z, n - v.w); }
static int4 operator*(int32 n, const int4& v) noexcept {
	return int4(n * v.x, n * v.y, n * v.z, n * v.w); }
static int4 operator/(int32 n, const int4& v) noexcept {
	return int4(n / v.x, n / v.y, n / v.z, n / v.w); }
static int4 operator%(int32 n, const int4& v) noexcept {
	return int4(n % v.x, n % v.y, n % v.z, n % v.w); }
static int4 operator&(int32 n, const int4& v) noexcept {
	return int4(n & v.x, n & v.y, n & v.z, n & v.w); }
static int4 operator|(int32 n, const int4& v) noexcept {
	return int4(n | v.x, n | v.y, n | v.z, n | v.w); }
static int4 operator^(int32 n, const int4& v) noexcept {
	return int4(n ^ v.x, n ^ v.y, n ^ v.z, n ^ v.w); }
static int4 operator>>(int32 n, const int4& v) noexcept {
	return int4(n >> v.x, n >> v.y, n >> v.z, n >> v.w); }
static int4 operator<<(int32 n, const int4& v) noexcept {
	return int4(n << v.x, n << v.y, n << v.z, n << v.w); }
static bool operator==(int32 n, const int4& v) noexcept { return int4(n) == v; }
static bool operator!=(int32 n, const int4& v) noexcept { return int4(n) != v; }
static bool operator<(int32 n, const int4& v) noexcept { return int4(n) < v; }
static bool operator>(int32 n, const int4& v) noexcept { return int4(n) > v; }
static bool operator<=(int32 n, const int4& v) noexcept { return int4(n) <= v; }
static bool operator>=(int32 n, const int4& v) noexcept { return int4(n) >= v; }

//------------------------------------------------------------------------------------------------------------
static int4 max(const int4& a, const int4& b) noexcept {
	return int4(std::max(a.x, b.x), std::max(a.y, b.y),
	std::max(a.z, b.z), std::max(a.w, b.w)); }
static int4 max(const int4& a, const int4& b, const int4& c)
	noexcept { return max(max(a, b), c); }
static int4 min(const int4& a, const int4& b) noexcept {
	return int4(std::min(a.x, b.x), std::min(a.y, b.y),
	std::min(a.z, b.z), std::min(a.w, b.w)); }
static int4 min(const int4& a, const int4& b, const int4& c)
	noexcept { return min(min(a, b), c); }
static int4 clamp(const int4& v, const int4& min, const int4& max) noexcept {
	return int4(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y),
	std::clamp(v.z, min.z, max.z), std::clamp(v.w, min.w, max.w)); }

static int32 dot(const int4& a, const int4& b) noexcept {
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}
static int32 length2(const int4& v) noexcept { return dot(v, v); }
static int32 distance2(const int4& a, const int4& b) noexcept { return length2(a - b); }

static bool isBinaryLess(const int4& a, const int4& b) noexcept {
	return memcmp(&a, &b, sizeof(int32) * 4) < 0; }

//------------------------------------------------------------------------------------------------------------
static uint8 calcMipCount(int32 size)
{
	return (uint8)(std::floor(std::log2((float)size))) + 1;
}
static uint8 calcMipCount(int2 size)
{
	return (uint8)(std::floor(std::log2((float)std::max(size.x, size.y)))) + 1;
}
static uint8 calcMipCount(const int3& size)
{
	return (uint8)(std::floor(std::log2((float)
		std::max(std::max(size.x, size.y), size.z)))) + 1;
}

//------------------------------------------------------------------------------------------------------------
static int32 calcSizeAtMip(int32 sizeAt0, uint8 mip)
{
	return std::max(sizeAt0 / (int32)std::exp2((float)mip), 1);
}
static int2 calcSizeAtMip(int2 sizeAt0, uint8 mip)
{
	return max(sizeAt0 / (int32)std::exp2((float)mip), int2(1));
}
static int3 calcSizeAtMip(const int3& sizeAt0, uint8 mip)
{
	return max(sizeAt0 / (int32)std::exp2((float)mip), int3(1));
}

} // namespace math