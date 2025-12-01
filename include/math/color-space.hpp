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

/**
 * @brief Converts linear RGB color to the XYZ color space. (CIE 1931)
 * @param rgb target linear RGB color
 */
static f32x4 rgbToXyz(f32x4 rgb) noexcept
{
	static const auto m = f32x4x4
	(
		0.4124564f, 0.2126729f, 0.0193339f, 0.0f,
		0.3575761f, 0.7151522f, 0.1191920f, 0.0f,
		0.1804375f, 0.0721750f, 0.9503041f, 0.0f,
		0.0f      , 0.0f      , 0.0f      , 0.0f
	);
	return multiply3x3(m, rgb);
}
/**
 * @brief Converts XYZ color to the linear RGB color space. (CIE 1931)
 * @param xyz target XYZ color
 */
static f32x4 xyzToRgb(f32x4 xyz) noexcept
{
	static const auto m = f32x4x4
	(
		 3.2404542f, -0.9692660f,  0.0556434f, 0.0f,
		-1.5371385f,  1.8760108f, -0.2040259f, 0.0f,
		-0.4985314f,  0.0415560f,  1.0572252f, 0.0f,
		 0.0f      ,  0.0f      ,  0.0f      , 0.0f
	);
	return multiply3x3(m, xyz);
}

/**
 * @brief Converts XYZ color to the YXY color space.
 * @param xyz target XYZ color
 */
static f32x4 xyzToYxy(f32x4 xyz) noexcept
{
	auto y = xyz.getY();
	auto inv = 1.0f / dot3(xyz, f32x4::one);
	return f32x4(y, xyz.getX() * inv, y * inv);
}
/**
 * @brief Converts YXY color to the XYZ color space.
 * @param yxy target YXY color
 */
static f32x4 yxyToXyz(f32x4 yxy) noexcept
{
	auto x = yxy.getX(), y = yxy.getY(), z = yxy.getZ();
	return f32x4(x * y / z, x, x * (1.0f - y - z) / z);
}

/**
 * @brief Converts linear RGB color to the YXY color space.
 * @param rgb target linear RGB color
 */
static f32x4 rgbToYxy(f32x4 rgb) noexcept { return xyzToYxy(rgbToXyz(rgb)); }
/**
 * @brief Converts YXY color to the linear RGB color space.
 * @param yxy target YXY color
 */
static f32x4 yxyToRgb(f32x4 yxy) noexcept { return xyzToRgb(yxyToXyz(yxy)); }

} // namespace math