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
class Texture1D : public Texture<GL_TEXTURE_1D, 1>
{
public:
    using Texture::Texture;

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
};

}
