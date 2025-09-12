#include "OGL/StorageBuffer.h"

using namespace OGL;

void StorageBuffer::bindBuffer(int binding)
{
    this->bind(GL_SHADER_STORAGE_BUFFER, binding);
}
