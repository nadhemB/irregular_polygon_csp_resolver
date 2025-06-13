#pragma once
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <array>
#include <vector>
#include "geometry/shapes2d.h"
#include "maths/math_tools.h"
class Triangle
{
public:

    Triangle() = default;
    Triangle(const glm::vec2 &v0, const glm::vec2 &v1, const glm::vec2 &v2):vertices{v0,v1,v2}
    {
        calculateBisectors();
        calculateMedians();
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

    std::vector<glm::vec2> getVertices() const
    {
        std::vector<glm::vec2> out = {vertices[0], vertices[1], vertices[2]};
        return out;
    }

    Circle innerCicrcle() const {
        glm::vec2 innerCenter = math::lineIntersection(bisectors[0], bisectors[1]);
        glm::vec2 measurePoint = math::project(innerCenter, vertices[0], vertices[1]);
        float innerRadius = glm::length(innerCenter - measurePoint);
        return Circle(innerCenter, innerRadius);
    }

    Circle circumCircle() const {
        glm::vec2  circumCenter = math::lineIntersection(medians[0], medians[1]);
        float radius = glm::length(circumCenter - vertices[0]);
        return Circle(circumCenter, radius);
    }

    void calculateBisectors()  {
        auto e01 = glm::normalize(vertices[1] - vertices[0]);
        auto e02 = glm::normalize(vertices[2] - vertices[0]);
        bisectors[0] = Ray(vertices[0], glm::normalize(e01 + e02));

        auto e12 = glm::normalize(vertices[2] - vertices[1]);
        auto e10 = glm::normalize(vertices[0] - vertices[1]);
        bisectors[1] = Ray(vertices[1], glm::normalize(e12 + e10));

        auto e20 = glm::normalize(vertices[0] - vertices[2]);
        auto e21 = glm::normalize(vertices[1] - vertices[2]);
        bisectors[2] = Ray(vertices[2], glm::normalize(e20 + e21));;
    }

    void calculateMedians() {
        auto e0 = vertices[2] - vertices[1];
        auto e1 = vertices[0] - vertices[2];
        auto e2 = vertices[1] - vertices[0];
        auto n0 = glm::vec2(-e0.y, e0.x);
        auto n1 = glm::vec2(-e1.y, e1.x);
        auto n2 = glm::vec2(-e2.y, e2.x);
        medians[0] = Ray((vertices[2] + vertices[1]) * 0.5f, n0);
        medians[1] = Ray((vertices[2] + vertices[0]) * 0.5f, n1);
        medians[2] = Ray((vertices[0] + vertices[1]) * 0.5f, n2);
    }

    std::array<glm::vec2, 3> vertices;


private:
    std::array<Ray, 3> bisectors{ Ray{glm::vec2(0), glm::vec2(0)},
                        Ray{glm::vec2(0), glm::vec2(0)},
                        Ray{glm::vec2(0), glm::vec2(0)} };

    std::array<Ray, 3> medians{ Ray{glm::vec2(0), glm::vec2(0)},
                        Ray{glm::vec2(0), glm::vec2(0)},
                        Ray{glm::vec2(0), glm::vec2(0)} };
};
