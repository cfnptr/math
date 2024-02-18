//------------------------------------------------------------------------------------------------------------
// Copyright 2022-2023 Nikita Fediuchin. All rights reserved.
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
//------------------------------------------------------------------------------------------------------------

#pragma once
#include "math/vector.hpp"

// Image Based Lighting
namespace math::ibl
{

const int32 iblDfgSize = 128;
const int32 shBandCount = 3;
const int32 shCoefCount = 9; // 3 * 3

using namespace math;

static float2 coordsToST(int2 coords, float invDim)
{
	return fma(1.0f - ((float2)coords + 0.5f) * invDim, float2(2.0f), float2(-1.0f));
}
static float3 stToDir(float2 st, uint32 face)
{
	float3 dir;
	switch (face)
	{
	case 0: dir = float3( 1.0f,  st.y,  st.x); break;
	case 1: dir = float3(-1.0f,  st.y, -st.x); break;
	case 2: dir = float3(-st.x,  1.0f, -st.y); break;
	case 3: dir = float3(-st.x, -1.0f,  st.y); break;
	case 4: dir = float3(-st.x,  st.y,  1.0f); break;
	case 5: dir = float3( st.x,  st.y, -1.0f); break;
	default: abort();
	}
	return normalize(dir);
}
static float3 coordsToDir(const int3& coords, float invDim)
{
	auto st = coordsToST((int2)coords, invDim);
	return stToDir(st, coords.z);
}

} // namespace math::ibl