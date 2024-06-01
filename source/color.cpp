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

#include "math/color.hpp"
using namespace math;

const Color Color::white = Color(255, 255, 255, 255);
const Color Color::black = Color(0, 0, 0, 255);
const Color Color::grey = Color(127, 127, 127, 255);
const Color Color::transparent = Color(0, 0, 0, 0);
const Color Color::red = Color(255, 0, 0, 255);
const Color Color::green = Color(0, 255, 0, 255);
const Color Color::blue = Color(0, 0, 255, 255);
const Color Color::cyan = Color(0, 255, 255, 255);
const Color Color::magenta = Color(255, 0, 255, 255);
const Color Color::yellow = Color(255, 255, 0, 255);