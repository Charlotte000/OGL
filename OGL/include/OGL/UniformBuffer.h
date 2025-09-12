#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

class UniformBuffer : public Buffer<GL_UNIFORM_BUFFER>
{
public:
    void bindUniform(unsigned int binding);
};

}