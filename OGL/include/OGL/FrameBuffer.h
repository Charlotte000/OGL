#pragma once

#include <GL/glew.h>

#include "OGL/Enums.h"
#include "OGL/Texture.h"

namespace OGL
{

class FrameBuffer
{
public:
    Texture colorTexture;
    Texture depthTexture;

    FrameBuffer(Texture&& colorTexture, Texture&& depthTexture);

    FrameBuffer(glm::uvec2 size);

    FrameBuffer(FrameBuffer&& fbo);

    ~FrameBuffer();

    void use();

    void clearColor(glm::vec4 color = glm::vec4(0, 0, 0, 1));

    void clearDepth(float depth = 1);

    void clearStencil(int stencil = 0);

    void clear(glm::vec4 color = glm::vec4(0, 0, 0, 1), float depth = 1, int stencil = 0);

    GLuint getHandler() const;

    glm::uvec2 getSize() const;

    static void stopUse();
private:
    GLuint handler = -1;
};

}
