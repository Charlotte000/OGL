#include "OGL/Texture1D.h"

using namespace OGL;

Texture1D::Texture1D(
    glm::uvec1 size,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<1, Wrap> wrap
) : Texture(GL_TEXTURE_1D, filter, glm::vec<3, Wrap>(wrap))
{
    glTextureStorage1D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x);
}

Texture1D::Texture1D(
    const Image1D& image,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<1, Wrap> wrap
) : Texture1D(image.size, internalFormat, filter, wrap)
{
    this->update(image, glm::uvec1(0));
}

Texture1D::Texture1D(Texture1D&& tex)
    : Texture(std::move(tex))
{
}

Texture1D::Texture1D(const Texture1D& tex)
    : Texture1D(tex.size(), tex.internalFormat(), tex.filter(), tex.wrap())
{
    const glm::uvec1 size = tex.size();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_1D, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_1D, 0, 0, 0, 0,
        size.x, 1, 1
    );
}

Texture1D& Texture1D::operator=(Texture1D&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void Texture1D::update(const void* pixels, glm::uvec1 offset, glm::uvec1 size, PixelFormat format, Type type)
{
    glm::uvec1 texSize = this->size();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));
    glTextureSubImage1D(this->handler, 0, offset.x, size.x, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture1D::update(const Image1D& image, glm::uvec1 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture1D::read(void* pixels, size_t bufSize, glm::uvec1 offset, glm::uvec1 size, PixelFormat format, Type type) const
{
    glm::uvec1 texSize = this->size();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));

    if (offset == glm::uvec1(0) && size == texSize)
    {
        // Whole read
        glGetTextureImage(this->handler, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
    else
    {
        // Partial read
        glGetTextureSubImage(this->handler, 0, offset.x, 0, 0, size.x, 1, 1, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
}

Image1D Texture1D::read(glm::uvec1 offset, glm::uvec1 size) const
{
    Image1D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image1D Texture1D::read() const
{
    return this->read(glm::uvec1(0), this->size());
}

glm::uvec1 Texture1D::size() const
{
    return Texture::size();
}
