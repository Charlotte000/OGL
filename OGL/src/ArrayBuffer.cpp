#include "OGL/ArrayBuffer.h"

using namespace OGL;

void ArrayBuffer::use()
{
    this->use(GL_ARRAY_BUFFER);
}

void ArrayBuffer::stopUse()
{
    Buffer::stopUse(GL_ARRAY_BUFFER);
}
