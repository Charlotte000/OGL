/**
 * @file Image3D.h
 */
#pragma once

#include <vector>
#include <filesystem>

#include <glm/glm.hpp>

namespace OGL
{

/**
 * @brief Image class that represents a 3D image with pixel data stored in a RAM.
 * 
 * Each pixel is represented as an RGBA floating-point values.
 */
struct Image3D
{
public:
    /**
     * @brief Size of the image in pixels (width, height, depth).
     */
    glm::uvec3 size;

    /**
     * @brief Pixel data stored in a row-major order.
     * 
     * Each pixel consists of 4 floating-point values (R, G, B, A).
     * The total number of pixels is size.x * size.y * size.z.
     */
    std::vector<glm::vec4> pixels;

    /**
     * @brief Create an image with the specified size and optional pixel data.
     * 
     * If the pixel data is not provided, the pixel data is initialized to zeros.
     * 
     * @param size Size of the image in pixels (width, height, depth).
     * @param pixels Pixel data.
     */
    Image3D(glm::uvec3 size, const std::initializer_list<glm::vec4>& pixels = {});

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x, y, z).
     * @return Reference to the pixel at the specified coordinates.
     */
    glm::vec4& operator[](glm::uvec3 coords);

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x, y, z).
     * @return Constant reference to the pixel at the specified coordinates.
     */
    const glm::vec4& operator[](glm::uvec3 coords) const;
};

}
