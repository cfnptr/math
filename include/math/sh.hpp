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
#include "math/ibl.hpp"
#include "math/matrix.hpp"

// Spherical Harmonics
namespace math::sh
{

using namespace math;
using namespace math::ibl;

//------------------------------------------------------------------------------------------------------------
#define M_SQRT_PI  1.77245385090551602729816748334114518
#define M_SQRT3    1.73205080756887729352744634150587237
#define M_SQRT5    2.23606797749978969640917366873127624
#define M_SQRT15   3.87298334620741688517926539978239961

// Precomputed for the 3 band SH.
static const float ki[shCoefCount] =
{
	(float)0.886226925452757940959713778283912688,
	(float)1.02332670794648827872208585176849738,
	(float)1.02332670794648827872208585176849738,
	(float)1.02332670794648827872208585176849738,
	(float)0.143014255134963907956091588857816532,
	(float)0.286028510269927815912183177715633065,
	(float)0.495415912200751318295033343019895256,
	(float)0.286028510269927815912183177715633065,
	(float)0.143014255134963907956091588857816532
};

static int32 shIndex(int32 m, int32 l) noexcept
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

//------------------------------------------------------------------------------------------------------------
static void computeShBasis(const float3& s, float shb[shCoefCount]) noexcept
{
	auto pml2 = 0.0f, pml1 = 1.0f;
	shb[0] = pml1;

	for (int32 l = 1; l < shBandCount; l++)
	{
		auto pml = ((2 * l - 1) * pml1 * s.z - (l - 1) * pml2) / l;
		pml2 = pml1; pml1 = pml;
		shb[shIndex(0, l)] = pml;
	}

	auto pmm = 1.0f;
	for (int32 m = 1; m < shBandCount; m++)
	{
		pmm = (1 - 2 * m) * pmm;
		pml2 = pmm; pml1 = (2 * m + 1) * pmm * s.z;

		shb[shIndex(-m, m)] = pml2;
		shb[shIndex( m, m)] = pml2;

		if (m + 1 < shBandCount)
		{
			shb[shIndex(-m, m + 1)] = pml1;
			shb[shIndex( m, m + 1)] = pml1;
		}
	}

	auto cm = s.x, sm = s.y;
	for (int32 m = 1; m <= shBandCount; m++)
	{
		for (int32 l = m; l < shBandCount; l++)
		{
			shb[shIndex(-m, l)] *= sm;
			shb[shIndex( m, l)] *= cm;
		}

		auto cm1 = cm * s.x - sm * s.y;
		auto sm1 = sm * s.x + cm * s.y;
		cm = cm1; sm = sm1;
	}
}

//------------------------------------------------------------------------------------------------------------
static void projectVecToSH2K(const float3& s, float r[5]) noexcept
{
	r[0] = s.y * s.x;
	r[1] = -(s.y * s.z);
	r[2] = 1.0f / (2.0f * (float)M_SQRT3) * ((3.0f * s.z * s.z - 1.0f));
	r[3] = -(s.z * s.x);
	r[4] = 0.5f * (s.x * s.x - s.y * s.y);
}
static void multiply(const float m[25], const float v[5], float r[5]) noexcept
{
	r[0] = m[0] * v[0] + m[5] * v[1] + m[10] * v[2] + m[15] * v[3] + m[20] * v[4];
	r[1] = m[1] * v[0] + m[6] * v[1] + m[11] * v[2] + m[16] * v[3] + m[21] * v[4];
	r[2] = m[2] * v[0] + m[7] * v[1] + m[12] * v[2] + m[17] * v[3] + m[22] * v[4];
	r[3] = m[3] * v[0] + m[8] * v[1] + m[13] * v[2] + m[18] * v[3] + m[23] * v[4];
	r[4] = m[4] * v[0] + m[9] * v[1] + m[14] * v[2] + m[19] * v[3] + m[24] * v[4];
}

//------------------------------------------------------------------------------------------------------------
static float3 rotateSphericalHarmonicBand1(const float3& band1, const float3x3& m) noexcept
{
	static const auto invA1TimesK = float3x3(
		 0.0f, -1.0f,  0.0f,
		 0.0f,  0.0f,  1.0f,
		-1.0f,  0.0f,  0.0f
	);

    auto mn0 = m[0];
    auto mn1 = m[1];
    auto mn2 = m[2];

	auto r1OverK = float3x3(
		-mn0.y, mn0.z, -mn0.x,
		-mn1.y, mn1.z, -mn1.x,
		-mn2.y, mn2.z, -mn2.x
	);

	return r1OverK * (invA1TimesK * band1);
}
static void rotateSphericalHarmonicBand2(const float band2[5], const float3x3& m, float r[5]) noexcept
{
	static const float invATimesK[25] =
	{
		 0.0f,           1.0f, 2.0f,  0.0f,  0.0f,
		-1.0f,           0.0f, 0.0f,  0.0f, -2.0f,
		 0.0f, (float)M_SQRT3, 0.0f,  0.0f,  0.0f,
		 1.0f,           1.0f, 0.0f, -2.0f,  0.0f,
		 2.0f,           1.0f, 0.0f,  0.0f,  0.0f
	};

	float invATimesKTimesBand2[5];
	multiply(invATimesK, band2, invATimesKTimesBand2);

	float p0[5], p1[5], p2[5], p3[5], p4[5];
	projectVecToSH2K(m[0], p0);
	projectVecToSH2K(m[2], p1);
	projectVecToSH2K((float)M_SQRT1_2 * (m[0] + m[1]), p2);
	projectVecToSH2K((float)M_SQRT1_2 * (m[0] + m[2]), p3);
	projectVecToSH2K((float)M_SQRT1_2 * (m[1] + m[2]), p4);

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
static void rotateSh3Bands(const float shw[shCoefCount], const float3x3& m, float r[shCoefCount]) noexcept
{
	auto b0 = shw[0];
	auto band1 = float3(shw[1], shw[2], shw[3]);
	auto b1 = rotateSphericalHarmonicBand1(band1, m);
	float band2[5] = { shw[4], shw[5], shw[6], shw[7], shw[8] }; float b2[5];
	rotateSphericalHarmonicBand2(band2, m, b2);
	r[0] = b0; r[1] = b1[0]; r[2] = b1[1]; r[3] = b1[2];
	r[4] = b2[0]; r[5] = b2[1]; r[6] = b2[2]; r[7] = b2[3]; r[8] = b2[4];
}

//------------------------------------------------------------------------------------------------------------
static float sincWindow(int32 l, float w) noexcept
{
	if (l == 0)
		return 1.0f;
	else if (l >= w)
		return 0.0f;
	auto x = ((float)M_PI * l) / w;
	x = std::sin(x) / x;
	return x * x * x * x;
}
static void windowing(float shw[shCoefCount], float cutoff) noexcept
{
	for (int32 l = 0; l < shBandCount; l++)
	{
		auto w = sincWindow(l, cutoff);
		shw[shIndex(0, l)] *= w;

		for (int32 m = 1; m <= l; m++)
		{
			shw[shIndex(-m, l)] *= w;
			shw[shIndex(m, l)]  *= w;
		}
	}
}
static float shmin(float shw[shCoefCount]) noexcept
{
	static const float ca[shCoefCount] =
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
	auto a = 3.0f * ca[6] * shw[6] + m2max;
	auto b = ca[2] * shw[2];
	auto c = ca[0] * shw[0] - ca[6] * shw[6] - m2max;

	auto zmin = -b / (2.0f * a);
	auto m0minZ = a * zmin * zmin + b * zmin + c;
	auto m0minB = std::min(a + b + c, a - b + c);
	auto m0min = (a > 0 && zmin >= -1.0f && zmin <= 1.0f) ? m0minZ : m0minB;
	auto d = ca[4] * std::sqrt(shw[5] * shw[5] + shw[7] * shw[7]);

	auto minimum = m0min - 0.5f * d;
	if (minimum < 0.0f)
	{
		auto dz = 0.0f;
		auto z = (float)-M_SQRT1_2;

		do
		{
			minimum = (a * z * z + b * z + c) + (d * z * std::sqrt(1.0f - z * z));
			dz = (z * z - 1.0f) * (d - 2.0f * d * z * z + (b + 2.0f * a * z) *
				std::sqrt(1.0f - z * z)) / (3.0f * d * z - 2.0f * d * z * z * z -
				2.0f * a * std::pow(1.0f - z * z, 1.5f));
			z = z - dz;
		} while (std::abs(z) <= 1.0 && std::abs(dz) > 1e-5f);

		if (std::abs(z) > 1.0f)
			minimum = std::min(a + b + c, a - b + c);
	}

	return minimum;
}

//------------------------------------------------------------------------------------------------------------
static void deringingSH(float4 sh[shCoefCount]) noexcept
{
	auto cutoff = (float)(shBandCount * 4 + 1);
	float shw[shCoefCount];

	for (uint32 channel = 0; channel < 3; channel++)
	{
		for (uint32 i = 0; i < shCoefCount; i++)
			shw[i] = sh[i][channel];

		float l = shBandCount;
		float r = cutoff;

		for (uint32 i = 0; i < 16 && l + 0.1f < r; i++)
		{
			float m = 0.5f * (l + r);
			windowing(shw, m);
			if (shmin(shw) < 0.0f)
				r = m;
			else
				l = m;
			cutoff = std::min(cutoff, l);
		}
	}

	for (int32 l = 0; l < shBandCount; l++)
	{
		float w = sincWindow(l, cutoff);
		sh[shIndex(0, l)] *= w;

		for (int m = 1; m <= l; m++)
		{
			sh[shIndex(-m, l)] *= w;
			sh[shIndex(m, l)] *= w;
		}
	}
}

//------------------------------------------------------------------------------------------------------------
static void shaderPreprocessSH(float4 sh[shCoefCount]) noexcept
{
	static const float ca[shCoefCount] =
	{
		(float)( 1.0      / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)(-M_SQRT3  / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)( M_SQRT3  / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)(-M_SQRT3  / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)( M_SQRT15 / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)(-M_SQRT15 / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)( M_SQRT5  / (4.0 * M_SQRT_PI) * M_1_PI),
		(float)(-M_SQRT15 / (2.0 * M_SQRT_PI) * M_1_PI),
		(float)( M_SQRT15 / (4.0 * M_SQRT_PI) * M_1_PI)
	};
	
	for (uint32 i = 0; i < shCoefCount; i++)
		sh[i] *= ca[i];
}

} // namespace math::sh