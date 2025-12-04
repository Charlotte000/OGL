#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

#include "OGL/FrameBuffer.h"

using namespace OGL;

FrameBuffer::FrameBuffer(Texture2D&& colorTexture, Texture2D&& depthTexture)
    : colorTexture(std::move(colorTexture)), depthTexture(std::move(depthTexture))
{
    // Create framebuffer
    glCreateFramebuffers(1, &this->handler);

    // Attach color texture
    glNamedFramebufferTexture(this->handler, GL_COLOR_ATTACHMENT0, this->colorTexture.getHandler(), 0);

    // Attach depth texture
    glNamedFramebufferTexture(this->handler, GL_DEPTH_ATTACHMENT, this->depthTexture.getHandler(), 0);

    if (const GLenum status = glCheckNamedFramebufferStatus(this->handler, GL_FRAMEBUFFER); status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Frame buffer failed: " + std::to_string(status));
    }

    this->clearDepth();
}

FrameBuffer::FrameBuffer(glm::uvec2 size)
    : FrameBuffer(Texture2D(size, ImageFormat::RGBA32F), Texture2D(size, ImageFormat::DEPTH32))
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

FrameBuffer& FrameBuffer::operator=(FrameBuffer&& fbo)
{
    if (this->handler != -1)
    {
        glDeleteFramebuffers(1, &this->handler);
    }

    this->handler = fbo.handler;
    this->colorTexture = std::move(fbo.colorTexture);
    this->depthTexture = std::move(fbo.depthTexture);

    fbo.handler = -1;
    return *this;
}

void FrameBuffer::use()
{
    glBindFramebuffer(GL_FRAMEBUFFER, this->handler);
}

void FrameBuffer::clearColor(glm::vec4 color)
{
    glClearNamedFramebufferfv(this->handler, GL_COLOR, 0, glm::value_ptr(color));
}

void FrameBuffer::clearDepth(float depth)
{
    glClearNamedFramebufferfv(this->handler, GL_DEPTH, 0, &depth);
}

void FrameBuffer::clearStencil(int stencil)
{
    glClearNamedFramebufferiv(this->handler, GL_STENCIL, 0, &stencil);
}

void FrameBuffer::clear(glm::vec4 color, float depth, int stencil)
{
    this->clearColor(color);
    this->clearDepth(depth);
    this->clearStencil(stencil);
}

void FrameBuffer::stopUse()
{
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
