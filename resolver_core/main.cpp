#include <iostream>
#include <glm/glm.hpp>
#include "geomtery/poly.h"
#include "solver/problem.h"
#include <fstream>
#include <sstream>
#include "solver/solver.h"

Problem problem;

int main()
{

    std::ifstream problemFile;
    problemFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        problemFile.open("assets/problem_data.json");
        std::stringstream stream;
        stream << problemFile.rdbuf();
        std::string content = stream.str();
        std::cout << content << std::endl;
        problem.fromJSON(content);
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    Solver solver = Solver(problem);
    solver.solve();

    std::cout << "press any key to exit!" << std::endl;
    std::cin.get();
    return 0;
}