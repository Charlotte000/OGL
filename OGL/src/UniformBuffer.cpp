#include "OGL/UniformBuffer.h"

using namespace OGL;

void UniformBuffer::use()
{
    this->use(GL_UNIFORM_BUFFER);
}

void UniformBuffer::bindUniform(unsigned int binding)
{
    this->bind(GL_UNIFORM_BUFFER, binding);
}

void UniformBuffer::stopUse()
{
    Buffer::stopUse(GL_UNIFORM_BUFFER);
}
