#pragma once
#include <glm/vec3.hpp>

struct PrintConfig
{
    glm::vec3 bgColor = glm::vec3(1);
    glm::vec3 fillColor = glm::vec3(.8, .8, .8);
    glm::vec3 borderColor = glm::vec3(1.0, 0, 0);
    glm::vec3 strokeColor = glm::vec3(0);
    float strokeWidth = 1.0f;
};