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
 * @brief Common spherical harmonics functions.
 * 
 * @details
 * Spherical harmonics (SH) are used to represent functions on the surface of a sphere, particularly for lighting and 
 * shading. SH allows for efficient approximations of complex lighting environments, such as image-based lighting 
 * (IBL), by encoding diffuse light and low-frequency details. SH are commonly used in precomputed radiance transfer 
 * (PRT) to achieve realistic lighting with low computational cost, especially for dynamic and global illumination in 
 * 3D scenes, enabling real-time performance in games.
 * 
 * Based on this project: https://google.github.io/filament/Filament.html
 */

#pragma once
#include "math/ibl.hpp"
#include "math/matrix.hpp"

// TODO: use SIMD where possible, but check if SH results are identical.

constexpr math::int32 sh2Count = 4;  /**< L1 spherical harmonics coefficient count. (2 * 2) */
constexpr math::int32 sh3Count = 9;  /**< L2 spherical harmonics coefficient count. (3 * 3) */
constexpr math::int32 sh4Count = 16; /**< L3 spherical harmonics coefficient count. (4 * 4) */

namespace math::sh
{

using namespace math::ibl;

#define M_SQRT_PI 1.77245385090551602729816748334114518
#define M_SQRT3   1.73205080756887729352744634150587237
#define M_SQRT5   2.23606797749978969640917366873127624
#define M_SQRT15  3.87298334620741688517926539978239961

/**
 * @brief Precomputed Lambertian reflection coefficients for the 3 band spherical harmonics.
 */
constexpr float ki3[sh3Count] =
{
	(float)0.886226925452757940959713778283912688,
	(float)1.023326707946488278722085851768497380,
	(float)1.023326707946488278722085851768497380,
	(float)1.023326707946488278722085851768497380,
	(float)0.143014255134963907956091588857816532,
	(float)0.286028510269927815912183177715633065,
	(float)0.495415912200751318295033343019895256,
	(float)0.286028510269927815912183177715633065,
	(float)0.143014255134963907956091588857816532
};

static constexpr int32 shIndex(int32 m, int32 l) noexcept
{
	return l * (l + 1) + m;
}

static float sphereQuadrantArea(float x, float y) noexcept
{
	return atan2(x * y, length(float3(x, y, 1.0f)));
}
static float calcSolidAngle(float2 st, float invDim) noexcept
{
	auto v0 = st - invDim, v1 = st + invDim;
	return sphereQuadrantArea(v0.x, v0.y) - sphereQuadrantArea(v0.x, v1.y) -
		sphereQuadrantArea(v1.x, v0.y) + sphereQuadrantArea(v1.x, v1.y);
}
static float calcSolidAngleFast(float2 st, float invDim) noexcept
{
	auto r2 = dot(st, st) + 1.0f;
	return (invDim * invDim * 4.0f) / (r2 * std::sqrt(r2));
}
static float calcSolidAngleFastA(float2 st, float area) noexcept
{
	auto r2 = dot(st, st) + 1.0f;
	return area / (r2 * std::sqrt(r2));
}

//**********************************************************************************************************************
static void computeShBasis(float3 n, float* shb, int32 bandCount) noexcept
{
	auto pml2 = 0.0f, pml1 = 1.0f;
	shb[0] = pml1;

	for (int32 l = 1; l < bandCount; l++)
	{
		auto pml = ((l * 2 - 1) * pml1 * 
			n.z - (l - 1) * pml2) / l;
		pml2 = pml1; pml1 = pml;
		shb[shIndex(0, l)] = pml;
	}

	auto pmm = 1.0f;
	for (int32 m = 1; m < bandCount; m++)
	{
		pmm = (1 - m * 2) * pmm;
		pml2 = pmm; pml1 = (m * 2 + 1) * pmm * n.z;

		shb[shIndex(-m, m)] = pml2;
		shb[shIndex( m, m)] = pml2;

		if (m + 1 < bandCount)
		{
			shb[shIndex(-m, m + 1)] = pml1;
			shb[shIndex( m, m + 1)] = pml1;
		}
	}

	auto cm = n.x, sm = n.y;
	for (int32 m = 1; m <= bandCount; m++)
	{
		for (int32 l = m; l < bandCount; l++)
		{
			shb[shIndex(-m, l)] *= sm;
			shb[shIndex( m, l)] *= cm;
		}

		auto cm1 = cm * n.x - sm * n.y;
		auto sm1 = sm * n.x + cm * n.y;
		cm = cm1; sm = sm1;
	}
}

static void computeSh3Basis(float3 n, float shb[sh3Count]) noexcept
{
	auto pml1 = n.z * -3.0f;
	shb[0] = 1.0f;                                   // l = 0, m =  0
	shb[1] = n.y * -1.0f;                            // l = 1, m = -1
	shb[2] = n.z;                                    // l = 1, m =  0
	shb[3] = n.x * -1.0f;                            // l = 1, m =  1
	shb[4] = std::fma(n.y, n.x, n.x * n.y) * 3.0f;   // l = 2, m = -2
	shb[5] = n.y * pml1;                             // l = 2, m = -1
	shb[6] = std::fma(n.z * n.z, 3.0f, -1.0) * 0.5f; // l = 2, m =  0
	shb[7] = n.x * pml1;                             // l = 2, m =  1
	shb[8] = (n.x * n.x - n.y * n.y) * 3.0f;         // l = 2, m =  2
}
// TODO: SH2, SH4.

static void projectVecToSH2K(float3 s, float r[5]) noexcept
{
	r[0] = s.y * s.x;
	r[1] = -(s.y * s.z);
	r[2] = std::fma(s.z * s.z, 3.0f, -1.0f) * float(1.0 / (M_SQRT3 * 2.0));
	r[3] = -(s.z * s.x);
	r[4] = (s.x * s.x - s.y * s.y) * 0.5f;
}
static void multiply(const float m[25], const float v[5], float r[5]) noexcept
{
	r[0] = m[0] * v[0] + m[5] * v[1] + m[10] * v[2] + m[15] * v[3] + m[20] * v[4];
	r[1] = m[1] * v[0] + m[6] * v[1] + m[11] * v[2] + m[16] * v[3] + m[21] * v[4];
	r[2] = m[2] * v[0] + m[7] * v[1] + m[12] * v[2] + m[17] * v[3] + m[22] * v[4];
	r[3] = m[3] * v[0] + m[8] * v[1] + m[13] * v[2] + m[18] * v[3] + m[23] * v[4];
	r[4] = m[4] * v[0] + m[9] * v[1] + m[14] * v[2] + m[19] * v[3] + m[24] * v[4];
}

//**********************************************************************************************************************
static float3 rotateShBand1(float3 band1, const float3x3& m) noexcept
{
	constexpr auto invA1TimesK = float3x3(0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f);
    auto mn0 = m[0], mn1 = m[1], mn2 = m[2];
	auto r1OverK = float3x3(-mn0.y, mn0.z, -mn0.x, -mn1.y, mn1.z, -mn1.x, -mn2.y, mn2.z, -mn2.x);
	return r1OverK * (invA1TimesK * band1);
}
static void rotateShBand2(const float band2[5], const float3x3& m, float r[5]) noexcept
{
	static constexpr float invAtimesK[25] =
	{
		 0.0f,           1.0f, 2.0f,  0.0f,  0.0f,
		-1.0f,           0.0f, 0.0f,  0.0f, -2.0f,
		 0.0f, (float)M_SQRT3, 0.0f,  0.0f,  0.0f,
		 1.0f,           1.0f, 0.0f, -2.0f,  0.0f,
		 2.0f,           1.0f, 0.0f,  0.0f,  0.0f
	};

	float invATimesKTimesBand2[5];
	multiply(invAtimesK, band2, invATimesKTimesBand2);

	float p0[5], p1[5], p2[5], p3[5], p4[5];
	projectVecToSH2K(m[0], p0); projectVecToSH2K(m[2], p1);
	projectVecToSH2K((m[0] + m[1]) * (float)M_SQRT1_2, p2);
	projectVecToSH2K((m[0] + m[2]) * (float)M_SQRT1_2, p3);
	projectVecToSH2K((m[1] + m[2]) * (float)M_SQRT1_2, p4);

	float rOverK[25] =
	{
		p0[0], p0[1], p0[2], p0[3], p0[4],
		p1[0], p1[1], p1[2], p1[3], p1[4],
		p2[0], p2[1], p2[2], p2[3], p2[4],
		p3[0], p3[1], p3[2], p3[3], p3[4],
		p4[0], p4[1], p4[2], p4[3], p4[4]
	};

	multiply(rOverK, invATimesKTimesBand2, r);
}
static void rotateSh3Bands(const float shw[sh3Count], const float3x3& m, float r[sh3Count]) noexcept
{
	auto b0 = shw[0]; auto band1 = float3(shw[1], shw[2], shw[3]);
	auto b1 = rotateShBand1(band1, m);
	float band2[5] = { shw[4], shw[5], shw[6], shw[7], shw[8] };
	float b2[5]; rotateShBand2(band2, m, b2);
	r[0] = b0; r[1] = b1[0]; r[2] = b1[1]; r[3] = b1[2]; r[4] = b2[0]; 
	r[5] = b2[1]; r[6] = b2[2]; r[7] = b2[3]; r[8] = b2[4];
}

//**********************************************************************************************************************
static float sincShWindow(int32 l, float w) noexcept
{
	if (l == 0) return 1.0f;
	else if (l >= w) return 0.0f;
	auto x = (l * (float)M_PI) / w;
	x = std::sin(x) / x;
	return x * x * x * x;
}
static void shWindowing(float* shw, float cutoff, int32 bandCount) noexcept
{
	for (int32 l = 0; l < bandCount; l++)
	{
		auto w = sincShWindow(l, cutoff);
		shw[shIndex(0, l)] *= w;

		for (int32 m = 1; m <= l; m++)
		{
			shw[shIndex(-m, l)] *= w;
			shw[shIndex(m, l)]  *= w;
		}
	}
}
static float shMin3(float shw[sh3Count]) noexcept
{
	static constexpr float ca[sh3Count] =
	{
		(float)( 1.0      / (2.0 * M_SQRT_PI)),
		(float)(-M_SQRT3  / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT3  / (2.0 * M_SQRT_PI)),
		(float)(-M_SQRT3  / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT15 / (2.0 * M_SQRT_PI)),
		(float)(-M_SQRT15 / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT5  / (4.0 * M_SQRT_PI)),
		(float)(-M_SQRT15 / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT15 / (4.0 * M_SQRT_PI))
	};

	auto dir = normalize(float3(-shw[3], -shw[1], shw[2]));
	auto zAxis = -dir;
	auto xAxis = normalize(cross(zAxis, float3(0.0f, 1.0f, 0.0f)));
	auto yAxis = cross(xAxis, zAxis);
	auto m = transpose(float3x3(xAxis, yAxis, -zAxis));
	rotateSh3Bands(shw, m, shw);

	auto m2max = ca[8] * std::sqrt(shw[8] * shw[8] + shw[4] * shw[4]);
	auto a = std::fma(ca[6] * shw[6], 3.0f, m2max);
	auto b = ca[2] * shw[2], c = ca[0] * shw[0] - ca[6] * shw[6] - m2max;

	auto zMin = b / (a * -2.0f);
	auto m0minZ = std::fma(zMin * zMin, a, std::fma(b, zMin, c));
	auto m0minB = std::min(a + b + c, a - b + c);
	auto m0min = (a > 0.0f && zMin >= -1.0f && zMin <= 1.0f) ? m0minZ : m0minB;
	auto d = ca[4] * std::sqrt(shw[5] * shw[5] + shw[7] * shw[7]);

	auto minimum = std::fma(d, -0.5f, m0min);
	if (minimum < 0.0f)
	{
		auto dz = 0.0f, z = (float)-M_SQRT1_2;
		do
		{
			minimum = std::fma(z * z, a, std::fma(b, z, c)) + (d * z * std::sqrt(1.0f - z * z));
			dz = std::fma(z, z, -1.0f) * (std::fma(d * z * z, -2.0f, d) + std::fma(a * z, 2.0f, b) * std::sqrt(1.0f - z * z)) / 
				std::fma(a * std::pow(1.0f - z * z, 1.5f), -2.0f, std::fma(d * z, 3.0f, d * z * z * z * -2.0f));
			z = z - dz;
		} while (std::abs(z) <= 1.0f && std::abs(dz) > 1e-5f);

		if (std::abs(z) > 1.0f)
			minimum = std::min(a + b + c, a - b + c);
	}

	return minimum;
}

//**********************************************************************************************************************
static void applyKiSh3(f32x4 sh[sh3Count]) noexcept
{
	for (uint32 i = 0; i < sh3Count; i++)
		sh[i] *= ki3[i];
}
static void deringSh3(f32x4 sh[sh3Count]) noexcept
{
	constexpr int32 bandCount = 3;
	auto cutoff = (float)(bandCount * 4 + 1);
	float shw[sh3Count];

	for (uint32 channel = 0; channel < 3; channel++)
	{
		for (uint32 i = 0; i < sh3Count; i++)
			shw[i] = sh[i][channel];

		float l = bandCount, r = cutoff;
		for (uint32 i = 0; i < 16 && l + 0.1f < r; i++)
		{
			float m = (l + r) * 0.5f;
			shWindowing(shw, m, bandCount);
			if (shMin3(shw) < 0.0f) r = m;
			else l = m;
			cutoff = std::min(cutoff, l);
		}
	}

	for (int32 l = 0; l < bandCount; l++)
	{
		auto w = sincShWindow(l, cutoff);
		sh[shIndex(0, l)] *= w;

		for (int32 m = 1; m <= l; m++)
		{
			sh[shIndex(-m, l)] *= w;
			sh[shIndex(m, l)] *= w;
		}
	}
}
// TODO: make sure it produces correct result: https://github.com/google/filament/blob/main/libs/ibl/src/CubemapSH.cpp

static void preprocessSh3(f32x4 sh[sh3Count]) noexcept
{
	static constexpr float ca[sh3Count] =
	{
		(float)( 1.0      / (2.0 * M_SQRT_PI)),
		(float)(-M_SQRT3  / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT3  / (2.0 * M_SQRT_PI)),
		(float)(-M_SQRT3  / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT15 / (2.0 * M_SQRT_PI)),
		(float)(-M_SQRT15 / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT5  / (4.0 * M_SQRT_PI)),
		(float)(-M_SQRT15 / (2.0 * M_SQRT_PI)),
		(float)( M_SQRT15 / (4.0 * M_SQRT_PI))
	};

	for (uint32 i = 0; i < sh3Count; i++)
		sh[i] *= ca[i];
}

} // namespace math::sh