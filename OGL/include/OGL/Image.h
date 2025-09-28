/**
 * @file Image.h
 */
#pragma once

#include <vector>
#include <filesystem>

#include <glm/glm.hpp>

namespace OGL
{

/**
 * @brief Image class that represents a 2D image with pixel data stored in a RAM.
 * 
 * Each pixel is represented as an RGBA floating-point values.
 */
struct Image
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
    std::vector<float> pixels;

    /**
     * @brief Load an image from a file.
     * @param path Path to the image file.
     * @throw std::runtime_error if the image cannot be loaded.
     */
    Image(const std::filesystem::path& path);

    /**
     * @brief Create an image with the specified size and optional pixel data.
     * 
     * If the pixel data is not provided or its size does not match the image size,
     * the pixel data is initialized to zeros.
     * 
     * @param size Size of the image in pixels (width, height).
     * @param pixels Pixel data.
     */
    Image(glm::uvec2 size, const std::initializer_list<float>& pixels = {});

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
     */
    Image resize(glm::uvec2 size) const;

    /**
     * @brief Get the pixel value at the specified coordinates.
     * 
     * Asserts that the coordinates are within the image bounds.
     * 
     * @param coords Coordinates of the pixel (x, y) where (0, 0) is the top-left corner.
     * @return Pixel value as a glm::vec4 (R, G, B, A).
     */
    glm::vec4 get(glm::uvec2 coords) const;

    /**
     * @brief Get the pixel value at the specified linear index.
     * 
     * Asserts that the index is within the image bounds.
     * 
     * @param index Linear index of the pixel (0 <= index < size.x * size.y).
     * @return Pixel value as a glm::vec4 (R, G, B, A).
     */
    glm::vec4 get(size_t index) const;

    /**
     * @brief Set the pixel value at the specified coordinates.
     * 
     * Asserts that the coordinates are within the image bounds.
     * 
     * @param coords Coordinates of the pixel (x, y) where (0, 0) is the top-left corner.
     * @param value New pixel value as a glm::vec4 (R, G, B, A).
     */
    void set(glm::uvec2 coords, glm::vec4 value);

    /**
     * @brief Set the pixel value at the specified linear index.
     * 
     * Asserts that the index is within the image bounds.
     * 
     * @param index Linear index of the pixel (0 <= index < size.x * size.y).
     * @param value New pixel value as a glm::vec4 (R, G, B, A).
     */
    void set(size_t index, glm::vec4 value);
};

}
