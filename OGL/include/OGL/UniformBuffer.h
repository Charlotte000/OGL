/**
 * @file UniformBuffer.h
 */
#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

/**
 * @brief Uniform buffer (UBO) class is used to store uniform data for a shader program.
 * 
 * They can be used to share uniforms between different programs, as well as quickly change between sets of uniforms for the same program object.
 */
class UniformBuffer : public Buffer
{
public:
    using Buffer::use;
    using Buffer::stopUse;

    /**
     * @brief Bind the buffer to the OpenGL context.
     */
    void use();

    /**
     * @brief Bind the UBO to a specified binding point.
     * @param binding The binding point index.
     */
    void bindUniform(unsigned int binding);

    /**
     * @brief Unbind any buffer from the OpenGL context.
     */
    static void stopUse();
};

}
