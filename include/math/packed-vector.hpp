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
 * @brief Common packed vector functions.
 */

// TODO: pack odd bit sizes.

#pragma once
#include "math/types.hpp"

#include <vector>
#include <cstdlib>

namespace math
{

/**
 * @brief Packed bits container. (Based on the @ref std::vector)
 * @tparam Bits number of bits per element.
 */
template<int Bits = 1>
class PackedVector final : public std::vector<uint8>
{
private:
	uint8* ptr = nullptr;
public:
	/**
	 * @brief Creates a new packed vector container.
	 */
	PackedVector()
	{
		static_assert(Bits > 0, "Should be at least 1 bit.");
		static_assert(Bits == 1 || Bits == 2 || Bits == 4, "Partial support of packing.");
		ptr = data();
	}
	/**
	 * @brief Creates a new packed vector container with specified size.
	 * @param elementCount target array element count
	 */
	PackedVector(psize elementCount)
	{
		static_assert(Bits > 0, "Should be at least 1 bit.");
		static_assert(Bits == 1 || Bits == 2 || Bits == 4, "Partial support of packing.");
		resize(elementCount);
	}

	/**
	 * @brief Returns packed vector element at specified index. (No asserts!)
	 * @param i target element index in the array
	 */
	uint8 unsafeGet(psize i) const noexcept
	{
		if constexpr (Bits == 1)
		{
			return (ptr[i / 8] >> (uint8)(i % 8)) & (uint8)0x01;
		}
		else if constexpr (Bits == 2)
		{
			return (ptr[i / 4] >> (uint8)((i % 4) * 2)) & (uint8)0x03;
		}
		else if constexpr (Bits == 4)
		{
			return (ptr[i / 2] >> (uint8)((i % 2) * 4)) & (uint8)0x0F;
		}
		abort();
	}
	/**
	 * @brief Returns packed vector element at specified index.
	 * @param i target element index in the array
	 */
	uint8 get(psize i) const noexcept
	{
		if constexpr (Bits == 1)
			assert(i / 8 < size());
		else if constexpr (Bits == 2)
			assert(i / 4 < size());
		else if constexpr (Bits == 4)
			assert(i / 8 < size());
		return unsafeGet(i);
	}

	/**
	 * @brief Sets packed vector element at specified index. (No asserts!)
	 *
	 * @param i target element index in the array
	 * @param value element value to set
	 */
	void unsafeSet(psize i, uint8 value) noexcept
	{
		if constexpr (Bits == 1)
		{
			auto& b = ptr[i / 8]; auto shift = (uint8)(i % 8);
			b = (b & ~((uint8)0x01 << shift)) | ((value & (uint8)0x01) << shift);
		}
		else if constexpr (Bits == 2)
		{
			auto& b = ptr[i / 4]; auto shift = (uint8)((i % 4) * 2);
			b = (b & ~((uint8)0x03 << shift)) | ((value & (uint8)0x03) << shift);
		}
		else if constexpr (Bits == 4)
		{
			auto& b = ptr[i / 2]; auto shift = (uint8)((i % 2) * 4);
			b = (b & ~((uint8)0x0F << shift)) | ((value & (uint8)0x0F) << shift);
		}
	}
	/**
	 * @brief Returns packed vector element at specified index.
	 *
	 * @param i target element index in the array
	 * @param value element value to set
	 */
	uint8 set(psize i, uint8 value) noexcept
	{
		if constexpr (Bits == 1)
			assert(i / 8 < size());
		else if constexpr (Bits == 2)
			assert(i / 4 < size());
		else if constexpr (Bits == 4)
			assert(i / 8 < size());
		return unsafeSet(i, value);
	}

	/**
	 * @brief Resizes packed vector array.
	 * @param elementCount target array element count
	 */
	void resize(psize elementCount)
	{
		if constexpr (Bits == 1)
			std::vector<uint8>::resize(elementCount / 8 + (elementCount % 8 != 0 ? 1 : 0));
		else if constexpr (Bits == 2)
			std::vector<uint8>::resize(elementCount / 4 + (elementCount % 4 != 0 ? 1 : 0));
		else if constexpr (Bits == 4)
			std::vector<uint8>::resize(elementCount / 2 + (elementCount % 2 != 0 ? 1 : 0));
		ptr = data();
	}
};

} // namespace math