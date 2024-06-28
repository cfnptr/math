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

#pragma once
#include "math/types.hpp"
#include <string>

namespace math
{

using namespace std;

//**********************************************************************************************************************
template <typename T>
static string toHex(T value, psize length = sizeof(T) << 1)
{
	static const char* digits = "0123456789ABCDEF";
	string hex(length, '0');
	for (psize i = 0, j = (length - 1) * 4; i < length; i++, j -= 4)
		hex[i] = digits[(value >> j) & 0x0f];
	return hex;
}

static uint32 toInt32(const string& hex)
{
	return std::stoul(hex, nullptr, 16);
}
static uint64 toInt64(const string& hex)
{
	return std::stoull(hex, nullptr, 16);
}

} // namespace math