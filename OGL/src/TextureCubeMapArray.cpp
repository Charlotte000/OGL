#include "OGL/TextureCubeMapArray.h"

using namespace OGL;

TextureCubeMapArray::TextureCubeMapArray(
    glm::uvec3 size,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<3, Wrap> wrap
) : Texture(GL_TEXTURE_CUBE_MAP_ARRAY, filter, wrap)
{
    if (size.x != size.y)
        throw std::invalid_argument("width and height of each cube face must be the same");

    glTextureStorage3D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y, size.z * 6);
}

TextureCubeMapArray::TextureCubeMapArray(
    const Image3D& image,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<3, Wrap> wrap
) : TextureCubeMapArray(image.size, internalFormat, filter, wrap)
{
    this->update(image);
}

TextureCubeMapArray::TextureCubeMapArray(TextureCubeMapArray&& tex)
    : Texture(std::move(tex))
{
}

TextureCubeMapArray::TextureCubeMapArray(const TextureCubeMapArray& tex)
    : TextureCubeMapArray(tex.size(), tex.internalFormat(), tex.filter(), tex.wrap())
{
    const glm::uvec3 size = tex.size();
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
    glm::uvec3 texSize = this->size();
    if (glm::any(glm::greaterThan(offset + size, texSize)))
        throw std::out_of_range("offset + size is greater than the size of the texture");

    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void TextureCubeMapArray::update(const Image3D& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void TextureCubeMapArray::read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type) const
{
    glm::uvec3 texSize = this->size();
    if (glm::any(glm::greaterThan(offset + size, texSize)))
        throw std::out_of_range("offset + size is greater than the size of the texture");

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
    return this->read(glm::uvec3(0), this->size());
}
