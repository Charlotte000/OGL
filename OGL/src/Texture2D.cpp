#include "OGL/Texture2D.h"

using namespace OGL;

Texture2D::Texture2D(
    glm::uvec2 size,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture(GL_TEXTURE_2D, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    glTextureStorage2D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y);
}

Texture2D::Texture2D(Texture2D&& tex)
    : Texture(std::move(tex))
{
}

Texture2D::Texture2D(const Texture2D& tex)
    : Texture2D(tex.getSize(), tex.getInternalFormat(), tex.getMagFilter(), tex.getMinFilter(), tex.getWrapS(), tex.getWrapT(), tex.getWrapR())
{
    const glm::uvec2 size = tex.getSize();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_2D, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_2D, 0, 0, 0, 0,
        size.x, size.y, 1
    );
}

void Texture2D::update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));
    glTextureSubImage2D(this->handler, 0, offset.x, offset.y, size.x, size.y, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture2D::update(const Image2D& image, glm::uvec2 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture2D::read(void* pixels, size_t bufSize, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type) const
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

Image2D Texture2D::read(glm::uvec2 offset, glm::uvec2 size) const
{
    Image2D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(float) * 4, offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image2D Texture2D::read() const
{
    return this->read(glm::uvec2(0, 0), this->getSize());
}

glm::uvec2 Texture2D::getSize() const
{
    GLint width, height;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH,  &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    return glm::uvec2(width, height);
}
