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

/***********************************************************************************************************************
 * @file
 * @brief Common random generation functions.
 */

#pragma once
#include "math/types.hpp"
#include <cmath>

namespace math
{

/**
 * @brief Generates halton sequence.
 * 
 * @param i sample index
 * @param b base value
 */
static float halton(uint32 i, uint32 b) noexcept
{
	auto f = 1.0f, r = 0.0f;
	while (i > 0)
	{
		f /= (float)b; r = std::fma(f, float(i % b), r);
		i = (uint32)std::floor((float)i / b);
	}
	return r;
}

} // namespace math