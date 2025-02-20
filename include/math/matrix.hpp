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
 * @brief Common matrix functions.
 * 
 * @details
 * Matrix is a mathematical structure used to represent transformations such as translation, rotation, scaling, and 
 * shearing. These matrices are often 4x4 matrices in 3D graphics, allowing for efficient manipulation of objects in 
 * 3D space using homogeneous coordinates. Matrices enable combining multiple transformations into a single operation 
 * and are essential in rendering pipelines, skeletal animation or camera movements.
 */

#pragma once
#include "math/matrix/float.hpp"