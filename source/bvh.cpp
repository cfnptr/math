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
//
// Bounding Volume Hierarchy
// Based on this: https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/

#include "math/bvh.hpp"

#include <cfloat>
#include <functional>

// TODO: Utilize Jolt BVH building and update optimizations.

using namespace math;

//**********************************************************************************************************************
static Aabb calculateNodeAabb(const Bvh::Node* node, const uint8* vertices, const uint8* indices,
	const uint32* primitives, uint32 vertexSize, uint32 indexSize, const function<uint32(const uint8*)>& getIndex)
{
	auto lastPrimitive = node->getFirstPrimitive() + node->getPrimitiveCount();
	simd_f32_4 min = simd_f32_4::max, max = simd_f32_4::minusMax;
	for (uint32 i = node->getFirstPrimitive(); i < lastPrimitive; i++)
	{
		auto offset = primitives[i] * Triangle::pointCount;
		auto i0 = getIndex(indices + (offset    ) * indexSize);
		auto i1 = getIndex(indices + (offset + 1) * indexSize);
		auto i2 = getIndex(indices + (offset + 2) * indexSize);
		auto v0 = simd_f32_4(*(const float3*)(vertices + i0 * vertexSize));
		auto v1 = simd_f32_4(*(const float3*)(vertices + i1 * vertexSize));
		auto v2 = simd_f32_4(*(const float3*)(vertices + i2 * vertexSize));
		min = math::min(math::min(math::min(min, v0), v1), v2); 
		max = math::max(math::max(math::max(max, v0), v1), v2);
	}
	return Aabb(min, max);
}

static Aabb calculateNodeAabb(const Bvh::Node* node, const Aabb* aabbs, const uint32* primitives)
{
	auto lastPrimitive = node->getFirstPrimitive() + node->getPrimitiveCount();
	simd_f32_4 min = simd_f32_4::max, max = simd_f32_4::minusMax;
	for (uint32 i = node->getFirstPrimitive(); i < lastPrimitive; i++)
	{
		auto aabb = aabbs[primitives[i]];
		min = math::min(min, aabb.getMin());
		max = math::max(max, aabb.getMax());
	}
	return Aabb(min, max);
}

//**********************************************************************************************************************
#define BIN_COUNT 8

namespace
{
	struct Bin final
	{
		simd_f32_4 min = simd_f32_4::max;
		simd_f32_4 max = simd_f32_4::minusMax;
	};
}

static void findBestSplitPlane(uint32 firstPrimitive, uint32 lastPrimitive, uint32 vertexSize, uint32 indexSize,
	const uint8* vertices, const uint8* indices, const uint32* primitives, const simd_f32_4* centroids,
	const function<uint32(const uint8*)>& getIndex, int32& axis, float& split, float& cost)
{
	auto bestAxis = 0;
	auto bestSplit = 0.0f, bestCost = FLT_MAX;

	for (int a = 0; a < 3; a++)
	{
		auto boundsMin = FLT_MAX, boundsMax = -FLT_MAX;
		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto value = centroids[primitives[i]][a];
			boundsMin = std::min(boundsMin, value);
			boundsMax = std::max(boundsMax, value);
		}

		if (boundsMin == boundsMax)
			continue;

		Bin bins[BIN_COUNT] = {};
		auto scale = BIN_COUNT / (boundsMax - boundsMin);

		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto index = primitives[i];
			auto offset = index * Triangle::pointCount;
			auto i0 = getIndex(indices + (offset    ) * indexSize);
			auto i1 = getIndex(indices + (offset + 1) * indexSize);
			auto i2 = getIndex(indices + (offset + 2) * indexSize);
			auto v0 = simd_f32_4(*(const float3*)(vertices + i0 * vertexSize));
			auto v1 = simd_f32_4(*(const float3*)(vertices + i1 * vertexSize));
			auto v2 = simd_f32_4(*(const float3*)(vertices + i2 * vertexSize));

			auto binIndex = std::min((int32)(BIN_COUNT - 1), (int32)((
				centroids[index][a] - boundsMin) * scale));
			auto& bin = bins[binIndex];
			bin.min = min(min(min(bin.min, v0), v1), v2);
			bin.max = max(max(max(bin.max, v0), v1), v2);
			bin.max.ints.w++;
		}

		float leftArea[BIN_COUNT - 1], rightArea[BIN_COUNT - 1];
		int32 leftCount[BIN_COUNT - 1], rightCount[BIN_COUNT - 1];
		simd_f32_4 leftMin = simd_f32_4::max, leftMax = simd_f32_4::minusMax;
		simd_f32_4 rightMin = simd_f32_4::max, rightMax = simd_f32_4::minusMax;
		int32 leftSum = 0, rightSum = 0;

		for (int i = 0; i < BIN_COUNT - 1; i++)
		{
			leftSum += bins[i].max.ints.w;
			leftCount[i] = leftSum;
			leftMin = min(leftMin, bins[i].min);
			leftMax = max(leftMax, bins[i].max);
			leftArea[i] = Aabb(leftMin, leftMax).calcArea();
			rightSum += bins[(BIN_COUNT - 1) - i].max.ints.w;
			rightCount[(BIN_COUNT - 2) - i] = rightSum;
			rightMin = min(rightMin, bins[(BIN_COUNT - 1) - i].min);
			rightMax = max(rightMax, bins[(BIN_COUNT - 1) - i].max);
			rightArea[(BIN_COUNT - 2) - i] = Aabb(rightMin, rightMax).calcArea();
		}

		scale = (boundsMax - boundsMin) / BIN_COUNT;
		for (int i = 0; i < BIN_COUNT - 1; i++)
		{
			float planeCost = leftCount[i] * leftArea[i] +
				rightCount[i] * rightArea[i];
				
			if (planeCost < bestCost)
			{
				bestSplit = boundsMin + scale * (i + 1);
				bestAxis = a; bestCost = planeCost;
			}
		}
	}

	axis = bestAxis;
	split = bestSplit;
	cost = bestCost;
}

//**********************************************************************************************************************
static void findBestSplitPlane(uint32 firstPrimitive, uint32 lastPrimitive, const Aabb* aabbs,
	const uint32* primitives, const simd_f32_4* centroids, int32& axis, float& split, float& cost)
{
	auto bestAxis = 0;
	auto bestSplit = 0.0f, bestCost = FLT_MAX;

	for (int a = 0; a < 3; a++)
	{
		auto boundsMin = FLT_MAX, boundsMax = -FLT_MAX;
		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto value = centroids[primitives[i]][a];
			boundsMin = std::min(boundsMin, value);
			boundsMax = std::max(boundsMax, value);
		}

		if (boundsMin == boundsMax)
			continue;

		Bin bins[BIN_COUNT] = {};
		auto scale = BIN_COUNT / (boundsMax - boundsMin);

		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto index = primitives[i];
			auto aabb = aabbs[index];
			auto binIndex = std::min((int32)(BIN_COUNT - 1), (int32)((
				centroids[index][a] - boundsMin) * scale));
			auto& bin = bins[binIndex];
			bin.min = min(bin.min, aabb.getMin());
			bin.max = max(bin.max, aabb.getMax());
			bin.max.ints.w++;
		}

		// TODO: share this function part with a previous one?
		float leftArea[BIN_COUNT - 1], rightArea[BIN_COUNT - 1];
		int32 leftCount[BIN_COUNT - 1], rightCount[BIN_COUNT - 1];
		simd_f32_4 leftMin = simd_f32_4::max, leftMax = simd_f32_4::minusMax;
		simd_f32_4 rightMin = simd_f32_4::max, rightMax = simd_f32_4::minusMax;
		int32 leftSum = 0, rightSum = 0;

		for (int i = 0; i < BIN_COUNT - 1; i++)
		{
			leftSum += bins[i].max.ints.w;
			leftCount[i] = leftSum;
			leftMin = min(leftMin, bins[i].min);
			leftMax = max(leftMax, bins[i].max);
			leftArea[i] = Aabb(leftMin, leftMax).calcArea();
			rightSum += bins[(BIN_COUNT - 1) - i].max.ints.w;
			rightCount[(BIN_COUNT - 2) - i] = rightSum;
			rightMin = min(rightMin, bins[(BIN_COUNT - 1) - i].min);
			rightMax = max(rightMax, bins[(BIN_COUNT - 1) - i].max);
			rightArea[(BIN_COUNT - 2) - i] = Aabb(rightMin, rightMax).calcArea();
		}

		scale = (boundsMax - boundsMin) / BIN_COUNT;
		for (int i = 0; i < BIN_COUNT - 1; i++)
		{
			float planeCost = leftCount[i] * leftArea[i] +
				rightCount[i] * rightArea[i];

			if (planeCost < bestCost)
			{
				bestSplit = boundsMin + scale * (i + 1);
				bestAxis = a; bestCost = planeCost;
			}
		}
	}

	axis = bestAxis;
	split = bestSplit;
	cost = bestCost;
}

//**********************************************************************************************************************
Bvh::Bvh(const uint8* vertices, const uint8* indices, const Aabb& aabb,
	uint32 indexCount, uint32 vertexSize, uint32 indexSize, const simd_f32_4* _centroids)
{
	recreate(vertices, indices, aabb, indexCount, vertexSize, indexSize, _centroids);
}
Bvh::Bvh(const Aabb* aabbs, const Aabb& aabb, uint32 aabbCount, const simd_f32_4* _centroids)
{
	recreate(aabbs, aabb, aabbCount, _centroids);
}

void Bvh::recreate(const uint8* vertices, const uint8* indices, const Aabb& aabb,
	uint32 indexCount, uint32 vertexSize, uint32 indexSize, const simd_f32_4* _centroids)
{
	assert(vertices);
	assert(indices);
	assert(indexCount > 0);
	assert(vertexSize > 0);
	assert(indexSize > 0);

	auto primitiveCount = indexCount / Triangle::pointCount;
	nodes.resize(primitiveCount * 2 - 1);
	primitives.resize(primitiveCount);

	for (uint32 i = 0; i < primitiveCount; i++)
		primitives[i] = i;

	function getIndex16 = [](const uint8* data) { return (uint32)*(const uint16*)data; };
	function getIndex32 = [](const uint8* data) { return *(const uint32*)data; };

	auto getIndex = getIndex32;
	if (indexSize == sizeof(uint16))
		getIndex = getIndex16;
	else if (indexSize != sizeof(uint32)) abort();

	const simd_f32_4* centroidData;
	if (!_centroids)
	{
		centroids.resize(primitiveCount);
		centroidData = centroids.data();

		for (uint32 i = 0; i < primitiveCount; i++)
		{
			auto offset = i * Triangle::pointCount;
			auto i0 = getIndex(indices + (offset    ) * indexSize);
			auto i1 = getIndex(indices + (offset + 1) * indexSize);
			auto i2 = getIndex(indices + (offset + 2) * indexSize);
			auto v0 = simd_f32_4(*(const float3*)(vertices + i0 * vertexSize));
			auto v1 = simd_f32_4(*(const float3*)(vertices + i1 * vertexSize));
			auto v2 = simd_f32_4(*(const float3*)(vertices + i2 * vertexSize));
			centroids[i] = (v0 + v1 + v2) * (1.0f / 3.0f);
		}
	}
	else
	{
		centroidData = _centroids;
	}

	auto nodeCount = (uint32)1;
	auto node = &nodes[0];
	node->aabb = aabb;
	node->setPrimitiveCount(primitiveCount);
	node->setFirstPrimitive(0);

	while (true)
	{
		auto firstPrimitive = node->getFirstPrimitive();
		auto primitiveCount = node->getPrimitiveCount();
		auto lastPrimitive = firstPrimitive + primitiveCount;

		int32 axis; float split, cost;
		findBestSplitPlane(firstPrimitive, lastPrimitive, vertexSize, indexSize,
			vertices, indices, primitives.data(), centroidData, getIndex, axis, split, cost);

		auto nodeCost = node->aabb.calcArea() * primitiveCount;
		if (cost >= nodeCost)
		{
			if (nodeStack.empty())
			{
				break;
			}
			else
			{
				node = nodeStack.top();  nodeStack.pop(); continue;
			}
		}

		auto i = firstPrimitive, j = i + primitiveCount - 1;
		while (i <= j)
		{
			if (centroidData[primitives[i]][axis] < split)
				i++;
			else
				std::swap(primitives[i], primitives[j--]);
		}

		auto count1 = i - firstPrimitive;
		if (count1 == 0 || count1 == primitiveCount)
		{
			if (nodeStack.empty())
			{
				break;
			}
			else
			{
				node = nodeStack.top(); nodeStack.pop(); continue;
			}
		}

		auto count2 = primitiveCount - count1;
		auto leftNodeID = nodeCount;
		auto rightNodeID = nodeCount + 1;
		nodeCount += 2;
		node->setLeftNode(leftNodeID);
		node->setPrimitiveCount(0);
	
		auto node1 = &nodes[leftNodeID];
		node1->setFirstPrimitive(firstPrimitive);
		node1->setPrimitiveCount(count1);
		node1->aabb = calculateNodeAabb(node1, vertices, indices, 
			primitives.data(), vertexSize, indexSize, getIndex);

		auto node2 = &nodes[rightNodeID];
		node2->setFirstPrimitive(i);
		node2->setPrimitiveCount(count2);
		node2->aabb = calculateNodeAabb(node2, vertices, indices, 
			primitives.data(), vertexSize, indexSize, getIndex);

		if (count2 > count1)
		{
			std::swap(count1, count2);
			std::swap(node1, node2);
		}

		if (count1 > 2)
		{
			node = node1;
			if (count2 > 2)
				nodeStack.push(node2);
			continue;
		}

		if (nodeStack.empty())
		{
			break;
		}
		else
		{
			node = nodeStack.top(); nodeStack.pop(); continue;
		}
	}

	nodes.resize(nodeCount);
}

//**********************************************************************************************************************
void Bvh::recreate(const Aabb* aabbs, const Aabb& aabb, uint32 aabbCount, const simd_f32_4* _centroids)
{
	assert(aabbs);
	assert(aabbCount > 0);
	nodes.resize(aabbCount * 2 - 1);

	primitives.resize(aabbCount);
	auto primitiveData = primitives.data();
	for (uint32 i = 0; i < aabbCount; i++)
		primitiveData[i] = i;

	const simd_f32_4* centroidData;
	if (!_centroids)
	{
		centroids.resize(aabbCount);
		centroidData = centroids.data();

		for (uint32 i = 0; i < aabbCount; i++)
		{
			auto aabb = aabbs[i];
			centroids[i] = aabb.getPosition();
		}
	}
	else
	{
		centroidData = _centroids;
	}

	auto nodeData = nodes.data();
	auto nodeCount = (uint32)1;
	auto node = &nodeData[0];
	node->aabb = aabb;
	node->setPrimitiveCount(aabbCount);
	node->setFirstPrimitive(0);

	while (true)
	{
		auto firstPrimitive = node->getFirstPrimitive();
		auto primitiveCount = node->getPrimitiveCount();
		auto lastPrimitive = firstPrimitive + primitiveCount;

		int32 axis; float split, cost;
		findBestSplitPlane(firstPrimitive, lastPrimitive, aabbs,
			primitiveData, centroidData, axis, split, cost);

		auto nodeCost = node->aabb.calcArea() * primitiveCount;
		if (cost >= nodeCost)
		{
			if (nodeStack.empty())
			{
				break;
			}
			else
			{
				node = nodeStack.top();  nodeStack.pop(); continue;
			}
		}

		auto i = firstPrimitive, j = i + primitiveCount - 1;
		while (i <= j)
		{
			if (centroidData[primitiveData[i]][axis] < split)
				i++;
			else
				std::swap(primitiveData[i], primitiveData[j--]);
		}

		auto count1 = i - firstPrimitive;
		if (count1 == 0 || count1 == primitiveCount)
		{
			if (nodeStack.empty())
			{
				break;
			}
			else
			{
				node = nodeStack.top(); nodeStack.pop(); continue;
			}
		}

		auto count2 = primitiveCount - count1;
		auto leftNodeID = nodeCount;
		auto rightNodeID = nodeCount + 1;
		nodeCount += 2;
		node->setLeftNode(leftNodeID);
		node->setPrimitiveCount(0);
	
		auto node1 = &nodeData[leftNodeID];
		node1->setFirstPrimitive(firstPrimitive);
		node1->setPrimitiveCount(count1);
		node1->aabb = calculateNodeAabb(node1, aabbs, primitiveData);

		auto node2 = &nodeData[rightNodeID];
		node2->setFirstPrimitive(i);
		node2->setPrimitiveCount(count2);
		node2->aabb = calculateNodeAabb(node2, aabbs, primitiveData);

		if (count2 > count1)
		{
			std::swap(count1, count2);
			std::swap(node1, node2);
		}

		if (count1 > 2)
		{
			node = node1;
			if (count2 > 2)
				nodeStack.push(node2);
			continue;
		}

		if (nodeStack.empty())
		{
			break;
		}
		else
		{
			node = nodeStack.top(); nodeStack.pop(); continue;
		}
	}

	nodes.resize(nodeCount);
}