#pragma once
#include <geometry/poly.h>
#include <glm/gtc/epsilon.hpp>
#include "maths/math_tools.h"



struct vertices_hasher {
    std::size_t operator()(const std::vector<glm::vec2>& vertices) {
        std::vector<glm::vec2> reversed;
        for (int i = vertices.size() -1; i >= 0; i--)
            reversed.push_back(vertices[i]);
        return hash(reversed) + hash(vertices);
    }

    size_t hash(const std::vector<glm::vec2>& vertices) {
        std::vector<glm::vec2> orderedList = math::order(vertices);
        //hash
        std::size_t seed = orderedList.size();
        for (const auto& v : orderedList) {
            glm::ivec2 integeized(v.x * 1e3, v.y * 1e3);
            auto h1 = std::hash<int>{}(integeized.x);
            auto h2 = std::hash<int>{}(integeized.y);
            size_t vertexHash = h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
            seed ^= vertexHash + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};








struct PolyHasher
{
	std::size_t operator()(const Polygon& poly) const {
		vertices_hasher hasher;
		return hasher.operator()(poly.getVertices());
	}
};

struct TriangleHasher
{
	std::size_t operator()(const Triangle& triangle) const {
		vertices_hasher hasher;
		return hasher.operator()(triangle.getVertices());
	}
};

struct EdgeHasher
{
	std::size_t operator()(const Edge& edge) const{

		std::vector<glm::vec2> vertices{ edge.getV0(), edge.getV1() };
		vertices_hasher hasher;
		return hasher.operator()(vertices);
	}
};


