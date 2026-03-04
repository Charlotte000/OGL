#include <assert.h>

#include "OGL/Texture.h"

using namespace OGL;

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
        this->handler = -1;
    }
}

Texture& Texture::operator=(Texture&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void Texture::bindSampler(unsigned int binding)
{
    glBindTextureUnit(binding, this->handler);
}

void Texture::bindImage(unsigned int binding, ImageUnitFormat format, Access access)
{
    glBindImageTexture(binding, this->handler, 0, GL_TRUE, 0, static_cast<GLenum>(access), static_cast<GLenum>(format));
}

void Texture::clear()
{
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, nullptr);
}

GLuint Texture::getHandler() const
{
    return this->handler;
}

ImageFormat Texture::internalFormat() const
{
    GLint internalFormat;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    return static_cast<ImageFormat>(internalFormat);
}

glm::vec<2, Filter> Texture::filter() const
{
    GLint magFilter, minFilter;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_MAG_FILTER, &magFilter);
    glGetTextureParameteriv(this->handler, GL_TEXTURE_MIN_FILTER, &minFilter);
    return glm::vec<2, Filter>(static_cast<Filter>(magFilter), static_cast<Filter>(minFilter));
}

void Texture::filter(glm::vec<2, Filter> filter)
{
    glTextureParameteri(this->handler, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter.x));
    glTextureParameteri(this->handler, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter.y));
}

glm::vec<3, Wrap> Texture::wrap() const
{
    GLint wrapS, wrapT, wrapR;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_WRAP_S, &wrapS);
    glGetTextureParameteriv(this->handler, GL_TEXTURE_WRAP_T, &wrapT);
    glGetTextureParameteriv(this->handler, GL_TEXTURE_WRAP_R, &wrapR);
    return glm::vec<3, Wrap>(static_cast<Wrap>(wrapS), static_cast<Wrap>(wrapT), static_cast<Wrap>(wrapR));
}

void Texture::wrap(glm::vec<3, Wrap> wrap)
{
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap.x));
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap.y));
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap.z));
}

glm::uvec3 Texture::size() const
{
    GLint width, height, depth;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH, &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_DEPTH, &depth);
    return glm::uvec3(width, height, depth);
}

Texture::Texture(GLenum target, glm::vec<2, Filter> filter, glm::vec<3, Wrap> wrap)
{
    glCreateTextures(target, 1, &this->handler);
    this->filter(filter);
    this->wrap(wrap);
}
