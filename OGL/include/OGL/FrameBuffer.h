/**
 * @file FrameBuffer.h
 */
#pragma once

#include <unordered_map>

#include "OGL/Texture2D.h"

namespace OGL
{

/**
 * @brief Framebuffer (FBO) class for off-screen rendering.
 * 
 * Framebuffers allow rendering to textures instead of the default framebuffer (screen).
 * This class supports color and depth attachments.
 */
class FrameBuffer
{
public:
    std::unordered_map<Attachment, Texture2D> textures;

    FrameBuffer(std::initializer_list<std::pair<const Attachment, Texture2D&&>> textures);

    FrameBuffer(Texture2D&& colorTexture, Texture2D&& depthTexture);

    FrameBuffer(glm::uvec2 size);

    FrameBuffer(FrameBuffer&& fbo);

    ~FrameBuffer();

    /**
     * @brief Bind the framebuffer to the OpenGL context.
     * 
     * This sets the framebuffer as the current render target.
     */
    void use();

    /**
     * @brief Clear the color attachment with the specified color.
     * @param color Color to clear the color attachment with.
     */
    void clearColor(glm::vec4 color = glm::vec4(0, 0, 0, 1));

    /**
     * @brief Clear the depth attachment with the specified depth value.
     * 
     * The depth value should be in the range [0, 1], where 1 represents the farthest depth.
     * 
     * @param depth Depth value to clear the depth attachment with.
     */
    void clearDepth(float depth = 1);

    /**
     * @brief Clear the stencil attachment with the specified stencil value.
     * 
     * The stencil value is an integer used in stencil testing operations.
     * 
     * @param stencil Stencil value to clear the stencil attachment with.
     */
    void clearStencil(int stencil = 0);

    /**
     * @brief Clear color, depth, and stencil attachments.
     * @param color Color to clear the color attachment with.
     * @param depth Depth value to clear the depth attachment with.
     * @param stencil Stencil value to clear the stencil attachment with.
     */
    void clear(glm::vec4 color = glm::vec4(0, 0, 0, 1), float depth = 1, int stencil = 0);

    /**
     * @brief Get the OpenGL handler of the framebuffer object.
     * @return The OpenGL handler of the framebuffer object.
     */
    GLuint getHandler() const;

    /**
     * @brief Get the size of the framebuffer.
     * 
     * The size is determined by the size of the attached textures.
     * 
     * @return The size of the framebuffer.
     */
    glm::uvec2 getSize() const;

    /**
     * @brief Unbind any framebuffer from the OpenGL context and revert to the default framebuffer (screen).
     */
    static void stopUse();
private:
    GLuint handler = -1;
};

}
