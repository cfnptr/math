# Copyright 2022-2025 Nikita Fediuchin. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.16)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
	message(FATAL_ERROR "Prevented in-tree build")
endif()

if(TARGET math-static)
	return()
endif()

project(math VERSION 0.0.1 LANGUAGES CXX
	DESCRIPTION "Linear algebra mathematics library."
	HOMEPAGE_URL "https://github.com/cfnptr/math")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

option(MATH_BUILD_SHARED "Build Math shared library" ON)
option(MATH_BUILD_TESTS "Build Math library tests" ON)

set(MATH_SOURCES source/aabb.cpp source/bvh.cpp)

add_library(math-static STATIC ${MATH_SOURCES})
target_include_directories(math-static PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(MATH_BUILD_SHARED)
	add_library(math-shared SHARED ${MATH_SOURCES})
	set_target_properties(math-shared PROPERTIES
		OUTPUT_NAME "math" WINDOWS_EXPORT_ALL_SYMBOLS ON)
	target_include_directories(math-shared PUBLIC ${PROJECT_SOURCE_DIR}/include)
endif()

if(MATH_BUILD_TESTS)
	enable_testing()

	if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		add_compile_options(/arch:AVX2)
	elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64" OR CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
		add_compile_options(-march=haswell)
	endif()

	add_executable(TestMathVector tests/test-vector.cpp)
	target_link_libraries(TestMathVector PUBLIC math-static)
	add_test(NAME TestMathVector COMMAND TestMathVector)

	add_executable(TestMathMatrix tests/test-matrix.cpp)
	target_link_libraries(TestMathMatrix PUBLIC math-static)
	add_test(NAME TestMathMatrix COMMAND TestMathMatrix)

	add_executable(TestMathQuaternion tests/test-quaternion.cpp)
	target_link_libraries(TestMathQuaternion PUBLIC math-static)
	add_test(NAME TestMathQuaternion COMMAND TestMathQuaternion)

	add_executable(TestMathContainers tests/test-containers.cpp)
	target_link_libraries(TestMathContainers PUBLIC math-static)
	add_test(NAME TestMathContainers COMMAND TestMathContainers)
endif()