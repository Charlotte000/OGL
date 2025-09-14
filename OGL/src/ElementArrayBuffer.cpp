#include <utility>

#include "OGL/ElementArrayBuffer.h"

using namespace OGL;

ElementArrayBuffer::ElementArrayBuffer(size_t stride, GLenum type)
    : Buffer(), stride(stride), type(type)
{
}

ElementArrayBuffer::ElementArrayBuffer(ElementArrayBuffer&& buff)
    : Buffer(std::move(buff)), stride(buff.stride), type(buff.type)
{
}
