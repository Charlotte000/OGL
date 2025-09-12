cmake_minimum_required(VERSION 3.10)
project(OGL)

include(FetchContent)
set(CMAKE_CXX_STANDARD 17)

add_library(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Texture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ArrayBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/FrameBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VertexArray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/StorageBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/UniformBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ElementArrayBuffer.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# GLM v1.0.1
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG        1.0.1
)
FetchContent_MakeAvailable(glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${glm_SOURCE_DIR})
target_compile_definitions(${PROJECT_NAME} PRIVATE GLM_ENABLE_EXPERIMENTAL)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

# GLEW 2.2.0
FetchContent_Declare(
    glew
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    URL      https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
    URL_HASH SHA256=a9046a913774395a095edcc0b0ac2d81c3aacca61787b39839b941e9be14e0d4
)
FetchContent_MakeAvailable(glew)
target_include_directories(${PROJECT_NAME} PUBLIC ${glew_SOURCE_DIR}/include)
target_sources(${PROJECT_NAME} PUBLIC ${glew_SOURCE_DIR}/src/glew.c)
target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)

# GLFW 3.4
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ${glfw_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        5c205738c191bcb0abc65c4febfa9bd25ff35234
)
FetchContent_MakeAvailable(stb)
target_include_directories(${PROJECT_NAME} PRIVATE ${stb_SOURCE_DIR})
