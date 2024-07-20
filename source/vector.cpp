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

#include "math/vector.hpp"
using namespace math;

const int2 int2::zero = int2(0);
const int2 int2::one = int2(1);
const int2 int2::minusOne = int2(-1);
const int2 int2::left = int2(-1, 0);
const int2 int2::right = int2(1, 0);
const int2 int2::bottom = int2(0, -1);
const int2 int2::top = int2(0, 1);

const float2 float2::zero = float2(0.0f);
const float2 float2::one = float2(1.0f);
const float2 float2::minusOne = float2(-1.0f);
const float2 float2::left = float2(-1.0f, 0.0f);
const float2 float2::right = float2(1.0f, 0.0f);
const float2 float2::bottom = float2(0.0f, -1.0f);
const float2 float2::top = float2(0.0f, 1.0f);

const int3 int3::zero = int3(0);
const int3 int3::one = int3(1);
const int3 int3::minusOne = int3(-1);
const int3 int3::left = int3(-1, 0, 0);
const int3 int3::right = int3(1, 0, 0);
const int3 int3::bottom = int3(0, -1, 0);
const int3 int3::top = int3(0, 1, 0);
const int3 int3::back = int3(0, 0, -1);
const int3 int3::front = int3(0, 0, 1);

const float3 float3::zero = float3(0.0f);
const float3 float3::one = float3(1.0f);
const float3 float3::minusOne = float3(-1.0f);
const float3 float3::left = float3(-1.0f, 0.0f, 0.0f);
const float3 float3::right = float3(1.0f, 0.0f, 0.0f);
const float3 float3::bottom = float3(0.0f, -1.0f, 0.0f);
const float3 float3::top = float3(0.0f, 1.0f, 0.0f);
const float3 float3::back = float3(0.0f, 0.0f, -1.0f);
const float3 float3::front = float3(0.0f, 0.0f, 1.0f);

const int4 int4::zero = int4(0);
const int4 int4::one = int4(1);
const int4 int4::minusOne = int4(-1);

const float4 float4::zero = float4(0.0f);
const float4 float4::one = float4(1.0f);
const float4 float4::minusOne = float4(-1.0f);