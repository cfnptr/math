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
 * @brief Common floating point 16 bit vector functions.
 */

// TODO: add common math functions after targeting AVX-512 or AVX10 instruction set.

#pragma once
#include "math/vector/long.hpp"

namespace math
{

/**
 * @brief A 2-component vector of 16-bit floating-point values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] half2
{
	half x; /**< First vector component. */
	half y; /**< Second vector component. */

	/**
	 * @brief Creates a new 2-component vector of 16-bit floating-point values.
	 * @param xy target value for all vector components
	 */
	constexpr explicit half2(half xy = 0.0_hf) noexcept : x(xy), y(xy) { }
	/**
	 * @brief Creates a new 2-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 */
	constexpr half2(half x, half y) noexcept : x(x), y(y) { }

	explicit constexpr half2(long4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(long3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(long2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(ulong4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(ulong3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(ulong2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(int4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(int3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(int2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(uint4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(uint3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(uint2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(short4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(short3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(short2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(ushort4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(ushort3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	explicit constexpr half2(ushort2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	constexpr half2(sbyte4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	constexpr half2(sbyte3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	constexpr half2(sbyte2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	constexpr half2(byte4 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	constexpr half2(byte3 xy) noexcept : x((half)xy.x), y((half)xy.y) { }
	constexpr half2(byte2 xy) noexcept : x((half)xy.x), y((half)xy.y) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	half& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((half*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	half operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((half*)this)[i];
	}

	constexpr explicit operator long2() const noexcept { return long2((int64)x, (int64)y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	constexpr bool operator==(half2 v) const noexcept { return x == v.x && y == v.y; }
	constexpr bool operator!=(half2 v) const noexcept { return x != v.x || y != v.y; }

	constexpr bool operator==(half n) const noexcept { return *this == half2(n); }
	constexpr bool operator!=(half n) const noexcept { return *this != half2(n); }

	static const half2 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top;
};

inline constexpr half2 half2::zero = half2(0.0_hf);
inline constexpr half2 half2::one = half2(1.0_hf);
inline constexpr half2 half2::minusOne = half2(-1.0_hf);
inline constexpr half2 half2::min = half2(FLT16_MIN);
inline constexpr half2 half2::minusMin = half2(-FLT16_MIN);
inline constexpr half2 half2::max = half2(FLT16_MAX);
inline constexpr half2 half2::minusMax = half2(-FLT16_MAX);
inline constexpr half2 half2::epsilon = half2(FLT16_EPSILON);
inline constexpr half2 half2::inf = half2((half)INFINITY);
inline constexpr half2 half2::minusInf = half2((half)-INFINITY);
inline constexpr half2 half2::nan = half2((half)NAN);
inline constexpr half2 half2::left = half2(-1.0_hf, 0.0_hf);
inline constexpr half2 half2::right = half2(1.0_hf, 0.0_hf);
inline constexpr half2 half2::bottom = half2(0.0_hf, -1.0_hf);
inline constexpr half2 half2::top = half2(0.0_hf, 1.0_hf);

/***********************************************************************************************************************
 * @brief A 3-component vector of 16-bit floating-point values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] half3
{
	half x; /**< First vector component. */
	half y; /**< Second vector component. */
	half z; /**< Third vector component. */

	/**
	 * @brief Creates a new 3-component vector of 16-bit floating-point values.
	 * @param xyz target value for all vector components
	 */
	constexpr explicit half3(half xyz = 0.0_hf) noexcept : x(xyz), y(xyz), z(xyz) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 */
	constexpr half3(half x, half y, half z) noexcept : x(x), y(y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit floating-point values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 */
	constexpr half3(half2 xy, half z) noexcept : x(xy.x), y(xy.y), z(z) { }
	/**
	 * @brief Creates a new 3-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 */
	constexpr half3(half x, half2 yz) noexcept : x(x), y(yz.x), z(yz.y) { }

	explicit constexpr half3(long4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(long3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(ulong4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(ulong3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(int4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(int3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(uint4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(uint3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(short4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(short3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(ushort4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	explicit constexpr half3(ushort3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	constexpr half3(sbyte4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	constexpr half3(sbyte3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	constexpr half3(byte4 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }
	constexpr half3(byte3 xyz) noexcept : x((half)xyz.x), y((half)xyz.y), z((half)xyz.z) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	half& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((half*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	half operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((half*)this)[i];
	}

	constexpr explicit operator long3() const noexcept { return long3((int64)x, (int64)y, (int64)z); }
	constexpr explicit operator ulong3() const noexcept { return ulong3((uint64)x, (uint64)y, (uint64)z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator half2() const noexcept { return half2((half)x, (half)y); }
	constexpr explicit operator long2() const noexcept { return long2((int64)x, (int64)y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	constexpr bool operator==(half3 v) const noexcept { return x == v.x && y == v.y && z == v.z; }
	constexpr bool operator!=(half3 v) const noexcept { return x != v.x || y != v.y || z != v.z; }

	constexpr bool operator==(half n) const noexcept { return *this == half3(n); }
	constexpr bool operator!=(half n) const noexcept { return *this != half3(n); }

	static const half3 zero, one, minusOne, min, minusMin, max, minusMax, 
		epsilon, inf, minusInf, nan, left, right, bottom, top, back, front;
};

inline constexpr half3 half3::zero = half3(0.0_hf);
inline constexpr half3 half3::one = half3(1.0_hf);
inline constexpr half3 half3::minusOne = half3(-1.0_hf);
inline constexpr half3 half3::min = half3(FLT16_MIN);
inline constexpr half3 half3::minusMin = half3(-FLT16_MIN);
inline constexpr half3 half3::max = half3(FLT16_MAX);
inline constexpr half3 half3::minusMax = half3(-FLT16_MAX);
inline constexpr half3 half3::epsilon = half3(FLT16_EPSILON);
inline constexpr half3 half3::inf = half3((half)INFINITY);
inline constexpr half3 half3::minusInf = half3((half)-INFINITY);
inline constexpr half3 half3::nan = half3((half)NAN);
inline constexpr half3 half3::left = half3(-1.0_hf, 0.0_hf, 0.0_hf);
inline constexpr half3 half3::right = half3(1.0_hf, 0.0_hf, 0.0_hf);
inline constexpr half3 half3::bottom = half3(0.0_hf, -1.0_hf, 0.0_hf);
inline constexpr half3 half3::top = half3(0.0_hf, 1.0_hf, 0.0_hf);
inline constexpr half3 half3::back = half3(0.0_hf, 0.0_hf, -1.0_hf);
inline constexpr half3 half3::front = half3(0.0_hf, 0.0_hf, 1.0_hf);

/***********************************************************************************************************************
 * @brief A 4-component vector of 16-bit floating-point values.
 * @details Commonly used to represent: points, positions, directions, velocities, etc.
 */
struct [[nodiscard]] half4
{
	half x; /**< First vector component. */
	half y; /**< Second vector component. */
	half z; /**< Third vector component. */
	half w; /**< Fourth vector component. */

	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 * @param xyzw target value for all vector components
	 */
	constexpr explicit half4(half xyzw = 0.0_hf) noexcept : x(xyzw), y(xyzw), z(xyzw), w(xyzw) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr half4(half x, half y, half z, half w) noexcept : x(x), y(y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param xy first and second vector component value
	 * @param z third vector component value
	 * @param w fourth vector component value
	 */
	constexpr half4(half2 xy, half z, half w) noexcept : x(xy.x), y(xy.y), z(z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param yz second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr half4(half x, half2 yz, half w) noexcept : x(x), y(yz.x), z(yz.y), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param y second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr half4(half x, half y, half2 zw) noexcept : x(x), y(y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param xy first and second vector component value
	 * @param zw third and fourth vector component value
	 */
	constexpr half4(half2 xy, half2 zw) noexcept : x(xy.x), y(xy.y), z(zw.x), w(zw.y) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param xyz first, second and third vector component value
	 * @param w fourth vector component value
	 */
	constexpr half4(half3 xyz, half w) noexcept : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
	/**
	 * @brief Creates a new 4-component vector of 16-bit floating-point values.
	 *
	 * @param x first vector component value
	 * @param yzw second, third and fourth vector component value
	 */
	constexpr half4(half x, half3 yzw) noexcept : x(x), y(yzw.x), z(yzw.y), w(yzw.z) { }

	explicit constexpr half4(long4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	explicit constexpr half4(ulong4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	explicit constexpr half4(int4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	explicit constexpr half4(uint4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	explicit constexpr half4(short4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	explicit constexpr half4(ushort4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	constexpr half4(sbyte4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }
	constexpr half4(byte4 xyzw) noexcept : x((half)xyzw.x), y((half)xyzw.y), z((half)xyzw.z), w((half)xyzw.w) { }

	/*******************************************************************************************************************
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	half& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((half*)this)[i];
	}
	/**
	 * @brief Returns vector component by index.
	 * @param i target component index
	 */
	half operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((half*)this)[i];
	}

	constexpr explicit operator long4() const noexcept { return long4((int64)x, (int64)y, (int64)z, (int64)w); }
	constexpr explicit operator ulong4() const noexcept { return ulong4((uint64)x, (uint64)y, (uint64)z, (uint64)w); }
	constexpr explicit operator int4() const noexcept { return int4((int32)x, (int32)y, (int32)z, (int32)w); }
	constexpr explicit operator uint4() const noexcept { return uint4((uint32)x, (uint32)y, (uint32)z, (uint32)w); }
	constexpr explicit operator short4() const noexcept { return short4((int16)x, (int16)y, (int16)z, (int16)w); }
	constexpr explicit operator ushort4() const noexcept { return ushort4((uint16)x, (uint16)y, (uint16)z, (uint16)w); }
	constexpr explicit operator sbyte4() const noexcept { return sbyte4((int8)x, (int8)y, (int8)z, (int8)w); }
	constexpr explicit operator byte4() const noexcept { return byte4((uint8)x, (uint8)y, (uint8)z, (uint8)w); }
	constexpr explicit operator half3() const noexcept { return half3((half)x, (half)y, (half)z); }
	constexpr explicit operator long3() const noexcept { return long3((int64)x, (int64)y, (int64)z); }
	constexpr explicit operator ulong3() const noexcept { return ulong3((uint64)x, (uint64)y, (uint64)z); }
	constexpr explicit operator int3() const noexcept { return int3((int32)x, (int32)y, (int32)z); }
	constexpr explicit operator uint3() const noexcept { return uint3((uint32)x, (uint32)y, (uint32)z); }
	constexpr explicit operator short3() const noexcept { return short3((int16)x, (int16)y, (int16)z); }
	constexpr explicit operator ushort3() const noexcept { return ushort3((uint16)x, (uint16)y, (uint16)z); }
	constexpr explicit operator sbyte3() const noexcept { return sbyte3((int8)x, (int8)y, (int8)z); }
	constexpr explicit operator byte3() const noexcept { return byte3((uint8)x, (uint8)y, (uint8)z); }
	constexpr explicit operator half2() const noexcept { return half2((half)x, (half)y); }
	constexpr explicit operator long2() const noexcept { return long2((int64)x, (int64)y); }
	constexpr explicit operator ulong2() const noexcept { return ulong2((uint64)x, (uint64)y); }
	constexpr explicit operator int2() const noexcept { return int2((int32)x, (int32)y); }
	constexpr explicit operator uint2() const noexcept { return uint2((uint32)x, (uint32)y); }
	constexpr explicit operator short2() const noexcept { return short2((int16)x, (int16)y); }
	constexpr explicit operator ushort2() const noexcept { return ushort2((uint16)x, (uint16)y); }
	constexpr explicit operator sbyte2() const noexcept { return sbyte2((int8)x, (int8)y); }
	constexpr explicit operator byte2() const noexcept { return byte2((uint8)x, (uint8)y); }

	constexpr bool operator==(half4 v) const noexcept { return x == v.x && y == v.y && z == v.z && w == v.w; }
	constexpr bool operator!=(half4 v) const noexcept { return x != v.x || y != v.y || z != v.z || w != v.w; }

	constexpr bool operator==(half n) const noexcept { return *this == half4(n); }
	constexpr bool operator!=(half n) const noexcept { return *this != half4(n); }

	static const half4 zero, one, minusOne, min, minusMin, max, minusMax, epsilon, inf, minusInf, nan;
};

inline constexpr half4 half4::zero = half4(0.0_hf);
inline constexpr half4 half4::one = half4(1.0_hf);
inline constexpr half4 half4::minusOne = half4(-1.0_hf);
inline constexpr half4 half4::min = half4(FLT16_MIN);
inline constexpr half4 half4::minusMin = half4(-FLT16_MIN);
inline constexpr half4 half4::max = half4(FLT16_MAX);
inline constexpr half4 half4::minusMax = half4(-FLT16_MAX);
inline constexpr half4 half4::epsilon = half4(FLT16_EPSILON);
inline constexpr half4 half4::inf = half4((half)INFINITY);
inline constexpr half4 half4::minusInf = half4((half)-INFINITY);
inline constexpr half4 half4::nan = half4((half)NAN);

} // namespace math