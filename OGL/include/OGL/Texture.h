#pragma once

#include "OGL/Image.h"

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace OGL
{

class FrameBuffer;

class Texture
{
public:
    /**
     * @param internalFormat { GL_RGBA32F, ... }
     * @param filter { GL_NEAREST, GL_LINEAR }
     * @param wrap { GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, GL_MIRROR_CLAMP_TO_EDGE }
     */
    Texture(GLint internalFormat = GL_RGBA32F, GLint filter = GL_LINEAR, GLint wrap = GL_REPEAT);

    Texture(Texture&& tex);

    ~Texture();

    void bindSampler(unsigned int binding);

    /**
     * @param access { GL_READ_ONLY, GL_WRITE_ONLY, GL_READ_WRITE }
     * @param format { GL_RGBA32F, ... }
     */
    void bindImage(unsigned int binding, GLenum access = GL_READ_WRITE, GLenum format = GL_RGBA32F);

    /**
     * @param format { GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, ... }
     * @param type { GL_UNSIGNED_BYTE, GL_INT, GL_FLOAT, ... }
     */
    void write(const void* pixels, glm::uvec2 offset, glm::uvec2 size, GLenum format = GL_RGBA, GLenum type = GL_FLOAT);

    void write(const void* pixels, glm::uvec2 size, GLenum format = GL_RGBA, GLenum type = GL_FLOAT);

    void write(const Image& image);

    void write(const Image& image, glm::uvec2 offset);

    Image read(glm::uvec2 offset, glm::uvec2 size) const;

    Image read() const;

    void clear();

    GLuint getHandler() const;

    glm::uvec2 getSize() const;
private:
    glm::uvec2 size = glm::uvec2(0, 0);
    GLuint handler;
    GLint internalFormat;

    friend class FrameBuffer;
};

}
