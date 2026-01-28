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
#include "math/vector.hpp"

/***********************************************************************************************************************
 * @file
 * @brief Common metric measuring system functions.
 */

namespace math
{

/**
 * @brief Converts metres to millimetres.
 * @param km target distance in kilometres
 */
template<class V = float>
static V mToMm(V m) noexcept { return m * 1000.0f; }
/**
 * @brief Converts metres to centimetres.
 * @param km target distance in kilometres
 */
template<class V = float>
static V mToCm(V m) noexcept { return m * 100.0f; }
/**
 * @brief Converts metres to kilometres.
 * @param km target distance in kilometres
 */
template<class V = float>
static V mToKm(V m) noexcept { return m * 0.001f; }

/**
 * @brief Converts kilometres to centimetres.
 * @param km target distance in kilometres
 */
template<class V = float>
static V kmToCm(V km) noexcept { return km * 100000.0f; }
/**
 * @brief Converts kilometres to metres.
 * @param km target distance in kilometres
 */
template<class V = float>
static V kmToM(V km) noexcept { return km * 1000.0f; }

} // namespace math