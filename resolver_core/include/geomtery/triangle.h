#pragma once
#include <glm/vec2.hpp> // glm::vec2
#include <array>

class Triangle
{
public:
    std::array<glm::vec2, 3> vertices;

    Triangle() = default;
    Triangle(const glm::vec2 &v0, const glm::vec2 &v1, const glm::vec2 &v2)
    {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }

    float signedArea() const
    {
        const auto &a = vertices[0];
        const auto &b = vertices[1];
        const auto &c = vertices[2];
        return 0.5f * ((a.x * (b.y - c.y)) + (b.x * (c.y - a.y)) + (c.x * (a.y - b.y)));
    }

    bool isCCW() const
    {
        return signedArea() > 0.0f;
    }
};
