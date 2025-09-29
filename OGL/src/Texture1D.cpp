#include "OGL/Texture1D.h"

using namespace OGL;

Image Texture1D::read(glm::uvec1 offset, glm::uvec1 size) const
{
    Image img(glm::uvec2(size, 1));
    Texture::read(img.pixels.data(), img.pixels.size() * sizeof(float), offset, size, OGL::PixelFormat::RGBA, OGL::Type::FLOAT);
    return img;
}

Image Texture1D::read() const
{
    return this->read(glm::uvec1(0), this->getSize());
}
