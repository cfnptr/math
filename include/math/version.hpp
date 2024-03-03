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
#include "math/types.hpp"

#include <string>
#include <cassert>

namespace math
{

using namespace std;

//------------------------------------------------------------------------------------------------------------
struct Version
{
	uint8 major = 0;
	uint8 minor = 0;
	uint8 patch = 0;
	uint8 build = 0;

	Version(uint8 major = 0, uint8 minor = 0, uint8 patch = 0, uint8 build = 0)
	{
		this->major = major; this->minor = minor;
		this->patch = patch; this->build = build;
	}
	Version(uint32 version)
	{
		this->major = (version >> 24u) & UINT8_MAX;
		this->minor = (version >> 16u) & UINT8_MAX;
		this->patch = (version >> 8u) & UINT8_MAX;
		this->build = version & UINT8_MAX;
	}

	explicit operator uint32() const noexcept
	{
		return ((uint32)major << 24u) | ((uint32)minor << 16u) | 
			((uint32)patch << 8u) | (uint32)build;
	}

	uint8& operator[](psize i) noexcept
	{
		assert(i <= 3);
		return ((uint8*)this)[i];
	}
	uint8 operator[](psize i) const noexcept
	{
		assert(i <= 3);
		return ((uint8*)this)[i];
	}

	bool operator==(Version v) const noexcept { return memcmp(this, &v, sizeof(Version)) == 0; }
	bool operator!=(Version v) const noexcept { return memcmp(this, &v, sizeof(Version)) != 0; }
	bool operator<(Version v) const noexcept { return (uint32)*this < (uint32)v; }
	bool operator>(Version v) const noexcept { return (uint32)*this > (uint32)v; }
	bool operator<=(Version v) const noexcept { return (uint32)*this <= (uint32)v; }
	bool operator>=(Version v) const noexcept { return (uint32)*this >= (uint32)v; }
		
	string toString4() const noexcept
	{
		return to_string(major) + "." + to_string(minor) + "." +
			to_string(patch) + "." + to_string(build);
	}
	string toString3() const noexcept
	{
		return to_string(major) + "." + to_string(minor) + "." + to_string(patch);
	}
	string toString2() const noexcept
	{
		return to_string(major) + "." + to_string(minor);
	}
	string toString1() const noexcept
	{
		return to_string(major);
	}
};

} // namespace math