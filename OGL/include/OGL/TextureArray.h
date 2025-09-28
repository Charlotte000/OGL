/**
 * @file TextureArray.h
 */
#pragma once

#include "OGL/Enums.h"
#include "OGL/Image.h"

namespace OGL
{

/**
 * @brief Texture array class is used to store several 2D images with the same internal format and size.
 * 
 * Array texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class TextureArray
{
public:
    TextureArray(glm::uvec3 size, OGL::ImageFormat internalFormat, Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    TextureArray(TextureArray&& tex);

    ~TextureArray();

    /**
     * @brief Bind the array texture to the specified texture unit.
     * @param binding The array texture unit, to which the texture object should be bound to.
     */
    void bindSampler(unsigned int binding);

    /**
     * @brief Bind the array texture to the specified image unit.
     * @param binding The index of the image unit to which to bind the array texture.
     * @param access Type of access that will be performed on the image.
     * @param format The format that the elements of the image will be treated as for the purposes of formatted stores. Must be compatible with the internal format of the texture array.
     */
    void bindImage(unsigned int binding, Access access = Access::READ_WRITE, OGL::ImageUnitFormat format = ImageUnitFormat::RGBA32F);

    /**
     * @brief Update a subset of the texure array object's image.
     * @param pixels Pointer to the new image that will be copied into the texture array store.
     * @param offset Offset into the texture array object's data store where image replacement will begin.
     * @param size Size of the image to be copied to the texture array store.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, OGL::PixelFormat format = OGL::PixelFormat::RGBA, Type type = Type::FLOAT);

    /**
     * @brief Update a subset of the texure array object's image.
     * @param image The image to be copied to the texture array store.
     * @param offset Offset into the texture array object's data store where image replacement will begin.
     */
    void update(const Image& image, glm::uvec3 offset);

    /**
     * @brief Read the region of the texture array store.
     * @param offset Offset of the texture array region to be copied.
     * @param size Size of the texture array region to be copied.
     * @return Image copied from the texture array.
     */
    Image read(glm::uvec3 offset, glm::uvec2 size) const;

    /**
     * @brief Clear the array texture with zeroes.
     */
    void clear();

    /**
     * @brief Get the OpenGL handler of the array texture object.
     * @return The OpenGL handler of the array texture object.
     */
    GLuint getHandler() const;

    /**
     * @brief Get the size of the array texture.
     * @return The size of the array texture.
     */
    glm::uvec3 getSize() const;

    /**
     * @brief Get the internal format of the array texture object.
     * 
     * Internal format describes the way that the images in array textures store their data.
     * 
     * @return The internal format of the array texture.
     */
    OGL::ImageFormat getInternalFormat() const;
private:
    GLuint handler = -1;
};

};