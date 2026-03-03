#include "OGL/Texture1DArray.h"

using namespace OGL;

Texture1DArray::Texture1DArray(
    glm::uvec2 size,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture(GL_TEXTURE_1D_ARRAY, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    glTextureStorage2D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y);
}

Texture1DArray::Texture1DArray(
    const Image2D& image,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture1DArray(image.size, internalFormat, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    this->update(image, glm::uvec2(0));
}

Texture1DArray::Texture1DArray(Texture1DArray&& tex)
    : Texture(std::move(tex))
{
}

Texture1DArray::Texture1DArray(const Texture1DArray& tex)
    : Texture1DArray(tex.getSize(), tex.getInternalFormat(), tex.getMagFilter(), tex.getMinFilter(), tex.getWrapS(), tex.getWrapT(), tex.getWrapR())
{
    const glm::uvec2 size = tex.getSize();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_1D_ARRAY, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_1D_ARRAY, 0, 0, 0, 0,
        size.x, size.y, 1
    );
}

Texture1DArray& Texture1DArray::operator=(Texture1DArray&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void Texture1DArray::update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));
    glTextureSubImage2D(this->handler, 0, offset.x, offset.y, size.x, size.y, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture1DArray::update(const Image2D& image, glm::uvec2 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture1DArray::read(void* pixels, size_t bufSize, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type) const
{
    glm::uvec2 texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));

    if (offset == glm::uvec2(0) && size == texSize)
    {
        // Whole read
        glGetTextureImage(this->handler, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
    else
    {
        // Partial read
        glGetTextureSubImage(this->handler, 0, offset.x, offset.y, 0, size.x, size.y, 1, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
}

Image2D Texture1DArray::read(glm::uvec2 offset, glm::uvec2 size) const
{
    Image2D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image2D Texture1DArray::read() const
{
    return this->read(glm::uvec2(0, 0), this->getSize());
}

glm::uvec2 Texture1DArray::getSize() const
{
    GLint width, height;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH,  &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    return glm::uvec2(width, height);
}
