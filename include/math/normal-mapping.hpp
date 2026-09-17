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
//
// Bidirectional Reflectance Distribution Function
// Based on this: https://google.github.io/filament/Filament.html

/***********************************************************************************************************************
 * @file
 * @brief Common normal mapping functions.
 */

#pragma once
#include "math/matrix.hpp"

namespace math
{

// TODO: add docs:

static float3 packNormal(float3 packedNormal) noexcept { return fma(packedNormal, float3(0.5f), float3(0.5f)); }
static float3 unpackNormal(float3 packedNormal) noexcept { return fma(packedNormal, float3(2.0f), float3(-1.0f)); }
static f32x4 packNormal(f32x4 packedNormal) noexcept { return fma(packedNormal, f32x4(0.5f), f32x4(0.5f)); }
static f32x4 unpackNormal(f32x4 packedNormal) noexcept { return fma(packedNormal, f32x4(2.0f), f32x4(-1.0f)); }

static uint32 packNormal3x10(float3 normal) noexcept
{
	auto packed = uint3(fma(packNormal(normal), float3(1023.0f), float3(0.5f)));
	return packed.x | (packed.y << 10u) | (packed.z << 20u);
}
static float3 unpackNormal3x10(uint32 packed) noexcept
{
	auto normal = float3(uint3(packed, packed >> 10u, packed >> 20u) & 1023u);
	return normalize(unpackNormal(normal * float(1.0 / 1023.0)));
}

//**********************************************************************************************************************
// Signed Octahedron Normal Encoding (R10G10B10A2)
// https://johnwhite3d.blogspot.com/2017/10/signed-octahedron-normal-encoding.html

static float2 projectNormToOctXY(float3 normal) noexcept
{
	return (float2)normal / dot3(abs((f32x4)normal), f32x4::one);
}

static float2 encodeNormalOct2(float3 normal) noexcept // [result in -1.0 - 1.0 range]
{
	auto projNorm = projectNormToOctXY(normal);
	auto normSign = float2(normal.x >= 0.0f ? 1.0f : -1.0f, normal.y >= 0.0f ? 1.0f : -1.0f);
	return normal.z >= 0.0f ? projNorm : (1.0f - abs(float2(projNorm.y, projNorm.x))) * normSign;
}
static float3 decodeNormalOct2(float2 encoded) noexcept
{
	auto normal = float3(encoded, 1.0f - (std::abs(encoded.x) + std::abs(encoded.y)));
	auto t = saturate(-normal.z);
	normal.x += normal.x >= 0.0f ? -t : t;
	normal.y += normal.y >= 0.0f ? -t : t;
	return normalize(normal);
}

static float3 encodeNormalOct3(float3 normal) noexcept // [result in 0.0 - 1.0 range]
{
	auto projNorm = projectNormToOctXY(normal);
	auto y = std::fma(projNorm.y, 0.5f, 0.5f);
	auto x = std::fma(projNorm.x, 0.5f, y);
	y = std::fma(projNorm.x, -0.5f, y);
	auto z = saturate(normal.z * FLT_MAX);
	return float3(x, y, z);
}
static float3 decodeNormalOct3(float3 encoded) noexcept
{
	auto normal = float3(encoded.x - encoded.y, 
		encoded.x + encoded.y - 1.0f, std::fma(encoded.z, 2.0f, -1.0f));
	normal.z *= 1.0f - (std::abs(normal.x) + std::abs(normal.y));
	return normalize(normal);
}

//**********************************************************************************************************************
static f32x4x4 computeTBN(const f32x4x4& model, f32x4 normal, f32x4 tangent) noexcept
{
	assert(normal == normalize3(normal));
	assert(tangent == normalize3(tangent));
	auto t = normalize3(model * f32x4(tangent, 0.0));
	auto n = normalize3(model * f32x4(normal, 0.0));
	t = normalize3(t - dot3(t, n) * n);
	auto b = cross3(n, t);
	return f32x4x4(t, b, n);
}
static f32x4x4 computeTBN(f32x4 normal) noexcept
{
	auto up = std::abs(normal.getZ()) < 0.999f ? 
		f32x4(0.0f, 0.0f, 1.0f) : f32x4(1.0f, 0.0f, 0.0f);
	auto tangent = normalize3(cross3(up, normal));
	auto bitangent = cross3(normal, tangent);
	return f32x4x4(tangent, bitangent, normal);
}

static f32x4x4 approximateTBN(f32x4 normal) noexcept
{
	auto up = std::abs(normal.getZ()) < 0.999f ? 
		f32x4(0.0f, 0.0f, 1.0f) : f32x4(1.0f, 0.0f, 0.0f);
	auto tangent = normalize3(cross3(up, normal));
	auto bitangent = cross3(normal, tangent);
	return f32x4x4(tangent, bitangent, normal);
}
static float3x3 fastApproximateTBN(float3 normal) noexcept // Branchless ONB (Duff et al. Orthonormal Basis)
{
	assert(normal == normalize(normal));
	float signZ = normal.z >= 0.0f ? 1.0f : -1.0f;
	float a = -1.0f / (signZ + normal.z), b = normal.x * normal.y * a;
	float3 tangent = float3(std::fma(signZ * normal.x * normal.x, 
		a, 1.0f), signZ * b, -signZ * normal.x);
	float3 bitangent = float3(b, std::fma(normal.y * normal.y, a, signZ), -normal.y);
	return float3x3(tangent, bitangent, normal);
}

static f32x4x4 tbnToTangentSpace(const f32x4x4& tbn) noexcept { return transpose3x3(tbn); }
static f32x4 getTbnTangent(const f32x4x4& tbn) noexcept { return tbn[0]; }
static f32x4 getTbnBitangent(const f32x4x4& tbn) noexcept { return tbn[1]; }
static f32x4 getTbnNormal(const f32x4x4& tbn) noexcept { return tbn[2]; }

static float3 snapToAxis(float3 normal) noexcept
{
	float3 a = abs(normal);
	return a.x > a.y && a.x > a.z ? float3(sign(normal.x), 0.0f, 0.0f) : (a.y > a.z ? 
		float3(0.0f, sign(normal.y), 0.0f) : float3(0.0f, 0.0f, sign(normal.z)));
}

} // namespace math