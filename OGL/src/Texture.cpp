#include <assert.h>

#include "OGL/Texture.h"

using namespace OGL;

Texture::Texture(GLint internalFormat, GLint filter, GLint wrap)
    : internalFormat(internalFormat)
{
    glGenTextures(1, &this->handler);

    glBindTexture(GL_TEXTURE_2D, this->handler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(Texture&& tex)
    : handler(tex.handler), size(tex.size), internalFormat(tex.internalFormat)
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

void Texture::bindImage(unsigned int binding, GLenum access, GLenum format)
{
    glBindImageTexture(binding, this->handler, 0, GL_FALSE, 0, access, format);
}

void Texture::write(const void* pixels, glm::uvec2 offset, glm::uvec2 size, GLenum format, GLenum type)
{
    assert(offset == glm::uvec2(0, 0) || glm::all(glm::lessThanEqual(offset + size, this->size)));

    glBindTexture(GL_TEXTURE_2D, this->handler);

    if (glm::any(glm::greaterThan(size, this->size)))
    {
        // Resize (offset should be 0)
        this->size = size;
        glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->size.x, this->size.y, 0, format, type, pixels);
    }
    else
    {
        // Partial write
        glTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, size.x, size.y, format, type, pixels);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::write(const void* pixels, glm::uvec2 size, GLenum format, GLenum type)
{
    return this->write(pixels, glm::uvec2(0, 0), size, format, type);
}

void Texture::write(const Image& image)
{
    this->write(image.pixels.data(), image.size, GL_RGBA, GL_FLOAT);
}

void Texture::write(const Image& image, glm::uvec2 offset)
{
    this->write(image.pixels.data(), offset, image.size, GL_RGBA, GL_FLOAT);
}

Image Texture::read(glm::uvec2 offset, glm::uvec2 size) const
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->size)));

    Image img(size);

    if (offset == glm::uvec2(0, 0) && size == this->size)
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
    return this->read(glm::uvec2(0, 0), this->size);
}

void Texture::clear()
{
    glBindTexture(GL_TEXTURE_2D, this->handler);
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getHandler() const
{
    return this->handler;
}

glm::uvec2 Texture::getSize() const
{
    return this->size;
}
