cmake_minimum_required(VERSION 3.10)
project(resolver_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenCL)

if(NOT OpenCL_FOUND)
    message(FATAL_ERROR "OpenCL not found on your system. Please install OpenCL SDK or drivers.")
endif()

message(STATUS "OpenCL include dirs: ${OpenCL_INCLUDE_DIRS}")
message(STATUS "OpenCL libraries: ${OpenCL_LIBRARIES}")

set(SHARED_SOURCES
    extern/tinyfiledialogs/tinyfiledialogs.c
)

set(SHARED_INCLUDE_DIRS
    include
    extern/glm
    extern/json/single_include
    extern/tinyfiledialogs
    ${OpenCL_INCLUDE_DIRS}
)

set(SHARED_LIBS
    ${CMAKE_DL_LIBS}
    ${OpenCL_LIBRARIES}
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB TEST_FILES tests/*.cpp)

if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in src/")
endif()

add_executable(resolver_core ${SRC_FILES} ${SHARED_SOURCES} main.cpp "include/maths/hashs.h")

target_include_directories(resolver_core PRIVATE
    ${SHARED_INCLUDE_DIRS}
)

target_link_libraries(resolver_core
    ${SHARED_LIBS}
)

add_custom_command(
    TARGET resolver_core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:resolver_core>/assets
)



        message("Configuring test executable")

    add_executable(solver_test  ${SRC_FILES} ${SHARED_SOURCES} test_runner.cpp "include/maths/hashs.h")

    target_include_directories(solver_test PRIVATE
        ${SHARED_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/tests
    )

    target_link_libraries(solver_test PRIVATE
        ${SHARED_LIBS}
    )

    # Enable ctest if needed
    enable_testing()
    add_test(NAME SolverTest COMMAND solver_test)


