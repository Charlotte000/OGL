#include <assert.h>

#include "OGL/Texture.h"

using namespace OGL;

Texture::Texture(Filter filter, Wrap wrap)
{
    glGenTextures(1, &this->handler);
    glBindTexture(GL_TEXTURE_2D, this->handler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)wrap);
    glBindTexture(GL_TEXTURE_2D, 0);
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

void Texture::bindImage(unsigned int binding, Access access, GLenum format)
{
    glBindImageTexture(binding, this->handler, 0, GL_FALSE, 0, (GLenum)access, format);
}

void Texture::write(const void* pixels, glm::uvec2 size, GLenum format, Type type, GLint internalFormat)
{
    glBindTexture(GL_TEXTURE_2D, this->handler);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, format, (GLenum)type, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::write(const Image& image, GLint internalFormat)
{
    this->write(image.pixels.data(), image.size, GL_RGBA, Type::FLOAT, internalFormat);
}

void Texture::update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, GLenum format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));

    glBindTexture(GL_TEXTURE_2D, this->handler);
    glTexSubImage2D(GL_TEXTURE_2D, 0, offset.x, offset.y, size.x, size.y, format, (GLenum)type, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::update(const Image& image, glm::uvec2 offset)
{
    return this->update(image.pixels.data(), offset, image.size, GL_RGBA, Type::FLOAT);
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
    glBindTexture(GL_TEXTURE_2D, this->handler);
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getHandler() const
{
    return this->handler;
}

glm::uvec2 Texture::getSize() const
{
    GLint width, height;
 
    glBindTexture(GL_TEXTURE_2D, this->handler);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
    glBindTexture(GL_TEXTURE_2D, 0);
    return glm::uvec2(width, height);
}

GLint Texture::getInternalFormat() const
{
    GLint internalFormat;
 
    glBindTexture(GL_TEXTURE_2D, this->handler);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    glBindTexture(GL_TEXTURE_2D, 0);
    return internalFormat;
}
