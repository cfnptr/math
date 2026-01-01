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
 * @brief Camera frustum planes.
 */

#pragma once
#include "math/plane.hpp"
#include "math/matrix.hpp"

namespace math
{

/**
 * @brief Camera view frustum planes container.
 */
struct [[nodiscard]] Frustum
{
	static constexpr uint8 fullCount = 6; /**< Full frustum plane count. (Cube side count) */
	Plane planes[fullCount]; /**< Viewing frustum planes. */
protected:
	uint8 count = fullCount;
public:
	/**
	 * @brief Creates a new camera frustum plane container.
	 * @param count target view frustum plane count
	 */
	Frustum(uint8 count = fullCount) noexcept : count(count)
	{
		assert(count > 0);
		assert(count <= fullCount);
	}
	/**
	 * @brief Extracts projection matrix frustum planes.
	 * @warning Extracted planes are unnormalized! Use @ref Frustum::normalize().
	 * @param[in] viewProj target view * projection matrix
	 */
	explicit Frustum(const f32x4x4& viewProj) noexcept // Gribb & Hartmann method
	{
		auto t = transpose4x4(viewProj);
		auto c0W = t.c0.getW(), c1W = t.c1.getW(), c2W = t.c2.getW(), c3W = t.c3.getW();
		planes[0] = Plane(f32x4(t.c3 + t.c0, 0.0f), c3W + c0W, false);
		planes[1] = Plane(f32x4(t.c3 - t.c0, 0.0f), c3W - c0W, false);
		planes[2] = Plane(f32x4(t.c3 - t.c1, 0.0f), c3W - c1W, false); // Flipped Vulkan NDC!
		planes[3] = Plane(f32x4(t.c3 + t.c1, 0.0f), c3W + c1W, false); // Flipped Vulkan NDC!
		planes[4] = Plane(f32x4(t.c2,        0.0f),       c2W, false);
		planes[5] = Plane(f32x4(t.c3 - t.c2, 0.0f), c3W - c2W, false);
	}

	/**
	 * @brief Returns view frustum plane count.
	 */
	uint8 getPlaneCount() const noexcept { return count; }
	/**
	 * @brief Sets view frustum plane count.
	 * @param count target view frustum plane count
	 */
	void setPlaneCount(uint8 count)
	{
		assert(count > 0);
		assert(count <= fullCount);
		this->count = count;
	}

	/**
	 * @brief Normalizes view frustum planes.
	 */
	void normalize() noexcept
	{
		for (uint8 i = 0; i < count; i++)
			planes[i].normalize();
	}
};

} // namespace math