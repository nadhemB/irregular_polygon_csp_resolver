#pragma once
#include "solver/problem.h"
#include "solver/solution.h"
#include <glm/glm.hpp>
#include <iostream>
#include <string>

class Solver
{
public:
    Solver(Problem &problem) : problem(problem) {}
    void solve();

private:
    Problem &problem;
    Solution bestSolution;
};