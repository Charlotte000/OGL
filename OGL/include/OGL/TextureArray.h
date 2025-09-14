#pragma once

#include <glm/glm.hpp>

#include "OGL/Enums.h"
#include "OGL/Image.h"

namespace OGL
{

class TextureArray
{
public:
    TextureArray(Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    TextureArray(TextureArray&& tex);

    ~TextureArray();

    void bindSampler(unsigned int binding);

    /**
     * @param format { GL_RGBA32F, ... }
     */
    void bindImage(unsigned int binding, Access access = Access::READ_WRITE, GLenum format = GL_RGBA32F);

    /**
     * @param format { GL_RED, GL_RG, GL_RGB, GL_RGBA, GL_STENCIL_INDEX, GL_DEPTH_COMPONENT, GL_DEPTH_STENCIL, ... }
     * @param internalFormat { GL_RGBA32F, ... }
     */
    void write(const void* pixels, glm::uvec3 size, GLenum format = GL_RGBA, Type type = Type::FLOAT, GLint internalFormat = GL_RGBA32F);

    void write(const std::vector<Image>& images, GLint internalFormat = GL_RGBA32F);

    void update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, GLenum format = GL_RGBA, Type type = Type::FLOAT);

    void update(const Image& image, glm::uvec3 offset);

    Image read(glm::uvec3 offset, glm::uvec2 size) const;

    void clear();

    GLuint getHandler() const;

    glm::uvec3 getSize() const;

    GLint getInternalFormat() const;
private:
    GLuint handler = -1;
};

};