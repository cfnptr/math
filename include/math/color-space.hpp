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
 * @brief Default gamma correction value.
 * 
 * @details
 * The default gamma correction value of 2.2 is chosen because it approximates the natural response curve of CRT 
 * monitors, which were the most common display technology when gamma correction became standard. Modern displays 
 * have inherited this standard, as it closely matches how human vision perceives brightness non-linearly.
 */
constexpr float defaultGamma = 2.2f;

/**
 * @brief Converts linear RGBA color to the sRGB color space.
 * @param rgba target linear RGBA color
 */
static f32x4 rgbToSrgb(f32x4 rgba) noexcept
{
	auto l = fma(pow(rgba, f32x4(1.0f / 2.4f)), f32x4(1.055f), f32x4(-0.055f));
	auto r = select(rgba <= f32x4(0.0031308f), rgba * 12.92f, l);
	r.setW(rgba.getW());
	return r;
}
/**
 * @brief Converts sRGB color to the linear RGBA color space.
 * @param sRGB target sRGB color
 */
static f32x4 srgbToRgb(f32x4 sRGB) noexcept
{
	auto l = pow((sRGB + 0.055f) * (1.0f / 1.055f), f32x4(2.4f));
	auto r = select(sRGB <= f32x4(0.04045f), sRGB * (1.0f / 12.92f), l);
	r.setW(sRGB.getW());
	return r;
}

/**
 * @brief Applies gamma correction to the specified color.
 * 
 * @details
 * Gamma correction is used to adjust the brightness of an image or display to match the 
 * nonlinear response of display devices, such as monitors. It compensates for the fact that 
 * displays do not linearly represent the light intensity of a color.
 * 
 * @param color target linear RGB color to gamma correct
 * @param invGamma inverse gamma correction value (1.0/x)
 */
static f32x4 gammaCorrection(f32x4 color, float invGamma) noexcept
{
	return f32x4(pow(color, f32x4(invGamma)), color.getW());
}
/**
 * @brief Applies gamma correction to the specified color.
 * @details See the @ref gammaCorrection().
 * @param color target linear RGB color to gamma correct
 */
static f32x4 gammaCorrection(f32x4 color) noexcept
{
	return f32x4(pow(color, f32x4(1.0f / defaultGamma)), color.getW());
}

/**
 * @brief Applies gamma correction to the specified color. (Fast approximation)
 * @details See the @ref gammaCorrection().
 * 
 * @param color target linear RGB color to gamma correct
 * @param invGamma inverse gamma correction value (1.0/x)
 */
static f32x4 fastGammaCorrection(f32x4 color, float invGamma) noexcept
{
	return f32x4(fastPow(color, f32x4(invGamma)), color.getW());
}
/**
 * @brief Applies gamma correction to the specified color. (Fast approximation)
 * @details See the @ref gammaCorrection().
 * @param color target linear RGB color to gamma correct
 */
static f32x4 fastGammaCorrection(f32x4 color) noexcept
{
	return f32x4(fastPow(color, f32x4(1.0f / defaultGamma)), color.getW());
}

/**
 * @brief Calculates relative luminance of a color. (Rec. 709)
 * @param x target linear color
 */
static float calcLum(f32x4 x) noexcept { return dot3(x, f32x4(0.2126f, 0.7152f, 0.0722f)); }
/**
 * @brief Calculates perceptual brightness (Luma) of a color. (Rec. 709)
 * @param rgb target linear RGB color
 */
static float rgbToLuma(f32x4 rgb) noexcept { return calcLum(fastGammaCorrection(rgb)); }

//**********************************************************************************************************************
// Linear sRGB <-> CIE XYZ
static const f32x4x4 rgbToXyzMat = f32x4x4
(
	f32x4(0.41239079926595934f, 0.21263900587151027f, 0.01933081871559182f, 0.0f),
	f32x4(0.35758433938387800f, 0.71516867876775600f, 0.11919477979462598f, 0.0f),
	f32x4(0.18048078840183430f, 0.07219231536073371f, 0.95053215224966070f, 0.0f),
	f32x4::zero
);
static const f32x4x4 xyzToRgbMat = f32x4x4
(
	f32x4( 3.2409699419045226f, -0.96924363628087960f,  0.05563007969699366f, 0.0f),
	f32x4(-1.5373831775700940f,  1.87596750150772020f, -0.20397695888897652f, 0.0f),
	f32x4(-0.4986107602930034f,  0.04155505740717559f,  1.05697151424287860f, 0.0f),
	f32x4::zero
);
// Note: do not remove f32x4()'s, because value order differs from the GLSL!

/**
 * @brief Converts linear sRGB color to the CIE XYZ color space.
 * @param rgb target linear sRGB color
 */
static f32x4 rgbToXyz(f32x4 rgb) noexcept { return dot3x3(rgbToXyzMat, rgb); }
/**
 * @brief Converts CIE XYZ color to the linear sRGB color space.
 * @param xyz target CIE XYZ color
 */
static f32x4 xyzToRgb(f32x4 xyz) noexcept { return dot3x3(xyzToRgbMat, xyz); }

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

//**********************************************************************************************************************
// Linear sRGB <-> LogLuv
static const f32x4x4 rgbToLogLuvMat = f32x4x4
(
	f32x4(0.1832848040f, 0.2126390040f, 0.252131164f, 0.0f),
	f32x4(0.1589263680f, 0.7151686540f, 0.788274765f, 0.0f),
	f32x4(0.0802136883f, 0.0721923187f, 0.283475161f, 0.0f),
	f32x4::zero
);
static const f32x4x4 logLuvToRgbMat = f32x4x4
(
	f32x4( 7.666140550f, -2.211964610f, -0.667561352f, 0.0f),
	f32x4( 0.955670714f,  1.668192390f, -5.488834380f, 0.0f),
	f32x4(-2.412632940f,  0.201072842f,  5.114378450f, 0.0f),
	f32x4::zero
);

static f32x4x4 calcLogLuvMat(const f32x4x4& rgbToXyzMat) noexcept
{
	static const f32x4x4 m1 = f32x4x4
	(
		f32x4(1.0f, 0.0f,  1.0f, 0.0f),
		f32x4(0.0f, 1.0f, 15.0f, 0.0f),
		f32x4(0.0f, 0.0f,  3.0f, 0.0f),
		f32x4::zero
	);
	static const f32x4x4 m2 = f32x4x4
	(
		f32x4(4.0f / 9.0f, 0.0f,         0.0f, 0.0f),
		f32x4(0.0f,        1.0f,         0.0f, 0.0f),
		f32x4(0.0f,        0.0f, 0.62f / 9.0f, 0.0f),
		f32x4::zero
	);
	return dot3x3(m2, dot3x3(m1, rgbToXyzMat));
}

/**
 * @brief Encodes linear RGB color (HDR) to the LogLuv format.
 * @details Encodes log2(Y) in [-20,20) range.
 * @param rgb target linear RGB color
 */
static uint32 rgbToLogLuv(f32x4 rgb) noexcept
{
	auto luv = max(dot3x3(rgbToLogLuvMat, rgb), f32x4(1e-6f));
	auto uv = (uint2)fma(saturate((float2)luv / luv.getZ()), float2(511.0f), float2(0.5f));
	auto le = (uint32)std::fma(saturate(std::fma(std::log2(
		luv.getY()), (1.0f / 40.0f), 0.5f)), 16383.0f, 0.5f);
	auto logLuv = (uv.y << 23u) | (uv.x << 14u) | le;
	return dot3(rgb, rgb) > 0.0f ? logLuv : 0;
}
/**
 * @brief Decodes linear RGB color (HDR) from the LogLuv format.
 * @param logLuv target LogLuv encoded color
 */
static f32x4 logLuvToRgb(uint32 logLuv)
{
	f32x4 luv; auto uv = float2(uint2(logLuv >> 14u, logLuv >> 23u) & 511u) * (1.0f / 511.0f);
	luv.floats.y = std::exp2(std::fma(logLuv & 16383u, 40.0f / 16383.0f, -20.0f));
	luv.floats.z = luv.floats.y / uv.y; luv.floats.x = luv.floats.z * uv.x;
	return logLuv > 0 ? max(dot3x3(logLuvToRgbMat, luv), f32x4::zero) : f32x4::zero;
}

/**
 * @brief Converts floating point value to the B10G11R11 value.
 *
 * @param value target floating point value
 * @param bits packed mantissa bit count
 * @param mask packed mantissa mask
 */
static uint32 encodeB10G11R11(float value, uint32 bits, uint32 mask) noexcept
{
	// TODO: use here SIMD vector instead, it all can be ported.
	auto valueBits = *(const uint32*)&value;
	auto exponent = (int32)((valueBits >> 23u) & 0xFFu) - 127 + 15; 
	if (exponent <= 0) return 0; // 5-bit exponent bias 15
	auto mantissa = (valueBits >> 12u) & mask;
	return (exponent << bits) | mantissa;
}
/**
 * @brief Converts 3D floating point vector to the B10G11R11 value.
 * @param rgb target 3D floating point vector
 */
static uint32 encodeB10G11R11(f32x4 rgb) noexcept
{
	rgb = clamp(rgb, f32x4::zero, f32x4(FLOAT_BIG_16));
	auto r = encodeB10G11R11(rgb.getX(), 6, 0b111111);
	auto g = encodeB10G11R11(rgb.getY(), 6, 0b111111);
	auto b = encodeB10G11R11(rgb.getZ(), 5, 0b11111);
	return (b << 22u) | (g << 11u) | r;
}

} // namespace math