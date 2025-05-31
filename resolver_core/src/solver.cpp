#include <iostream>
#include <glm/glm.hpp>
#include "geomtery/poly.h"
#include "solver/problem.h"

int main()
{

    std::vector<glm::vec2> vertices;
    vertices.push_back(glm::vec2(0, 0));
    vertices.push_back(glm::vec2(1, 0));
    vertices.push_back(glm::vec2(1, 1));
    vertices.push_back(glm::vec2(0, 1));
    Polygon poly = Polygon(vertices);
    std::vector<Polygon> pieces;
    pieces.push_back(poly);
    Problem problem(glm::vec2(2500, 1800), pieces);

    std::cout << problem.toJsonString() << std::endl;
    std::cerr << "press any key to exit!";
    std::cin.get();
    return 0;
}