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

static f32x4x4 computeTBN(f32x4x4 model, f32x4 normal, f32x4 tangent) noexcept
{
	assert(normal == normalize3(normal));
	assert(tangent == normalize3(tangent));
	auto t = normalize3(model * f32x4(tangent, 0.0));
	auto n = normalize3(model * f32x4(normal, 0.0));
	t = normalize3(t - dot3(t, n) * n);
	auto b = cross3(n, t);
	return f32x4x4(t, b, n);
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

static f32x4x4 tbnToTangentSpace(f32x4x4 tbn) noexcept { return transpose3x3(tbn); }
static f32x4 getTbnTangent(f32x4x4 tbn) noexcept { return tbn[0]; }
static f32x4 getTbnBitangent(f32x4x4 tbn) noexcept { return tbn[1]; }
static f32x4 getTbnNormal(f32x4x4 tbn) noexcept { return tbn[2]; }

static float3 snapToAxis(float3 normal) noexcept
{
	float3 a = abs(normal);
	return a.x > a.y && a.x > a.z ? float3(sign(normal.x), 0.0f, 0.0f) : (a.y > a.z ? 
		float3(0.0f, sign(normal.y), 0.0f) : float3(0.0f, 0.0f, sign(normal.z)));
}

} // namespace math