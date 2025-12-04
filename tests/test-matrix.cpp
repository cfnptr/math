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

#include "math/matrix.hpp"
#include <stdexcept>

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
static void cmp(f32x4x4 a, float4x4 b, float tolerance = 1.0e-9f)
{
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			if (isnan(a[c][r]))
				a[c][r] = 0.0f;
			if (isnan(b[c][r]))
				b[c][r] = 0.0f;
		}

		auto difference = distanceSq((float4)a[c], b[c]);
		if (difference > tolerance)
			throw runtime_error("Float4 matrices test failed.");
	}
}
static void cmp(f32x4x4 a, float3x3 b, float tolerance = 1.0e-9f)
{
	for (int c = 0; c < 3; c++)
	{
		for (int r = 0; r < 3; r++)
		{
			if (isnan(a[c][r]))
				a[c][r] = 0.0f;
			if (isnan(b[c][r]))
				b[c][r] = 0.0f;
		}

		auto difference = distanceSq((float3)a[c], b[c]);
		if (difference > tolerance)
			throw runtime_error("Float4 matrices test failed.");
	}
}
static void cmp(uint32 a, uint32 b)
{
	if (a != b)
		throw runtime_error("Uint test failed.");
}

static constexpr auto matLeft = float4x4(
	0.0f, 2.3f, 4.56f, 78.9f,
	1.0f, 0.023f, 4.5f, 6789.0f,
	0.01f, 0.0f, 23.456f, 7.089f,
	1.234f, 5.0006f, 78.09f, 0.0f);
static constexpr auto matRight = float4x4(
	1.0f, -23.0f, 4.56f, -0.0789,
	10.023f, -4.0f, -56.708f, 0.009f,
	-100.0f, 23.0405f, 0.0678f, -0.9f,
	1.234f, 6789.0f, 500.0f, 1.0f);
static const auto simdLeft = f32x4x4(matLeft), simdRight = f32x4x4(matRight);

static void testFloatMatrices()
{
	cmp(simdLeft, matLeft);
	cmp(simdRight, matRight);
	cmp(simdLeft * simdRight, matLeft * matRight, 1.0e-3f); // fma has better precision
	cmp(simdLeft * simdRight.c0, matLeft * matRight.c0);
	cmp(simdRight * simdRight.c0, matRight * matRight.c0);
	cmp(simdRight + 123.4f, matRight + 123.4f);
	cmp(simdRight - 123.4f, matRight - 123.4f);
	cmp(simdRight * 123.4f, matRight * 123.4f);
	cmp(simdRight / 123.4f, matRight / 123.4f);
	cmp(simdLeft == simdLeft, true);
	cmp(simdRight == simdRight, true);
	cmp(simdLeft != simdRight, true);
	cmp(simdRight == simdLeft, false);
	cmp(simdRight == simdLeft, false);
	cmp(multiply3x3(simdLeft, simdRight.c0), (float3x3)matLeft * (float3)matRight.c0);
	cmp(multiply3x3(simdRight, simdRight.c0), (float3x3)matRight * (float3)matRight.c0);
	cmp(transpose4x4(simdLeft), transpose(matLeft));
	cmp(transpose3x3(simdRight), transpose((float3x3)matRight));
	cmp(inverse4x4(simdLeft), inverse(matLeft));
}

// TODO: test transformations

int main()
{
	testFloatMatrices();
	return EXIT_SUCCESS;
}