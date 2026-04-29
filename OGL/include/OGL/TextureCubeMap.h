/**
 * @file TextureCubeMap.h
 */
#pragma once

#include "OGL/Image3D.h"
#include "OGL/Texture.h"

namespace OGL
{

/**
 * @brief Texture Cubemap is used to store a cube map texture.
 * 
 * A cube map textute contains 6 2D image slices corresponding to the six faces of the cube: X+, X-, Y+, Y-, Z+, Z- directions respectively. Width and height of each cube face must be the same.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class TextureCubeMap : public Texture
{
public:
    /**
    * @brief Construct a new Texture Cubemap object
    * @param size Size of the texture in pixels (width and height of each cube face). Width and height of each cube face must be the same.
    * @param internalFormat Internal format of the texture.
    * @param filter Filter mode of the texture (magnification and minification).
    * @param wrap Wrap mode of the texture (for S, T and R texture coordinates).
    * @throw std::invalid_argument if width and height of each cube face are not the same.
    */
    TextureCubeMap(
        glm::uvec2 size,
        ImageFormat internalFormat,
        glm::vec<2, Filter> filter = glm::vec<2, Filter>(Filter::LINEAR),
        glm::vec<3, Wrap> wrap = glm::vec<3, Wrap>(Wrap::REPEAT)
    );

    /**
     * @brief Construct a new Texture Cubemap object from the specified image.
     * @param image The image to be copied to the texture store. The image must contain 6 layers corresponding to the six faces of the cube: X+, X-, Y+, Y-, Z+, Z- directions respectively. Width and height of each layer must be the same.
     * @param internalFormat Internal format of the texture.
     * @param filter Filter mode of the texture (magnification and minification).
     * @param wrap Wrap mode of the texture (for S, T and R texture coordinates).
     * @throw std::invalid_argument if width and height of each cube face are not the same.
     */
    TextureCubeMap(
        const Image3D& image,
        ImageFormat internalFormat,
        glm::vec<2, Filter> filter = glm::vec<2, Filter>(Filter::LINEAR),
        glm::vec<3, Wrap> wrap = glm::vec<3, Wrap>(Wrap::REPEAT)
    );

    TextureCubeMap(TextureCubeMap&& tex);

    TextureCubeMap(const TextureCubeMap& tex);

    TextureCubeMap& operator=(TextureCubeMap&& tex);

    /**
     * @brief Update a region of the texture object's image.
     * @param pixels Pointer to the new image that will be copied into the texture store.
     * @param offset Offset into the texture object's data store where image replacement will begin.
     * @param size Size of the image to be copied to the texture store.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, PixelFormat format = PixelFormat::RGBA, Type type = Type::FLOAT);

    /**
     * @brief Update the region of the texture array object's image.
     * @param image The image to be copied to the texture array store.
     * @param offset Offset into the texture array object's data store where image replacement will begin.
     */
    void update(const Image3D& image, glm::uvec3 offset = glm::uvec3(0, 0, 0));

    /**
     * @brief Read the region of the texture object's store.
     * @param pixels Pointer to the new image that will be copied from the texture store.
     * @param bufSize The size of the buffer pixels in bytes.
     * @param offset Offset of the texture's region to be copied.
     * @param size Size of the texture's region to be copied.
     * @param format The format of the pixel data.
     * @param type The data type of the pixel data.
     */
    void read(void* pixels, size_t bufSize, glm::uvec3 offset, glm::uvec3 size, PixelFormat format = PixelFormat::RGBA, Type type = Type::FLOAT) const;

    /**
     * @brief Read the region of the texture array store.
     * @param offset Offset of the texture array region to be copied.
     * @param size Size of the texture array region to be copied.
     * @return Image copied from the texture array.
     */
    Image3D read(glm::uvec3 offset, glm::uvec3 size) const;

    /**
     * @brief Read the texture store.
     * @return Image copied from the texture.
     */
    Image3D read() const;

    /**
     * @brief Get the size of the texture.
     * @return The size of the texture.
     */
    glm::uvec3 size() const;
};

}
