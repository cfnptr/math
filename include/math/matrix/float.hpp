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
 * @brief Common floating point matrix functions.
 * 
 * Coordinate system: X-right, Y-up, Z-forward (Left handed)
 * Matrices order: Column-major. (OpenGL, Vulkan like)
 * floatCxR -where C columns and R rows
 * 
 * Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

/**
 * @brief Floating point 2x2 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct [[nodiscard]] float2x2
{
	float2 c0; /**< First matrix column. */
	float2 c1; /**< Second matrix column. */

	/**
	 * @brief Creates a new floating point 2x2 matrix structure.
	 * @param n target value for all columns and rows
	 */
	constexpr explicit float2x2(float n = 0.0f) noexcept : c0(n), c1(n) { }
	/**
	 * @brief Creates a new floating point 2x2 matrix structure.
	 * @details See the @ref float2x2.
	 */
	constexpr float2x2(
		float c0r0, float c1r0,
		float c0r1, float c1r1) noexcept :
		c0(float2(c0r0, c0r1)),
		c1(float2(c1r0, c1r1)) { }
	/**
	 * @brief Creates a new floating point 2x2 matrix structure.
	 * 
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 */
	constexpr float2x2(float2 c0, float2 c1) noexcept : c0(c0), c1(c1) { }
	
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float2& operator[](psize i) noexcept
	{
		assert(i <= 1);
		return ((float2*)this)[i];
	}
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float2 operator[](psize i) const noexcept
	{
		assert(i <= 1);
		return ((float2*)this)[i];
	}

	constexpr float2x2 operator+(float n) const noexcept { return float2x2(c0 + n, c1 + n); }
	constexpr float2x2 operator-(float n) const noexcept { return float2x2(c0 - n, c1 - n); }
	constexpr float2x2 operator*(float n) const noexcept { return float2x2(c0 * n, c1 * n); }
	constexpr float2x2 operator/(float n) const noexcept { return float2x2(c0 / n, c1 / n); }
	float2x2& operator+=(float n) noexcept { c0 += n; c1 += n; return *this; }
	float2x2& operator-=(float n) noexcept { c0 -= n; c1 -= n; return *this; }
	float2x2& operator*=(float n) noexcept { c0 *= n; c1 *= n; return *this; }
	float2x2& operator/=(float n) noexcept { c0 /= n, c1 /= n; return *this; }

	/**
	 * @brief Calculates dot product between two matrices.
	 * @param m target matrix to dot by
	 */
	constexpr float2x2 operator*(float2x2 m) const noexcept
	{
		return float2x2(
			c0 * m.c0.x + c1 * m.c0.y,
			c0 * m.c1.x + c1 * m.c1.y);
	}
	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param v target vector to dot by
	 */
	constexpr float2 operator*(float2 v) const noexcept
	{
		return float2(
			c0.x * v.x + c1.x * v.y,
			c0.y * v.x + c1.y * v.y);
	}
	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	float2x2& operator*=(const float2x2& m) noexcept { return *this = *this * m; }

	/**
	 * @brief Returns true if matrices have the same values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator==(const float2x2& m) const noexcept { return memcmp(this, &m, sizeof(float2x2)) == 0; }
	/**
	 * @brief Returns true if matrices have different values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator!=(const float2x2& m) const noexcept { return memcmp(this, &m, sizeof(float2x2)) != 0; }

	static const float2x2 zero, one, minusOne, identity;
};

inline const float2x2 float2x2::identity = float2x2(
	1.0f, 0.0f,
	0.0f, 1.0f);
inline const float2x2 float2x2::zero = float2x2(0.0f);
inline const float2x2 float2x2::one = float2x2(1.0f);
inline const float2x2 float2x2::minusOne = float2x2(-1.0f);

/***********************************************************************************************************************
 * @brief Floating point 3x3 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct [[nodiscard]] float3x3
{
	float3 c0; /**< First matrix column. */
	float3 c1; /**< Second matrix column. */
	float3 c2; /**< Third matrix column. */

	/**
	 * @brief Creates a new floating point 3x3 matrix structure.
	 * @param n target value for all columns and rows
	 */
	constexpr explicit float3x3(float n = 0.0f) noexcept : c0(n), c1(n), c2(n) { }
	/**
	 * @brief Creates a new floating point 3x3 matrix structure.
	 * @details See the @ref float3x3.
	 */
	constexpr float3x3(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1,
		float c0r2, float c1r2, float c2r2) noexcept :
		c0(float3(c0r0, c0r1, c0r2)),
		c1(float3(c1r0, c1r1, c1r2)),
		c2(float3(c2r0, c2r1, c2r2)) { }
	/**
	 * @brief Creates a new floating point 3x3 matrix structure.
	 *
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 * @param c2 third matrix column value
	 */
	constexpr float3x3(float3 c0, float3 c1, float3 c2) noexcept : c0(c0), c1(c1), c2(c2) { }

	/**
	 * @brief Returns matrix 2x2 part.
	 */
	constexpr explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }
	
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float3& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((float3*)this)[i];
	}
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float3 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float3*)this)[i];
	}

	constexpr float3x3 operator+(float n) const noexcept { return float3x3(c0 + n, c1 + n, c2 + n); }
	constexpr float3x3 operator-(float n) const noexcept { return float3x3(c0 - n, c1 - n, c2 - n); }
	constexpr float3x3 operator*(float n) const noexcept { return float3x3(c0 * n, c1 * n, c2 * n); }
	constexpr float3x3 operator/(float n) const noexcept { return float3x3(c0 / n, c1 / n, c2 / n); }
	float3x3& operator+=(float n) noexcept { c0 += n; c1 += n; c2 += n; return *this; }
	float3x3& operator-=(float n) noexcept { c0 -= n; c1 -= n; c2 -= n; return *this; }
	float3x3& operator*=(float n) noexcept { c0 *= n; c1 *= n; c2 *= n; return *this; }
	float3x3& operator/=(float n) noexcept { c0 /= n, c1 /= n; c2 /= n; return *this; }

	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	constexpr float3x3 operator*(const float3x3& m) const noexcept
	{
		return float3x3(
			c0 * m.c0.x + c1 * m.c0.y + c2 * m.c0.z,
			c0 * m.c1.x + c1 * m.c1.y + c2 * m.c1.z,
			c0 * m.c2.x + c1 * m.c2.y + c2 * m.c2.z);
	}
	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param v target vector to dot by
	 */
	constexpr float3 operator*(float3 v) const noexcept
	{
		return float3(
			c0.x * v.x + c1.x * v.y + c2.x * v.z,
			c0.y * v.x + c1.y * v.y + c2.y * v.z,
			c0.z * v.x + c1.z * v.y + c2.z * v.z);
	}
	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	float3x3& operator*=(const float3x3& m) noexcept { return *this = *this * m; }

	/**
	 * @brief Returns true if matrices have the same values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator==(const float3x3& m) const noexcept { return memcmp(this, &m, sizeof(float3x3)) == 0; }
	/**
	 * @brief Returns true if matrices have different values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator!=(const float3x3& m) const noexcept { return memcmp(this, &m, sizeof(float3x3)) != 0; }

	static const float3x3 zero, one, minusOne, identity;
};

inline const float3x3 float3x3::identity = float3x3(
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f);
inline const float3x3 float3x3::zero = float3x3(0.0f);
inline const float3x3 float3x3::one = float3x3(1.0f);
inline const float3x3 float3x3::minusOne = float3x3(-1.0f);

/***********************************************************************************************************************
 * @brief Floating point 4x3 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct [[nodiscard]] float4x3
{
	float3 c0; /**< First matrix column. */
	float3 c1; /**< Second matrix column. */
	float3 c2; /**< Third matrix column. */
	float3 c3; /**< Fourth matrix column. */

	/**
	 * @brief Creates a new floating point 4x3 matrix structure.
	 * @param n target value for all columns and rows
	 */
	constexpr explicit float4x3(float n = 0.0f) noexcept : c0(n), c1(n), c2(n), c3(n) { }
	/**
	 * @brief Creates a new floating point 4x3 matrix structure.
	 * @details See the @ref float3x3.
	 */
	constexpr float4x3(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2) noexcept :
		c0(float3(c0r0, c0r1, c0r2)),
		c1(float3(c1r0, c1r1, c1r2)),
		c2(float3(c2r0, c2r1, c2r2)),
		c3(float3(c3r0, c3r1, c3r2)) { }
	/**
	 * @brief Creates a new floating point 4x3 matrix structure.
	 *
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 * @param c2 third matrix column value
	 * @param c3 fourth matrix column value
	 */
	constexpr float4x3(float3 c0, float3 c1, float3 c2, float3 c3) noexcept : c0(c0), c1(c1), c2(c2), c3(c3) { }

	/**
	 * @brief Returns matrix 2x2 part.
	 */
	constexpr explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }
	/**
	 * @brief Returns matrix 3x3 part.
	 */
	constexpr explicit operator float3x3() const noexcept { return float3x3(c0, c1, c2); }

	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float3& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((float3*)this)[i];
	}
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float3 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float3*)this)[i];
	}

	constexpr float4x3 operator+(float n) const noexcept { return float4x3(c0 + n, c1 + n, c2 + n, c3 + n); }
	constexpr float4x3 operator-(float n) const noexcept { return float4x3(c0 - n, c1 - n, c2 - n, c3 - n); }
	constexpr float4x3 operator*(float n) const noexcept { return float4x3(c0 * n, c1 * n, c2 * n, c3 * n); }
	constexpr float4x3 operator/(float n) const noexcept { return float4x3(c0 / n, c1 / n, c2 / n, c3 / n); }
	float4x3& operator+=(float n) noexcept { c0 += n; c1 += n; c2 += n; c3 += n; return *this; }
	float4x3& operator-=(float n) noexcept { c0 -= n; c1 -= n; c2 -= n; c3 -= n; return *this; }
	float4x3& operator*=(float n) noexcept { c0 *= n; c1 *= n; c2 *= n; c3 *= n; return *this; }
	float4x3& operator/=(float n) noexcept { c0 /= n, c1 /= n; c2 /= n; c3 /= n; return *this; }

	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param v target vector to dot by
	 */
	constexpr float3 operator*(float4 v) const noexcept
	{
		return float3(
			c0.x * v.x + c1.x * v.y + c2.x * v.z + c3.x * v.w,
			c0.y * v.x + c1.y * v.y + c2.y * v.z + c3.y * v.w,
			c0.z * v.x + c1.z * v.y + c2.z * v.z + c3.z * v.w);
	}

	/**
	 * @brief Returns true if matrices have the same values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator==(const float4x3& m) const noexcept { return memcmp(this, &m, sizeof(float4x3)) == 0; }
	/**
	 * @brief Returns true if matrices have different values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator!=(const float4x3& m) const noexcept { return memcmp(this, &m, sizeof(float4x3)) != 0; }

	static const float4x3 zero, one, minusOne, identity;
};

inline const float4x3 float4x3::identity = float4x3(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f);
inline const float4x3 float4x3::zero = float4x3(0.0f);
inline const float4x3 float4x3::one = float4x3(1.0f);
inline const float4x3 float4x3::minusOne = float4x3(-1.0f);

/***********************************************************************************************************************
 * @brief Floating point 3x4 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct [[nodiscard]] float3x4
{
	float4 c0; /**< First matrix column. */
	float4 c1; /**< Second matrix column. */
	float4 c2; /**< Third matrix column. */

	/**
	 * @brief Creates a new floating point 3x4 matrix structure.
	 * @param n target value for all columns and rows
	 */
	constexpr explicit float3x4(float n = 0.0f) noexcept : c0(n), c1(n), c2(n) { }
	/**
	 * @brief Creates a new floating point 3x4 matrix structure.
	 * @details See the @ref float3x3.
	 */
	constexpr float3x4(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1,
		float c0r2, float c1r2, float c2r2,
		float c0r3, float c1r3, float c2r3) noexcept :
		c0(float4(c0r0, c0r1, c0r2, c0r3)),
		c1(float4(c1r0, c1r1, c1r2, c1r3)),
		c2(float4(c2r0, c2r1, c2r2, c2r3)) { }
	/**
	 * @brief Creates a new floating point 3x4 matrix structure.
	 *
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 * @param c2 third matrix column value
	 */
	constexpr float3x4(float4 c0, float4 c1, float4 c2) noexcept : c0(c0), c1(c1), c2(c2) { }

	/**
	 * @brief Returns matrix 2x2 part.
	 */
	constexpr explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }
	/**
	 * @brief Returns matrix 3x3 part.
	 */
	constexpr explicit operator float3x3() const noexcept { return float3x3((float3)c0, (float3)c1, (float3)c2); }

	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float4& operator[](psize i) noexcept
	{
		assert(i <= 2);
		return ((float4*)this)[i];
	}
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float4 operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float4*)this)[i];
	}

	constexpr float3x4 operator+(float n) const noexcept { return float3x4(c0 + n, c1 + n, c2 + n); }
	constexpr float3x4 operator-(float n) const noexcept { return float3x4(c0 - n, c1 - n, c2 - n); }
	constexpr float3x4 operator*(float n) const noexcept { return float3x4(c0 * n, c1 * n, c2 * n); }
	constexpr float3x4 operator/(float n) const noexcept { return float3x4(c0 / n, c1 / n, c2 / n); }
	float3x4& operator+=(float n) noexcept { c0 += n; c1 += n; c2 += n; return *this; }
	float3x4& operator-=(float n) noexcept { c0 -= n; c1 -= n; c2 -= n; return *this; }
	float3x4& operator*=(float n) noexcept { c0 *= n; c1 *= n; c2 *= n; return *this; }
	float3x4& operator/=(float n) noexcept { c0 /= n, c1 /= n; c2 /= n; return *this; }

	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param v target vector to dot by
	 */
	constexpr float4 operator*(float3 v) const noexcept
	{
		return float4(
			c0.x * v.x + c1.x * v.y + c2.x * v.z,
			c0.y * v.x + c1.y * v.y + c2.y * v.z,
			c0.z * v.x + c1.z * v.y + c2.z * v.z,
			c0.w * v.x + c1.w * v.y + c2.w * v.z);
	}

	/**
	 * @brief Returns true if matrices have the same values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator==(const float3x4& m) const noexcept { return memcmp(this, &m, sizeof(float3x4)) == 0; }
	/**
	 * @brief Returns true if matrices have different values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator!=(const float3x4& m) const noexcept { return memcmp(this, &m, sizeof(float3x4)) != 0; }

	static const float3x4 zero, one, minusOne, identity;
};

inline const float3x4 float3x4::identity = float3x4(
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f);
inline const float3x4 float3x4::zero = float3x4(0.0f);
inline const float3x4 float3x4::one = float3x4(1.0f);
inline const float3x4 float3x4::minusOne = float3x4(-1.0f);

/***********************************************************************************************************************
 * @brief Floating point 4x4 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct [[nodiscard]] float4x4
{
	float4 c0; /**< First matrix column. */
	float4 c1; /**< Second matrix column. */
	float4 c2; /**< Third matrix column. */
	float4 c3; /**< Fourth matrix column. */

	/**
	 * @brief Creates a new floating point 4x4 matrix structure.
	 * @param n target value for all columns and rows
	 */
	constexpr explicit float4x4(float n = 0.0f) noexcept : c0(n), c1(n), c2(n), c3(n) { }
	/**
	 * @brief Creates a new floating point 4x4 matrix structure.
	 *
	 * @param[in] c0 first matrix column value
	 * @param[in] c1 second matrix column value
	 * @param[in] c2 third matrix column value
	 * @param[in] c3 fourth matrix column value
	 */
	constexpr float4x4(float4 c0, float4 c1, float4 c2, float4 c3) noexcept : 
		c0(c0), c1(c1), c2(c2), c3(c3) { }
	/**
	 * @brief Creates a new floating point 4x4 matrix structure.
	 * @details See the @ref float4x4.
	 */
	constexpr float4x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2,
		float c0r3, float c1r3, float c2r3, float c3r3) noexcept :
		c0(float4(c0r0, c0r1, c0r2, c0r3)),
		c1(float4(c1r0, c1r1, c1r2, c1r3)),
		c2(float4(c2r0, c2r1, c2r2, c2r3)),
		c3(float4(c3r0, c3r1, c3r2, c3r3)) { }
	/**
	 * @brief Creates a new floating point 4x4 matrix structure.
	 *
	 * @param[in] m4x3 target 4x3 matrix
	 * @param r3 third rows vector
	 */
	constexpr float4x4(const float4x3& m4x3, float4 r3 = float4::zero) noexcept :
		c0(float4(m4x3.c0, r3.x)), c1(float4(m4x3.c1, r3.y)), c2(float4(m4x3.c2, r3.z)), c3(float4(m4x3.c3, r3.w)) { }
	/**
	 * @brief Creates a new floating point 4x4 matrix structure.
	 * 
	 * @param[in] m target 3x3 matrix value
	 * @param c3 third columns SIMD vector
	 * @param r3 third rows SIMD vector
	 */
	constexpr float4x4(const float3x3& m, float4 c3 = float4::zero, float4 r3 = float4::zero) noexcept : 
		c0(float4(m.c0, r3.x)), c1(float4(m.c1, r3.y)), c2(float4(m.c2, r3.z)), c3(c3) { }

	/**
	 * @brief Returns matrix 4x3 part.
	 */
	constexpr explicit operator float4x3() const noexcept
	{
		return float4x3((float3)c0, (float3)c1, (float3)c2, (float3)c3);
	}
	/**
	 * @brief Returns matrix 3x3 part.
	 */
	constexpr explicit operator float3x3() const noexcept { return float3x3((float3)c0, (float3)c1, (float3)c2); }
	/**
	 * @brief Returns matrix 2x2 part.
	 */
	constexpr explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }

	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float4& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((float4*)this)[i];
	}
	/**
	 * @brief Returns matrix column by index.
	 * @param i target column index
	 */
	float4 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float4*)this)[i];
	}

	constexpr float4x4 operator+(float n) const noexcept { return float4x4(c0 + n, c1 + n, c2 + n, c3 + n); }
	constexpr float4x4 operator-(float n) const noexcept { return float4x4(c0 - n, c1 - n, c2 - n, c3 - n); }
	constexpr float4x4 operator*(float n) const noexcept { return float4x4(c0 * n, c1 * n, c2 * n, c3 * n); }
	constexpr float4x4 operator/(float n) const noexcept { return float4x4(c0 / n, c1 / n, c2 / n, c3 / n); }
	float4x4& operator+=(float n) noexcept { c0 += n; c1 += n; c2 += n; c3 += n; return *this; }
	float4x4& operator-=(float n) noexcept { c0 -= n; c1 -= n; c2 -= n; c3 -= n; return *this; }
	float4x4& operator*=(float n) noexcept { c0 *= n; c1 *= n; c2 *= n; c3 *= n; return *this; }
	float4x4& operator/=(float n) noexcept { c0 /= n, c1 /= n; c2 /= n; c3 /= n; return *this; }

	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	constexpr float4x4 operator*(const float4x4& m) const noexcept
	{
		return float4x4(
			c0 * m.c0.x + c1 * m.c0.y + c2 * m.c0.z + c3 * m.c0.w,
			c0 * m.c1.x + c1 * m.c1.y + c2 * m.c1.z + c3 * m.c1.w,
			c0 * m.c2.x + c1 * m.c2.y + c2 * m.c2.z + c3 * m.c2.w,
			c0 * m.c3.x + c1 * m.c3.y + c2 * m.c3.z + c3 * m.c3.w);
	}
	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param v target vector to dot by
	 */
	constexpr float4 operator*(float4 v) const noexcept
	{
		return float4(
			c0.x * v.x + c1.x * v.y + c2.x * v.z + c3.x * v.w,
			c0.y * v.x + c1.y * v.y + c2.y * v.z + c3.y * v.w,
			c0.z * v.x + c1.z * v.y + c2.z * v.z + c3.z * v.w,
			c0.w * v.x + c1.w * v.y + c2.w * v.z + c3.w * v.w);
	}
	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	float4x4& operator*=(const float4x4& m) noexcept { return *this = *this * m; }

	/**
	 * @brief Returns true if matrices have the same values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator==(const float4x4& m) const noexcept { return memcmp(this, &m, sizeof(float4x4)) == 0; }
	/**
	 * @brief Returns true if matrices have different values.
	 * @param[in] m another matrix to compare with
	 */
	bool operator!=(const float4x4& m) const noexcept { return memcmp(this, &m, sizeof(float4x4)) != 0; }

	/**
	 * @brief Model matrix without any transformations.
	 */
	static const float4x4 identity;

	static const float4x4 zero, one, minusOne;
};

inline const float4x4 float4x4::identity = float4x4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);
inline const float4x4 float4x4::zero = float4x4(0.0f);
inline const float4x4 float4x4::one = float4x4(1.0f);
inline const float4x4 float4x4::minusOne = float4x4(-1.0f);

//**********************************************************************************************************************
static constexpr float4x4 operator+(float n, const float4x4& m) noexcept
{
	return float4x4(n + m.c0, n + m.c1, n + m.c2, n + m.c3);
}
static constexpr float4x4 operator-(float n, const float4x4& m) noexcept
{
	return float4x4(n - m.c0, n - m.c1, n - m.c2, n - m.c3);
}
static constexpr float4x4 operator*(float n, const float4x4& m) noexcept
{
	return float4x4(n * m.c0, n * m.c1, n * m.c2, n * m.c3);
}
static constexpr float4x4 operator/(float n, const float4x4& m) noexcept
{
	return float4x4(n / m.c0, n / m.c1, n / m.c2, n / m.c3);
}

static constexpr float4x3 operator+(float n, const float4x3& m) noexcept
{
	return float4x3(n + m.c0, n + m.c1, n + m.c2, n + m.c3);
}
static constexpr float4x3 operator-(float n, const float4x3& m) noexcept
{
	return float4x3(n - m.c0, n - m.c1, n - m.c2, n - m.c3);
}
static constexpr float4x3 operator*(float n, const float4x3& m) noexcept
{
	return float4x3(n * m.c0, n * m.c1, n * m.c2, n * m.c3);
}
static constexpr float4x3 operator/(float n, const float4x3& m) noexcept
{
	return float4x3(n / m.c0, n / m.c1, n / m.c2, n / m.c3);
}

static constexpr float3x3 operator+(float n, const float3x3& m) noexcept { return float3x3(n + m.c0, n + m.c1, n + m.c2); }
static constexpr float3x3 operator-(float n, const float3x3& m) noexcept { return float3x3(n - m.c0, n - m.c1, n - m.c2); }
static constexpr float3x3 operator*(float n, const float3x3& m) noexcept { return float3x3(n * m.c0, n * m.c1, n * m.c2); }
static constexpr float3x3 operator/(float n, const float3x3& m) noexcept { return float3x3(n / m.c0, n / m.c1, n / m.c2); }

static constexpr float2x2 operator+(float n, const float2x2& m) noexcept { return float2x2(n + m.c0, n + m.c1); }
static constexpr float2x2 operator-(float n, const float2x2& m) noexcept { return float2x2(n - m.c0, n - m.c1); }
static constexpr float2x2 operator*(float n, const float2x2& m) noexcept { return float2x2(n * m.c0, n * m.c1); }
static constexpr float2x2 operator/(float n, const float2x2& m) noexcept { return float2x2(n / m.c0, n / m.c1); }

/***********************************************************************************************************************
 * @brief Calculates dot product between vector and matrix.
 * 
 * @param v target vector to dot with
 * @param m target matrix to dot by
 */
static constexpr float2 operator*(float2 v, float2x2 m) noexcept
{
	return float2(
		m.c0.x * v.x + m.c1.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y);
}
/**
 * @brief Calculates dot product between vector and matrix.
 *
 * @param v target vector to dot with
 * @param[in] m target matrix to dot by
 */
static constexpr float3 operator*(float3 v, const float3x3& m) noexcept
{
	return float3(
		m.c0.x * v.x + m.c1.x * v.x + m.c2.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y + m.c2.y * v.y,
		m.c0.z * v.z + m.c1.z * v.z + m.c2.z * v.z);
}
/**
 * @brief Calculates dot product between vector and matrix.
 *
 * @param v target vector to dot with
 * @param[in] m target matrix to dot by
 */
static constexpr float4 operator*(float4 v, const float4x4& m) noexcept
{
	return float4(
		m.c0.x * v.x + m.c1.x * v.x + m.c2.x * v.x + m.c3.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y + m.c2.y * v.y + m.c3.y * v.y,
		m.c0.z * v.z + m.c1.z * v.z + m.c2.z * v.z + m.c3.z * v.z,
		m.c0.w * v.w + m.c1.w * v.w + m.c2.w * v.w + m.c3.w * v.w);
}

/***********************************************************************************************************************
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param m target matrix to transpose
 */
static constexpr float2x2 transpose(float2x2 m) noexcept
{
	return float2x2(
		m.c0.x, m.c0.y,
		m.c1.x, m.c1.y);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param m target matrix to transpose
 */
static constexpr float3x3 transpose(float3x3 m) noexcept
{
	return float3x3(
		m.c0.x, m.c0.y, m.c0.z,
		m.c1.x, m.c1.y, m.c1.z,
		m.c2.x, m.c2.y, m.c2.z);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param[in] m target matrix to transpose
 */
static constexpr float3x4 transpose(float4x3 m) noexcept
{
	return float3x4(
		m.c0.x, m.c0.y, m.c0.z,
		m.c1.x, m.c1.y, m.c1.z,
		m.c2.x, m.c2.y, m.c2.z,
		m.c3.x, m.c3.y, m.c3.z);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param[in] m target matrix to transpose
 */
static constexpr float4x3 transpose(float3x4 m) noexcept
{
	return float4x3(
		m.c0.x, m.c0.y, m.c0.z, m.c0.w,
		m.c1.x, m.c1.y, m.c1.z, m.c1.w,
		m.c2.x, m.c2.y, m.c2.z, m.c2.w);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param[in] m target matrix to transpose
 */
static constexpr float4x4 transpose(float4x4 m) noexcept
{
	return float4x4(
		m.c0.x, m.c0.y, m.c0.z, m.c0.w,
		m.c1.x, m.c1.y, m.c1.z, m.c1.w,
		m.c2.x, m.c2.y, m.c2.z, m.c2.w,
		m.c3.x, m.c3.y, m.c3.z, m.c3.w);
}

/***********************************************************************************************************************
 * @brief Calculates matrix inverse. (Usefull for undoing transformations)
 * @param matrix target matrix to inverse
 */
static constexpr float2x2 inverse(float2x2 m) noexcept
{
	auto oneOverDeterminant = 1.0f / (m.c0.x * m.c1.y - m.c1.x * m.c0.y);
	return float2x2(m.c1.y * oneOverDeterminant, -m.c0.y * oneOverDeterminant,
		-m.c1.x * oneOverDeterminant, m.c0.x * oneOverDeterminant);
}
/**
 * @brief Calculates matrix inverse. (Usefull for undoing transformations)
 * @param matrix target matrix to inverse
 */
static constexpr float3x3 inverse(float3x3 m) noexcept
{
	auto oneOverDeterminant = 1.0f / (
		m.c0.x * (m.c1.y * m.c2.z - m.c2.y * m.c1.z)
		-m.c1.x * (m.c0.y * m.c2.z - m.c2.y * m.c0.z) +
		m.c2.x * (m.c0.y * m.c1.z - m.c1.y * m.c0.z));
	return float3x3(
		(m.c1.y * m.c2.z - m.c2.y * m.c1.z) * oneOverDeterminant,
		-(m.c0.y * m.c2.z - m.c2.y * m.c0.z) * oneOverDeterminant,
		(m.c0.y * m.c2.z - m.c1.y * m.c0.z) * oneOverDeterminant,
		-(m.c1.x * m.c2.z - m.c2.x * m.c1.z) * oneOverDeterminant,
		(m.c0.x * m.c2.z - m.c2.x * m.c0.z) * oneOverDeterminant,
		-(m.c0.x * m.c2.z - m.c1.x * m.c0.z) * oneOverDeterminant,
		(m.c1.x * m.c2.y - m.c2.x * m.c1.y) * oneOverDeterminant,
		-(m.c0.x * m.c2.y - m.c2.x * m.c0.y) * oneOverDeterminant,
		(m.c0.x * m.c2.y - m.c1.x * m.c0.y) * oneOverDeterminant);
}
/**
 * @brief Calculates matrix inverse. (Usefull for undoing transformations)
 * @param[in] m target matrix to inverse
 */
static float4x4 inverse(float4x4 m) noexcept
{
	auto c00 = m.c2.z * m.c3.w - m.c3.z * m.c2.w;
	auto c02 = m.c1.z * m.c3.w - m.c3.z * m.c1.w;
	auto c03 = m.c1.z * m.c2.w - m.c2.z * m.c1.w;
	auto c04 = m.c2.y * m.c3.w - m.c3.y * m.c2.w;
	auto c06 = m.c1.y * m.c3.w - m.c3.y * m.c1.w;
	auto c07 = m.c1.y * m.c2.w - m.c2.y * m.c1.w;
	auto c08 = m.c2.y * m.c3.z - m.c3.y * m.c2.z;
	auto c10 = m.c1.y * m.c3.z - m.c3.y * m.c1.z;
	auto c11 = m.c1.y * m.c2.z - m.c2.y * m.c1.z;
	auto c12 = m.c2.x * m.c3.w - m.c3.x * m.c2.w;
	auto c14 = m.c1.x * m.c3.w - m.c3.x * m.c1.w;
	auto c15 = m.c1.x * m.c2.w - m.c2.x * m.c1.w;
	auto c16 = m.c2.x * m.c3.z - m.c3.x * m.c2.z;
	auto c18 = m.c1.x * m.c3.z - m.c3.x * m.c1.z;
	auto c19 = m.c1.x * m.c2.z - m.c2.x * m.c1.z;
	auto c20 = m.c2.x * m.c3.y - m.c3.x * m.c2.y;
	auto c22 = m.c1.x * m.c3.y - m.c3.x * m.c1.y;
	auto c23 = m.c1.x * m.c2.y - m.c2.x * m.c1.y;

	float4 f0(c00, c00, c02, c03);
	float4 f1(c04, c04, c06, c07);
	float4 f2(c08, c08, c10, c11);
	float4 f3(c12, c12, c14, c15);
	float4 f4(c16, c16, c18, c19);
	float4 f5(c20, c20, c22, c23);

	float4 v0(m.c1.x, m.c0.x, m.c0.x, m.c0.x);
	float4 v1(m.c1.y, m.c0.y, m.c0.y, m.c0.y);
	float4 v2(m.c1.z, m.c0.z, m.c0.z, m.c0.z);
	float4 v3(m.c1.w, m.c0.w, m.c0.w, m.c0.w);

	float4 i0(v1 * f0 - v2 * f1 + v3 * f2);
	float4 i1(v0 * f0 - v2 * f3 + v3 * f4);
	float4 i2(v0 * f1 - v1 * f3 + v3 * f5);
	float4 i3(v0 * f2 - v1 * f4 + v2 * f5);

	float4 sA( 1.0f, -1.0f,  1.0f, -1.0f);
	float4 sB(-1.0f,  1.0f, -1.0f,  1.0f);
	float4x4 i(i0 * sA, i1 * sB, i2 * sA, i3 * sB);
	float4 r0(i.c0.x, i.c1.x, i.c2.x, i.c3.x);
	float4 d0(m.c0 * r0);
	auto d1 = (d0.x + d0.y) + (d0.z + d0.w);
	return i * (1.0f / d1);
}

} // namespace math