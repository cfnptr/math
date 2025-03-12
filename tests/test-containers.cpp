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

#include "math/angles.hpp"
#include "math/sphere.hpp"
#include "math/matrix/projection.hpp"
#include <stdexcept>

using namespace math;

static void testPlanes()
{
	auto plane = Plane(f32x4(1.0f, 2.0f, 3.0f), 12.3f);
	if (!isNormalized3(plane.getNormal()))
		throw runtime_error("Plane is not normalized.");

	Plane frustumPlanes[Plane::frustumCount];
	auto viewProj = calcPerspProjInfRevZ(radians(90.0f), 16.0f / 9.0f, 0.01f);
	extractFrustumPlanes(f32x4x4(viewProj), frustumPlanes);
	normalizePlanes(frustumPlanes, Plane::frustumCount);
}

// TODO: test other containers.

int main()
{
	testPlanes();
	return EXIT_SUCCESS;
}