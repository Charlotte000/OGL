/**
 * @file Texture.h
 */
#pragma once

#include "OGL/Image.h"
#include "OGL/Enums.h"

namespace OGL
{

/**
 * @brief Generic texture class is used to store one or more images that all have the same internal format.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
template <GLenum Target, size_t N>
class Texture
{
public:
    static_assert(N > 0 && N < 4, "Only 1D, 2D and 3D textures are supported");

    Texture(glm::vec<N, glm::uint> size, OGL::ImageFormat internalFormat, Filter filter = Filter::LINEAR, Wrap wrap = Wrap::REPEAT);

    Texture(Texture<Target, N>&& tex);

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
     * @brief Update a region of the texure object's image.
     * @param pixels Pointer to the new image that will be copied into the texture store.
     * @param offset Offset into the texture object's data store where image replacement will begin.
     * @param size Size of the image to be copied to the texture store.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void update(const void* pixels, glm::vec<N, glm::uint> offset, glm::vec<N, glm::uint> size, OGL::PixelFormat format = OGL::PixelFormat::RGBA, Type type = Type::FLOAT);

    /**
     * @brief Read the region of the texture object's store.
     * @param pixels Pointer to the new image that will be copied from the texture store.
     * @param bufSize The size of the buffer pixels in bytes.
     * @param offset Offset of the texture's region to be copied.
     * @param size Size of the texture's region to be copied.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void read(void* pixels, size_t bufSize, glm::vec<N, glm::uint> offset, glm::vec<N, glm::uint> size, OGL::PixelFormat format = OGL::PixelFormat::RGBA, Type type = Type::FLOAT) const;

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
    glm::vec<N, glm::uint> getSize() const;

    /**
     * @brief Get the internal format of the texture object.
     * 
     * Internal format describes the way that the images in textures store their data.
     * 
     * @return The internal format of the texture.
     */
    OGL::ImageFormat getInternalFormat() const;
protected:
    GLuint handler = -1;
};

template class Texture<GL_TEXTURE_1D, 1>;
template class Texture<GL_TEXTURE_2D, 2>;
template class Texture<GL_TEXTURE_3D, 3>;

template class Texture<GL_TEXTURE_1D_ARRAY, 2>;
template class Texture<GL_TEXTURE_2D_ARRAY, 3>;

}
