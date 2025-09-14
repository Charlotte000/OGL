#include <utility>

#include "OGL/ElementArrayBuffer.h"

using namespace OGL;

ElementArrayBuffer::ElementArrayBuffer(TypeU type)
    : Buffer(), type(type)
{
}

ElementArrayBuffer::ElementArrayBuffer(ElementArrayBuffer&& buff)
    : Buffer(std::move(buff)), type(buff.type)
{
}
