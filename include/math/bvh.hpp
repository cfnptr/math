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

/***********************************************************************************************************************
 * @file
 * @brief Common Bounding Volume Hierarchy functions. (BVH)
 * @details Based on this: https://jacco.ompf2.com/2022/04/13/how-to-build-a-bvh-part-1-basics/
 */

#pragma once
#include "math/aabb.hpp"

#include <stack>
#include <vector>

namespace math
{

using namespace std;

/***********************************************************************************************************************
 * @brief Bounding Volume Hierarchy container. (BVH)
 * 
 * @details
 * A data structure commonly used in ray tracing, and collision detection to efficiently manage and process large sets 
 * of geometric objects, such as triangles or 3D models. The BVH organizes these objects into a hierarchical tree of 
 * bounding volumes (usually axis-aligned bounding boxes or spheres), allowing for faster queries related to visibility, 
 * collisions, and intersections.
 */
struct Bvh
{
	/**
	 * @brief BVH hierarchy base node container.
	 * @details See the @ref Bvh::Node.
	 */
	struct BaseNode
	{
		float3 min = float3(0.0f);
		uint32 primitiveCount = 0;
		float3 max = float3(0.0f);
	};
	/**
	 * @brief BVH hierarchy child node container.
	 * @details See the @ref Bvh::Node.
	 */
	struct ChildNode
	{
		float3 min = float3(0.0f);
		uint32 primitiveCount = 0;
		float3 max = float3(0.0f);
		uint32 leftNode = 0;
	};
	/**
	 * @brief BVH hierarchy leaf node container.
	 * @details See the @ref Bvh::Node.
	 */
	struct LeafNode
	{
		float3 min = float3(0.0f);
		uint32 primitiveCount = 0;
		float3 max = float3(0.0f);
		uint32 firstPrimitive = 0;
	};
	/**
	 * @brief BVH hierarchy node container.
	 * 
	 * @details
	 * The "hierarchy" in BVH refers to the tree structure of bounding volumes. Each internal node in the tree represents 
	 * a bounding volume that contains other, smaller bounding volumes (either other internal nodes or leaf nodes). 
	 * The leaf nodes of the tree contain the actual geometric objects (e.g., triangles in a 3D model).
	 */
	union Node
	{
		BaseNode base;
		ChildNode child;
		LeafNode leaf;
		Node() : leaf() { }
		
		/**
		 * @brief Returns true if this is leaf node. (Contain the actual geometric objects)
		 */
		bool isLeaf() const noexcept { return base.primitiveCount; }
		/**
		 * @brief Returns node Axis Aligned Bounding Box. (AABB)
		 */
		Aabb getAabb() const noexcept { return Aabb(base.min, base.max); }
		/**
		 * @brief Sets node Axis Aligned Bounding Box. (AABB)
		 * @param[in] aabb target aabb value
		 */
		void setAabb(const Aabb& aabb) noexcept { base.min = aabb.getMin(), base.max = aabb.getMax(); }
	};
private:
	vector<Node> nodes;
	vector<uint32> primitives;
	vector<float3> centroids;
	stack<Node*> nodeStack;
public:
	/*******************************************************************************************************************
	 * @brief Creates a new BVH from the triangle array.
	 * 
	 * @param[in] vertices target vertex array
	 * @param[in] indices target index array
	 * @param[in] aabb root node AABB
	 * @param indexCount index array size
	 * @param vertexSize size of the vertex in bytes
	 * @param indexSize size of the index in bytes
	 * @param centroids precalculated centroid array
	 */
	Bvh(const uint8* vertices, const uint8* indices, const Aabb& aabb, uint32 indexCount,
		uint32 vertexSize, uint32 indexSize, const float3* centroids = nullptr);
	/**
	 * @brief Creates a new BVH from the AABB array.
	 *
	 * @param[in] aabbs target AABB array
	 * @param[in] aabb root node AABB
	 * @param aabbCount AABB array size
	 * @param centroids precalculated centroid array
	 */
	Bvh(const Aabb* aabbs, const Aabb& aabb, uint32 aabbCount, const float3* centroids = nullptr);
	/**
	 * @brief Creates a new empty BVH.
	 */
	Bvh() = default;
	
	/**
	 * @brief Returns BVH node array.
	 */
	const vector<Node>& getNodes() const noexcept { return nodes; }
	/**
	 * @brief Returns BVH primitive array.
	 */
	const vector<uint32>& getPrimitives() const noexcept { return primitives; }
	/**
	 * @brief Returns BVH centroid array.
	 */
	const vector<float3>& getCentroids() const noexcept { return centroids; }

	/**
	 * @brief Recreates BVH from the triangle array.
	 *
	 * @param[in] vertices target vertex array
	 * @param[in] indices target index array
	 * @param[in] aabb root node AABB
	 * @param indexCount index array size
	 * @param vertexSize size of the vertex in bytes
	 * @param indexSize size of the index in bytes
	 * @param centroids precalculated centroid array or null
	 */
	void recreate(const uint8* vertices, const uint8* indices, const Aabb& aabb, uint32 indexCount,
		uint32 vertexSize, uint32 indexSize, const float3* centroids = nullptr);
	/**
	 * @brief Recreates BVH from the AABB array.
	 *
	 * @param[in] aabbs target AABB array
	 * @param[in] aabb root node AABB
	 * @param aabbCount AABB array size
	 * @param centroids precalculated centroid array or null
	 */
	void recreate(const Aabb* aabbs, const Aabb& aabb, uint32 aabbCount, const float3* centroids = nullptr);

	// TODO: add traverse function
};

} // namespace math