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

int main()
{
	float3 a(1.0f, 2.0f, 3.0f);
	auto b = float3(0.4f, 0.5f, 0.6f);
	auto c = a + b;

	if (c.x != 1.4f || c.y != 2.5f || c.z != 3.6f || c != float3(1.4f, 2.5f, 3.6f))
		throw runtime_error("Bad vector test value.");

	auto d = int3(10);
	auto e = d / 2;

	if (e != int3(5))
		throw runtime_error("Bad vector test value.");

	return EXIT_SUCCESS;
}