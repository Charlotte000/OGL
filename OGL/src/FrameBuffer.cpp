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

    const GLenum status = glCheckNamedFramebufferStatus(this->handler, GL_FRAMEBUFFER);
    switch (status)
    {
        case GL_FRAMEBUFFER_COMPLETE:
            break;
        case GL_FRAMEBUFFER_UNDEFINED:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_UNDEFINED): the specified framebuffer is the default read or draw framebuffer, but the default framebuffer does not exist");
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT): any of the framebuffer attachment points are framebuffer incomplete");
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT): the framebuffer does not have at least one image attached to it");
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER): the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) named by GL_DRAW_BUFFERi");
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER): GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for the color attachment point named by GL_READ_BUFFER");
        case GL_FRAMEBUFFER_UNSUPPORTED:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_UNSUPPORTED): the combination of internal formats of the attached images violates an implementation-dependent set of restrictions");
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE): the value of GL_RENDERBUFFER_SAMPLES is not the same for all attached renderbuffers; the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; the attached images are a mix of renderbuffers and textures, the value of GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES; the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; the attached images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not GL_TRUE for all attached textures");
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            throw std::runtime_error("Frame buffer failed (GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS): any framebuffer attachment is layered, and any populated attachment is not layered, or if all populated color attachments are not from textures of the same target");
        default:
            throw std::runtime_error("Frame buffer failed (" + std::to_string(status) + ")");
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

FrameBuffer& FrameBuffer::operator=(FrameBuffer&& fbo)
{
    if (this->handler != -1)
    {
        this->textures.clear();
        glDeleteFramebuffers(1, &this->handler);
    }

    this->handler = fbo.handler;
    this->textures = std::move(fbo.textures);
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

glm::uvec2 FrameBuffer::getSize(Attachment attachment) const
{
    return this->textures.at(attachment).getSize();
}
