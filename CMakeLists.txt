cmake_minimum_required(VERSION 3.10)
project(OGLProject)

option(OGL_BUILD_EXAMPLE "Build example" OFF)

add_subdirectory(OGL)

if (OGL_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
