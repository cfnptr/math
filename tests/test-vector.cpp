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

#include "math/vector.hpp"
#include <stdexcept>
#include <iostream>

using namespace math;

static void cmp(f32x4 a, float4 b, float tolerance = 1.0e-9f)
{
	for (int i = 0; i < 4; i++)
	{
		if (isnan(a[i]))
			a[i] = 0.0f;
		if (isnan(b[i]))
			b[i] = 0.0f;
	}

	auto difference = distanceSq((float4)a, b);
	if (difference > tolerance)
		throw runtime_error("Float4 vectors test failed.");
}
static void cmp(f32x4 a, float3 b, float tolerance = 1.0e-9f)
{
	for (int i = 0; i < 3; i++)
	{
		if (isnan(a[i]))
			a[i] = 0.0f;
		if (isnan(b[i]))
			b[i] = 0.0f;
	}

	auto difference = distanceSq((float3)a, b);
	if (difference > tolerance)
		throw runtime_error("Float3 vectors test failed.");
}
static void cmp(i32x4 a, int4 b)
{
	if ((int4)a != b)
		throw runtime_error("Int4 vectors test failed.");
}
static void cmp(u32x4 a, uint4 b)
{
	if ((uint4)a != b)
		throw runtime_error("Uint4 vectors test failed.");
}
static void cmp(float a, float b, float tolerance = 1.0e-9f)
{
	auto difference = (a - b) * (a - b);
	if (difference > tolerance)
		throw runtime_error("Float test failed.");
}
static void cmp(uint32 a, uint32 b)
{
	if (a != b)
		throw runtime_error("Uint test failed.");
}
static void cmp(bool a, bool b)
{
	if (a != b)
		throw runtime_error("Bool test failed.");
}

static void testFloatVectors()
{
	const auto vecLeft = float4(0.0f, 2.3f, 4.56f, 78.9f), vecRight = float4(1.0f, -23.0f, 4.56f, -0.0789);
	const auto simdLeft = f32x4(vecLeft), simdRight = f32x4(vecRight);
	cmp(simdLeft, vecLeft);
	cmp(simdRight, vecRight);
	cmp(simdLeft + simdRight, vecLeft + vecRight);
	cmp(simdLeft - simdRight, vecLeft - vecRight);
	cmp(simdLeft * simdRight, vecLeft * vecRight);
	cmp(simdLeft / simdRight, vecLeft / vecRight);
	cmp(-simdLeft, -vecLeft);
	cmp(-simdRight, -vecRight);
	cmp(simdLeft == simdLeft, true);
	cmp(simdRight == simdRight, true);
	cmp(simdLeft != simdRight, true);
	cmp(simdRight == simdLeft, false);
	cmp(simdLeft < simdRight, vecLeft < vecRight);
	cmp(simdLeft > simdRight, vecLeft > vecRight);
	cmp(simdLeft <= simdRight, vecLeft <= vecRight);
	cmp(simdLeft >= simdRight, vecLeft >= vecRight);
	cmp(equal(simdLeft, simdLeft), equal(vecLeft, vecLeft));
	cmp(equal(simdRight, simdRight), equal(vecRight, vecRight));
	cmp(equal(simdLeft, simdRight), equal(vecLeft, vecRight));
	cmp(notEqual(simdLeft, simdLeft), notEqual(vecLeft, vecLeft));
	cmp(notEqual(simdRight, simdRight), notEqual(vecRight, vecRight));
	cmp(notEqual(simdLeft, simdRight), notEqual(vecLeft, vecRight));
	cmp(select(u32x4(1, 0, 0, 1), simdLeft, simdRight), select(uint4(1, 0, 0, 1), vecLeft, vecRight));
	cmp(select(u32x4(0, 1, 0, 1), simdRight, simdLeft), select(uint4(0, 1, 0, 1), vecRight, vecLeft));
	cmp(min(simdLeft, simdRight), min(vecLeft, vecRight));
	cmp(max(simdLeft, simdRight), max(vecLeft, vecRight));
	cmp(min3(simdLeft), min(vecLeft.x, vecLeft.y, vecLeft.z));
	cmp(min3(simdRight), min(vecRight.x, vecRight.y, vecRight.z));
	cmp(max3(simdLeft), max(vecLeft.x, vecLeft.y, vecLeft.z));
	cmp(max3(simdRight), max(vecRight.x, vecRight.y, vecRight.z));
	cmp(fma(simdLeft, simdRight, simdRight), fma(vecLeft, vecRight, vecRight));
	cmp(abs(simdLeft), abs(vecLeft));
	cmp(abs(simdRight), abs(vecRight));
	cmp(sqrt(simdLeft), sqrt(vecLeft));
	cmp(sqrt(simdRight), sqrt(vecRight));
	cmp(sign(simdLeft), sign(vecLeft));
	cmp(sign(simdRight), sign(vecRight));
	cmp(signBits(simdLeft), signBits(vecLeft));
	cmp(signBits(simdRight), signBits(vecRight));
	cmp(round(simdLeft), round(vecLeft));
	cmp(round(simdRight), round(vecRight));
	cmp(floor(simdLeft), floor(vecLeft));
	cmp(floor(simdRight), floor(vecRight));
	cmp(ceil(simdLeft), ceil(vecLeft));
	cmp(ceil(simdRight), ceil(vecRight));
	cmp(trunc(simdLeft), trunc(vecLeft));
	cmp(trunc(simdRight), trunc(vecRight));
	cmp(dotV4(simdLeft, simdRight), float4(dot(vecLeft, vecRight)));
	cmp(dot4(simdLeft, simdRight), dot(vecLeft, vecRight));
	cmp(dotV3(simdLeft, simdRight), float4(dot((float3)vecLeft, (float3)vecRight)));
	cmp(dot3(simdLeft, simdRight), dot((float3)vecLeft, (float3)vecRight));
	cmp(cross3(simdLeft, simdRight), cross((float3)vecLeft, (float3)vecRight));
	cmp(length4(simdLeft), length(vecLeft));
	cmp(length4(simdRight), length(vecRight));
	cmp(length3(simdLeft), length((float3)vecLeft));
	cmp(length3(simdRight), length((float3)vecRight));
	cmp(normalize4(simdLeft), normalize(vecLeft));
	cmp(normalize4(simdRight), normalize(vecRight));
	cmp(normalize3(simdLeft), normalize((float3)vecLeft));
	cmp(normalize3(simdRight), normalize((float3)vecRight));
	cmp(isNormalized4(normalize4(simdLeft)), true);
	cmp(isNormalized3(normalize3(simdRight)), true);
	cmp(isNormalized(normalize(vecLeft)), true);
	cmp(isNormalized(normalize((float3)vecRight)), true);
	cmp(log(simdLeft), log(vecLeft));
	cmp(log(simdRight), log(vecRight));
	cmp(exp(simdLeft), exp(vecLeft));
	cmp(exp(simdRight), exp(vecRight));
	{
		const auto vecPow = float4(2.0f, 1.0f, 0.5f, 0.0f);
		const auto simdPow = f32x4(vecPow);
		cmp(mod(simdLeft, simdPow), mod(vecLeft, vecPow));
		cmp(mod(simdRight, simdPow), mod(vecRight, vecPow));
		cmp(pow(simdLeft, simdPow), pow(vecLeft, vecPow));
		cmp(pow(simdRight, simdPow), pow(vecRight, vecPow));
		cmp(fastPow(simdLeft, simdPow), pow(vecLeft, vecPow), 1.0e-6f);
		cmp(fastPow(simdRight, simdPow), pow(vecRight, vecPow), 1.0e-6f);
	}
	{
		f32x4 simdSin, simdCos;
		sinCos(simdLeft, simdSin, simdCos);
		cmp(simdSin, sin(vecLeft));
		cmp(simdCos, cos(vecLeft));
		sinCos(simdRight, simdSin, simdCos);
		cmp(simdSin, sin(vecRight));
		cmp(simdCos, cos(vecRight));
	}
	cmp((f32x4)(f16x4)simdLeft, vecLeft, 1.0e-3f);
	cmp((f32x4)(f16x4)simdRight, vecRight, 1.0e-3f);
}
static void testIntVectors()
{
	auto vecLeft = int4(0, 23, 4, 56789), vecRight = int4(1, -123, 4, -56789);
	auto simdLeft = i32x4(vecLeft), simdRight = i32x4(vecRight);
	cmp(simdLeft, vecLeft);
	cmp(simdRight, vecRight);
	cmp(simdLeft + simdRight, vecLeft + vecRight);
	cmp(simdLeft - simdRight, vecLeft - vecRight);
	cmp(simdLeft * simdRight, vecLeft * vecRight);
	cmp(simdLeft / simdRight, vecLeft / vecRight);
	cmp(simdLeft % simdRight, vecLeft % vecRight);
	cmp(simdLeft & simdRight, vecLeft & vecRight);
	cmp(simdLeft | simdRight, vecLeft | vecRight);
	cmp(simdLeft ^ simdRight, vecLeft ^ vecRight);
	cmp(simdRight >> i32x4(1, 0, 4, 8), vecRight >> int4(1, 0, 4, 8));
	cmp(simdRight << i32x4(1, 0, 4, 8), vecRight << int4(1, 0, 4, 8));
	cmp(simdLeft >> 4, vecLeft >> 4);
	cmp(simdLeft << 4, vecLeft << 4);
	cmp(-simdLeft, -vecLeft);
	cmp(-simdRight, -vecRight);
	cmp(!simdLeft, !vecLeft);
	cmp(!simdRight, !vecRight);
	cmp(~simdLeft, ~vecLeft);
	cmp(~simdRight, ~vecRight);
	cmp(simdLeft == simdLeft, true);
	cmp(simdRight == simdRight, true);
	cmp(simdLeft != simdRight, true);
	cmp(simdRight == simdLeft, false);
	cmp(simdLeft < simdRight, vecLeft < vecRight);
	cmp(simdLeft > simdRight, vecLeft > vecRight);
	cmp(simdLeft <= simdRight, vecLeft <= vecRight);
	cmp(simdLeft >= simdRight, vecLeft >= vecRight);
	cmp(equal(simdLeft, simdLeft), equal(vecLeft, vecLeft));
	cmp(equal(simdRight, simdRight), equal(vecRight, vecRight));
	cmp(equal(simdLeft, simdRight), equal(vecLeft, vecRight));
	cmp(notEqual(simdLeft, simdLeft), notEqual(vecLeft, vecLeft));
	cmp(notEqual(simdRight, simdRight), notEqual(vecRight, vecRight));
	cmp(notEqual(simdLeft, simdRight), notEqual(vecLeft, vecRight));
	cmp(select(u32x4(1, 0, 0, 1), simdLeft, simdRight), select(uint4(1, 0, 0, 1), vecLeft, vecRight));
	cmp(select(u32x4(0, 1, 0, 1), simdRight, simdLeft), select(uint4(0, 1, 0, 1), vecRight, vecLeft));
	cmp(min(simdLeft, simdRight), min(vecLeft, vecRight));
	cmp(max(simdLeft, simdRight), max(vecLeft, vecRight));
}
static void testUintVectors()
{
	auto vecLeft = uint4(0, 1, 23, 456789), vecRight = uint4(123, 4, 5, 6789);
	auto simdLeft = u32x4(vecLeft), simdRight = u32x4(vecRight);
	cmp(simdLeft, vecLeft);
	cmp(simdRight, vecRight);
	cmp(simdLeft + simdRight, vecLeft + vecRight);
	cmp(simdLeft - simdRight, vecLeft - vecRight);
	cmp(simdLeft * simdRight, vecLeft * vecRight);
	cmp(simdLeft / simdRight, vecLeft / vecRight);
	cmp(simdLeft % simdRight, vecLeft % vecRight);
	cmp(simdLeft & simdRight, vecLeft & vecRight);
	cmp(simdLeft | simdRight, vecLeft | vecRight);
	cmp(simdLeft ^ simdRight, vecLeft ^ vecRight);
	cmp(simdLeft >> u32x4(1, 0, 4, 8), vecLeft >> uint4(1, 0, 4, 8));
	cmp(simdLeft << u32x4(1, 0, 4, 8), vecLeft << uint4(1, 0, 4, 8));
	cmp(simdLeft >> 4, vecLeft >> 4);
	cmp(simdLeft << 4, vecLeft << 4);
	cmp(!simdLeft, !vecLeft);
	cmp(!simdRight, !vecRight);
	cmp(~simdLeft, ~vecLeft);
	cmp(~simdRight, ~vecRight);
	cmp(simdLeft == simdLeft, true);
	cmp(simdRight == simdRight, true);
	cmp(simdLeft != simdRight, true);
	cmp(simdRight == simdLeft, false);
	cmp(simdLeft < simdRight, vecLeft < vecRight);
	cmp(simdLeft > simdRight, vecLeft > vecRight);
	cmp(simdLeft <= simdRight, vecLeft <= vecRight);
	cmp(simdLeft >= simdRight, vecLeft >= vecRight);
	cmp(areAllTrue(u32x4(UINT32_MAX)), areAllTrue(uint4(UINT32_MAX)));
	cmp(areAllFalse(u32x4(0u)), areAllTrue(uint4(0u)));
	cmp(areAnyTrue(u32x4(0, 1, 0, 0)), areAllTrue(uint4(0, 1, 0, 0)));
	cmp(equal(simdLeft, simdLeft), equal(vecLeft, vecLeft));
	cmp(equal(simdRight, simdRight), equal(vecRight, vecRight));
	cmp(equal(simdLeft, simdRight), equal(vecLeft, vecRight));
	cmp(notEqual(simdLeft, simdLeft), notEqual(vecLeft, vecLeft));
	cmp(notEqual(simdRight, simdRight), notEqual(vecRight, vecRight));
	cmp(notEqual(simdLeft, simdRight), notEqual(vecLeft, vecRight));
	cmp(select(u32x4(1, 0, 1, 0), simdLeft, simdRight), select(uint4(1, 0, 1, 0), vecLeft, vecRight));
	cmp(select(u32x4(0, 1, 1, 0), simdRight, simdLeft), select(uint4(0, 1, 1, 0), vecRight, vecLeft));
	cmp(min(simdLeft, simdRight), min(vecLeft, vecRight));
	cmp(max(simdLeft, simdRight), max(vecLeft, vecRight));
}

int main()
{
	const auto simdLevels = ""
		#if defined(MATH_SIMD_SUPPORT_SSE)
		" SSE"
		#endif
		#if defined(MATH_SIMD_SUPPORT_SSE4_1)
		" SSE4.1"
		#endif
		#if defined(MATH_SIMD_SUPPORT_AVX2)
		" AVX2"
		#endif
		#if defined(MATH_SIMD_SUPPORT_NEON)
		" NEON"
		#endif
	;
	cout << "SIMD levels:" << simdLevels << endl;

	testFloatVectors();
	testIntVectors();
	return EXIT_SUCCESS;
}