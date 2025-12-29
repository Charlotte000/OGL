/**
 * @file Texture3D.h
 */
#pragma once

#include "OGL/Image3D.h"
#include "OGL/Texture.h"

namespace OGL
{

/**
 * @brief Texture 3D class is used to store 3D image.
 * 
 * Texture objects are immutable, meaning their size, internal format, filter and wrap modes can not be changed after creation.
 */
class Texture3D : public Texture<GL_TEXTURE_3D, 3>
{
public:
    using Texture::Texture;

    /**
     * @brief Update the region of the texure array object's image.
     * @param image The image to be copied to the texture array store.
     * @param offset Offset into the texture array object's data store where image replacement will begin.
     */
    void update(const Image3D& image, glm::uvec3 offset);

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
};

}
