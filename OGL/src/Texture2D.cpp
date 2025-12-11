#include "OGL/Texture2D.h"

using namespace OGL;

void Texture2D::update(const Image& image, glm::uvec2 offset)
{
    Texture::update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

Image Texture2D::read(glm::uvec2 offset, glm::uvec2 size) const
{
    Image img(size);
    Texture::read(img.pixels.data(), img.pixels.size() * sizeof(float), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image Texture2D::read() const
{
    return this->read(glm::uvec2(0, 0), this->getSize());
}
