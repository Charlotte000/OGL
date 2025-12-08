#include "OGL/StorageBuffer.h"

using namespace OGL;

void StorageBuffer::use()
{
    this->use(GL_SHADER_STORAGE_BUFFER);
}

void StorageBuffer::bindBuffer(int binding)
{
    this->bind(GL_SHADER_STORAGE_BUFFER, binding);
}

void StorageBuffer::stopUse()
{
    Buffer::stopUse(GL_SHADER_STORAGE_BUFFER);
}
