#include "OGL/TextureCubeMapArray.h"

using namespace OGL;

TextureCubeMapArray::TextureCubeMapArray(
    glm::uvec3 size,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture(GL_TEXTURE_CUBE_MAP_ARRAY, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    glTextureStorage3D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y, size.z * 6);
}

TextureCubeMapArray::TextureCubeMapArray(
    const Image3D& image,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : TextureCubeMapArray(image.size, internalFormat, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    this->update(image, glm::uvec3(0));
}

TextureCubeMapArray::TextureCubeMapArray(TextureCubeMapArray&& tex)
    : Texture(std::move(tex))
{
}

TextureCubeMapArray::TextureCubeMapArray(const TextureCubeMapArray& tex)
    : TextureCubeMapArray(tex.getSize(), tex.getInternalFormat(), tex.getMagFilter(), tex.getMinFilter(), tex.getWrapS(), tex.getWrapT(), tex.getWrapR())
{
    const glm::uvec3 size = tex.getSize();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_CUBE_MAP_ARRAY, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_CUBE_MAP_ARRAY, 0, 0, 0, 0,
        size.x, size.y, size.z
    );
}

TextureCubeMapArray& TextureCubeMapArray::operator=(TextureCubeMapArray&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void TextureCubeMapArray::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));

    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void TextureCubeMapArray::update(const Image3D& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void TextureCubeMapArray::read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type) const
{
    glm::uvec3 texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));

    if (offset == glm::uvec3(0) && size == texSize)
    {
        // Whole read
        glGetTextureImage(this->handler, 0, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
    else
    {
        // Partial read
        glGetTextureSubImage(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), bufSize, pixels);
    }
}

Image3D TextureCubeMapArray::read(glm::uvec3 offset, glm::uvec3 size) const
{
    Image3D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image3D TextureCubeMapArray::read() const
{
    return this->read(glm::uvec3(0), this->getSize());
}

glm::uvec3 TextureCubeMapArray::getSize() const
{
    GLint width, height, depth;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH,  &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_DEPTH,  &depth);
    return glm::uvec3(width, height, depth);
}
