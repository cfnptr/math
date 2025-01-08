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
 * @brief Common color space conversion functions.
 */

#pragma once
#include "math/matrix.hpp"

namespace math
{

/**
 * @brief Converts linear RGB color to the sRGB color space.
 * @param[in] rgb target linear RGB color
 */
static float3 rgbToSrgb(const float3& rgb) noexcept
{
	constexpr auto c = 0.0031308f;
	auto l = fma(pow(rgb, float3(1.0f / 2.4f)), float3(1.055f), float3(-0.055f));
	auto h = rgb * 12.92f;
	return float3(rgb.x <= c ? h.x : l.x, rgb.y <= c ? h.y : l.y, rgb.z <= c ? h.z : l.z);
}
/**
 * @brief Converts sRGB color to the linear RGB color space.
 * @param[in] srgb target sRGB color
 */
static float3 srgbToRgb(const float3& srgb) noexcept
{
	constexpr auto c = 0.04045f;
	auto l = pow((srgb + 0.055f) * (1.0f / 1.055f), float3(2.4f));
	auto h = srgb * (1.0f / 12.92f);
	return float3(srgb.x <= c ? h.x : l.x, srgb.y <= c ? h.y : l.y, srgb.z <= c ? h.z : l.z);
}

/**
 * @brief Converts linear RGB color to the XYZ color space. (CIE 1931)
 * @param[in] rgb target linear RGB color
 */
static float3 rgbToXyz(const float3& rgb) noexcept
{
	constexpr auto m = float3x3
	(
		0.4124564f, 0.2126729f, 0.0193339f,
		0.3575761f, 0.7151522f, 0.1191920f,
		0.1804375f, 0.0721750f, 0.9503041f
	);
	return m * rgb;
}
/**
 * @brief Converts XYZ color to the linear RGB color space. (CIE 1931)
 * @param[in] xyz target XYZ color
 */
static float3 xyzToRgb(const float3& xyz) noexcept
{
	constexpr auto m = float3x3
	(
		 3.2404542f, -0.9692660f,  0.0556434f,
		-1.5371385f,  1.8760108f, -0.2040259f,
		-0.4985314f,  0.0415560f,  1.0572252f
	);
	return m * xyz;
}

/**
 * @brief Converts XYZ color to the YXY color space.
 * @param[in] xyz target XYZ color
 */
static float3 xyzToYxy(const float3& xyz) noexcept
{
	auto inv = 1.0f / dot(xyz, float3(1.0f));
	return float3(xyz.y, xyz.x * inv, xyz.y * inv);
}
/**
 * @brief Converts YXY color to the XYZ color space.
 * @param[in] yxy target YXY color
 */
static float3 yxyToXyz(const float3& yxy) noexcept
{
	return float3(yxy.x * yxy.y / yxy.z, yxy.x, 
		yxy.x * (1.0f - yxy.y - yxy.z) / yxy.z);
}

/**
 * @brief Converts linear RGB color to the YXY color space.
 * @param[in] rgb target linear RGB color
 */
static float3 rgbToYxy(const float3& rgb) noexcept { return xyzToYxy(rgbToXyz(rgb)); }
/**
 * @brief Converts YXY color to the linear RGB color space.
 * @param[in] yxy target YXY color
 */
static float3 yxyToRgb(const float3& yxy) noexcept { return xyzToRgb(yxyToXyz(yxy)); }

} // namespace math