cmake_minimum_required(VERSION 3.10)
project(Example)

include(FetchContent)
set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# GLM
target_compile_definitions(${PROJECT_NAME} PRIVATE GLM_ENABLE_EXPERIMENTAL)

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
