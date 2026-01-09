#include "OGL/Texture3D.h"

using namespace OGL;

Texture3D::Texture3D(
    glm::uvec3 size,
    ImageFormat internalFormat,
    Filter magFilter,
    Filter minFilter,
    Wrap wrapS,
    Wrap wrapT,
    Wrap wrapR
) : Texture(GL_TEXTURE_3D, magFilter, minFilter, wrapS, wrapT, wrapR)
{
    glTextureStorage3D(this->handler, 1, static_cast<GLenum>(internalFormat), size.x, size.y, size.z);
}

Texture3D::Texture3D(Texture3D&& tex)
    : Texture(std::move(tex))
{
}

Texture3D::Texture3D(const Texture3D& tex)
    : Texture3D(tex.getSize(), tex.getInternalFormat(), tex.getMagFilter(), tex.getMinFilter(), tex.getWrapS(), tex.getWrapT(), tex.getWrapR())
{
    const glm::uvec3 size = tex.getSize();
    glCopyImageSubData(
        tex.getHandler(), GL_TEXTURE_3D, 0, 0, 0, 0,
        this->handler,    GL_TEXTURE_3D, 0, 0, 0, 0,
        size.x, size.y, size.z
    );
}

void Texture3D::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));
    glTextureSubImage3D(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, size.z, static_cast<GLenum>(format), static_cast<GLenum>(type), pixels);
}

void Texture3D::update(const Image3D& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, image.size, PixelFormat::RGBA, Type::FLOAT);
}

void Texture3D::read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format, Type type) const
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

Image3D Texture3D::read(glm::uvec3 offset, glm::uvec3 size) const
{
    Image3D img(size);
    this->read(img.pixels.data(), img.pixels.size() * sizeof(float) * 4, offset, size, PixelFormat::RGBA, Type::FLOAT);
    return img;
}

Image3D Texture3D::read() const
{
    return this->read(glm::uvec3(0), this->getSize());
}

glm::uvec3 Texture3D::getSize() const
{
    GLint width, height, depth;
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_WIDTH,  &width);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTextureLevelParameteriv(this->handler, 0, GL_TEXTURE_DEPTH,  &depth);
    return glm::uvec3(width, height, depth);
}
