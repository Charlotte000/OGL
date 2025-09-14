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
     * @param attributes [ ( type, count, offset ) ]. e.g. { { Type::FLOAT, 2, 0 }, { GL_FLOAT, 2, 8 } }
     */
    ArrayBuffer(size_t stride, const std::vector<std::tuple<Type, size_t, size_t>>& attributes);

    /**
     * @param attributes [ ( type, count ) ]. e.g. { { Type::FLOAT, 2 }, { GL_FLOAT, 2 } }
     */
    ArrayBuffer(const std::vector<std::tuple<Type, size_t>>& attributes);

    ArrayBuffer(ArrayBuffer&& buff);

    void bindAttributes();
private:
    size_t stride = 0;
    const std::vector<std::tuple<Type, size_t, size_t>> attributes;

    friend class VertexArray;
};

}