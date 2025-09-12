#pragma once

#include <GL/glew.h>

#include "OGL/Texture.h"

namespace OGL
{

class FrameBuffer
{
public:
    Texture colorTexture;
    Texture depthTexture;

    FrameBuffer(glm::uvec2 size, Texture&& colorTexture, Texture&& depthTexture);

    FrameBuffer(glm::uvec2 size);

    FrameBuffer(FrameBuffer&& fbo);

    ~FrameBuffer();

    void use();

    void clear(glm::vec4 color = glm::vec4(0, 0, 0, 1), GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint getHandler() const;

    glm::uvec2 getSize() const;

    static void stopUse();
private:
    GLuint handler = -1;
};

}
