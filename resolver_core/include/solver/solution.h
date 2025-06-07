#pragma once
#include <vector>
#include "geomtery/poly.h"
#include <glm/ext/matrix_float4x4.hpp>

class Solution
{
public:
    Solution() = default;
    std::vector<Polygon> panels;
    std::vector<Polygon> pieces;
    std::vector<glm::mat4> transforms;
    std::vector<glm::ivec3> layout;
};