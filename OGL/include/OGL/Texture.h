#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "OGL/Image.h"
#include "OGL/Enums.h"

namespace OGL
{

class FrameBuffer;

class Texture
{
public:
    Texture(Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    Texture(Texture&& tex);

    ~Texture();

    void bindSampler(unsigned int binding);

    /**
     * @param format { GL_RGBA32F, ... }
     */
    void bindImage(unsigned int binding, Access access = Access::READ_WRITE, GLenum format = GL_RGBA32F);

    /**
     * @param format { GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, ... }
     * @param internalFormat { GL_RGBA32F, ... }
     */
    void write(const void* pixels, glm::uvec2 size, GLenum format = GL_RGBA, Type type = Type::FLOAT, GLint internalFormat = GL_RGBA32F);

    void write(const Image& image, GLint internalFormat = GL_RGBA32F);

    void update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, GLenum format = GL_RGBA, Type type = Type::FLOAT);

    void update(const Image& image, glm::uvec2 offset);

    Image read(glm::uvec2 offset, glm::uvec2 size) const;

    Image read() const;

    void clear();

    GLuint getHandler() const;

    glm::uvec2 getSize() const;

    GLint getInternalFormat() const;
private:
    GLuint handler = -1;
};

}
