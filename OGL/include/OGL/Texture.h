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
    ImageFormat internalFormat() const;

    /**
     * @brief Get the filter mode of the texture object.
     * 
     * Filter mode describes the way that the texture is sampled when it is minified or magnified.
     * 
     * @return A vec2 containing the magnification and minification filter modes of the texture.
     */
    glm::vec<2, Filter> filter() const;

    /**
     * @brief Set the filter mode of the texture object.
     * 
     * Filter mode describes the way that the texture is sampled when it is minified or magnified.
     * 
     * @param filter A vec2 containing the magnification and minification filter modes of the texture.
     */
    void filter(glm::vec<2, Filter> filter);

    /**
     * @brief Get the wrap mode of the texture object.
     * 
     * Wrap mode describes the way that the texture is sampled when texture coordinates are outside the range [0, 1].
     * 
     * @return A vec3 containing the wrap modes of the texture for the S, T and R texture coordinates.
     */
    glm::vec<3, Wrap> wrap() const;

    /**
     * @brief Set the wrap mode of the texture object.
     * 
     * Wrap mode describes the way that the texture is sampled when texture coordinates are outside the range [0, 1].
     * 
     * @param wrap A vec3 containing the wrap modes of the texture for the S, T and R texture coordinates.
     */
    void wrap(glm::vec<3, Wrap> wrap);

    /**
     * @brief Get the size of the texture.
     * @return The size of the texture.
     */
    glm::uvec3 size() const;
protected:
    Texture(
        GLenum target,
        glm::vec<2, Filter> filter = glm::vec<2, Filter>(Filter::LINEAR),
        glm::vec<3, Wrap> wrap = glm::vec<3, Wrap>(Wrap::REPEAT)
    );

    GLuint handler = -1;
};

}
