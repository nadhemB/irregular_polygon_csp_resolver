cmake_minimum_required(VERSION 3.10)
project(resolver_core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in src/")
endif()

add_executable(resolver_core ${SRC_FILES})

target_include_directories(resolver_core PRIVATE
    include
    extern/glm
    extern/json/single_include
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
