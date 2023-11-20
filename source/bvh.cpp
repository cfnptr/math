//------------------------------------------------------------------------------------------------------------
// Copyright 2022-2023 Nikita Fediuchin. All rights reserved.
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
//--------------------------------------------------------------------------------------------------

#include "math/bvh.hpp"

#include <cfloat>
#include <functional>

using namespace math;

//--------------------------------------------------------------------------------------------------
static Aabb calculateNodeAabb(const Bvh::Node* node,
	const uint8* vertices, const uint8* indices, const uint32* primitives, 
	uint32 vertexSize, uint32 indexSize, function<uint32(const uint8*)> getIndex)
{
	auto lastPrimitive = node->leaf.firstPrimitive + node->base.primitiveCount;
	float3 min = float3(FLT_MAX), max = float3(-FLT_MAX);
	for (uint32 i = node->leaf.firstPrimitive; i < lastPrimitive; i++)
	{
		auto offset = primitives[i] * TRIANGLE_POINT_COUNT;
		auto i0 = getIndex(indices + (offset    ) * indexSize);
		auto i1 = getIndex(indices + (offset + 1) * indexSize);
		auto i2 = getIndex(indices + (offset + 2) * indexSize);
		auto v0 = *(const float3*)(vertices + i0 * vertexSize);
		auto v1 = *(const float3*)(vertices + i1 * vertexSize);
		auto v2 = *(const float3*)(vertices + i2 * vertexSize);
		min = ::min(min, v0); max = ::max(max, v0);
		min = ::min(min, v1); max = ::max(max, v1);
		min = ::min(min, v2); max = ::max(max, v2);
	}
	return Aabb(min, max);
}

//--------------------------------------------------------------------------------------------------
static Aabb calculateNodeAabb(const Bvh::Node* node,
	const Aabb* aabbs, const uint32* primitives)
{
	auto lastPrimitive = node->leaf.firstPrimitive + node->base.primitiveCount;
	float3 min = float3(FLT_MAX), max = float3(-FLT_MAX);
	for (uint32 i = node->leaf.firstPrimitive; i < lastPrimitive; i++)
	{
		auto aabb = aabbs[primitives[i]];
		min = ::min(min, aabb.getMin());
		max = ::max(max, aabb.getMax());
	}
	return Aabb(min, max);
}

//--------------------------------------------------------------------------------------------------
#define BIN_COUNT 8

static void findBestSplitPlane(uint32 firstPrimitive, uint32 lastPrimitive,
	uint32 vertexSize, uint32 indexSize, const uint8* vertices, const uint8* indices,
	const uint32* primitives, const float3* centroids,
	function<uint32(const uint8*)> getIndex, int32& axis, float& split, float& cost)
{
	auto bestAxis = 0;
	auto bestSplit = 0.0f, bestCost = FLT_MAX;

	for (uint8 a = 0; a < 3; a++)
	{
		auto boundsMin = FLT_MAX, boundsMax = -FLT_MAX;
		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto value = centroids[primitives[i]][a];
			boundsMin = std::min(boundsMin, value);
			boundsMax = std::max(boundsMax, value);
		}
		if (boundsMin == boundsMax) continue;

		struct Bin
		{
			float3 min = float3(FLT_MAX);
			float3 max = float3(-FLT_MAX);
			int32 primitiveCount = 0;
		} bins[BIN_COUNT] = {};

		auto scale = BIN_COUNT / (boundsMax - boundsMin);
		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto index = primitives[i];
			auto offset = index * TRIANGLE_POINT_COUNT;
			auto i0 = getIndex(indices + (offset    ) * indexSize);
			auto i1 = getIndex(indices + (offset + 1) * indexSize);
			auto i2 = getIndex(indices + (offset + 2) * indexSize);
			auto v0 = *(const float3*)(vertices + i0 * vertexSize);
			auto v1 = *(const float3*)(vertices + i1 * vertexSize);
			auto v2 = *(const float3*)(vertices + i2 * vertexSize);

			auto binIndex = std::min((int32)(BIN_COUNT - 1), (int32)((
				centroids[index][a] - boundsMin) * scale));
			auto& bin = bins[binIndex];
			bin.min = min(bin.min, v0); bin.max = max(bin.max, v0);
			bin.min = min(bin.min, v1); bin.max = max(bin.max, v1);
			bin.min = min(bin.min, v2); bin.max = max(bin.max, v2);
			bin.primitiveCount++;
		}

		float leftArea[BIN_COUNT - 1], rightArea[BIN_COUNT - 1];
		int32 leftCount[BIN_COUNT - 1], rightCount[BIN_COUNT - 1];
		float3 leftMin = float3(FLT_MAX), leftMax = float3(-FLT_MAX);
		float3 rightMin = float3(FLT_MAX), rightMax = float3(-FLT_MAX);
		int32 leftSum = 0, rightSum = 0;

		for (uint8 i = 0; i < BIN_COUNT - 1; i++)
		{
			leftSum += bins[i].primitiveCount;
			leftCount[i] = leftSum;
			leftMin = min(leftMin, bins[i].min);
			leftMax = max(leftMax, bins[i].max);
			leftArea[i] = Aabb(leftMin, leftMax).getArea();
			rightSum += bins[(BIN_COUNT - 1) - i].primitiveCount;
			rightCount[(BIN_COUNT - 2) - i] = rightSum;
			rightMin = min(rightMin, bins[(BIN_COUNT - 1) - i].min);
			rightMax = max(rightMax, bins[(BIN_COUNT - 1) - i].max);
			rightArea[(BIN_COUNT - 2) - i] = Aabb(rightMin, rightMax).getArea();
		}

		scale = (boundsMax - boundsMin) / BIN_COUNT;
		for (uint8 i = 0; i < BIN_COUNT - 1; i++)
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

//--------------------------------------------------------------------------------------------------
static void findBestSplitPlane(uint32 firstPrimitive, uint32 lastPrimitive,
	const Aabb* aabbs, const uint32* primitives, const float3* centroids,
	int32& axis, float& split, float& cost)
{
	auto bestAxis = 0;
	auto bestSplit = 0.0f, bestCost = FLT_MAX;

	for (uint8 a = 0; a < 3; a++)
	{
		auto boundsMin = FLT_MAX, boundsMax = -FLT_MAX;
		for (uint32 i = firstPrimitive; i < lastPrimitive; i++)
		{
			auto value = centroids[primitives[i]][a];
			boundsMin = std::min(boundsMin, value);
			boundsMax = std::max(boundsMax, value);
		}
		if (boundsMin == boundsMax) continue;

		struct Bin
		{
			float3 min = float3(FLT_MAX);
			float3 max = float3(-FLT_MAX);
			int32 primitiveCount = 0;
		} bins[BIN_COUNT] = {};

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
			bin.primitiveCount++;
		}

		// TODO: share this function part with a previous one?
		float leftArea[BIN_COUNT - 1], rightArea[BIN_COUNT - 1];
		int32 leftCount[BIN_COUNT - 1], rightCount[BIN_COUNT - 1];
		float3 leftMin = float3(FLT_MAX), leftMax = float3(-FLT_MAX);
		float3 rightMin = float3(FLT_MAX), rightMax = float3(-FLT_MAX);
		int32 leftSum = 0, rightSum = 0;

		for (uint8 i = 0; i < BIN_COUNT - 1; i++)
		{
			leftSum += bins[i].primitiveCount;
			leftCount[i] = leftSum;
			leftMin = min(leftMin, bins[i].min);
			leftMax = max(leftMax, bins[i].max);
			leftArea[i] = Aabb(leftMin, leftMax).getArea();
			rightSum += bins[(BIN_COUNT - 1) - i].primitiveCount;
			rightCount[(BIN_COUNT - 2) - i] = rightSum;
			rightMin = min(rightMin, bins[(BIN_COUNT - 1) - i].min);
			rightMax = max(rightMax, bins[(BIN_COUNT - 1) - i].max);
			rightArea[(BIN_COUNT - 2) - i] = Aabb(rightMin, rightMax).getArea();
		}

		scale = (boundsMax - boundsMin) / BIN_COUNT;
		for (uint8 i = 0; i < BIN_COUNT - 1; i++)
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

//--------------------------------------------------------------------------------------------------
Bvh::Bvh(const uint8* vertices, const uint8* indices, const Aabb& aabb,
	uint32 indexCount, uint32 vertexSize, uint32 indexSize, const float3* _centroids)
{
	recreate(vertices, indices, aabb, indexCount, vertexSize, indexSize, _centroids);
}
Bvh::Bvh(const Aabb* aabbs, const Aabb& aabb, uint32 aabbCount, const float3* _centroids)
{
	recreate(aabbs, aabb, aabbCount, _centroids);
}

//--------------------------------------------------------------------------------------------------
void Bvh::recreate(const uint8* vertices, const uint8* indices,
	const Aabb& aabb, uint32 indexCount, uint32 vertexSize,
	uint32 indexSize, const float3* _centroids)
{
	assert(vertices);
	assert(indices);
	assert(indexCount > 0);
	assert(vertexSize > 0);
	assert(indexSize > 0);

	auto primitiveCount = indexCount / TRIANGLE_POINT_COUNT;
	nodes.resize(primitiveCount * 2 - 1);
	primitives.resize(primitiveCount);
	auto primitiveData = primitives.data();
	for (uint32 i = 0; i < primitiveCount; i++) primitiveData[i] = i;

	function getIndex16 = [](const uint8* data)
	{ return (uint32)*(const uint16*)data; };
	function getIndex32 = [](const uint8* data)
	{ return *(const uint32*)data; };
	auto getIndex = getIndex32;
	if (indexSize == sizeof(uint16)) getIndex = getIndex16;
	else if (indexSize != sizeof(uint32)) abort();

	const float3* centroidData;
	if (!_centroids)
	{
		centroids.resize(primitiveCount);
		centroidData = centroids.data();
		auto data = centroids.data();

		for (uint32 i = 0; i < primitiveCount; i++)
		{
			auto offset = i * TRIANGLE_POINT_COUNT;
			auto i0 = getIndex(indices + (offset    ) * indexSize);
			auto i1 = getIndex(indices + (offset + 1) * indexSize);
			auto i2 = getIndex(indices + (offset + 2) * indexSize);
			auto v0 = (const float3*)(vertices + i0 * vertexSize);
			auto v1 = (const float3*)(vertices + i1 * vertexSize);
			auto v2 = (const float3*)(vertices + i2 * vertexSize);
			data[i] = (*v0 + *v1 + *v2) * (1.0f / 3.0f);
		}
	}
	else centroidData = _centroids;

	auto nodeData = nodes.data();
	auto nodeCount = (uint32)1;
	auto node = &nodeData[0];
	node->setAabb(aabb);
	node->leaf.primitiveCount = primitiveCount;
	node->leaf.firstPrimitive = 0;

	while (true)
	{
		auto firstPrimitive = node->leaf.firstPrimitive;
		auto primitiveCount = node->leaf.primitiveCount;
		auto lastPrimitive = firstPrimitive + primitiveCount;

		int32 axis; float split, cost;
		findBestSplitPlane(firstPrimitive, lastPrimitive, vertexSize, indexSize,
			vertices, indices, primitiveData, centroidData, getIndex, axis, split, cost);

		auto nodeCost = node->getAabb().getArea() * primitiveCount;
		if (cost >= nodeCost)
		{
			if (nodeStack.empty()) break;
			else { node = nodeStack.top();  nodeStack.pop(); continue; }
		}

		auto i = firstPrimitive, j = i + primitiveCount - 1;
		while (i <= j)
		{
			if (centroidData[primitiveData[i]][axis] < split) i++;
			else std::swap(primitiveData[i], primitiveData[j--]);
		}

		auto count1 = i - firstPrimitive;
		if (count1 == 0 || count1 == primitiveCount)
		{
			if (nodeStack.empty()) break;
			else { node = nodeStack.top(); nodeStack.pop(); continue; }
		}

		auto count2 = primitiveCount - count1;
		auto leftNodeID = nodeCount;
		auto rightNodeID = nodeCount + 1;
		nodeCount += 2;
		node->child.leftNode = leftNodeID;
		node->child.primitiveCount = 0;
	
		auto node1 = &nodeData[leftNodeID];
		node1->leaf.firstPrimitive = firstPrimitive;
		node1->leaf.primitiveCount = count1;
		node1->setAabb(calculateNodeAabb(node1, vertices,
			indices, primitiveData, vertexSize, indexSize, getIndex));

		auto node2 = &nodeData[rightNodeID];
		node2->leaf.firstPrimitive = i;
		node2->leaf.primitiveCount = count2;
		node2->setAabb(calculateNodeAabb(node2, vertices,
			indices, primitiveData, vertexSize, indexSize, getIndex));

		if (count2 > count1)
		{
			std::swap(count1, count2);
			std::swap(node1, node2);
		}

		if (count1 > 2)
		{
			node = node1;
			if (count2 > 2) nodeStack.push(node2);
			continue;
		}

		if (nodeStack.empty()) break;
		else { node = nodeStack.top(); nodeStack.pop(); continue; }
	}

	nodes.resize(nodeCount);
}

//--------------------------------------------------------------------------------------------------
void Bvh::recreate(const Aabb* aabbs, const Aabb& aabb,
	uint32 aabbCount, const float3* _centroids)
{
	assert(aabbs);
	assert(aabbCount > 0);
	nodes.resize(aabbCount * 2 - 1);

	primitives.resize(aabbCount);
	auto primitiveData = primitives.data();
	for (uint32 i = 0; i < aabbCount; i++) primitiveData[i] = i;

	const float3* centroidData;
	if (!_centroids)
	{
		centroids.resize(aabbCount);
		centroidData = centroids.data();
		auto data = centroids.data();

		for (uint32 i = 0; i < aabbCount; i++)
		{
			auto aabb = aabbs[i];
			data[i] = aabb.getPosition();
		}
	}
	else centroidData = _centroids;

	auto nodeData = nodes.data();
	auto nodeCount = (uint32)1;
	auto node = &nodeData[0];
	node->setAabb(aabb);
	node->leaf.primitiveCount = aabbCount;
	node->leaf.firstPrimitive = 0;

	while (true)
	{
		auto firstPrimitive = node->leaf.firstPrimitive;
		auto primitiveCount = node->leaf.primitiveCount;
		auto lastPrimitive = firstPrimitive + primitiveCount;

		int32 axis; float split, cost;
		findBestSplitPlane(firstPrimitive, lastPrimitive, aabbs,
			primitiveData, centroidData, axis, split, cost);

		auto nodeCost = node->getAabb().getArea() * primitiveCount;
		if (cost >= nodeCost)
		{
			if (nodeStack.empty()) break;
			else { node = nodeStack.top();  nodeStack.pop(); continue; }
		}

		auto i = firstPrimitive, j = i + primitiveCount - 1;
		while (i <= j)
		{
			if (centroidData[primitiveData[i]][axis] < split) i++;
			else std::swap(primitiveData[i], primitiveData[j--]);
		}

		auto count1 = i - firstPrimitive;
		if (count1 == 0 || count1 == primitiveCount)
		{
			if (nodeStack.empty()) break;
			else { node = nodeStack.top(); nodeStack.pop(); continue; }
		}

		auto count2 = primitiveCount - count1;
		auto leftNodeID = nodeCount;
		auto rightNodeID = nodeCount + 1;
		nodeCount += 2;
		node->child.leftNode = leftNodeID;
		node->child.primitiveCount = 0;
	
		auto node1 = &nodeData[leftNodeID];
		node1->leaf.firstPrimitive = firstPrimitive;
		node1->leaf.primitiveCount = count1;
		node1->setAabb(calculateNodeAabb(node1, aabbs, primitiveData));

		auto node2 = &nodeData[rightNodeID];
		node2->leaf.firstPrimitive = i;
		node2->leaf.primitiveCount = count2;
		node2->setAabb(calculateNodeAabb(node2, aabbs, primitiveData));

		if (count2 > count1)
		{
			std::swap(count1, count2);
			std::swap(node1, node2);
		}

		if (count1 > 2)
		{
			node = node1;
			if (count2 > 2) nodeStack.push(node2);
			continue;
		}

		if (nodeStack.empty()) break;
		else { node = nodeStack.top(); nodeStack.pop(); continue; }
	}

	nodes.resize(nodeCount);
}