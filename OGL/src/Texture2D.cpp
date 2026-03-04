#include "OGL/Texture2D.h"

using namespace OGL;

Texture2D::Texture2D(
    glm::uvec2 size,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<2, Wrap> wrap
) : Texture(GL_TEXTURE_2D, filter, glm::vec<3, Wrap>(wrap.x, wrap.y, Wrap::REPEAT))
{
    glTextureStorage2D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y);
}

Texture2D::Texture2D(
    const Image2D& image,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<2, Wrap> wrap
) : Texture2D(image.size, internalFormat, filter, wrap)
{
    this->update(image, glm::uvec2(0));
}

Texture2D::Texture2D(Texture2D&& tex)
    : Texture(std::move(tex))
{
}

Texture2D::Texture2D(const Texture2D& tex)
    : Texture2D(tex.size(), tex.internalFormat(), tex.filter(), tex.wrap())
{
    const glm::uvec2 size = tex.size();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_2D, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_2D, 0, 0, 0, 0,
        size.x, size.y, 1
    );
}

Texture2D& Texture2D::operator=(Texture2D&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void Texture2D::update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type)
{
    glm::uvec2 texSize = this->size();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));
    glTextureSubImage2D(this->handler, 0, offset.x, offset.y, size.x, size.y, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture2D::update(const Image2D& image, glm::uvec2 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture2D::read(void* pixels, size_t bufSize, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type) const
{
    glm::uvec2 texSize = this->size();
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
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image2D Texture2D::read() const
{
    return this->read(glm::uvec2(0, 0), this->size());
}

glm::uvec2 Texture2D::size() const
{
    return Texture::size();
}
