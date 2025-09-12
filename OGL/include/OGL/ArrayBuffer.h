#pragma once

#include <vector>

#include "OGL/Buffer.h"

namespace OGL
{

class VertexArray;

class ArrayBuffer : public Buffer<GL_ARRAY_BUFFER>
{
public:
    /**
     * @param attributes [ ( type, count, offset ) ]. e.g. { { GL_FLOAT, 2, 0 }, { GL_FLOAT, 2,  8 } }
     */
    ArrayBuffer(size_t stride, const std::vector<std::tuple<GLenum, size_t, size_t>>& attributes, GLenum usage = GL_STATIC_COPY);

    ArrayBuffer(ArrayBuffer&& buff);

    void bindAttributes();
private:
    size_t stride = 0;
    const std::vector<std::tuple<GLenum, size_t, size_t>> attributes;

    friend class VertexArray;
};

}