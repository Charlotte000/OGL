/**
 * @file Image1D.h
 */
#pragma once

#include "OGL/Image2D.h"

namespace OGL
{

/**
 * @brief Image class that represents a 1D image with pixel data stored in a RAM.
 * 
 * Each pixel is represented as an RGBA floating-point values.
 */
struct Image1D
{
public:
    /**
     * @brief Size of the image in pixels (width).
     */
    glm::uvec1 size;

    /**
     * @brief Pixel data.
     * 
     * Each pixel consists of 4 floating-point values (R, G, B, A).
     * The total number of pixels is size.x.
     */
    std::vector<glm::vec4> pixels;

    /**
     * @brief Create an image with the specified size and optional pixel data.
     * 
     * If the pixel data is not provided, the pixel data is initialized to zeros.
     * 
     * @param size Size of the image in pixels (width).
     * @param pixels Pixel data.
     */
    Image1D(glm::uvec1 size, const std::initializer_list<glm::vec4>& pixels = {});

    /**
     * @brief Create an image with the specified size and pixel data.
     * @param size Size of the image in pixels (width).
     * @param data Pixel data where each pixel consists of 4 floating-point values (R, G, B, A).
     */
    Image1D(glm::uvec1 size, const void* data);

    /**
     * @brief Convert to 2D image.
     * @return The copied 2D image with height 1.
     */
    operator Image2D() const;

    /**
     * @brief Convert to 3D image.
     * @return The copied 3D image with height 1 and depth 1.
     */
    operator Image3D() const;

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x).
     * @return Reference to the pixel at the specified coordinates.
     */
    glm::vec4& operator[](glm::uvec1 coords);

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x).
     * @return Constant reference to the pixel at the specified coordinates.
     */
    const glm::vec4& operator[](glm::uvec1 coords) const;
};

}
