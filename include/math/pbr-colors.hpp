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
 * @brief Common physically based rendering colors.
 * 
 * @details
 * Based on real world measurements and simulations. For metals we are using Brendel-Bormann model when available.
 * Wavelengths: R = 0.7µm, G = 0.5461µm, B = 0.4358µm (CIE 1931).
 * 
 * https://refractiveindex.info/
 * https://en.wikipedia.org/wiki/CIE_1931_color_space#CIE_RGB_color_space
 */

#pragma once
#include "math/color.hpp"

// Commented colors are in the linear RGB space.
static constexpr auto lithiumBaseColor = Color(); // 0.94315, 0.90261, 0.81365
static constexpr auto berylliumBaseColor = Color(); // 0.54531, 0.53371, 0.53445
static constexpr auto diamondBaseColor = Color(); // 0.17048, 0.17284, 0.17587
static constexpr auto cvdDiamondBaseColor = Color(); // 0.16818, 0.17084, 0.17489
static constexpr auto graphiteBaseColor = Color(); // 0.16715, 0.13826, 0.11993
static constexpr auto sodiumBaseColor = Color();  // 0.98354, 0.96629, 0.91929
static constexpr auto magnesiumBaseColor = Color();  // 0.89588, 0.88292, 0.89765
static constexpr auto aluminumBaseColor = Color();  // 0.90712, 0.91397, 0.92081
static constexpr auto aluminaBaseColor = Color();  // 0.88938, 0.90687, 0.91107
static constexpr auto siliconBaseColor = Color(); // 0.33748, 0.36896, 0.43407
static constexpr auto potassiumBaseColor = Color(); // 0.96248, 0.93759, 0.91846
static constexpr auto calciumBaseColor = Color(); // 0.89292, 0.83834, 0.73150
static constexpr auto titaniumBaseColor = Color(); // 0.62520, 0.58068, 0.54372
static constexpr auto vanadiumBaseColor = Color(); // 0.53509, 0.53366, 0.56753
static constexpr auto chromiumBaseColor = Color(); // 0.56211, 0.55489, 0.55033
static constexpr auto manganeseBaseColor = Color(); // 0.61643, 0.57570, 0.53850
static constexpr auto ironBaseColor = Color(); // 0.54275, 0.51196, 0.49153
static constexpr auto hematiteBaseColor = Color(); // 0.24653, 0.29675, 0.31407
static constexpr auto magnetiteBaseColor = Color(); // 0.16426, 0.16224, 0.17130
static constexpr auto cobaltBaseColor = Color(); // 0.69855, 0.65590, 0.61303
static constexpr auto nickelBaseColor = Color(); // 0.72042, 0.64205, 0.55746
static constexpr auto copperBaseColor = Color(); // 0.95502, 0.61667, 0.52365
static constexpr auto zincBaseColor = Color(); // 0.87726, 0.86903, 0.85318
static constexpr auto germaniumBaseColor = Color(); // 0.44932, 0.51809, 0.46252
static constexpr auto seleniumBaseColor = Color(); // 0.026697, 0.038136, 0.039013
static constexpr auto rubidiumBaseColor = Color(); // 0.89526, 0.85000, 0.76979
static constexpr auto zirconiumBaseColor = Color(); // 0.58107, 0.57292, 0.53025
static constexpr auto niobiumBaseColor = Color(); // 0.51392, 0.50564, 0.49676
static constexpr auto molybdenumBaseColor = Color(); // 0.60131, 0.60232, 0.59436
static constexpr auto rhodiumBaseColor = Color(); // 0.80714, 0.76722, 0.74687
static constexpr auto palladiumBaseColor = Color(); // 0.74922, 0.69694, 0.64859
static constexpr auto silverBaseColor = Color(); // 0.99321, 0.98289, 0.97836
static constexpr auto indiumBaseColor = Color(); // 0.86354, 0.85244, 0.85314
static constexpr auto telluriumBaseColor = Color(); // 0.50451, 0.56156, 0.53886
static constexpr auto caesiumBaseColor = Color(); // 0.70902, 0.57696, 0.33747
static constexpr auto lutetiumBaseColor = Color(); // 0.61051, 0.59940, 0.57928
static constexpr auto tantalumBaseColor = Color(); // 0.90729, 0.83927, 0.74525
static constexpr auto rheniumBaseColor = Color(); // 0.94234, 0.82943, 0.77274
static constexpr auto osmiumBaseColor = Color(); // 0.43865, 0.58482, 0.66003
static constexpr auto iridiumBaseColor = Color(); // 0.75080, 0.73119, 0.69471
static constexpr auto platinumBaseColor = Color(); // 0.96038, 0.93238, 0.81340
static constexpr auto goldBaseColor = Color(); // 0.97053, 0.77521, 0.40798
static constexpr auto mercuryBaseColor = Color(); // 0.78209, 0.77934, 0.77818
static constexpr auto leadBaseColor = Color(); // 0.67203, 0.66206, 0.70042
static constexpr auto bismuthBaseColor = Color(); // 0.58151, 0.53059, 0.48055
static constexpr auto austeniticSteelBaseColor = Color(); // 0.67566, 0.63933, 0.59518
static constexpr auto ferriticSteelBaseColor = Color(); // 0.61667, 0.58737, 0.56676
static constexpr auto gildingBrassBaseColor = Color(); // 0.92401, 0.72851, 0.46527
static constexpr auto dzrBrassBaseColor = Color(); // 0.90586, 0.78129, 0.39912
static constexpr auto permalloyBaseColor = Color(); // 0.66871, 0.62652, 0.57444
static constexpr auto purplePlagueBaseColor = Color(); // 0.64247, 0.37980, 0.50502
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
static constexpr auto BaseColor = Color(); // , , 
