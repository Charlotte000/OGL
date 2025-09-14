#pragma once

#include "OGL/Enums.h"
#include "OGL/Buffer.h"

namespace OGL
{

class VertexArray;

class ElementArrayBuffer : public Buffer<GL_ELEMENT_ARRAY_BUFFER>
{
public:
    ElementArrayBuffer(TypeU type = TypeU::UNSIGNED_INT);

    ElementArrayBuffer(ElementArrayBuffer&& buff);
private:
    TypeU type;

    friend class VertexArray;
};

}