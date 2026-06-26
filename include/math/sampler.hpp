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
 * @brief Common texture (image) sampler functions.
 */

#pragma once
#include "math/vector.hpp"

namespace math
{

/**
 * @brief Texture (image) sampler 4D. (Includes 3D textures and mipmap levels)
 */
class Sampler4D
{
	u32x4 size = u32x4::zero;
	const void* const* mips = nullptr;
	uint32 layerSize = 0;
public:
	/**
	 * @brief Creates a new 4D texture (image) sampler.
	 *
	 * @param[in] mips target texture mipmap pixel data
	 * @param size target texture 3D size in texels
	 * @param mipCount texture mipmap level count
	 */
	Sampler4D(const void* const* mips, uint3 size, uint8 mipCount = 1) noexcept :
		mips(mips), size(size.x, size.y, size.z, mipCount), layerSize(size.x * size.y)
	{
		assert(mips);
		assert(areAllTrue(size > uint3::zero));
		assert(mipCount > 0);

		#ifndef NDEBUG
		for (uint8 mip = 0; mip < mipCount; mip++)
			assert((psize)mips[mip] % sizeof(f32x4) == 0);
		#endif
	}

	/**
	 * @brief Returns texel at specified position and mip level.
	 *
	 * @param position texel 3D position and mipmap level
	 * @param mip texture mipmap level (default = 0)
	 * @tparam T type of the texture pixel
	 */
	template<class T = f32x4>
	T get(uint3 position, uint8 mip) const noexcept
	{
		mip = std::min(mip, (uint8)(size.getW() - 1));
		auto mipSize = calcSizeAtMip3(size, mip);
		auto p = min((u32x4)position, (u32x4)mipSize - 1);
		auto layerSize = mipSize.getX() * mipSize.getY();
		auto index = (psize)p.getZ() * layerSize + p.getY() * mipSize.getX() + p.getX();
		return ((const T*)mips[mip])[index];
	}

	/**
	 * @brief Samples nearest texel from an image.
	 *
	 * @param uv 3D texture coordinates where to sample
	 * @param mip mipmap level to sample (default = 0.0)
	 * @param repeatMode clamp to border or repeat sampling mode
	 * @tparam T type of the texture pixel
	 */
	template<class T = f32x4>
	T sampleNearest(float3 uv, float mip, bool repeatMode = false) const noexcept
	{
		auto texCoords = repeatMode ? (f32x4)uv - floor((f32x4)uv) : 
			max(f32x4(uv.x, uv.y, uv.z, mip), f32x4::zero);
		return get<T>((uint3)(u32x4)texCoords, (uint8)texCoords.getW());
	}
};

/***********************************************************************************************************************
 * @brief Texture (image) sampler 3D.
 */
class Sampler3D
{
	u32x4 size = u32x4::zero;
	const void* texels = nullptr;
	uint32 layerSize = 0;
public:
	/**
	 * @brief Creates a new 3D texture (image) sampler.
	 *
	 * @param[in] texels target texture texel data
	 * @param size target texture 3D size in texels
	 * @param mipCount texture mipmap level count
	 */
	Sampler3D(const void* texels, uint3 size) noexcept :
		texels(texels), size(size), layerSize(size.x * size.y)
	{
		assert(texels);
		assert((psize)texels % sizeof(f32x4) == 0);
		assert(areAllTrue(size > uint3::zero));
	}

	/**
	 * @brief Returns texel at specified position.
	 *
	 * @param position texel 3D position and mipmap level
	 * @tparam T type of the texture pixel
	 */
	template<class T = f32x4>
	T get(uint3 position) const noexcept
	{
		auto p = min((u32x4)position, (u32x4)size - 1);
		auto index = (psize)p.getZ() * layerSize + p.getY() * size.getX() + p.getX();
		return ((const T*)texels)[index];
	}

	/**
	 * @brief Samples nearest texel from an image.
	 *
	 * @param uv 3D texture coordinates where to sample
	 * @param repeatMode clamp to border or repeat sampling mode
	 * @tparam T type of the texture pixel
	 */
	template<class T = f32x4>
	T sampleNearest(float3 uv, bool repeatMode = false) const noexcept
	{
		auto texCoords = repeatMode ? (f32x4)uv - floor((f32x4)uv) : max((f32x4)uv, f32x4::zero);
		return get<T>((uint3)(u32x4)texCoords);
	}
};

/***********************************************************************************************************************
 * @brief Texture (image) sampler 2D.
 */
class Sampler2D
{
	uint2 size = uint2::zero;
	const void* texels = nullptr;
public:
	/**
	 * @brief Creates a new 2D texture (image) sampler.
	 *
	 * @param[in] texels target texture texel data
	 * @param size target texture 3D size in texels
	 * @param mipCount texture mipmap level count
	 */
	Sampler2D(const void* texels, uint3 size) noexcept : texels(texels), size(size)
	{
		assert(texels);
		assert((psize)texels % sizeof(f32x4) == 0);
		assert(areAllTrue(size > uint3::zero));
	}

	/**
	 * @brief Returns texel at specified position.
	 *
	 * @param position texel 2D position and mipmap level
	 * @tparam T type of the texture pixel
	 */
	template<class T = f32x4>
	T get(uint2 position) const noexcept
	{
		auto p = min(position, (uint2)size - 1);
		auto index = p.y * size.x + p.x;
		return ((const T*)texels)[index];
	}

	/**
	 * @brief Samples nearest texel from an image.
	 *
	 * @param uv 2D texture coordinates where to sample
	 * @param repeatMode clamp to border or repeat sampling mode
	 * @tparam T type of the texture pixel
	 */
	template<class T = f32x4>
	T sampleNearest(float2 uv, bool repeatMode = false) const noexcept
	{
		auto texCoords = repeatMode ? uv - floor(uv) : max(uv, float2::zero);
		return get<T>((uint2)texCoords);
	}
};

// TODO: samplerLinear() bilinear ant trilinear

} // namespace math