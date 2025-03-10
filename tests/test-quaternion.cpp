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

#include "math/quaternion.hpp"
#include "math/angles.hpp"

#include <stdexcept>
#include <iostream>

using namespace math;

static void cmp(simd_f32_4 a, float4 b, float tolerance = 1.0e-9f)
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
static void cmp(simd_f32_4 a, float3 b, float tolerance = 1.0e-9f)
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
static void cmp(float a, float b, float tolerance = 1.0e-9f)
{
	auto difference = (a - b) * (a - b);
	if (difference > tolerance)
		throw runtime_error("Float test failed.");
}

static void testQuatVectors()
{
	const auto vecAngles = radians(float4(90.0f, -1.23f, 45.0f, 0.0f));
	const auto simdAngles = simd_f32_4(vecAngles);
	const auto vecQuat = quat((float3)vecAngles);
	const auto simdQuat = fromEulerAngles(simdAngles);
	cmp(simdQuat, vecQuat);
	cmp(simd_f32_quat(vecAngles.x, simd_f32_4(1.0f, 0.0f, 0.0f, 0.0f)), quat(vecAngles.x, float3::right));
	cmp(simd_f32_quat(vecAngles.y, simd_f32_4(0.0f, -1.0f, 0.0f, 0.0f)), quat(vecAngles.y, float3::bottom));
	cmp(simdQuat.extractEulerAngles(), vecQuat.extractEulerAngles());
	cmp(simdQuat.extractPitch(), vecQuat.extractPitch());
	cmp(simdQuat.extractYaw(), vecQuat.extractYaw());
	cmp(simdQuat.extractRoll(), vecQuat.extractRoll());
	cmp(conjugate(simdQuat), conjugate(vecQuat));
	cmp(inverse(simdQuat), inverse(vecQuat));
	cmp(slerp(simdQuat, simdQuat * simdQuat, 0.75f), 
		slerp(vecQuat, vecQuat * vecQuat, 0.75f));
	cmp(simdQuat * simdQuat, vecQuat * vecQuat);
	{
		const auto vev = float3(1.0f, 2.34f, -0.5678f);
		const auto simd = simd_f32_4(vev);
		cmp(simdQuat * simd, vecQuat * vev);
		cmp(simd * simdQuat, vev * vecQuat);
	}
}

int main()
{
	testQuatVectors();
	return EXIT_SUCCESS;
}