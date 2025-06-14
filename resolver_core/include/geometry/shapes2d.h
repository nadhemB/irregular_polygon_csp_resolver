#pragma once
#include <glm/glm.hpp>

struct Circle
{
    glm::vec2 center;
    float radius;

    bool contains(const glm::vec2& point) {
        return glm::length(center - point) <= radius;
    }
};

struct Ray
{

    Ray& operator=(const Ray& other) = default;
    Ray(const glm::vec2 &origin, const glm::vec2 &direction)
        : origin(origin), dir(glm::normalize(direction)) {}

    glm::vec2 origin;
    glm::vec2 dir;
};
