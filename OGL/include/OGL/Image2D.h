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
    enum class ResizeEdge
    {
        CLAMP = 0,
        REFLECT = 1,
        WRAP = 2,
        ZERO = 3,
    };

    enum class ResizeFilter
    {
        DEFAULT      = 0,  // use same filter type that easy-to-use API chooses
        BOX          = 1,  // A trapezoid w/1-pixel wide ramps, same result as box for integer scale ratios
        TRIANGLE     = 2,  // On upsampling, produces same results as bilinear texture filtering
        CUBICBSPLINE = 3,  // The cubic b-spline (aka Mitchell-Netrevalli with B=1,C=0), gaussian-esque
        CATMULLROM   = 4,  // An interpolating cubic spline
        MITCHELL     = 5,  // Mitchell-Netrevalli filter with B=1/3, C=1/3
        POINT_SAMPLE = 6,  // Simple point sampling
    };

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
     */
    Image2D(const std::filesystem::path& path);

    /**
     * @brief Create an image with the specified size and optional pixel data.
     * 
     * If the pixel data is not provided, the pixel data is initialized to zeros.
     * 
     * @param size Size of the image in pixels (width, height).
     * @param pixels Pixel data.
     */
    Image2D(glm::uvec2 size, const std::initializer_list<glm::vec4>& pixels = {});

    /**
     * @brief Convert to 3D image.
     * @return The copied 3D image with depth 1.
     */
    operator Image3D() const;

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x, y).
     * @return Reference to the pixel at the specified coordinates.
     */
    glm::vec4& operator[](glm::uvec2 coords);

    /**
     * @brief Access pixel at the specified coordinates.
     * @param coords Coordinates of the pixel (x, y).
     * @return Constant reference to the pixel at the specified coordinates.
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
     * @param filter Filter type.
     * @param edge Edge handling mode.
     * @return Resized image.
     */
    Image2D resize(glm::uvec2 size, ResizeFilter filter = ResizeFilter::DEFAULT, ResizeEdge edge = ResizeEdge::CLAMP) const;
};

}
