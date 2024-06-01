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

#include "math/aabb.hpp"
using namespace math;

const Aabb Aabb::zero = Aabb(float3(0.0f), float3(0.0f));
const Aabb Aabb::one = Aabb(float3(-0.5f), float3(0.5f));
const Aabb Aabb::two = Aabb(float3(-1.0f), float3(1.0f));
const Aabb Aabb::half = Aabb(float3(-0.25f), float3(0.25f));