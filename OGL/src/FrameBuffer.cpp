#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

#include "OGL/FrameBuffer.h"

using namespace OGL;

FrameBuffer::FrameBuffer(std::initializer_list<std::pair<const Attachment, Texture2D&&>> textures)
{
    glCreateFramebuffers(1, &this->handler);

    for (auto& [att, tex] : textures)
    {
        glNamedFramebufferTexture(this->handler, static_cast<GLenum>(att), tex.getHandler(), 0);
        this->textures.emplace(att, std::move(tex));
    }

    if (const GLenum status = glCheckNamedFramebufferStatus(this->handler, GL_FRAMEBUFFER); status != GL_FRAMEBUFFER_COMPLETE)
    {
        throw std::runtime_error("Frame buffer failed: " + std::to_string(status));
    }
}

FrameBuffer::FrameBuffer(Texture2D&& colorTexture, Texture2D&& depthTexture)
    : FrameBuffer({ { Attachment::COLOR0, std::move(colorTexture) }, { Attachment::DEPTH, std::move(depthTexture) } })
{
}

FrameBuffer::FrameBuffer(glm::uvec2 size)
    : FrameBuffer({ { Attachment::COLOR0, Texture2D(size, ImageFormat::RGBA32F) }, { Attachment::DEPTH, Texture2D(size, ImageFormat::DEPTH32) } })
{
}

FrameBuffer::FrameBuffer(FrameBuffer&& fbo)
    : handler(fbo.handler), textures(std::move(fbo.textures))
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
    return this->textures.at(Attachment::COLOR0).getSize();
}
