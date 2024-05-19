//------------------------------------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------------------------------------

#pragma once
#include "math/hex.hpp"
#include "math/vector.hpp"

namespace math
{

using namespace std;

// sRGB color container.
struct Color
{
	uint8 r = 0, g = 0, b = 0, a = 0;

	explicit Color(uint8 rgba = 0) noexcept {
		this->r = rgba; this->g = rgba; this->b = rgba; this->a = rgba; }
	Color(uint8 r, uint8 g, uint8 b, uint8 a) noexcept {
		this->r = r; this->g = g; this->b = b; this->a = a; }

	explicit Color(uint32 data)
	{
		*(uint32*)this = data;
	}
	explicit Color(const string& hex)
	{
		assert(hex.length() == 8 || hex.length() == 6);
		r = toInt32(string(hex.c_str(), 2));
		g = toInt32(string(hex.c_str() + 2, 2));
		b = toInt32(string(hex.c_str() + 4, 2));

		if (hex.length() == 8)
			a = toInt32(string(hex.c_str() + 6, 2));
	}
	
	explicit Color(const float2& normRg)
	{
		const auto mul = 255.0f;
		r = std::min(normRg.x, 1.0f) * mul;
		g = std::min(normRg.y, 1.0f) * mul;
		b = a = 0;
	}
	explicit Color(const float3& normRgb)
	{
		const auto mul = 255.0f;
		r = std::min(normRgb.x, 1.0f) * mul;
		g = std::min(normRgb.y, 1.0f) * mul;
		b = std::min(normRgb.z, 1.0f) * mul;
		a = 0;
	}
	explicit Color(const float4& normRgba)
	{
		const auto mul = 255.0f;
		r = std::min(normRgba.x, 1.0f) * mul;
		g = std::min(normRgba.y, 1.0f) * mul;
		b = std::min(normRgba.z, 1.0f) * mul;
		a = std::min(normRgba.w, 1.0f) * mul;
	}

	string toHex() const
	{
		auto hex = math::toHex(r);
		hex += math::toHex(g);
		hex += math::toHex(b);
		hex += math::toHex(a);
		return hex;
	}
	
	explicit operator float2() const noexcept
	{
		const auto mul = (1.0f / 255.0f);
		return float2(r * mul, g * mul);
	}
	explicit operator float3() const noexcept
	{
		const auto mul = (1.0f / 255.0f);
		return float3(r * mul, g * mul, b * mul);
	}
	explicit operator float4() const noexcept
	{
		const auto mul = (1.0f / 255.0f);
		return float4(r * mul, g * mul, b * mul, a * mul);
	}

	explicit operator uint32() const noexcept { return *(const uint32*)this; }

//------------------------------------------------------------------------------------------------------------
	Color operator+(Color c) const noexcept { 
		return Color(r + c.r, g + c.g, b + c.b, a + c.a); }
	Color operator-(Color c) const noexcept { 
		return Color(r - c.r, g - c.g, b - c.b, a - c.a); }
	Color operator*(Color c) const noexcept { 
		return Color(r * c.r, g * c.g, b * c.b, a * c.a); }
	Color operator/(Color c) const noexcept { 
		return Color(r / c.r, g / c.g, b / c.b, a / c.a); }
	Color& operator+=(Color c) noexcept { 
		r += c.r; g += c.g; b += c.b; a += c.a; return *this; }
	Color& operator-=(Color c) noexcept { 
		r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this; }
	Color& operator*=(Color c) noexcept { 
		r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this; }
	Color& operator/=(Color c) noexcept { 
		r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this; }
	Color& operator+=(uint8 n) noexcept { r += n; g += n; b += n; a += n; return *this; }
	Color& operator-=(uint8 n) noexcept { r -= n; g -= n; b -= n; a -= n; return *this; }
	Color& operator*=(uint8 n) noexcept { r *= n; g *= n; b *= n; a *= n; return *this; }
	Color& operator/=(uint8 n) noexcept { r /= n; g /= n; b /= n; a /= n; return *this; }
	Color& operator=(uint8 n) noexcept { r = n; g = n; b = n; a = n; return *this; }
	bool operator==(Color c) const noexcept {
		return *((const uint32*)this) == *((const uint32*)&c); }
	bool operator!=(Color c) const noexcept {
		return *((const uint32*)this) != *((const uint32*)&c); }
	bool operator<(Color c) const noexcept {
		return r < c.r && g < c.g && b < c.b && a < c.a; }
	bool operator>(Color c) const noexcept {
		return r > c.r && g > c.g && b > c.b && a > c.a; }
	bool operator<=(Color c) const noexcept {
		return r <= c.r && g <= c.g && b <= c.b && a <= c.a; }
	bool operator>=(Color c) const noexcept {
		return r >= c.r && g >= c.g && b >= c.b && a >= c.a; }

	string toString() const noexcept
	{
		return to_string(r) + " " + to_string(g) + " " +
			to_string(b) + " " + to_string(a);
	}

	static const Color white, black, grey, transparent,
		red, green, blue, cyan, magenta, yellow;
};

//------------------------------------------------------------------------------------------------------------
static Color operator+(Color c, uint8 n) noexcept {
	return Color(c.r + n, c.g + n, c.b + n, c.a + n); }
static Color operator-(Color c, uint8 n) noexcept {
	return Color(c.r - n, c.g - n, c.b - n, c.a - n); }
static Color operator*(Color c, uint8 n) noexcept {
	return Color(c.r * n, c.g * n, c.b * n, c.a * n); }
static Color operator/(Color c, uint8 n) noexcept {
	return Color(c.r / n, c.g / n, c.b / n, c.a / n); }
static bool operator==(Color c, uint8 n) noexcept { return c == Color(n); }
static bool operator!=(Color c, uint8 n) noexcept { return c != Color(n); }
static bool operator<(Color c, uint8 n) noexcept { return c < Color(n); }
static bool operator>(Color c, uint8 n) noexcept { return c > Color(n); }
static bool operator<=(Color c, uint8 n) noexcept { return c <= Color(n); }
static bool operator>=(Color c, uint8 n) noexcept { return c >= Color(n); }

static Color operator+(uint8 n, Color c) noexcept {
	return Color(n + c.r, n + c.g, n + c.b, n + c.a); }
static Color operator-(uint8 n, Color c) noexcept {
	return Color(n - c.r, n - c.g, n - c.b, n - c.a); }
static Color operator*(uint8 n, Color c) noexcept {
	return Color(n * c.r, n * c.g, n * c.b, n * c.a); }
static Color operator/(uint8 n, Color c) noexcept {
	return Color(n / c.r, n / c.g, n / c.b, n / c.a); }
static bool operator==(uint8 n, Color c) noexcept { return Color(n) == c; }
static bool operator!=(uint8 n, Color c) noexcept { return Color(n) != c; }
static bool operator<(uint8 n, Color c) noexcept { return Color(n) < c; }
static bool operator>(uint8 n, Color c) noexcept { return Color(n) > c; }
static bool operator<=(uint8 n, Color c) noexcept { return Color(n) <= c; }
static bool operator>=(uint8 n, Color c) noexcept { return Color(n) >= c; }

static bool isBinaryLess(Color a, Color b) noexcept {
	return  *((const uint32*)&a) < *((const uint32*)&b); }

// TODO: color conversion functions.

} // namespace math