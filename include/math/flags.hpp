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

namespace math
{

/***********************************************************************************************************************
 * @brief Declares enum class common operators. (|, &, |=, &=, !, ~, ^, hasAnyFlag, hasOneFlag)
 */
#define DECLARE_ENUM_CLASS_FLAG_OPERATORS(enumType)                              \
static constexpr enumType operator|(enumType a, enumType b) noexcept             \
{                                                                                \
	return (enumType)((uint64)a | (uint64)b);                                    \
}                                                                                \
static constexpr enumType operator&(enumType a, enumType b) noexcept             \
{                                                                                \
	return (enumType)((uint64)a & (uint64)b);                                    \
}                                                                                \
static constexpr enumType operator^(enumType a, enumType b) noexcept             \
{                                                                                \
	return (enumType)((uint64)a ^ (uint64)b);                                    \
}                                                                                \
static constexpr enumType operator!(enumType v) noexcept                         \
{                                                                                \
	return (enumType)!((uint64)v);                                               \
}                                                                                \
static constexpr enumType operator~(enumType v) noexcept                         \
{                                                                                \
	return (enumType)~((uint64)v);                                               \
}                                                                                \
static constexpr enumType& operator|=(enumType& a, enumType b) noexcept          \
{                                                                                \
	return a = a | b;                                                            \
}                                                                                \
static constexpr enumType& operator&=(enumType& a, enumType b) noexcept          \
{                                                                                \
	return a = a & b;                                                            \
}                                                                                \
static constexpr enumType& operator^=(enumType& a, enumType b) noexcept          \
{                                                                                \
	return a = a ^ b;                                                            \
}

/**
 * @brief Returns true if variable have any of specified flags.
 *
 * @tparam T type of the variable (enum or integer)
 * @param v target variable to check for flags
 * @param flags flag bitmask to check for
 */
template<class T = uint64>
static constexpr bool hasAnyFlag(T v, T flags) noexcept { return (uint64)(v & flags) ? true : false; }
/**
 * @brief Returns true if variable have only one specified flag.
 *
 * @tparam T type of the variable (enum or integer)
 * @param v target variable to check for flag
 * @param flags single flag to check for
 */
template<class T = uint64>
static constexpr bool hasOneFlag(T v, T flag) noexcept { return (v & flag) == v; }
/**
 * @brief Sets specified flags to the variable. (Enables flags)
 *
 * @tparam T type of the variable (enum or integer)
 * @param[in,out] v target variable to set
 * @param flags flag bitmask to set
 */
template<class T = uint64>
static constexpr void setFlags(T& v, T flags) noexcept { v |= flags; }
/**
 * @brief Sets or unsets specified flags in the variable.
 *
 * @tparam T type of the variable (enum or integer)
 * @param[in,out] v target variable to set or unset
 * @param flags flag bitmask to set or unset
 * @param enable to enable or disable flags
 */
template<class T = uint64>
static constexpr void setFlags(T& v, T flags, bool enable) noexcept { v = enable ? v | flags : v & (~flags); }
/**
 * @brief Unsets specified flags in the variable. (Disable flags)
 *
 * @tparam T type of the variable (enum or integer)
 * @param[in,out] v target variable to unset
 * @param flags flag bitmask to unset
 */
template<class T = uint64>
static constexpr void unsetFlags(T& v, T flags) noexcept { v &= ~flags; }

} // namespace math