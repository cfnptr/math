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
 * @brief Common version functions.
 */

#pragma once
#include "math/types.hpp"

#include <string>
#include <cstring>
#include <cassert>

namespace math
{

using namespace std;

/**
 * @brief Version information container.
 * @details Made of major, minor, patch and build parts.
 */
struct [[nodiscard]] Version
{
	uint8 major; /**< Major version part. */
	uint8 minor; /**< Minor version part. */
	uint8 patch; /**< Patch version part. */
	uint8 build; /**< Build version part. */

	/**
	 * @brief Creates a new version structure.
	 * 
	 * @param major version major part value
	 * @param minor version minor part value
	 * @param patch version patch part value
	 * @param build version build part value
	 */
	constexpr Version(uint8 major = 0, uint8 minor = 0, uint8 patch = 0, uint8 build = 0) noexcept :
		major(major), minor(minor), patch(patch), build(build) { }
	/**
	 * @brief Creates a new version structure from encoded data.
	 * @param version target version encoded data
	 */
	constexpr Version(uint32 version) noexcept :
		major((version >> 24u) & UINT8_MAX), minor((version >> 16u) & UINT8_MAX),
		patch((version >> 8u) & UINT8_MAX), build(version & UINT8_MAX) { }

	/**
	 * @brief Encodes version data to the integer value.
	 */
	constexpr explicit operator uint32() const noexcept
	{
		return ((uint32)major << 24u) | ((uint32)minor << 16u) | ((uint32)patch << 8u) | (uint32)build;
	}

	/**
	 * @brief Returns version part by the index.
	 * @param i target version part index
	 */
	uint8& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((uint8*)this)[i];
	}
	/**
	 * @brief Returns version part by the index.
	 * @param i target version part index
	 */
	uint8 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((uint8*)this)[i];
	}

	constexpr bool operator<(Version v) const noexcept { return (uint32)*this < (uint32)v; }
	constexpr bool operator>(Version v) const noexcept { return (uint32)*this > (uint32)v; }
	constexpr bool operator<=(Version v) const noexcept { return (uint32)*this <= (uint32)v; }
	constexpr bool operator>=(Version v) const noexcept { return (uint32)*this >= (uint32)v; }
	constexpr bool operator==(Version v) const noexcept { return (uint32)*this == (uint32)v; }
	constexpr bool operator!=(Version v) const noexcept { return (uint32)*this != (uint32)v; }
	
	/**
	 * @brief Creates a new version string. (X.X.X.X)
	 */
	string toString4() const noexcept
	{
		return to_string(major) + "." + to_string(minor) + "." + to_string(patch) + "." + to_string(build);
	}
	/**
	 * @brief Creates a new version string. (X.X.X)
	 */
	string toString3() const noexcept
	{
		return to_string(major) + "." + to_string(minor) + "." + to_string(patch);
	}
	/**
	 * @brief Creates a new version string. (X.X)
	 */
	string toString2() const noexcept
	{
		return to_string(major) + "." + to_string(minor);
	}
	/**
	 * @brief Creates a new version string. (X)
	 */
	string toString1() const noexcept
	{
		return to_string(major);
	}
};

} // namespace math