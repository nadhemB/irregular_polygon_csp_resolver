cmake_minimum_required(VERSION 3.10)
project(resolver_core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(resolver_core
    PRIVATE
    include
    extern/glm
    extern/json/single_include
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(resolver_core ${SRC_FILES})

# Link everything statically
target_link_libraries(resolver_core
    ${CMAKE_DL_LIBS}
)
