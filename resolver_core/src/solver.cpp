#include <iostream>
#include <glm/glm.hpp>
#include "geomtery/poly.h"
#include "solver/problem.h"
#include <fstream>
#include <sstream>
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
        Problem problem;
        problem.fromJSON(content);
        std::cout << problem.toJsonString() << std::endl;
    }
    catch (std::ifstream::failure &e)
    {
        std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }

    std::cout << "press any key to exit!" << std::endl;
    std::cin.get();
    return 0;
}