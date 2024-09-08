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
 * @brief Common matrix transformation functions.
 * 
 * @details
 * Matrix is a mathematical structure used to represent transformations such as translation, rotation, scaling, and 
 * shearing. These matrices are often 4x4 matrices in 3D graphics, allowing for efficient manipulation of objects in 
 * 3D space using homogeneous coordinates. Matrices enable combining multiple transformations into a single operation 
 * and are essential in rendering pipelines, skeletal animation or camera movements.
 * 
 * Coordinate system: X-right, Y-up, Z-forward (Left handed)
 * Matrices order: Column-major. (OpenGL, Vulkan like)
 * floatNxM - N columns and M rows
 * 
 * Projection matrices are fixed for the Vulkan NDC space.
 * http://matthewwellings.com/blog/the-new-vulkan-coordinate-system/
 * 
 * Based on this project: https://github.com/g-truc/glm
 */

#pragma once
#include "math/quaternion.hpp"

namespace math
{

/**
 * @brief Floating-point 2x2 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct float2x2
{
	float2 c0; /**< First matrix column. */
	float2 c1; /**< Second matrix column. */

	/**
	 * @brief Creates a new floating-point 2x2 matrix structure.
	 * @param v target value for all columns and rows
	 */
	explicit float2x2(float v = 0.0f) noexcept { this->c0 = v; this->c1 = v; }
	/**
	 * @brief Creates a new floating-point 2x2 matrix structure.
	 * 
	 * @param c0 first matrix column value
	 * @param c1 second matrix column value
	 */
	float2x2(float2 c0, float2 c1) noexcept { this->c0 = c0; this->c1 = c1; }
	/**
	 * @brief Creates a new floating-point 2x2 matrix structure.
	 * @details See the @ref float2x2.
	 */
	float2x2(
		float c0r0, float c1r0, 
		float c0r1, float c1r1) noexcept
	{
		this->c0 = float2(c0r0, c0r1);
		this->c1 = float2(c1r0, c1r1);
	}
	
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

	/**
	 * @brief Multiplies all matrix columns by specified value.
	 * @param v target multiplier value
	 */
	float2x2 operator*(float v) const noexcept { return float2x2(c0 * v, c1 * v); }

	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	float2x2 operator*(const float2x2& m) const noexcept
	{
		return float2x2(
			c0 * m.c0.x + c1 * m.c0.y,
			c0 * m.c1.x + c1 * m.c1.y);
	}
	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param v target vector to dot by
	 */
	float2 operator*(float2 v) const noexcept
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

/***********************************************************************************************************************
 * @brief Floating-point 3x3 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct float3x3
{
	float3 c0; /**< First matrix column. */
	float3 c1; /**< Second matrix column. */
	float3 c2; /**< Third matrix column. */

	/**
	 * @brief Creates a new floating-point 3x3 matrix structure.
	 * @param v target value for all columns and rows
	 */
	explicit float3x3(float v = 0.0f) noexcept { this->c0 = v; this->c1 = v; this->c2 = v; }
	/**
	 * @brief Creates a new floating-point 3x3 matrix structure.
	 *
	 * @param[in] c0 first matrix column value
	 * @param[in] c1 second matrix column value
	 * @param[in] c2 third matrix column value
	 */
	float3x3(const float3& c0, const float3& c1, const float3& c2) noexcept
	{
		this->c0 = c0; this->c1 = c1; this->c2 = c2;
	}
	/**
	 * @brief Creates a new floating-point 3x3 matrix structure.
	 * @details See the @ref float3x3.
	 */
	float3x3(
		float c0r0, float c1r0, float c2r0,
		float c0r1, float c1r1, float c2r1,
		float c0r2, float c1r2, float c2r2) noexcept
	{
		this->c0 = float3(c0r0, c0r1, c0r2);
		this->c1 = float3(c1r0, c1r1, c1r2);
		this->c2 = float3(c2r0, c2r1, c2r2);
	}

	/**
	 * @brief Returns matrix 2x2 part.
	 */
	explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }
	
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
	const float3& operator[](psize i) const noexcept
	{
		assert(i <= 2);
		return ((float3*)this)[i];
	}

	/**
	 * @brief Multiplies all matrix columns by specified value.
	 * @param v target multiplier value
	 */
	float3x3 operator*(float v) const noexcept { return float3x3(c0 * v, c1 * v, c2 * v); }

	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	float3x3 operator*(const float3x3& m) const noexcept
	{
		return float3x3(
			c0 * m.c0.x + c1 * m.c0.y + c2 * m.c0.z,
			c0 * m.c1.x + c1 * m.c1.y + c2 * m.c1.z,
			c0 * m.c2.x + c1 * m.c2.y + c2 * m.c2.z);
	}
	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param[in] v target vector to dot by
	 */
	float3 operator*(const float3& v) const noexcept
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

/***********************************************************************************************************************
 * @brief Floating-point 4x4 matrix structure.
 * @details Commonly used for basic transformations: translation, scale, rotation, etc.
 */
struct float4x4
{
	float4 c0; /**< First matrix column. */
	float4 c1; /**< Second matrix column. */
	float4 c2; /**< Third matrix column. */
	float4 c3; /**< Fourth matrix column. */

	/**
	 * @brief Creates a new floating-point 4x4 matrix structure.
	 * @param v target value for all columns and rows
	 */
	explicit float4x4(float v = 0.0f) noexcept { this->c0 = v; this->c1 = v; this->c2 = v; this->c3 = v; }
	/**
	 * @brief Creates a new floating-point 4x4 matrix structure.
	 *
	 * @param[in] c0 first matrix column value
	 * @param[in] c1 second matrix column value
	 * @param[in] c2 third matrix column value
	 */
	float4x4(const float4& c0, const float4& c1, const float4& c2, const float4& c3) noexcept
	{
		this->c0 = c0; this->c1 = c1; this->c2 = c2; this->c3 = c3;
	}
	/**
	 * @brief Creates a new floating-point 4x4 matrix structure.
	 * @details See the @ref float4x4.
	 */
	float4x4(
		float c0r0, float c1r0, float c2r0, float c3r0,
		float c0r1, float c1r1, float c2r1, float c3r1,
		float c0r2, float c1r2, float c2r2, float c3r2,
		float c0r3, float c1r3, float c2r3, float c3r3) noexcept
	{
		this->c0 = float4(c0r0, c0r1, c0r2, c0r3);
		this->c1 = float4(c1r0, c1r1, c1r2, c1r3);
		this->c2 = float4(c2r0, c2r1, c2r2, c2r3);
		this->c3 = float4(c3r0, c3r1, c3r2, c3r3);
	}

	/**
	 * @brief Returns matrix 3x3 part.
	 */
	explicit operator float3x3() const noexcept { return float3x3((float3)c0, (float3)c1, (float3)c2); }
	/**
	 * @brief Returns matrix 2x2 part.
	 */
	explicit operator float2x2() const noexcept { return float2x2((float2)c0, (float2)c1); }

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
	const float4& operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((float4*)this)[i];
	}

	/**
	 * @brief Multiplies all matrix columns by specified value.
	 * @param v target multiplier value
	 */
	float4x4 operator*(float v) const noexcept { return float4x4(c0 * v, c1 * v, c2 * v, c3 * v); }

	/**
	 * @brief Calculates dot product between two matrices.
	 * @param[in] m target matrix to dot by
	 */
	float4x4 operator*(const float4x4& m) const noexcept
	{
		return float4x4(
			c0 * m.c0.x + c1 * m.c0.y + c2 * m.c0.z + c3 * m.c0.w,
			c0 * m.c1.x + c1 * m.c1.y + c2 * m.c1.z + c3 * m.c1.w,
			c0 * m.c2.x + c1 * m.c2.y + c2 * m.c2.z + c3 * m.c2.w,
			c0 * m.c3.x + c1 * m.c3.y + c2 * m.c3.z + c3 * m.c3.w);
	}
	/**
	 * @brief Calculates dot product between matrix and vector.
	 * @param[in] v target vector to dot by
	 */
	float4 operator*(const float4& v) const noexcept
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

	static const float4x4 zero, one, minusOne
};

/***********************************************************************************************************************
 * @brief Calculates dot product between vector and matrix.
 * 
 * @param[in] v target vector to dot with
 * @param[in] m target matrix to dot by
 */
static float2 operator*(float2 v, const float2x2& m) noexcept
{
	return float2(
		m.c0.x * v.x + m.c1.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param[in] m target matrix to transpose
 */
static float2x2 transpose(const float2x2& m) noexcept
{
	return float2x2(
		m.c0.x, m.c0.y,
		m.c1.x, m.c1.y);
}
/**
 * @brief Calculates matrix inverse. (Usefull for undoing transformations)
 * @param[in] m target matrix to inverse
 */
static float2x2 inverse(const float2x2& matrix) noexcept
{
	auto m = matrix;
	auto oneOverDeterminant = 1.0f / (m.c0.x * m.c1.y - m.c1.x * m.c0.y);
	return float2x2(m.c1.y * oneOverDeterminant, -m.c0.y * oneOverDeterminant,
		-m.c1.x * oneOverDeterminant, m.c0.x * oneOverDeterminant);
}

/**
 * @brief Calculates dot product between vector and matrix.
 *
 * @param[in] v target vector to dot with
 * @param[in] m target matrix to dot by
 */
static float3 operator*(const float3& v, const float3x3& m) noexcept
{
	return float3(
		m.c0.x * v.x + m.c1.x * v.x + m.c2.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y + m.c2.y * v.y,
		m.c0.z * v.z + m.c1.z * v.z + m.c2.z * v.z);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param[in] m target matrix to transpose
 */
static float3x3 transpose(const float3x3& m) noexcept
{
	return float3x3(
		m.c0.x, m.c0.y, m.c0.z,
		m.c1.x, m.c1.y, m.c1.z,
		m.c2.x, m.c2.y, m.c2.z);
}
/**
 * @brief Calculates matrix inverse. (Usefull for undoing transformations)
 * @param[in] m target matrix to inverse
 */
static float3x3 inverse(const float3x3& matrix) noexcept
{
	auto m = matrix;
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

/***********************************************************************************************************************
 * @brief Calculates dot product between vector and matrix.
 *
 * @param[in] v target vector to dot with
 * @param[in] m target matrix to dot by
 */
static float4 operator*(const float4& v, const float4x4& m) noexcept
{
	return float4(
		m.c0.x * v.x + m.c1.x * v.x + m.c2.x * v.x + m.c3.x * v.x,
		m.c0.y * v.y + m.c1.y * v.y + m.c2.y * v.y + m.c3.y * v.y,
		m.c0.z * v.z + m.c1.z * v.z + m.c2.z * v.z + m.c3.z * v.z,
		m.c0.w * v.w + m.c1.w * v.w + m.c2.w * v.w + m.c3.w * v.w);
}
/**
 * @brief Flips matrix over its diagonal, swapping rows and columns.
 * @param[in] m target matrix to transpose
 */
static float4x4 transpose(const float4x4& m) noexcept
{
	return float4x4(
		m.c0.x, m.c0.y, m.c0.z, m.c0.w,
		m.c1.x, m.c1.y, m.c1.z, m.c1.w,
		m.c2.x, m.c2.y, m.c2.z, m.c2.w,
		m.c3.x, m.c3.y, m.c3.z, m.c3.w);
}
/**
 * @brief Calculates matrix inverse. (Usefull for undoing transformations)
 * @param[in] m target matrix to inverse
 */
static float4x4 inverse(const float4x4& matrix) noexcept
{
	auto m = matrix;
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

/***********************************************************************************************************************
 * @brief Applies translation transformation to an object in 3D space.
 * 
 * @param[in] m target model matrix to translate
 * @param[in] t target object translation
 */
static float4x4 translate(const float4x4& m, const float3& t) noexcept
{
	return float4x4(m.c0, m.c1, m.c2, m.c0 * t.x + m.c1 * t.y + m.c2 * t.z + m.c3);
}
/**
 * @brief Creates a new matrix with a specified object position in 3D space.
 * @param[in] t target object translation
 */
static float4x4 translate(const float3& t) noexcept
{
	return float4x4(
		1.0f, 0.0f, 0.0f, t.x,
		0.0f, 1.0f, 0.0f, t.y,
		0.0f, 0.0f, 1.0f, t.z,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Returns total matrix translation transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float3 getTranslation(const float4x4& m) noexcept
{
	return float3(m.c3.x, m.c3.y, m.c3.z);
}
/**
 * @brief Sets total matrix translation transformation of an object in 3D space.
 * 
 * @param[out] m target model matrix to set
 * @param[in] t target object position
 */
static void setTranslation(float4x4& m, const float3& t) noexcept
{
	m.c3.x = t.x; m.c3.y = t.y; m.c3.z = t.z;
}

/***********************************************************************************************************************
 * @brief Applies scale transformation to an object in 3D space.
 *
 * @param[in] m target model matrix to scale
 * @param[in] s target object scale
 */
static float4x4 scale(const float4x4& m, const float3& s) noexcept
{
	return float4x4(m.c0 * s.x, m.c1 * s.y, m.c2 * s.z, m.c3);
}
/**
 * @brief Creates a new matrix with a specified object scale in 3D space.
 * @param[in] s target object scale
 */
static float4x4 scale(const float3& s) noexcept
{
	return float4x4(
		s.x, 0.0f, 0.0f, 0.0f,
		0.0f, s.y, 0.0f, 0.0f,
		0.0f, 0.0f, s.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Extracts total matrix scale transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float3 extractScale(const float4x4& m) noexcept
{
	return float3(length((float3)m.c0), length((float3)m.c1), length((float3)m.c2));
}
/**
 * @brief Extracts total matrix 2D scale transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float2 extractScale2(const float4x4& m) noexcept
{
	return float2(length((float3)m.c0), length((float3)m.c1));
}

/***********************************************************************************************************************
 * @brief Creates a new matrix with a specified object rotation in 3D space.
 * @param[in] q target object rotation
 */
static float4x4 rotate(const quat& q) noexcept
{
	auto xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
	auto xz = q.x * q.z, xy = q.x * q.y, yz = q.y * q.z;
	auto wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
	return float4x4(
		1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
		2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f,
		2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates a new rotation matrix from look vectors in 3D space.
 *
 * @param[in] lookFrom viewer position in 3D space
 * @param[in] lookTo object position in 3D space
 * @param[in] up space up direction vector
 */
static float4x4 rotate(const float3& lookFrom, const float3& lookTo, const float3& up = float3::top) noexcept
{
	auto f = normalize(lookTo - lookFrom);
	auto s = normalize(cross(up, f));
	auto u = cross(f, s);
	return float4x4(
		s.x, s.y, s.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		f.x, f.y, f.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates a new matrix from direction vector in 3D space.
 *
 * @param[in] front view direction vector in 3D space
 * @param[in] up space up direction vector
 */
static float4x4 rotate(const float3& front, const float3& up = float3::top) noexcept
{
	auto f = front;
	auto s = normalize(cross(up, f));
	auto u = cross(f, s);
	return float4x4(
		s.x, s.y, s.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		f.x, f.y, f.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Extracts total matrix rotation transformation of an object in 3D space.
 * @param[in] m target model matrix to extract from
 */
static float4x4 extractRotation(const float4x4& m) noexcept
{
	auto invScale = 1.0f / extractScale(m);
	auto c0 = (float3)m.c0 * invScale.x;
	auto c1 = (float3)m.c1 * invScale.y;
	auto c2 = (float3)m.c2 * invScale.z;
	return float4x4(float4(c0, 0.0f), float4(c1, 0.0f), float4(c2, 0.0f), float4(0.0f, 0.0f, 0.0f, 1.0f));
}

/**
 * @brief Extracts total matrix rotation quaternion of an object in 3D space.
 * @param[in] m target rotation matrix to extract from
 */
static quat extractQuat(const float3x3& m) noexcept;
/**
 * @brief Extracts total matrix rotation quaternion of an object in 3D space.
 * @param[in] m target rotation matrix to extract from
 */
static quat extractQuat(const float4x4& m) noexcept
{
	return extractQuat((float3x3)m);
}

/***********************************************************************************************************************
 * @brief Calculates object model matrix from it position, rotation and scale.
 *
 * @param[in] position object position in 3D space
 * @param[in] rotation object rotation in 3D space
 * @param[in] scale object scale in 3D space
 */
static float4x4 calcModel(const float3& position = float3(0.0f),
	const quat& rotation = quat::identity, const float3& scale = float3(1.0f)) noexcept
{
	return translate(position) * rotate(normalize(rotation)) * math::scale(scale);
}
/**
 * @brief Extracts total matrix position, rotation and scale of an object in 3D space. (Decompose)
 *
 * @param[in] m target model matrix to extract from
 * @param[out] position object position in 3D space
 * @param[out] scale object scale in 3D space
 * @param[out] rotation object rotation in 3D space
 */
static void extractTransform(const float4x4& m, float3& position, float3& scale, quat& rotation) noexcept
{
	position = getTranslation(m);
	scale = extractScale(m);
	rotation = extractQuat(extractRotation(m));
}

/***********************************************************************************************************************
 * @brief Calculates infinite reversed Z perspective projection matrix.
 *
 * @param fieldOfView camera field of view in radians
 * @param aspectRatio camera aspect ratio (ex. width / height)
 * @param nearPlane distance to the camera near plane
 */
static float4x4 calcPerspProjInfRevZ(float fieldOfView, float aspectRatio, float nearPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);
	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, nearPlane,
		0.0f, 0.0f, 1.0f, 0.0f);
}
/**
 * @brief Calculates reversed Z perspective projection matrix.
 *
 * @param fieldOfView camera field of view in radians
 * @param aspectRatio camera aspect ratio (ex. width / height)
 * @param nearPlane distance to the camera near plane
 * @param farPlane distance to the camera far plane
 */
static float4x4 calcPerspProjRevZ(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);
	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, nearPlane / (nearPlane - farPlane),
		-(nearPlane * farPlane) / (nearPlane - farPlane),
		0.0f, 0.0f, 1.0f, 0.0f);
}
/**
 * @brief Calculates perspective projection matrix.
 *
 * @param fieldOfView camera field of view in radians
 * @param aspectRatio camera aspect ratio (ex. width / height)
 * @param nearPlane distance to the camera near plane
 * @param farPlane distance to the camera far plane
 */
static float4x4 calcPerspProj(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) noexcept
{
	float tanHalfFov = std::tan(fieldOfView * 0.5f);
	return float4x4(
		1.0f / (aspectRatio * tanHalfFov), 0.0f, 0.0f, 0.0f,
		0.0f, -1.0f / tanHalfFov, 0.0f, 0.0f,
		0.0f, 0.0f, farPlane / (farPlane - nearPlane),
		-(farPlane * nearPlane) / (farPlane - nearPlane),
		0.0f, 0.0f, 1.0f, 0.0f);
}

/***********************************************************************************************************************
 * @brief Calculates reversed Z orthographic projection matrix.
 *
 * @param width camera width (ex. from -1.0 to 1.0)
 * @param height camera heght (ex. from -1.0 to 1.0)
 * @param depth camera depth (ex. from 0.0 to 1.0)
 */
static float4x4 calcOrthoProjRevZ(float2 width, float2 height, float2 depth) noexcept
{
	return float4x4(
		2.0f / (width.y - width.x), 0.0f, 0.0f, -(width.y + width.x) / (width.y - width.x),
		0.0f, -2.0f / (height.y - height.x), 0.0f, (height.y + height.x) / (height.y - height.x),
		0.0f, 0.0f, 1.0f / (depth.x - depth.y), -depth.y / (depth.x - depth.y),
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates orthographic projection matrix.
 *
 * @param width camera width (ex. from -1.0 to 1.0)
 * @param height camera heght (ex. from -1.0 to 1.0)
 * @param depth camera depth (ex. from 0.0 to 1.0)
 */
static float4x4 calcOrthoProj(float2 width, float2 height, float2 depth) noexcept
{
	return float4x4(
		2.0f / (width.y - width.x), 0.0f, 0.0f, -(width.y + width.x) / (width.y - width.x),
		0.0f, -2.0f / (height.y - height.x), 0.0f, (height.y + height.x) / (height.y - height.x),
		0.0f, 0.0f, 1.0f / (depth.y - depth.x), -depth.x / (depth.y - depth.x),
		0.0f, 0.0f, 0.0f, 1.0f);
}

/***********************************************************************************************************************
 * @brief Calculates a new model matrix from look vectors in 3D space.
 *
 * @param[in] from viewer position in 3D space
 * @param[in] to object position in 3D space
 * @param[in] up space up direction vector
 */
static float4x4 lookAt(const float3& from, const float3& to, const float3& up = float3::top) noexcept
{
	auto f = normalize(to - from);
	auto s = normalize(cross(up, f));
	auto u = cross(f, s);
	return float4x4(
		s.x, s.y, s.z, -dot(s, from),
		u.x, u.y, u.z, -dot(u, from),
		f.x, f.y, f.z, -dot(f, from),
		0.0f, 0.0f, 0.0f, 1.0f);
}
/**
 * @brief Calculates a new quaternion from direction vector in 3D space.
 *
 * @param[in] direction viewer direction in 3D space
 * @param[in] up space up direction vector
 */
static quat lookAtQuat(const float3& direction, const float3& up = float3::top) noexcept
{
	auto right = cross(up, direction);
	auto c0 = right * (1.0f / std::sqrt(std::max(0.00001f, dot(right, right))));
	auto c1 = cross(right, c0);
	auto m = float3x3(c0, c1, direction);
	return extractQuat(m);
}

} // namespace math