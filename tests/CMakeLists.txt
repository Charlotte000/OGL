cmake_minimum_required(VERSION 3.10)
project(Tests)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BufferTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureTest.cpp
)

# OGL
target_link_libraries(${PROJECT_NAME} PRIVATE OGL)

# GLFW 3.4
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Gtest v1.17.0
FetchContent_Declare(
    gtest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
)
FetchContent_MakeAvailable(gtest)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest_main)
gtest_discover_tests(${PROJECT_NAME})
