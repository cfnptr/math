// Copyright 2022-2026 Nikita Fediuchin. All rights reserved.
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

using namespace math;

static void cmp(f32x4 a, f32x4 b, float tolerance = 1.0e-9f)
{
	for (int i = 0; i < 4; i++)
	{
		if (isnan(a[i]))
			a[i] = 0.0f;
		if (isnan(b[i]))
			b[i] = 0.0f;
	}

	auto difference = distanceSq4(a, b);
	if (difference > tolerance)
		throw runtime_error("Float4 vectors test failed.");
}
static void cmp(float a, float b, float tolerance = 1.0e-9f)
{
	auto difference = (a - b) * (a - b);
	if (difference > tolerance)
		throw runtime_error("Float test failed.");
}

static void testQuatVectors()
{
	const auto eulerAngles = radians(f32x4(90.0f, -1.23f, 45.0f, 0.0f));
	const auto quat = fromEulerAngles(eulerAngles);
	cmp(conjugate(conjugate(quat)), quat);
	cmp(inverse(inverse(quat)), quat);

	// TODO: more tests
}

int main()
{
	testQuatVectors();
	return EXIT_SUCCESS;
}