#include <assert.h>

#include "OGL/Texture.h"

using namespace OGL;

Texture::Texture(glm::uvec2 size, InternalFormat internalFormat, Filter filter, Wrap wrap)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &this->handler);
    glTextureParameteri(this->handler, GL_TEXTURE_MAG_FILTER, (GLint)filter);
    glTextureParameteri(this->handler, GL_TEXTURE_MIN_FILTER, (GLint)filter);
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_S, (GLint)wrap);
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_T, (GLint)wrap);
    glTextureStorage2D(this->handler, 1, (GLenum)internalFormat, size.x, size.y);
}

Texture::Texture(Texture&& tex)
    : handler(tex.handler)
{
    tex.handler = -1;
}

Texture::~Texture()
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }
}

void Texture::bindSampler(unsigned int binding)
{
    glBindTextureUnit(binding, this->handler);
}

void Texture::bindImage(unsigned int binding, Access access, ImageUnitFormat format)
{
    glBindImageTexture(binding, this->handler, 0, GL_FALSE, 0, (GLenum)access, (GLenum)format);
}

void Texture::update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));
    glTextureSubImage2D(this->handler, 0, offset.x, offset.y, size.x, size.y, (GLenum)format, (GLenum)type, pixels);
}

void Texture::update(const Image& image, glm::uvec2 offset)
{
    return this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

Image Texture::read(glm::uvec2 offset, glm::uvec2 size) const
{
    glm::uvec2 texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));

    Image img(size);

    if (offset == glm::uvec2(0, 0) && size == texSize)
    {
        // Whole read
        glGetTextureImage(this->handler, 0, GL_RGBA, GL_FLOAT, img.pixels.size() * sizeof(float), img.pixels.data());
    }
    else
    {
        // Partial read
        glGetTextureSubImage(this->handler, 0, offset.x, offset.y, 0, size.x, size.y, 1, GL_RGBA, GL_FLOAT, img.pixels.size() * sizeof(float), img.pixels.data());
    }

    return img;
}

Image Texture::read() const
{
    return this->read(glm::uvec2(0, 0), this->getSize());
}

void Texture::clear()
{
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, nullptr);
}

GLuint Texture::getHandler() const
{
    return this->handler;
}

glm::uvec2 Texture::getSize() const
{
    GLint width, height;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH, &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    return glm::uvec2(width, height);
}

InternalFormat Texture::getInternalFormat() const
{
    GLint internalFormat;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    return (InternalFormat)internalFormat;
}
