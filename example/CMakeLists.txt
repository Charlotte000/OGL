cmake_minimum_required(VERSION 3.10)
project(Example)

include(FetchContent)
set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/SceneExample.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RayTracerExample.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/InstancedExample.hpp
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

# ImGui v1.92.5-docking
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.92.5-docking
)
FetchContent_MakeAvailable(imgui)
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${imgui_SOURCE_DIR}
    PRIVATE ${imgui_SOURCE_DIR}/backends
)
target_sources(
    ${PROJECT_NAME}
    PRIVATE ${imgui_SOURCE_DIR}/imgui.cpp
    PRIVATE ${imgui_SOURCE_DIR}/imgui_draw.cpp
    PRIVATE ${imgui_SOURCE_DIR}/imgui_tables.cpp
    PRIVATE ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    PRIVATE ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    PRIVATE ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_compile_definitions(${PROJECT_NAME} PRIVATE IMGUI_DEFINE_MATH_OPERATORS)
