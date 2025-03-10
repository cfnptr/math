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
 * @brief Common color conversion functions.
 */

#pragma once
#include "math/hex.hpp"
#include "math/color-space.hpp"

namespace math
{

/**
 * @brief sRGB color container.
 */
struct [[nodiscard]] Color
{
	uint8 r = 0; /**< Red color channel value. */
	uint8 g = 0; /**< Green color channel value. */
	uint8 b = 0; /**< Blue color channel value. */
	uint8 a = 0; /**< Alpha color channel value. (Transparency) */

	/**
	 * @brief Creates a new sRGB color structure.
	 * @param rgba target color value for all RGBA channels
	 */
	constexpr explicit Color(uint8 rgba = 0) noexcept : r(rgba), g(rgba), b(rgba), a(rgba) { }
	/**
	 * @brief Creates a new sRGB color structure.
	 * 
	 * @param r red channel color value
	 * @param g green channel color value
	 * @param b blue channel color value
	 * @param a alpha channel color value (transparency)
	 */
	constexpr Color(uint8 r, uint8 g, uint8 b, uint8 a) noexcept : r(r), g(g), b(b), a(a) { }

	/**
	 * @brief Creates a new sRGB color structure from the binary data.
	 * @param data target binary color data
	 */
	constexpr explicit Color(uint32 data) { *(uint32*)this = data; }
	/**
	 * @brief Creates a new sRGB color structure from the hexadecimal string.
	 * @param[in] hex target hexadecimal color string
	 */
	explicit Color(const string& hex)
	{
		assert(hex.length() == 8 || hex.length() == 6);
		r = toInt32(string(hex.c_str(), 2));
		g = toInt32(string(hex.c_str() + 2, 2));
		b = toInt32(string(hex.c_str() + 4, 2));

		if (hex.length() == 8)
			a = toInt32(string(hex.c_str() + 6, 2));
	}
	
	/**
	 * @brief Creates a new sRGB color structure from the normalized R and G channels. (Red, Green)
	 * @param normRg target normalized R and G channel color values
	 */
	constexpr explicit Color(float2 normRg)
	{
		auto c = clamp(normRg, float2(0.0f), float2(1.0f)) * 255.0f + 0.5f;
		r = (uint8)c.x, g = (uint8)c.y, b = a = 0;
	}
	/**
	 * @brief Creates a new sRGB color structure from the normalized RGB channels. (Red, Green, Blue)
	 * @param normRgb target normalized RGB channel color values
	 */
	constexpr explicit Color(float3 normRgb)
	{
		auto c = clamp(normRgb, float3(0.0f), float3(1.0f)) * 255.0f + 0.5f;
		r = (uint8)c.x, g = (uint8)c.y, b = (uint8)c.z, a = 0;
	}
	/**
	 * @brief Creates a new sRGB color structure from the normalized RGBA channels. (Red, Green, Blue, Alpha)
	 * @param normRgba target normalized RGBA channel color values
	 */
	constexpr explicit Color(float4 normRgba)
	{
		auto c = clamp(normRgba, float4(0.0f), float4(1.0f)) * 255.0f + 0.5f;
		r = (uint8)c.x, g = (uint8)c.y, b = (uint8)c.z, a = (uint8)c.w;
	}
	/**
	 * @brief Creates a new sRGB color structure from the normalized RGBA channels. (Red, Green, Blue, Alpha)
	 * @param normRgba target normalized RGBA channel color SIMD values
	 */
	explicit Color(simd_f32_4 normRgba)
	{
		auto c = clamp(normRgba, simd_f32_4::zero, simd_f32_4::one) * 255.0f + 0.5f;
		r = (uint8)c.getX(), g = (uint8)c.getY(), b = (uint8)c.getZ(), a = (uint8)c.getW();
	}
	
	/*******************************************************************************************************************
	 * @brief Converts sRGB color to the normalized RG vector. (Red, Green)
	 */
	constexpr explicit operator float2() const noexcept { return float2(r, g) * (1.0f / 255.0f); }
	/**
	 * @brief Converts sRGB color to the normalized RGB vector. (Red, Green, Blue)
	 */
	constexpr explicit operator float3() const noexcept { return float3(r, g, b) * (1.0f / 255.0f); }
	/**
	 * @brief Converts sRGB color to the normalized RGBA vector. (Red, Green, Blue, Alpha)
	 */
	constexpr explicit operator float4() const noexcept { return float4(r, g, b, a) * (1.0f / 255.0f); }
	/**
	 * @brief Converts sRGB color to the normalized RGBA SIMD vector. (Red, Green, Blue, Alpha)
	 */
	explicit operator simd_f32_4() const noexcept { return simd_f32_4(r, g, b, a) * (1.0f / 255.0f); }
	/**
	 * @brief Returns color binary data.
	 */
	constexpr explicit operator uint32() const noexcept { return *(const uint32*)this; }

	/*******************************************************************************************************************
	 * @brief Returns sRGB color normalizer R channel. (Red)
	 */
	constexpr float getNormR() const noexcept { return r * (1.0f / 255.0f); }
	/**
	 * @brief Returns sRGB color normalizer G channel. (Green)
	 */
	constexpr float getNormG() const noexcept { return g * (1.0f / 255.0f); }
	/**
	 * @brief Returns sRGB color normalizer B channel. (Blue)
	 */
	constexpr float getNormB() const noexcept { return b * (1.0f / 255.0f); }
	/**
	 * @brief Returns sRGB color normalizer A channel. (Alpha)
	 */
	constexpr float getNormA() const noexcept { return a * (1.0f / 255.0f); }

	/**
	 * @brief Sets sRGB color normalizer R channel. (Red)
	 */
	constexpr void setNormR(float r) noexcept { this->r = std::clamp(r, 0.0f, 1.0f) * 255.0f; }
	/**
	 * @brief Sets sRGB color normalizer G channel. (Green)
	 */
	constexpr void setNormG(float g) noexcept { this->g = std::clamp(g, 0.0f, 1.0f) * 255.0f; }
	/**
	 * @brief Sets sRGB color normalizer B channel. (Blue)
	 */
	constexpr void setNormB(float b) noexcept { this->b = std::clamp(b, 0.0f, 1.0f) * 255.0f; }
	/**
	 * @brief Sets sRGB color normalizer A channel. (Alpha)
	 */
	constexpr void setNormA(float a) noexcept { this->a = std::clamp(a, 0.0f, 1.0f) * 255.0f; }

	/*******************************************************************************************************************
	 * @brief Converts sRGB color to the string. (Space separated)
	 */
	string toString4() const noexcept
	{
		return to_string(r) + " " + to_string(g) + " " + to_string(b) + " " + to_string(a);
	}
	/***
	 * @brief Converts sRGB color to the string. (Space separated)
	 */
	string toString3() const noexcept { return to_string(r) + " " + to_string(g) + " " + to_string(b); }
	/***
	 * @brief Converts sRGB color to the string. (Space separated)
	 */
	string toString2() const noexcept { return to_string(r) + " " + to_string(g); }
	/***
	 * @brief Converts sRGB color to the string. (Space separated)
	 */
	string toString1() const noexcept { return to_string(r); }

	/**
	 * @brief Converts sRGB color to the RGB hexadecimal string.
	 */
	string toHex4() const noexcept
	{
		auto hex = math::toHex(r);
		hex += math::toHex(g);
		hex += math::toHex(b);
		hex += math::toHex(a);
		return hex;
	}
	/**
	 * @brief Converts sRGB color to the RGBA hexadecimal string.
	 */
	string toHex3() const noexcept
	{
		auto hex = math::toHex(r);
		hex += math::toHex(g);
		hex += math::toHex(b);
		return hex;
	}

	/**
	 * @brief Converts sRGB color to the normalized linear RGB color space.
	 */
	simd_f32_4 toLinear() const noexcept { return srgbToRgb((simd_f32_4)*this); }

	/**
	 * @brief Converts normalized linear RGB color to the sRGB color space.
	 */
	static Color fromLinear(simd_f32_4 normRGBA) noexcept { return Color(rgbToSrgb(normRGBA)); }

	//******************************************************************************************************************
	constexpr bool operator==(Color c) const noexcept { return r == c.r && g == c.g && b == c.b && a == c.a; }
	constexpr bool operator!=(Color c) const noexcept { return r != c.r || g != c.g || b != c.b || a != c.a; }
	constexpr bool operator<(Color c) const noexcept { return r < c.r && g < c.g && b < c.b && a < c.a; }
	constexpr bool operator>(Color c) const noexcept { return r > c.r && g > c.g && b > c.b && a > c.a; }
	constexpr bool operator<=(Color c) const noexcept { return r <= c.r && g <= c.g && b <= c.b && a <= c.a; }
	constexpr bool operator>=(Color c) const noexcept { return r >= c.r && g >= c.g && b >= c.b && a >= c.a; }
	constexpr bool operator==(uint8 n) const noexcept { return r == n && g == n && b == n && a == n; }
	constexpr bool operator!=(uint8 n) const noexcept { return r != n || g != n || b != n || a != n; }
	constexpr bool operator<(uint8 n) const noexcept { return r < n && g < n && b < n && a < n; }
	constexpr bool operator>(uint8 n) const noexcept { return r > n && g > n && b > n && a > n; }
	constexpr bool operator<=(uint8 n) const noexcept { return r <= n && g <= n && b <= n && a <= n; }
	constexpr bool operator>=(uint8 n) const noexcept { return r >= n && g >= n && b >= n && a >= n; }

	static const Color white, black, grey, transparent, red, green, blue, cyan, magenta, yellow;
};

inline const Color Color::white = Color(255, 255, 255, 255);
inline const Color Color::black = Color(0, 0, 0, 255);
inline const Color Color::grey = Color(127, 127, 127, 255);
inline const Color Color::transparent = Color(0, 0, 0, 0);
inline const Color Color::red = Color(255, 0, 0, 255);
inline const Color Color::green = Color(0, 255, 0, 255);
inline const Color Color::blue = Color(0, 0, 255, 255);
inline const Color Color::cyan = Color(0, 255, 255, 255);
inline const Color Color::magenta = Color(255, 0, 255, 255);
inline const Color Color::yellow = Color(255, 255, 0, 255);

static constexpr bool operator==(uint8 n, Color c) noexcept { return Color(n) == c; }
static constexpr bool operator!=(uint8 n, Color c) noexcept { return Color(n) != c; }
static constexpr bool operator<(uint8 n, Color c) noexcept { return Color(n) < c; }
static constexpr bool operator>(uint8 n, Color c) noexcept { return Color(n) > c; }
static constexpr bool operator<=(uint8 n, Color c) noexcept { return Color(n) <= c; }
static constexpr bool operator>=(uint8 n, Color c) noexcept { return Color(n) >= c; }

/**
 * @brief Returns true if first color binary representation is less than the second.
 *
 * @param a first color to binary compare
 * @param b second color to binary compare
 */
static bool isBinaryLess(Color a, Color b) noexcept { return  *((const uint32*)&a) < *((const uint32*)&b); }

// TODO: color conversion functions.

} // namespace math