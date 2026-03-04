#include "OGL/Texture2DArray.h"

using namespace OGL;

Texture2DArray::Texture2DArray(
    glm::uvec3 size,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<3, Wrap> wrap
) : Texture(GL_TEXTURE_2D_ARRAY, filter, wrap)
{
    glTextureStorage3D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y, size.z);
}

Texture2DArray::Texture2DArray(
    const Image3D& image,
    ImageFormat internalFormat,
    glm::vec<2, Filter> filter,
    glm::vec<3, Wrap> wrap
) : Texture2DArray(image.size, internalFormat, filter, wrap)
{
    this->update(image, glm::uvec3(0));
}

Texture2DArray::Texture2DArray(Texture2DArray&& tex)
    : Texture(std::move(tex))
{
}

Texture2DArray::Texture2DArray(const Texture2DArray& tex)
    : Texture2DArray(tex.size(), tex.internalFormat(), tex.filter(), tex.wrap())
{
    const glm::uvec3 size = tex.size();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0,
        size.x, size.y, size.z
    );
}

Texture2DArray& Texture2DArray::operator=(Texture2DArray&& tex)
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }

    this->handler = tex.handler;
    tex.handler = -1;
    return *this;
}

void Texture2DArray::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type)
{
    glm::uvec3 texSize = this->size();
    assert(glm::all(glm::lessThanEqual(offset + size, texSize)));
    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture2DArray::update(const Image3D& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture2DArray::read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type) const
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

Image3D Texture2DArray::read(glm::uvec3 offset, glm::uvec3 size) const
{
    Image3D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(glm::vec4), offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image3D Texture2DArray::read() const
{
    return this->read(glm::uvec3(0), this->size());
}
