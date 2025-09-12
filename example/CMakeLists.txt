cmake_minimum_required(VERSION 3.10)
project(Example)

include(FetchContent)
set(CMAKE_CXX_STANDARD 17)

add_executable(
    ${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# OGL
target_link_libraries(${PROJECT_NAME} PRIVATE OGL)
