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
#include <stdexcept>

using namespace math;

int main()
{
	float4x4 a(2.0f);
	auto b = float4x4::identity;
	auto c = b * a;
	
	if (c != float4x4(2.0f))
		throw runtime_error("Bad test matrix value.");
	
	return EXIT_SUCCESS;
}