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

#include "math/matrix.hpp"

using namespace math;

const float2x2 float2x2::zero = float2x2(0.0f);
const float2x2 float2x2::one = float2x2(1.0f);
const float2x2 float2x2::minusOne = float2x2(-1.0f);
const float2x2 float2x2::identity = float2x2(
	1.0f, 0.0f,
	0.0f, 1.0f);

const float3x3 float3x3::zero = float3x3(0.0f);
const float3x3 float3x3::one = float3x3(1.0f);
const float3x3 float3x3::minusOne = float3x3(-1.0f);
const float3x3 float3x3::identity = float3x3(
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f);

const float4x4 float4x4::zero = float4x4(0.0f);
const float4x4 float4x4::one = float4x4(1.0f);
const float4x4 float4x4::minusOne = float4x4(-1.0f);
const float4x4 float4x4::identity = float4x4(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f);

//**********************************************************************************************************************
quat extractQuat(const float3x3& m) noexcept
{
	auto fourXSquaredMinus1 = m.c0.x - m.c1.y - m.c2.z;
	auto fourYSquaredMinus1 = m.c1.y - m.c0.x - m.c2.z;
	auto fourZSquaredMinus1 = m.c2.z - m.c0.x - m.c1.y;
	auto fourWSquaredMinus1 = m.c0.x + m.c1.y + m.c2.z;

	int biggestIndex = 0;
	auto fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	auto biggestVal = std::sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
	auto mult = 0.25f / biggestVal;

	switch (biggestIndex)
	{
	case 0: return quat((m.c1.z - m.c2.y) * mult, (m.c2.x - m.c0.z) * mult, (m.c0.y - m.c1.x) * mult, biggestVal);
	case 1: return quat(biggestVal, (m.c0.y + m.c1.x) * mult, (m.c2.x + m.c0.z) * mult, (m.c1.z - m.c2.y) * mult);
	case 2: return quat((m.c0.y + m.c1.x) * mult, biggestVal, (m.c1.z + m.c2.y) * mult, (m.c2.x - m.c0.z) * mult);
	case 3: return quat((m.c2.x + m.c0.z) * mult, (m.c1.z + m.c2.y) * mult, biggestVal, (m.c0.y - m.c1.x) * mult);
	default: abort();
	}
}