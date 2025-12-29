#include "OGL/Texture1DArray.h"

using namespace OGL;

void Texture1DArray::update(const Image2D& image, glm::uvec2 offset)
{
    Texture::update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

Image2D Texture1DArray::read(glm::uvec2 offset, glm::uvec2 size) const
{
    Image2D img(size);
    Texture::read(img.pixels.data(), img.pixels.size() * sizeof(float) * 4, offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image2D Texture1DArray::read() const
{
    return this->read(glm::uvec2(0, 0), this->getSize());
}
