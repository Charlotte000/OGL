/**
 * @file StorageBuffer.h
 */
#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

/**
 * @brief Shader storage buffer (SSBO) class is used to store and retrieve data from within the OpenGL Shading Language.
 */
class StorageBuffer : public Buffer
{
public:
    using Buffer::use;
    using Buffer::stopUse;

    /**
     * @brief Bind the buffer to the OpenGL context.
     */
    void use();

    /**
     * @brief Bind the SSBO to a specified binding point.
     * @param binding The binding point index.
     */
    void bindBuffer(int binding);

    /**
     * @brief Unbind any buffer from the OpenGL context.
     */
    static void stopUse();
};

}
