#include <assert.h>

#include "OGL/Texture.h"

using namespace OGL;

template <GLenum Target, size_t N>
Texture<Target, N>::Texture(glm::vec<N, glm::uint> size, ImageFormat internalFormat, Filter filter, Wrap wrap)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &this->handler);
    glTextureParameteri(this->handler, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(filter));
    glTextureParameteri(this->handler, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(filter));
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_S, static_cast<GLint>(wrap));
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_T, static_cast<GLint>(wrap));
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_R, static_cast<GLint>(wrap));

    if constexpr (N == 1)
    {
        glTextureStorage1D(this->handler, 1, static_cast<GLenum>(internalFormat), size[0]);
    }
    else if (N == 2)
    {
        glTextureStorage2D(this->handler, 1, static_cast<GLenum>(internalFormat), size[0], size[1]);
    }
    else if (N == 3)
    {
        glTextureStorage3D(this->handler, 1, static_cast<GLenum>(internalFormat), size[0], size[1], size[2]);
    }
}

template <GLenum Target, size_t N>
Texture<Target, N>::Texture(Texture<Target, N>&& tex)
    : handler(tex.handler)
{
    tex.handler = -1;
}

template <GLenum Target, size_t N>
Texture<Target, N>::~Texture()
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }
}

template <GLenum Target, size_t N>
Texture<Target, N>& Texture<Target, N>::operator=(Texture<Target, N>&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

template <GLenum Target, size_t N>
void Texture<Target, N>::bindSampler(unsigned int binding)
{
    glBindTextureUnit(binding, this->handler);
}

template <GLenum Target, size_t N>
void Texture<Target, N>::bindImage(unsigned int binding, ImageUnitFormat format, Access access)
{
    glBindImageTexture(binding, this->handler, 0, GL_FALSE, 0, static_cast<GLenum>(access), static_cast<GLenum>(format));
}

template <GLenum Target, size_t N>
void Texture<Target, N>::update(const void* pixels, glm::vec<N, glm::uint> offset, glm::vec<N, glm::uint> size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));

    if constexpr (N == 1)
    {
        glTextureSubImage1D(this->handler, 0, offset[0], size[0], static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
    }
    else if (N == 2)
    {
        glTextureSubImage2D(this->handler, 0, offset[0], offset[1], size[0], size[1], static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
    }
    else if (N == 3)
    {
        glTextureSubImage3D(this->handler, 0, offset[0], offset[1], offset[2], size[0], size[1], size[2], static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
    }
}

template <GLenum Target, size_t N>
void Texture<Target, N>::read(void* pixels, size_t bufSize, glm::vec<N, glm::uint> offset, glm::vec<N, glm::uint> size, OGL::PixelFormat format, Type type) const
{
    glm::vec<N, glm::uint> texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));

    if (offset == glm::vec<N, glm::uint>(0) && size == texSize)
    {
        // Whole read
        glGetTextureImage(this->handler, 0, GL_RGBA, GL_FLOAT, bufSize, pixels);
    }
    else
    {
        // Partial read
        if constexpr (N == 1)
        {
            glGetTextureSubImage(this->handler, 0, offset[0], 0, 0, size[0], 1, 1, GL_RGBA, GL_FLOAT, bufSize, pixels);
        }
        else if (N == 2)
        {
            glGetTextureSubImage(this->handler, 0, offset[0], offset[1], 0, size[0], size[1], 1, GL_RGBA, GL_FLOAT, bufSize, pixels);
        }
        else if (N == 3)
        {
            glGetTextureSubImage(this->handler, 0, offset[0], offset[1], offset[2], size[0], size[1], size[2], GL_RGBA, GL_FLOAT, bufSize, pixels);
        }
    }
}

template <GLenum Target, size_t N>
void Texture<Target, N>::clear()
{
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, nullptr);
}

template <GLenum Target, size_t N>
GLuint Texture<Target, N>::getHandler() const
{
    return this->handler;
}

template <GLenum Target, size_t N>
glm::vec<N, glm::uint> Texture<Target, N>::getSize() const
{
    glm::vec<N, glm::uint> size;

    GLint val;
    if constexpr (N > 0)
    {
        glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH, &val);
        size[0] = val;
    }

    if constexpr (N > 1)
    {
        glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &val);
        size[1] = val;
    }

    if constexpr (N > 2)
    {
        glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_DEPTH, &val);
        size[2] = val;
    }

    return size;
}

template <GLenum Target, size_t N>
ImageFormat Texture<Target, N>::getInternalFormat() const
{
    GLint internalFormat;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    return static_cast<ImageFormat>(internalFormat);
}
