#include "OGL/Texture2DArray.h"

using namespace OGL;

void Texture2DArray::update(const Image& image, glm::uvec3 offset)
{
    Texture::update(image.pixels.data(), offset, glm::uvec3(image.size, 1), PixelFormat::RGBA, Type::FLOAT);
}

Image Texture2DArray::read(glm::uvec3 offset, glm::uvec2 size) const
{
    Image img(size);
    Texture::read(img.pixels.data(), img.pixels.size() * sizeof(float), offset, glm::uvec3(size, 1), PixelFormat::RGBA, Type::FLOAT);
    return img;
}
