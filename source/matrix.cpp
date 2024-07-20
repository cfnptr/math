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