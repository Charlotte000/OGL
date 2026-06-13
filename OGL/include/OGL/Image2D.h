/**
 * @file Image2D.h
 */
#pragma once

#include "OGL/Image3D.h"

namespace OGL
{

/**
 * @brief Image class that represents a 2D image with pixel data stored in a RAM.
 * 
 * Each pixel is represented as an RGBA floating-point values.
 */
struct Image2D
{
public:
    /**
     * @brief Size of the image in pixels (width, height).
     */
    glm::uvec2 size;

    /**
     * @brief Pixel data stored in a row-major order.
     * 
     * Each pixel consists of 4 floating-point values (R, G, B, A).
     * The total number of floats is size.x * size.y * 4.
     */
    std::vector<glm::vec4> pixels;

    /**
     * @brief Load an image from a file.
     * @param path Path to the image file.
     * @throw std::runtime_error if the image cannot be loaded.
     * @throw std::invalid_argument if the size of the image does not match the number of pixels provided.
     */
    Image2D(const std::filesystem::path& path);

    /**
     * @brief Create an image with the specified size and optional pixel data.
     * 
     * If the pixel data is not provided, the pixel data is initialized to zeros.
     * 
     * @param size Size of the image in pixels (width, height).
     * @param pixels Pixel data in a row-major order. If empty, the pixel data is initialized to zeros.
     * @throw std::invalid_argument if the size of the image does not match the number of pixels provided.
     */
    Image2D(glm::uvec2 size, const std::initializer_list<glm::vec4>& pixels = {});

    /**
     * @brief Create an image with the specified size and pixel data.
     * @param size Size of the image in pixels (width, height).
     * @param data Pixel data where each pixel consists of 4 floating-point values (R, G, B, A) in a row-major order.
     * @throw std::invalid_argument if the size of the image does not match the number of pixels provided.
     */
    Image2D(glm::uvec2 size, const void* data);

    /**
     * @brief Convert to 3D image.
     * @return The copied 3D image with depth 1.
     */
    operator Image3D() const;

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x, y).
     * @return Reference to the pixel at the specified coordinates.
     * @throw std::out_of_range if the pixel coordinates are out of range.
     */
    glm::vec4& operator[](glm::uvec2 coords);

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x, y).
     * @return Constant reference to the pixel at the specified coordinates.
     * @throw std::out_of_range if the pixel coordinates are out of range.
     */
    const glm::vec4& operator[](glm::uvec2 coords) const;

    /**
     * @brief Save the image to a file.
     * @param path Path to the output file. Supported formats: png, hdr, jpg, bmp.
     * @throw std::runtime_error if the image cannot be saved.
     */
    void saveToFile(const std::filesystem::path& path) const;

    /**
     * @brief Resize the image to the specified size using nearest-neighbor interpolation.
     * @param size New size of the image in pixels (width, height).
     * @return Resized image.
     * @throw std::runtime_error if failed to resize the image.
     */
    Image2D resize(glm::uvec2 size) const;
};

}
