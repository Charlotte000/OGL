/**
 * @file Texture.h
 */
#pragma once

#include <glm/glm.hpp>

#include "OGL/Enums.h"

namespace OGL
{

/**
 * @brief Generic texture class is used to store one or more images that all have the same internal format.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class Texture
{
public:
    Texture(Texture&& tex);

    ~Texture();

    Texture& operator=(Texture&& tex);

    /**
     * @brief Bind the texture to the specified texture unit.
     * @param binding The texture unit, to which the texture object should be bound to.
     */
    void bindSampler(unsigned int binding);

    /**
     * @brief Bind the texture to the specified image unit.
     * @param binding The index of the image unit to which to bind the texture.
     * @param format The format that the elements of the image will be treated as for the purposes of formatted stores. Must be compatible with the internal format of the texture.
     * @param access Type of access that will be performed on the image.
     */
    void bindImage(unsigned int binding, ImageUnitFormat format = ImageUnitFormat::RGBA32F, Access access = Access::READ_WRITE);

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
     * @brief Get the internal format of the texture object.
     * 
     * Internal format describes the way that the images in textures store their data.
     * 
     * @return The internal format of the texture.
     */
    ImageFormat getInternalFormat() const;

    Filter getMagFilter() const;

    Filter getMinFilter() const;

    Wrap getWrapS() const;

    Wrap getWrapT() const;

    Wrap getWrapR() const;

    void setMagFilter(Filter filter);

    void setMinFilter(Filter filter);

    void setFilter(Filter filter);

    void setWrapS(Wrap wrap);

    void setWrapT(Wrap wrap);

    void setWrapR(Wrap wrap);

    void setWrap(Wrap wrap);
protected:
    Texture(
        GLenum target,
        Filter magFilter = Filter::LINEAR,
        Filter minFilter = Filter::LINEAR,
        Wrap wrapS       = Wrap::REPEAT,
        Wrap wrapT       = Wrap::REPEAT,
        Wrap wrapR       = Wrap::REPEAT
    );

    GLuint handler = -1;
};

}
