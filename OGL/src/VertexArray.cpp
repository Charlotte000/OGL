#include "OGL/VertexArray.h"

using namespace OGL;

static size_t getVertexStride(const std::vector<std::tuple<Type, size_t>>& attributes)
{
    size_t size = 0;
    for (const auto& [type, count] : attributes)
    {
        size += getTypeSize(type) * count;
    }

    return size;
}

static std::vector<std::tuple<Type, size_t, size_t>> getFullAttributes(const std::vector<std::tuple<Type, size_t>>& attributes)
{
    std::vector<std::tuple<Type, size_t, size_t>> full(attributes.size());

    size_t offset = 0;
    size_t index = 0;
    for (const auto& [ type, count ] : attributes)
    {
        full[index] = { type, count, offset };
        offset += getTypeSize(type) * count;
        index++;
    }

    return full;
}

VertexArray::VertexArray(size_t vertexStride, const std::vector<std::tuple<Type, size_t, size_t>>& vertexAttributes, TypeU indexType)
    : vertexStride(vertexStride), indexType(indexType)
{
    glCreateVertexArrays(1, &this->handler);

    // VBO
    const size_t bindingindex = 0;
    glVertexArrayVertexBuffer(this->handler, bindingindex, this->vbo.getHandler(), 0, vertexStride);

    size_t index = 0;
    for (const auto& [ type, count, offset ] : vertexAttributes)
    {
        glEnableVertexArrayAttrib(this->handler, index);
        glVertexArrayAttribFormat(this->handler, index, count, static_cast<GLenum>(type), GL_FALSE, offset);
        glVertexArrayAttribBinding(this->handler, index, bindingindex);
        index++;
    }

    // EBO
    glVertexArrayElementBuffer(this->handler, this->ebo.getHandler());
}

VertexArray::VertexArray(const std::vector<std::tuple<Type, size_t>>& vertexAttributes, TypeU indexType)
    : VertexArray(getVertexStride(vertexAttributes), getFullAttributes(vertexAttributes), indexType)
{
}

VertexArray::VertexArray(VertexArray&& vao)
    : handler(vao.handler), indexType(vao.indexType), vbo(std::move(vao.vbo)), ebo(std::move(vao.ebo))
{
    vao.handler = -1;
}

VertexArray::~VertexArray()
{
    if (this->handler != -1)
    {
        glDeleteVertexArrays(1, &this->handler);
    }
}

VertexArray& VertexArray::operator=(VertexArray&& vao)
{
    if (this->handler != -1)
    {
        glDeleteVertexArrays(1, &this->handler);
    }

    this->handler = vao.handler;
    this->indexType = vao.indexType;
    this->vbo = std::move(vao.vbo);
    this->ebo = std::move(vao.ebo);

    vao.handler = -1;
    return *this;
}

void VertexArray::use()
{
    glBindVertexArray(this->handler);
}

void VertexArray::drawArrays(PrimitiveType mode, unsigned int count, unsigned int offset, unsigned int instanceCount)
{
    const size_t maxCount = this->vbo.getSize() / vertexStride;
    if (count == -1) count = maxCount;

    assert(offset + count <= maxCount);

    this->use();
    glDrawArraysInstanced(static_cast<GLenum>(mode), offset, count, instanceCount);
    VertexArray::stopUse();
}

void VertexArray::drawElements(PrimitiveType mode, unsigned int count, unsigned int offset, unsigned int instanceCount, unsigned int vertexOffset)
{
    const size_t stride = getTypeSize(this->indexType);
    const size_t maxCount = this->ebo.getSize() / stride;
    if (count == -1) count = maxCount;

    assert(offset + count <= maxCount);

    this->use();
    glDrawElementsInstancedBaseVertex(
        static_cast<GLenum>(mode),
        count,
        static_cast<GLenum>(this->indexType),
        reinterpret_cast<const void*>(offset * stride),
        instanceCount,
        vertexOffset
    );
    VertexArray::stopUse();
}

GLuint VertexArray::getHandler() const
{
    return this->handler;
}

void VertexArray::stopUse()
{
    glBindVertexArray(0);
}
