#include "OGL/Texture1D.h"

using namespace OGL;

Image1D Texture1D::read(glm::uvec1 offset, glm::uvec1 size) const
{
    Image1D img(size);
    Texture::read(img.pixels.data(), img.pixels.size() * sizeof(float) * 4, offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image1D Texture1D::read() const
{
    return this->read(glm::uvec1(0), this->getSize());
}
