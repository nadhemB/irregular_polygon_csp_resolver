#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include <array>
#include <io/serializable.h>
#include <string>
#include "io/json_adapter.h"
#include <maths/math_tools.h>

class Polygon : public Serializable
{
public:
    Polygon() = default;
    explicit Polygon(const std::vector<glm::vec2> &points)
        : vertices(points) {}

    bool operator==(const Polygon& other) const {
        if (vertices.size() != other.getVertices().size())
            return false;
        bool equal = true;
        std::vector<glm::vec2> ordered0 = math::order(vertices);
        std::vector<glm::vec2> reversed = std::vector<glm::vec2>(vertices.begin(), vertices.end());
        reversed = math::order(reversed);
        std::reverse(reversed.begin(), reversed.end());
        std::vector<glm::vec2> ordered1 = math::order(other.getVertices());

        for (int i = 0; i < ordered0.size(); i++) {
            glm::bvec2 comp = glm::epsilonEqual(ordered0[i], ordered1[i], static_cast<float>(1e-6));
            if (!comp.x || !comp.y) {
                equal = false;
                break;
            }
        }
        if (!equal) {
            equal = true;
            for (int i = 0; i < ordered0.size(); i++) {
                glm::bvec2 comp = glm::epsilonEqual(reversed[i], ordered1[i], static_cast<float>(1e-6));
                if (!comp.x || !comp.y) {
                    equal = false;
                    break;
                }
            }
        }
        return equal;
    }

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
        return 0.5f * a;
    }

    void setWinding(short winding)
    {
        float currentWinding = signedArea();
        if (currentWinding == 0)
            return;

        if ((winding * currentWinding < 0))
        {
            std::reverse(vertices.begin(), vertices.end());
        }
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

    void fromJSON(const std::string &json) override
    {
        nlohmann::json j = nlohmann::json::parse(json);
        vertices = j.get<std::vector<glm::vec2>>();
    }

    std::vector<glm::vec2> vertices;
};
