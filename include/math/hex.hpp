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

#pragma once
#include "math/types.hpp"
#include <string>

namespace math
{

using namespace std;

static constexpr const char* hexDigits = "0123456789ABCDEF"; /**< Hexadecimal digits array. */

/**
 * @brief Converts integer value to the hexadecimal string.
 * 
 * @tparam T integer value type
 * @param value target integer value
 * @param length hexadecimal string length
 */
template <typename T>
static string toHex(T value, psize length = sizeof(T) << 1) noexcept
{
	string hex(length, '0');
	for (psize i = 0, j = (length - 1) * 4; i < length; i++, j -= 4)
		hex[i] = hexDigits[(value >> j) & 0x0F];
	return hex;
}
/**
 * @brief Converts integer array to the hexadecimal string.
 * 
 * @tparam T integer value type
 * @param[in] data target integer array
 * @param size integer array size
 */
template <typename T>
static string toHex(const T* data, psize size) noexcept
{
	constexpr auto length = sizeof(T) << 1;
	string hex(size * length, '0');
	for (uint32 n = 0; n < size; n++)
	{
		auto offset = n * length; auto value = data[n];
		for (psize i = 0, j = (length - 1) * 4; i < length; i++, j -= 4)
			hex[i + offset] = hexDigits[(value >> j) & 0x0F];
	}
	return hex;
}
/**
 * @brief Converts binary data to the hexadecimal string.
 * 
 * @param[in] data target binary array
 * @param size array size in bytes
 */
static string toHex8(const uint8* data, psize size) noexcept
{
	auto count = size * 2; string hex(count, '0');
	for (psize i = 0; i < size; i++)
	{
        auto value = data[i];
        hex[i * 2    ] = hexDigits[value >> 4];
        hex[i * 2 + 1] = hexDigits[value & 0x0F];
    }
	return hex;
}

/***********************************************************************************************************************
 * @brief Converts hexadecimal string to the 32bit integer value.
 * @param[in] hex target hexadecimal string
 */
static uint32 toInt32(const string& hex) noexcept { return std::stoul(hex, nullptr, 16); }
/**
 * @brief Converts hexadecimal string to the 64bit integer value.
 * @param[in] hex target hexadecimal string
 */
static uint64 toInt64(const string& hex) noexcept { return std::stoull(hex, nullptr, 16); }

} // namespace math