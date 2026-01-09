/**
 * @file Texture1D.h
 */
#pragma once

#include "OGL/Image1D.h"
#include "OGL/Texture.h"

namespace OGL
{

/**
 * @brief Texture 1D class is used to store 1D image.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class Texture1D : public Texture
{
public:
    Texture1D(
        glm::uvec1 size,
        ImageFormat internalFormat,
        Filter magFilter = Filter::LINEAR,
        Filter minFilter = Filter::LINEAR,
        Wrap wrapS       = Wrap::REPEAT,
        Wrap wrapT       = Wrap::REPEAT,
        Wrap wrapR       = Wrap::REPEAT
    );

    Texture1D(Texture1D&& tex);

    Texture1D(const Texture1D& tex);

    /**
     * @brief Update a region of the texure object's image.
     * @param pixels Pointer to the new image that will be copied into the texture store.
     * @param offset Offset into the texture object's data store where image replacement will begin.
     * @param size Size of the image to be copied to the texture store.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void update(const void* pixels, glm::uvec1 offset, glm::uvec1 size, PixelFormat format = PixelFormat::RGBA, Type type = Type::FLOAT);

    /**
     * @brief Update the region of the texure object's image.
     * @param image The image to be copied to the texture store.
     * @param offset Offset into the texture object's data store where image replacement will begin.
     */
    void update(const Image1D& image, glm::uvec1 offset);

    /**
     * @brief Read the region of the texture object's store.
     * @param pixels Pointer to the new image that will be copied from the texture store.
     * @param bufSize The size of the buffer pixels in bytes.
     * @param offset Offset of the texture's region to be copied.
     * @param size Size of the texture's region to be copied.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void read(void* pixels, size_t bufSize, glm::uvec1 offset, glm::uvec1 size, PixelFormat format = PixelFormat::RGBA, Type type = Type::FLOAT) const;

    /**
     * @brief Read the region of the texture store.
     * @param offset Offset of the texture's region to be copied.
     * @param size Size of the texture's region to be copied.
     * @return Image copied from the texture.
     */
    Image1D read(glm::uvec1 offset, glm::uvec1 size) const;

    /**
     * @brief Read the texture store.
     * @return Image copied from the texture.
     */
    Image1D read() const;

    /**
     * @brief Get the size of the texture.
     * @return The size of the texture.
     */
    glm::uvec1 getSize() const;
};

}
