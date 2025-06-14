#include "tests/opencl_query_test.h"
#include <iostream>
#include "tests/delaunay_test.h"
#include "tests/test_hash.h"
int main()
{
    // queryOpenCLDevices();
    // testTriangleHash();
    //test_hash();
    delaunayTest();
    std::cout << "press any key to exit!" << std::endl;
    std::cin.get();
    return 0;
}