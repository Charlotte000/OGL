#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "OGL/Image.h"
#include "OGL/Enums.h"

namespace OGL
{

class FrameBuffer;

// Immutable
class Texture
{
public:
    Texture(glm::uvec2 size, OGL::InternalFormat internalFormat, Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    Texture(Texture&& tex);

    ~Texture();

    void bindSampler(unsigned int binding);

    void bindImage(unsigned int binding, Access access = Access::READ_WRITE, OGL::ImageUnitFormat format = ImageUnitFormat::RGBA32F);

    void update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, OGL::PixelFormat format = OGL::PixelFormat::RGBA, Type type = Type::FLOAT);

    void update(const Image& image, glm::uvec2 offset);

    Image read(glm::uvec2 offset, glm::uvec2 size) const;

    Image read() const;

    void clear();

    GLuint getHandler() const;

    glm::uvec2 getSize() const;

    OGL::InternalFormat getInternalFormat() const;
private:
    GLuint handler = -1;
};

}
