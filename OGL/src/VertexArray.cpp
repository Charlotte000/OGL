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
        glVertexArrayAttribFormat(this->handler, index, count, (GLenum)type, GL_FALSE, offset);
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

void VertexArray::drawArrays(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size)
{
    const size_t count = this->vbo.getSize() / vertexStride;

    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawArrays((GLenum)mode, 0, count);
    glBindVertexArray(0);
}

void VertexArray::drawElements(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size)
{
    const size_t count = this->ebo.getSize() / getTypeSize(this->indexType);

    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawElements((GLenum)mode, count, (GLenum)this->indexType, nullptr);
    glBindVertexArray(0);
}

void VertexArray::drawArraysInstanced(PrimitiveType mode, size_t instanceCount, glm::uvec2 pos, glm::uvec2 size)
{
    const size_t count = this->vbo.getSize() / vertexStride;

    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawArraysInstanced((GLenum)mode, 0, count, instanceCount);
    glBindVertexArray(0);
}

void VertexArray::drawElementsInstanced(PrimitiveType mode, size_t instanceCount, glm::uvec2 pos, glm::uvec2 size)
{
    const size_t count = this->ebo.getSize() / getTypeSize(this->indexType);

    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawElementsInstanced((GLenum)mode, count, (GLenum)this->indexType, nullptr, instanceCount);
    glBindVertexArray(0);
}

GLuint VertexArray::getHandler() const
{
    return this->handler;
}
