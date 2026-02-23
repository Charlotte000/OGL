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

ImageFormat Texture::getInternalFormat() const
{
    GLint internalFormat;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    return static_cast<ImageFormat>(internalFormat);
}

Filter Texture::getMagFilter() const
{
    GLint filter;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_MAG_FILTER, &filter);
    return static_cast<Filter>(filter);
}

Filter Texture::getMinFilter() const
{
    GLint filter;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_MIN_FILTER, &filter);
    return static_cast<Filter>(filter);
}

Wrap Texture::getWrapS() const
{
    GLint wrap;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_WRAP_S, &wrap);
    return static_cast<Wrap>(wrap);
}

Wrap Texture::getWrapT() const
{
    GLint wrap;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_WRAP_T, &wrap);
    return static_cast<Wrap>(wrap);
}

Wrap Texture::getWrapR() const
{
    GLint wrap;
    glGetTextureParameteriv(this->handler, GL_TEXTURE_WRAP_R, &wrap);
    return static_cast<Wrap>(wrap);
}

void Texture::setMagFilter(Filter filter)
{
    glTextureParameteri(this->handler, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
}

void Texture::setMinFilter(Filter filter)
{
    glTextureParameteri(this->handler, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
}

void Texture::setFilter(Filter filter)
{
    this->setMagFilter(filter);
    this->setMinFilter(filter);
}

void Texture::setWrapS(Wrap wrap)
{
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
}

void Texture::setWrapT(Wrap wrap)
{
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
}

void Texture::setWrapR(Wrap wrap)
{
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap));
}

void Texture::setWrap(Wrap wrap)
{
    this->setWrapS(wrap);
    this->setWrapT(wrap);
    this->setWrapR(wrap);
}

Texture::Texture(GLenum target, Filter magFilter, Filter minFilter, Wrap wrapS, Wrap wrapT, Wrap wrapR)
{
    glCreateTextures(target, 1, &this->handler);
    this->setMagFilter(magFilter);
    this->setMinFilter(minFilter);
    this->setWrapS(wrapS);
    this->setWrapT(wrapT);
    this->setWrapR(wrapR);
}
