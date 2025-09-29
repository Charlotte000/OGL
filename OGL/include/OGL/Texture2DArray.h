/**
 * @file Texture2DArray.h
 */
#pragma once

#include "OGL/Texture.h"

namespace OGL
{

/**
 * @brief Texture 2D array class is used to store several 2D images with the same internal format and size.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class Texture2DArray : public Texture<GL_TEXTURE_2D_ARRAY, 3>
{
public:
    using Texture::Texture;

    /**
     * @brief Update the region of the texure array object's image.
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
};

}
