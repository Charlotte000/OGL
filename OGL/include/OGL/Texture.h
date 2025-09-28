/**
 * @file Texture.h
 */
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "OGL/Image.h"
#include "OGL/Enums.h"

namespace OGL
{

class FrameBuffer;

/**
 * @brief Texture class is used to store a 2D image.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class Texture
{
public:
    Texture(glm::uvec2 size, OGL::ImageFormat internalFormat, Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    Texture(Texture&& tex);

    ~Texture();

    /**
     * @brief Bind the texture to the specified texture unit.
     * @param binding The texture unit, to which the texture object should be bound to.
     */
    void bindSampler(unsigned int binding);

    /**
     * @brief Bind the texture to the specified image unit.
     * @param binding The index of the image unit to which to bind the texture.
     * @param access Type of access that will be performed on the image.
     * @param format The format that the elements of the image will be treated as for the purposes of formatted stores. Must be compatible with the internal format of the texture.
     */
    void bindImage(unsigned int binding, Access access = Access::READ_WRITE, OGL::ImageUnitFormat format = ImageUnitFormat::RGBA32F);

    /**
     * @brief Update a subset of the texure object's image.
     * @param pixels Pointer to the new image that will be copied into the texture store.
     * @param offset Offset into the texture object's data store where image replacement will begin.
     * @param size Size of the image to be copied to the texture store.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void update(const void* pixels, glm::uvec2 offset, glm::uvec2 size, OGL::PixelFormat format = OGL::PixelFormat::RGBA, Type type = Type::FLOAT);

    /**
     * @brief Update a subset of the texure object's image.
     * @param image The image to be copied to the texture store.
     * @param offset Offset into the texture object's data store where image replacement will begin.
     */
    void update(const Image& image, glm::uvec2 offset);

    /**
     * @brief Read the region of the texture store.
     * @param offset Offset of the texture's region to be copied.
     * @param size Size of the texture's region to be copied.
     * @return Image copied from the texture.
     */
    Image read(glm::uvec2 offset, glm::uvec2 size) const;

    /**
     * @brief Read the texture store.
     * @return Image copied from the texture.
     */
    Image read() const;

    /**
     * @brief Clear the texture with zeroes.
     */
    void clear();

    /**
     * @brief Get the OpenGL handler of the texture object.
     * @return The OpenGL handler of the texture object.
     */
    GLuint getHandler() const;

    /**
     * @brief Get the size of the texture.
     * @return The size of the texture.
     */
    glm::uvec2 getSize() const;

    /**
     * @brief Get the internal format of the texture object.
     * 
     * Internal format describes the way that the images in textures store their data.
     * 
     * @return The internal format of the texture.
     */
    OGL::ImageFormat getInternalFormat() const;
private:
    GLuint handler = -1;
};

}
