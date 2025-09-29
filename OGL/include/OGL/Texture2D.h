/**
 * @file Texture2D.h
 */
#pragma once

#include "OGL/Texture.h"

namespace OGL
{

/**
 * @brief Texture 2D class is used to store 2D image.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class Texture2D : public Texture<GL_TEXTURE_2D, 2>
{
public:
    using Texture::Texture;

    /**
     * @brief Update the region of the texure object's image.
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
};

}
