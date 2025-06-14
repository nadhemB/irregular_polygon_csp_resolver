#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>
#include "geometry/shapes2d.h"
#include <random>

namespace math {


    glm::vec2 lineIntersection(const Ray& r1, const Ray& r2);

    int random_int(int min, int max);

    glm::vec2* calculate_boundaries(std::vector<glm::vec2> points);

    glm::vec2 project(glm::vec2 point, glm::vec2 a, glm::vec2 b);

    std::vector<glm::vec2> order(std::vector<glm::vec2> list);

    bool verticesEquality(const std::vector<glm::vec2>& vertices0,
        const std::vector<glm::vec2>& vertices1);

}

