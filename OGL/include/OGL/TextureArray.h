#pragma once

#include <glm/glm.hpp>

#include "OGL/Enums.h"
#include "OGL/Image.h"

namespace OGL
{

// Immutable
class TextureArray
{
public:
    TextureArray(glm::uvec3 size, OGL::InternalFormat internalFormat, Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    TextureArray(TextureArray&& tex);

    ~TextureArray();

    void bindSampler(unsigned int binding);

    void bindImage(unsigned int binding, Access access = Access::READ_WRITE, OGL::ImageUnitFormat format = ImageUnitFormat::RGBA32F);

    void update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, OGL::PixelFormat format = OGL::PixelFormat::RGBA, Type type = Type::FLOAT);

    void update(const Image& image, glm::uvec3 offset);

    Image read(glm::uvec3 offset, glm::uvec2 size) const;

    void clear();

    GLuint getHandler() const;

    glm::uvec3 getSize() const;

    OGL::InternalFormat getInternalFormat() const;
private:
    GLuint handler = -1;
};

};