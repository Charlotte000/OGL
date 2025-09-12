#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

class VertexArray;

class ElementArrayBuffer : public Buffer<GL_ELEMENT_ARRAY_BUFFER>
{
public:
    /**
     * @param type { GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_UNSIGNED_INT }
     */
    ElementArrayBuffer(size_t stride = sizeof(unsigned int), GLenum type = GL_UNSIGNED_INT, GLenum usage = GL_STATIC_COPY);

    ElementArrayBuffer(ElementArrayBuffer&& buff);
private:
    size_t stride;
    GLenum type;

    friend class VertexArray;
};

}