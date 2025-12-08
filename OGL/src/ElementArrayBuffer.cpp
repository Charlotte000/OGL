#include "OGL/ElementArrayBuffer.h"

using namespace OGL;

void ElementArrayBuffer::use()
{
    this->use(GL_ELEMENT_ARRAY_BUFFER);
}

void ElementArrayBuffer::stopUse()
{
    Buffer::stopUse(GL_ELEMENT_ARRAY_BUFFER);
}
