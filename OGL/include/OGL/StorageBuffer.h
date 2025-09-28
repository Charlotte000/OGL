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
class StorageBuffer : public Buffer<GL_SHADER_STORAGE_BUFFER>
{
public:
    /**
     * @brief Bind the SSBO to a specified binding point.
     * @param binding The binding point index.
     */
    void bindBuffer(int binding);
};

}