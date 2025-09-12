#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <assert.h>
#include <stdexcept>
#include <stb_image.h>
#include <stb_image_write.h>
#include <stb_image_resize2.h>

#include "OGL/Image.h"

using namespace OGL;

Image::Image(const std::filesystem::path& path)
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
    const size_t pixelCount = this->size.x * this->size.y * 4;
    this->pixels.resize(pixelCount);
    std::copy(data, data + pixelCount, this->pixels.data());

    stbi_image_free(data);
}

Image::Image(glm::uvec2 size, const std::vector<float>& pixels)
    : size(size), pixels(size.x * size.y * 4 == pixels.size() ? pixels : std::vector<float>(size.x * size.y * 4, 0))
{
}

void Image::saveToFile(const std::filesystem::path& path) const
{
    if (!path.has_extension())
    {
        throw std::runtime_error("The file path must have an extension to determine the image format: " + path.string());
    }

    // HDR
    if (path.extension() == ".hdr")
    {
        if (!stbi_write_hdr(path.string().c_str(), this->size.x, this->size.y, 4, this->pixels.data()))
        {
            throw std::runtime_error("Failed to save the image: " + path.string());
        }

        return;
    }

    // Convert to unsigned char
    std::vector<unsigned char> data(this->pixels.size());
    for (size_t i = 0; i < this->pixels.size(); i++)
    {
        data[i] = (unsigned char)(this->pixels[i] * 255);
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

Image Image::resize(glm::uvec2 size) const
{
    Image img(size);
    stbir_resize_float_linear(this->pixels.data(), this->size.x, this->size.y, 0, img.pixels.data(), size.x, size.y, 0, stbir_pixel_layout::STBIR_RGBA);
    return img;
}

glm::vec4 Image::get(glm::uvec2 coords) const
{
    assert(coords.x < this->size.x && coords.y < this->size.y);
    const size_t index = (coords.y * this->size.x + coords.x) * 4;
    return glm::vec4(this->pixels[index + 0], this->pixels[index + 1], this->pixels[index + 2], this->pixels[index + 3]);
}

glm::vec4 Image::get(size_t index) const
{
    assert(index < this->size.x * this->size.y);
    index *= 4;
    return glm::vec4(this->pixels[index + 0], this->pixels[index + 1], this->pixels[index + 2], this->pixels[index + 3]);
}

void Image::set(glm::uvec2 coords, glm::vec4 value)
{
    assert(coords.x < this->size.x && coords.y < this->size.y);
    const size_t index = (coords.y * this->size.x + coords.x) * 4;
    this->pixels[index + 0] = value.r;
    this->pixels[index + 1] = value.g;
    this->pixels[index + 2] = value.b;
    this->pixels[index + 3] = value.a;
}

void Image::set(size_t index, glm::vec4 value)
{
    assert(index < this->size.x * this->size.y);
    index *= 4;
    this->pixels[index + 0] = value.r;
    this->pixels[index + 1] = value.g;
    this->pixels[index + 2] = value.b;
    this->pixels[index + 3] = value.a;
}
