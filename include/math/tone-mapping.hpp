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

/***********************************************************************************************************************
 * @file
 * @brief Common tone mapping functions.
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

/**
 * @brief Default gamma correction value.
 * 
 * @details
 * The default gamma correction value of 2.2 is chosen because it approximates the natural response curve of CRT 
 * monitors, which were the most common display technology when gamma correction became standard. Modern displays 
 * have inherited this standard, as it closely matches how human vision perceives brightness non-linearly.
 */
constexpr float defaultGamma = 2.2f;

/**
 * @brief Applies gamma correction to the specified color. (Fast approximation)
 * 
 * @details
 * Gamma correction is used to adjust the brightness of an image or display to match the 
 * nonlinear response of display devices, such as monitors. It compensates for the fact that 
 * displays do not linearly represent the light intensity of a color.
 * 
 * @param color target color to gamma correct
 * @param invGamma inverse gamma correction value (1.0/x)
 */
static f32x4 fastGammaCorrection(f32x4 color, float invGamma) noexcept
{
	return f32x4(fastPow(color, f32x4(invGamma)), color.getW());
}
/**
 * @brief Applies gamma correction to the specified color. (Fast approximation)
 * @details See the @ref gammaCorrection().
 * @param color target color to gamma correct
 */
static f32x4 fastGammaCorrection(f32x4 color) noexcept
{
	return f32x4(fastPow(color, f32x4(1.0f / defaultGamma)), color.getW());
}

} // namespace math