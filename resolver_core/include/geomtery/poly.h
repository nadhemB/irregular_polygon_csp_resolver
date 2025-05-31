#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <array>
#include <io/serializable.h>
#include <string>
#include "io/json_adapter.h"

class Polygon : public Serializable<Polygon>
{
public:
    Polygon() = default;

    explicit Polygon(const std::vector<glm::vec2> &points)
        : vertices(points) {}

    const std::vector<glm::vec2> &getVertices() const { return vertices; }
    void setVertices(const std::vector<glm::vec2> &points) { vertices = points; }

    float signedArea() const
    {
        float a = 0.0f;
        int n = static_cast<int>(vertices.size());
        if (n < 3)
            return 0.0f; // Not a polygon

        for (int i = 0; i < n; ++i)
        {
            const glm::vec2 &curr = vertices[i];
            const glm::vec2 &next = vertices[(i + 1) % n];
            a += curr.x * next.y - next.x * curr.y;
        }
        return 0.5f * std::abs(a);
    }

    std::vector<std::array<glm::vec2, 3>> triangulate() const
    {
        // TODO: implement triangulation
        return {};
    }

    std::string toJsonString() const override
    {
        nlohmann::json j;
        j["vertices"] = vertices;
        return j.dump(4); // pretty print
    }

    Polygon fromJSON(std::string json) override
    {
        nlohmann::json j = nlohmann::json::parse(json);
        vertices = j.at("vertices").get<std::vector<glm::vec2>>();
        return *this;
    };

private:
    std::vector<glm::vec2> vertices;
};
