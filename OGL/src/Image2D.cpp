#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <assert.h>
#include <stdexcept>

#include <stb_image.h>
#include <stb_image_write.h>
#include <stb_image_resize2.h>

#include "OGL/Image2D.h"

using namespace OGL;

Image2D::Image2D(const std::filesystem::path& path)
{
    // Read from file
    glm::ivec2 size;
    float* data = stbi_loadf(path.string().c_str(), &size.x, &size.y, nullptr, 4);
    if (data == nullptr)
    {
        throw std::runtime_error("Failed to load the image: " + path.string());
    }

    // Copy to image
    this->size = size;
    const size_t pixelCount = this->size.x * this->size.y;
    this->pixels.resize(pixelCount);
    std::copy(data, data + pixelCount * 4, reinterpret_cast<float*>(this->pixels.data()));

    stbi_image_free(data);
}

Image2D::Image2D(glm::uvec2 size, const std::initializer_list<glm::vec4>& pixels)
    : size(size), pixels(pixels.size() != 0 ? pixels : std::vector<glm::vec4>(size.x * size.y, glm::vec4(0)))
{
    assert(this->size.x * this->size.y == this->pixels.size());
}

Image2D::Image2D(glm::uvec2 size, const void* data)
    : size(size), pixels(reinterpret_cast<const glm::vec4*>(data), reinterpret_cast<const glm::vec4*>(data) + size.x * size.y)
{
}

Image2D::operator Image3D() const
{
    Image3D img(glm::uvec3(this->size, 1));
    img.pixels = this->pixels;
    return img;
}

glm::vec4& Image2D::operator[](glm::uvec2 coords)
{
    assert(coords.x < this->size.x && coords.y < this->size.y);
    const size_t index = coords.y * this->size.x + coords.x;
    return this->pixels[index];
}

const glm::vec4& Image2D::operator[](glm::uvec2 coords) const
{
    assert(coords.x < this->size.x && coords.y < this->size.y);
    const size_t index = coords.y * this->size.x + coords.x;
    return this->pixels[index];
}

void Image2D::saveToFile(const std::filesystem::path& path) const
{
    if (!path.has_extension())
    {
        throw std::runtime_error("The file path must have an extension to determine the image format: " + path.string());
    }

    // HDR
    if (path.extension() == ".hdr")
    {
        if (!stbi_write_hdr(path.string().c_str(), this->size.x, this->size.y, 4, reinterpret_cast<const float*>(this->pixels.data())))
        {
            throw std::runtime_error("Failed to save the image: " + path.string());
        }

        return;
    }

    // Convert to unsigned char
    std::vector<glm::vec<4, unsigned char>> data(this->pixels.size());
    for (size_t i = 0; i < this->pixels.size(); i++)
    {
        data[i] = glm::vec<4, unsigned char>(this->pixels[i] * 255.f);
    }

    // JPEG
    if (path.extension() == ".jpg")
    {
        if (!stbi_write_jpg(path.string().c_str(), this->size.x, this->size.y, 4, data.data(), 100))
        {
            throw std::runtime_error("Failed to save the image: " + path.string());
        }

        return;
    }

    // BMP
    if (path.extension() == ".bmp")
    {
        if (!stbi_write_bmp(path.string().c_str(), this->size.x, this->size.y, 4, data.data()))
        {
            throw std::runtime_error("Failed to save the image: " + path.string());
        }

        return;
    }

    // PNG
    if (path.extension() == ".png")
    {
        if (!stbi_write_png(path.string().c_str(), this->size.x, this->size.y, 4, data.data(), 0))
        {
            throw std::runtime_error("Failed to save the image: " + path.string());
        }

        return;
    }

    // Unsupported format
    throw std::runtime_error("Unsupported image format: " + path.extension().string());
}

Image2D Image2D::resize(glm::uvec2 size, ResizeFilter filter, ResizeEdge edge) const
{
    Image2D img(size);
    stbir_resize(
        this->pixels.data(),
        this->size.x,
        this->size.y,
        0,
        img.pixels.data(),
        size.x,
        size.y,
        0,
        stbir_pixel_layout::STBIR_RGBA,
        stbir_datatype::STBIR_TYPE_FLOAT,
        static_cast<stbir_edge>(edge),
        static_cast<stbir_filter>(filter)
    );
    return img;
}
