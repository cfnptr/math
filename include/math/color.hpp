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
#include <string_view>

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
	 * @brief Creates a new sRGB color structure.
	 * 
	 * @param rgb red green and blue channel color value
	 * @param a alpha channel color value (transparency)
	 */
	 constexpr Color(Color rgb, uint8 a) noexcept : r(rgb.r), g(rgb.g), b(rgb.b), a(a) { }

	/**
	 * @brief Creates a new sRGB color structure from the binary data.
	 * @param data target binary color data
	 */
	constexpr explicit Color(uint32 data) { *(uint32*)this = data; }
	/**
	 * @brief Creates a new sRGB color structure from the hexadecimal string.
	 * @param hex target hexadecimal color string
	 */
	explicit Color(string_view hex)
	{
		assert(hex.length() == 8 || hex.length() == 6);
		char buffer[3]; buffer[2] = '\0';
		auto data = hex.data();

		buffer[0] = data[0]; buffer[1] = data[1];
		r = std::stoul(buffer, nullptr, 16);
		buffer[0] = data[2]; buffer[1] = data[3];
		g = std::stoul(buffer, nullptr, 16);
		buffer[0] = data[4]; buffer[1] = data[5];
		b = std::stoul(buffer, nullptr, 16);

		if (hex.length() == 8)
		{
			buffer[0] = data[6]; buffer[1] = data[7];
			a = std::stoul(buffer, nullptr, 16);
		}
	}
	/**
	 * @brief Creates a new sRGB color structure from the hexadecimal string.
	 * @param hex target hexadecimal color string
	 */
	explicit Color(u32string_view hex)
	{
		assert(hex.length() == 8 || hex.length() == 6);
		char buffer[8]; auto data = hex.data();
		for (psize i = 0; i < hex.length(); i++)
			buffer[i] = (char)data[i]; // Note: ASCII hex string maps directly.
		*this = Color(string_view(buffer, hex.length()));
	}
	
	/**
	 * @brief Creates a new sRGB color structure from the normalized R and G channels. (Red, Green)
	 * @param normRg target normalized R and G channel color values
	 */
	explicit Color(float2 normRg)
	{
		auto c = fma(clamp(normRg, float2(0.0f), float2(1.0f)), float2(255.0f), float2(0.5f));
		r = (uint8)c.x, g = (uint8)c.y, b = a = 0;
	}
	/**
	 * @brief Creates a new sRGB color structure from the normalized RGB channels. (Red, Green, Blue)
	 * @param normRgb target normalized RGB channel color values
	 */
	explicit Color(float3 normRgb)
	{
		auto c = fma(clamp(normRgb, float3(0.0f), float3(1.0f)), float3(255.0f), float3(0.5f));
		r = (uint8)c.x, g = (uint8)c.y, b = (uint8)c.z, a = 0;
	}
	/**
	 * @brief Creates a new sRGB color structure from the normalized RGBA channels. (Red, Green, Blue, Alpha)
	 * @param normRgba target normalized RGBA channel color values
	 */
	explicit Color(float4 normRgba)
	{
		auto c = fma(clamp(normRgba, float4(0.0f), float4(1.0f)), float4(255.0f), float4(0.5f));
		r = (uint8)c.x, g = (uint8)c.y, b = (uint8)c.z, a = (uint8)c.w;
	}
	/**
	 * @brief Creates a new sRGB color structure from the normalized RGBA channels. (Red, Green, Blue, Alpha)
	 * @param normRgba target normalized RGBA channel color SIMD values
	 */
	explicit Color(f32x4 normRgba)
	{
		auto c = fma(clamp(normRgba, f32x4::zero, f32x4::one), f32x4(255.0f), f32x4(0.5f));
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
	explicit operator f32x4() const noexcept { return f32x4(r, g, b, a) * (1.0f / 255.0f); }
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
	void setNormR(float r) noexcept { this->r = std::fma(std::clamp(r, 0.0f, 1.0f), 255.0f, 0.5f); }
	/**
	 * @brief Sets sRGB color normalizer G channel. (Green)
	 */
	void setNormG(float g) noexcept { this->g = std::fma(std::clamp(g, 0.0f, 1.0f), 255.0f, 0.5f); }
	/**
	 * @brief Sets sRGB color normalizer B channel. (Blue)
	 */
	void setNormB(float b) noexcept { this->b = std::fma(std::clamp(b, 0.0f, 1.0f), 255.0f, 0.5f); }
	/**
	 * @brief Sets sRGB color normalizer A channel. (Alpha)
	 */
	void setNormA(float a) noexcept { this->a = std::fma(std::clamp(a, 0.0f, 1.0f), 255.0f, 0.5f); }

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
	string toHex4() const noexcept { return math::toHex8((const uint8*)this, 4); }
	/**
	 * @brief Converts sRGB color to the RGBA hexadecimal string.
	 */
	string toHex3() const noexcept { return math::toHex8((const uint8*)this, 3); }

	/**
	 * @brief Converts sRGB color to the normalized linear RGB color space.
	 */
	f32x4 toLinear() const noexcept { return srgbToRgb((f32x4)*this); }

	/**
	 * @brief Converts normalized linear RGB color to the sRGB color space.
	 */
	static Color fromLinear(f32x4 normRGBA) noexcept { return Color(rgbToSrgb(normRGBA)); }

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