#include "solver/solver.h"

void Solver::solve()
{
    float totalArea = 0;
    for (Polygon poly : problem.getPieces())
    {
        totalArea += glm::abs(poly.signedArea());
    }
    std::cout << "total area: " + std::to_string(totalArea) << std::endl;
}