//--------------------------------------------------------------------------------------------------
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
//--------------------------------------------------------------------------------------------------

#pragma once
#include "math/aabb.hpp"

#include <stack>
#include <vector>

namespace math
{

using namespace std;

// Bounding Volume Hierarchy
struct Bvh
{
	struct BaseNode
	{
		float3 min = float3(0.0f);
		uint32 primitiveCount = 0;
		float3 max = float3(0.0f);
	};
	struct ChildNode
	{
		float3 min = float3(0.0f);
		uint32 primitiveCount = 0;
		float3 max = float3(0.0f);
		uint32 leftNode = 0;
	};
	struct LeafNode
	{
		float3 min = float3(0.0f);
		uint32 primitiveCount = 0;
		float3 max = float3(0.0f);
		uint32 firstPrimitive = 0;
	};
	union Node
	{
		BaseNode base;
		ChildNode child;
		LeafNode leaf;
		Node() : leaf() { }
		
		bool isLeaf() const noexcept { return base.primitiveCount; }
		Aabb getAabb() const noexcept { return Aabb(base.min, base.max); }
		void setAabb(const Aabb& aabb) noexcept
		{ base.min = aabb.getMin(), base.max = aabb.getMax(); }
	};
private:
	vector<Node> nodes;
	vector<uint32> primitives;
	vector<float3> centroids;
	stack<Node*> nodeStack;
public:
	Bvh(const uint8* vertices, const uint8* indices,
		const Aabb& aabb, uint32 indexCount,uint32 vertexSize,
		uint32 indexSize, const float3* centroids = nullptr);
	Bvh(const Aabb* aabbs, const Aabb& aabb,
		uint32 aabbCount, const float3* centroids = nullptr);
	Bvh() = default;
	
	const vector<Node>& getNodes() const noexcept { return nodes; }
	const vector<uint32>& getPrimitives() const noexcept { return primitives; }
	const vector<float3>& getCentroids() const noexcept { return centroids; }

	void recreate(const uint8* vertices, const uint8* indices,
		const Aabb& aabb, uint32 indexCount, uint32 vertexSize,
		uint32 indexSize, const float3* centroids = nullptr);
	void recreate(const Aabb* aabbs, const Aabb& aabb,
		uint32 aabbCount, const float3* centroids = nullptr);
};

} // math