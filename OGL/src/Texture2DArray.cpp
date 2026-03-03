#include "OGL/Texture2DArray.h"

using namespace OGL;

Texture2DArray::Texture2DArray(
    glm::uvec3 size,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture(GL_TEXTURE_2D_ARRAY, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    glTextureStorage3D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y, size.z);
}

Texture2DArray::Texture2DArray(
    const Image3D& image,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture2DArray(image.size, internalFormat, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    this->update(image, glm::uvec3(0));
}

Texture2DArray::Texture2DArray(Texture2DArray&& tex)
    : Texture(std::move(tex))
{
}

Texture2DArray::Texture2DArray(const Texture2DArray& tex)
    : Texture2DArray(tex.getSize(), tex.getInternalFormat(), tex.getMagFilter(), tex.getMinFilter(), tex.getWrapS(), tex.getWrapT(), tex.getWrapR())
{
    const glm::uvec3 size = tex.getSize();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
        size.x, size.y, size.z
    );
}

Texture2DArray& Texture2DArray::operator=(Texture2DArray&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void Texture2DArray::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));
    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture2DArray::update(const Image3D& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture2DArray::read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type) const
{
    glm::uvec3 texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));

    if (offset == glm::uvec3(0) && size == texSize)
    {
        // Whole read
        glGetTextureImage(this->handler, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
    else
    {
        // Partial read
        glGetTextureSubImage(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
}

Image3D Texture2DArray::read(glm::uvec3 offset, glm::uvec3 size) const
{
    Image3D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image3D Texture2DArray::read() const
{
    return this->read(glm::uvec3(0), this->getSize());
}

glm::uvec3 Texture2DArray::getSize() const
{
    GLint width, height, depth;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH,  &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_DEPTH,  &depth);
    return glm::uvec3(width, height, depth);
}
