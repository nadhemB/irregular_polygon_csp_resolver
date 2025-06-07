cmake_minimum_required(VERSION 3.10)
project(resolver_core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SHARED_SOURCES
    extern/tinyfiledialogs/tinyfiledialogs.c
)

set(SHARED_INCLUDE_DIRS
    include
    extern/glm
    extern/json/single_include
    extern/tinyfiledialogs
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB TEST_FILES tests/*.cpp)

if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in src/")
endif()

add_executable(resolver_core ${SRC_FILES} ${SHARED_SOURCES} main.cpp)

target_include_directories(resolver_core PRIVATE
    ${SHARED_INCLUDE_DIRS}
)

target_link_libraries(resolver_core
    ${CMAKE_DL_LIBS}
)

add_custom_command(
    TARGET resolver_core POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:resolver_core>/assets
)

file(GLOB TEST_FILES tests/*.cpp)

if(TEST_FILES)
    add_executable(resolver_tests ${TEST_FILES} ${SRC_FILES} ${SHARED_SOURCES})

    target_include_directories(resolver_tests PRIVATE
        ${SHARED_INCLUDE_DIRS}
    )

    target_link_libraries(resolver_tests PRIVATE
        ${CMAKE_DL_LIBS}
    )

    # Enable ctest if needed
    enable_testing()
    add_test(NAME SvgPrinterTest COMMAND resolver_tests)
endif()
