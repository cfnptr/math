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
 * @brief Common color space conversion functions.
 */

#pragma once
#include "math/matrix.hpp"

namespace math
{

/**
 * @brief Converts linear RGBA color to the sRGB color space.
 * @param rgba target linear RGBA color
 */
static f32x4 rgbToSrgb(f32x4 rgba) noexcept
{
	auto l = fma(pow(rgba, f32x4(1.0f / 2.4f)), f32x4(1.055f), f32x4(-0.055f));
	auto h = rgba * 12.92f;
	auto r = select(rgba <= f32x4(0.0031308f), h, l); r.setW(rgba.getW());
	return r;
}
/**
 * @brief Converts sRGB color to the linear RGBA color space.
 * @param sRGB target sRGB color
 */
static f32x4 srgbToRgb(f32x4 sRGB) noexcept
{
	auto l = pow((sRGB + 0.055f) * (1.0f / 1.055f), f32x4(2.4f));
	auto h = sRGB * (1.0f / 12.92f);
	auto r = select(sRGB <= f32x4(0.04045f), h, l); r.setW(sRGB.getW());
	return r;
}

static const f32x4x4 rgbToXyzMat = f32x4x4
(
	0.41239079926595934f, 0.21263900587151027f, 0.01933081871559182f, 0.0f,
	0.35758433938387800f, 0.71516867876775600f, 0.11919477979462598f, 0.0f,
	0.18048078840183430f, 0.07219231536073371f, 0.95053215224966070f, 0.0f,
	0.0f                , 0.0f                , 0.0f                , 0.0f
);
static const f32x4x4 xyzToRgbMat = f32x4x4
(
	 3.2409699419045226f, -0.96924363628087960f,  0.05563007969699366f, 0.0f,
	-1.5373831775700940f,  1.87596750150772020f, -0.20397695888897652f, 0.0f,
	-0.4986107602930034f,  0.04155505740717559f,  1.05697151424287860f, 0.0f,
	 0.0f               ,  0.0f                ,  0.0f                , 0.0f
);

/**
 * @brief Converts linear sRGB color to the CIE XYZ color space.
 * @param rgb target linear sRGB color
 */
static f32x4 rgbToXyz(f32x4 rgb) noexcept { return multiply3x3(rgbToXyzMat, rgb); }
/**
 * @brief Converts CIE XYZ color to the linear sRGB color space.
 * @param xyz target CIE XYZ color
 */
static f32x4 xyzToRgb(f32x4 xyz) noexcept { return multiply3x3(xyzToRgbMat, xyz); }

/**
 * @brief Converts CIE XYZ color to the CIE xyY color space.
 * @param xyz target CIE XYZ color
 */
static f32x4 xyzToXyy(f32x4 xyz) noexcept
{
	auto a = std::max(xyz.getX() + xyz.getY() + xyz.getZ(), 1e-5f);
	return f32x4(xyz.getX() / a, xyz.getY() / a, xyz.getY());
}
/**
 * @brief Converts CIE xyY color to the CIE XYZ color space.
 * @param xyy target CIE xyY color
 */
static f32x4 xyyToXyz(f32x4 xyy) noexcept
{
	float a = xyy.getZ() / std::max(xyy.getY(), 1e-5f);
	return f32x4(xyy.getX() * a, xyy.getZ(), (1.0f - xyy.getX() - xyy.getY()) * a);
}

/**
 * @brief Converts linear sRGB color to the CIE xyY color space.
 * @param rgb target linear RGB color
 */
static f32x4 rgbToXyy(f32x4 rgb) noexcept { return xyzToXyy(rgbToXyz(rgb)); }
/**
 * @brief Converts CIE xyY color to the linear sRGB color space.
 * @param xyy target CIE xyY color
 */
static f32x4 xyyToRgb(f32x4 xyy) noexcept { return xyzToRgb(xyyToXyz(xyy)); }

} // namespace math