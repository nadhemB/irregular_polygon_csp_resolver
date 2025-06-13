#pragma once
#include <glm/ext/vector_float2.hpp>

class Edge
{
public:
    Edge(glm::vec2 v0, glm::vec2 v1) : v0(v0), v1(v1) {}

    bool operator==(const Edge &other) const
    {
        bool a = v0 == other.v0 && v1 == other.v1;
        bool b = v0 == other.v1 && v1 == other.v0;
        return a || b;
    }

    glm::vec2 getV0() const
    {
        return v0;
    }

    glm::vec2 getV1() const
    {
        return v1;
    }

private:
    glm::vec2 v0;
    glm::vec2 v1;
};

namespace std
{
    template <>
    struct hash<Edge>
    {
        size_t operator()(const Edge &e) const
        {
            auto hash_vec2 = [](const glm::vec2 &v)
            {
                size_t h1 = std::hash<float>()(v.x);
                size_t h2 = std::hash<float>()(v.y);
                return h1 ^ (h2 << 1);
            };
            size_t h_v0 = hash_vec2(e.getV0());
            size_t h_v1 = hash_vec2(e.getV1());
            return h_v0 ^ h_v1;
        }
    };
}