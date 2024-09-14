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

/***********************************************************************************************************************
 * @file
 * @brief Common tone mapping functions.
 */

#pragma once
#include "math/common.hpp"

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
const float defaultGamma = 2.2f;

/**
 * @brief Applies gamma correction to the specified color.
 * 
 * @details
 * Gamma correction is used to adjust the brightness of an image or display to match the 
 * nonlinear response of display devices, such as monitors. It compensates for the fact that 
 * displays do not linearly represent the light intensity of a color.
 * 
 * @param[in] color target color to gamma correct
 * @param invGamma inverse gamma correction value (1.0/x)
 */
static float3 gammaCorrection(const float3& color, float invGamma)
{
	return pow(color, float3(invGamma));
}
/**
 * @brief Applies gamma correction to the specified color.
 * @details See the @ref gammaCorrection().
 * @param[in] color target color to gamma correct
 */
static float3 gammaCorrection(const float3& color)
{
	return pow(color, float3(1.0f / defaultGamma));
}

} // namespace math