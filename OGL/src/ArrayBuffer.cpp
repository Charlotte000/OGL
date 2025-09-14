#include "OGL/ArrayBuffer.h"

using namespace OGL;

size_t getStride(const std::vector<std::tuple<Type, size_t>>& attributes)
{
    size_t size = 0;
    for (const auto& [ type, count ] : attributes)
    {
        size += getTypeSize(type) * count;
    }

    return size;
}

std::vector<std::tuple<Type, size_t, size_t>> getFullAttributes(const std::vector<std::tuple<Type, size_t>>& attributes)
{
    std::vector<std::tuple<Type, size_t, size_t>> full(attributes.size());

    size_t offset = 0;
    for (size_t i = 0; i < attributes.size(); i++)
    {
        const auto& [ type, count ] = attributes[i];
        full[i] = { type, count, offset };
        offset += getTypeSize(type) * count;
    }

    return full;
}

ArrayBuffer::ArrayBuffer(size_t stride, const std::vector<std::tuple<Type, size_t, size_t>>& attributes)
    : Buffer(), stride(stride), attributes(attributes)
{
}

ArrayBuffer::ArrayBuffer(const std::vector<std::tuple<Type, size_t>>& attributes)
    : Buffer(), stride(getStride(attributes)), attributes(getFullAttributes(attributes))
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
        const auto& [ type, count, offset ] = this->attributes[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, count, (GLenum)type, GL_FALSE, this->stride, (GLvoid*)offset);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
