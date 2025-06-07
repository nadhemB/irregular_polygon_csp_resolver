#include "opencl_query_test.h"

#include <iostream>

int main()
{
    queryOpenCLDevices();

    std::cout << "press any key to exit!" << std::endl;
    std::cin.get();
    return 0;
}