#include "OGL/TextureArray.h"

using namespace OGL;

TextureArray::TextureArray(glm::uvec3 size, ImageFormat internalFormat, Filter filter, Wrap wrap)
{
    glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &this->handler);
    glTextureParameteri(this->handler, GL_TEXTURE_MAG_FILTER, (GLint)filter);
    glTextureParameteri(this->handler, GL_TEXTURE_MIN_FILTER, (GLint)filter);
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_S, (GLint)wrap);
    glTextureParameteri(this->handler, GL_TEXTURE_WRAP_T, (GLint)wrap);
    glTextureStorage3D(this->handler, 1, (GLenum)internalFormat, size.x, size.y, size.z);
}

TextureArray::TextureArray(TextureArray&& tex)
    : handler(tex.handler)
{
    tex.handler = -1;
}

TextureArray::~TextureArray()
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }
}

void TextureArray::bindSampler(unsigned int binding)
{
    glBindTextureUnit(binding, this->handler);
}

void TextureArray::bindImage(unsigned int binding, Access access, ImageUnitFormat format)
{
    glBindImageTexture(binding, this->handler, 0, GL_FALSE, 0, (GLenum)access, (GLenum)format);
}

void TextureArray::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));
    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, 1, (GLenum)format, (GLenum)type, pixels);
}

void TextureArray::update(const Image& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, glm::uvec3(image.size, 1), PixelFormat::RGBA, Type::FLOAT);
}

Image TextureArray::read(glm::uvec3 offset, glm::uvec2 size) const
{
    glm::uvec3 texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + glm::uvec3(size, 1), texSize)));

    Image img(size);
    glGetTextureSubImage(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, 1, GL_RGBA, GL_FLOAT, img.pixels.size() * sizeof(float), img.pixels.data());

    return img;
}

void TextureArray::clear()
{
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, nullptr);
}

GLuint TextureArray::getHandler() const
{
    return this->handler;
}

glm::uvec3 TextureArray::getSize() const
{
    GLint width, height, depth;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH, &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_DEPTH, &depth);
    return glm::uvec3(width, height, depth);
}

ImageFormat TextureArray::getInternalFormat() const
{
    GLint internalFormat;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    return (ImageFormat)internalFormat;
}
