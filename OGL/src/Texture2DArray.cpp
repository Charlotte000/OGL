#include "OGL/Texture2DArray.h"

using namespace OGL;

void Texture2DArray::update(const Image3D& image, glm::uvec3 offset)
{
    Texture::update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

Image3D Texture2DArray::read(glm::uvec3 offset, glm::uvec3 size) const
{
    Image3D img(size);
    Texture::read(img.pixels.data(), img.pixels.size() * sizeof(float) * 4, offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image3D Texture2DArray::read() const
{
    return this->read(glm::uvec3(0), this->getSize());
}
