#include "OGL/UniformBuffer.h"

using namespace OGL;

void UniformBuffer::bindUniform(unsigned int binding)
{
    this->bind(GL_UNIFORM_BUFFER, binding);
}