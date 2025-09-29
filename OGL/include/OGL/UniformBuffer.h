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
class UniformBuffer : public Buffer<GL_UNIFORM_BUFFER>
{
public:
    /**
     * @brief Bind the UBO to a specified binding point.
     * @param binding The binding point index.
     */
    void bindUniform(unsigned int binding);
};

}
