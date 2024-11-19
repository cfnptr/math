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

namespace math
{

/***********************************************************************************************************************
 * @brief Declares enum class common operators. (|, &, |=, &=, !, ~, ^, hasAnyFlag, hasOneFlag)
 */
#define DECLARE_ENUM_CLASS_FLAG_OPERATORS(enumType)                     \
static constexpr enumType operator|(enumType a, enumType b) noexcept    \
{                                                                       \
	return (enumType)((uint64)a | (uint64)b);                           \
}                                                                       \
static constexpr enumType operator&(enumType a, enumType b) noexcept    \
{                                                                       \
	return (enumType)((uint64)a & (uint64)b);                           \
}                                                                       \
static constexpr enumType operator^(enumType a, enumType b) noexcept    \
{                                                                       \
	return (enumType)((uint64)a ^ (uint64)b);                           \
}                                                                       \
static constexpr enumType operator!(enumType a) noexcept                \
{                                                                       \
	return (enumType)!((uint64)a);                                      \
}                                                                       \
static constexpr enumType operator~(enumType a) noexcept                \
{                                                                       \
	return (enumType)~((uint64)a);                                      \
}                                                                       \
static constexpr enumType& operator|=(enumType& a, enumType b) noexcept \
{                                                                       \
	return a = a | b;                                                   \
}                                                                       \
static constexpr enumType& operator&=(enumType& a, enumType b) noexcept \
{                                                                       \
	return a = a & b;                                                   \
}                                                                       \
static constexpr enumType& operator^=(enumType& a, enumType b) noexcept \
{                                                                       \
	return a = a ^ b;                                                   \
}                                                                       \
static constexpr bool hasAnyFlag(enumType a, enumType flags) noexcept   \
{                                                                       \
	return (uint64)(a & flags);                                         \
}                                                                       \
static constexpr bool hasOneFlag(enumType a, enumType flag) noexcept    \
{                                                                       \
	return (uint64)(a & flag) == (uint64)a;                             \
}

} // namespace math