#include "OGL/TextureCubeMap.h"

using namespace OGL;

TextureCubeMap::TextureCubeMap(
    glm::uvec2 size,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<3, Wrap> wrap
) : Texture(GL_TEXTURE_CUBE_MAP, filter, wrap)
{
    glTextureStorage2D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y);
}

TextureCubeMap::TextureCubeMap(
    const Image3D& image,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<3, Wrap> wrap
) : TextureCubeMap(glm::uvec2(image.size.x, image.size.y), internalFormat, filter, wrap)
{
    this->update(image, glm::uvec3(0));
}

TextureCubeMap::TextureCubeMap(TextureCubeMap&& tex)
    : Texture(std::move(tex))
{
}

TextureCubeMap::TextureCubeMap(const TextureCubeMap& tex)
    : TextureCubeMap(glm::uvec2(tex.size()), tex.internalFormat(), tex.filter(), tex.wrap())
{
    const glm::uvec3 size = tex.size();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_CUBE_MAP, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_CUBE_MAP, 0, 0, 0, 0,
        size.x, size.y, size.z
    );
}

TextureCubeMap& TextureCubeMap::operator=(TextureCubeMap&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void TextureCubeMap::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type)
{
    glm::uvec3 texSize = this->size();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));
    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void TextureCubeMap::update(const Image3D& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void TextureCubeMap::read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type) const
{
    glm::uvec3 texSize = this->size();
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

Image3D TextureCubeMap::read(glm::uvec3 offset, glm::uvec3 size) const
{
    Image3D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image3D TextureCubeMap::read() const
{
    return this->read(glm::uvec3(0), this->size());
}

glm::uvec3 TextureCubeMap::size() const
{
    glm::uvec3 size = Texture::size();
    return glm::uvec3(size.x, size.y, 6);
}
