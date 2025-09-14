#include <stdexcept>

#include "OGL/FrameBuffer.h"

using namespace OGL;

FrameBuffer::FrameBuffer(glm::uvec2 size, Texture&& colorTexture, Texture&& depthTexture)
    : colorTexture(std::move(colorTexture)), depthTexture(std::move(depthTexture))
{
    this->colorTexture.write(nullptr, size, GL_RGB, GL_FLOAT, GL_RGBA32F);
    this->depthTexture.write(nullptr, size, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, GL_DEPTH_COMPONENT);

    // Create framebuffer
    glGenFramebuffers(1, &this->handler);
    glBindFramebuffer(GL_FRAMEBUFFER, this->handler);

    // Attach color texture
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorTexture.getHandler(), 0);

    // Attach depth texture
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->depthTexture.getHandler(), 0);

    if (const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER); status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Frame buffer failed: " + std::to_string(status));
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    this->clear();
}

FrameBuffer::FrameBuffer(glm::uvec2 size)
    : FrameBuffer(size, Texture(), Texture())
{
}

FrameBuffer::FrameBuffer(FrameBuffer&& fbo)
    : handler(fbo.handler), colorTexture(std::move(fbo.colorTexture)), depthTexture(std::move(fbo.depthTexture))
{
    fbo.handler = -1;
}

FrameBuffer::~FrameBuffer()
{
    if (this->handler != -1)
    {
        glDeleteFramebuffers(1, &this->handler);
    }
}

void FrameBuffer::use()
{
    const glm::uvec2 size = this->getSize();

    glBindFramebuffer(GL_FRAMEBUFFER, this->handler);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, size.x, size.y);
}

void FrameBuffer::clear(glm::vec4 color, ClearMode mask)
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->handler);
    glClearColor(color.r, color.g, color.b, color.a);
    glClear((GLbitfield)mask);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::stopUse()
{
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint FrameBuffer::getHandler() const
{
    return this->handler;
}

glm::uvec2 FrameBuffer::getSize() const
{
    return this->colorTexture.getSize();
}
