#include "OGL/ArrayBuffer.h"

using namespace OGL;

ArrayBuffer::ArrayBuffer(size_t stride, const std::vector<std::tuple<GLenum, size_t, size_t>>& attributes, GLenum usage)
    : Buffer(usage), stride(stride), attributes(attributes)
{
}

ArrayBuffer::ArrayBuffer(ArrayBuffer&& buff)
    : Buffer(std::move(buff)), stride(buff.stride), attributes(buff.attributes)
{
}

void ArrayBuffer::bindAttributes()
{
    glBindBuffer(GL_ARRAY_BUFFER, this->handler);

    for (size_t i = 0; i < this->attributes.size(); i++)
    {
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            std::get<1>(this->attributes[i]),
            std::get<0>(this->attributes[i]),
            GL_FALSE,
            this->stride,
            (GLvoid*)std::get<2>(this->attributes[i])
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
