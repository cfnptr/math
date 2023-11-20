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

#include "math/plane.hpp"
using namespace math;

const Plane Plane::left = Plane(float3(-1.0f, 0.0f, 0.0f), 0.0f, false);
const Plane Plane::right = Plane(float3(1.0f, 0.0f, 0.0f), 0.0f, false);
const Plane Plane::bottom = Plane(float3(0.0f, -1.0f, 0.0f), 0.0f, false);
const Plane Plane::top = Plane(float3(0.0f, 1.0f, 0.0f), 0.0f, false);
const Plane Plane::back = Plane(float3(0.0f, 0.0f, -1.0f), 0.0f, false);
const Plane Plane::front = Plane(float3(0.0f, 0.0f, 1.0f), 0.0f, false);