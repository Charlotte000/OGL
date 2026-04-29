cmake_minimum_required(VERSION 3.10)
project(OGLProject)

option(OGL_BUILD_EXAMPLE "Build example" OFF)
option(OGL_BUILD_TESTS   "Build tests"   OFF)

add_subdirectory(OGL)

if (OGL_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if (OGL_BUILD_TESTS)
    include(CTest)
    include(GoogleTest)

    enable_testing()
    add_subdirectory(tests)
endif()
