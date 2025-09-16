#include "OGL/VertexArray.h"

using namespace OGL;

VertexArray::VertexArray(size_t vertexStride, const std::vector<std::tuple<Type, size_t, size_t>>& vertexAttributes, TypeU indexType)
    : vbo(), ebo(), vertexStride(vertexStride), indexType(indexType)
{
    glCreateVertexArrays(1, &this->handler);

    // VBO
    const size_t bindingindex = 0;
    glVertexArrayVertexBuffer(this->handler, bindingindex, this->vbo.getHandler(), 0, vertexStride);
    for (size_t i = 0; i < vertexAttributes.size(); i++)
    {
        const auto& [ type, count, offset ] = vertexAttributes[i];

        glEnableVertexArrayAttrib(this->handler, i);
        glVertexArrayAttribFormat(this->handler, i, count, (GLenum)type, GL_FALSE, offset);
        glVertexArrayAttribBinding(this->handler, i, bindingindex);
    }

    // EBO
    glVertexArrayElementBuffer(this->handler, this->ebo.getHandler());
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

void VertexArray::drawArrays(PrimitiveType mode, glm::uvec2 size)
{
    this->drawArrays(mode, glm::uvec2(0, 0), size);
}

void VertexArray::drawElements(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size)
{
    const size_t count = this->ebo.getSize() / getTypeSize(this->indexType);

    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawElements((GLenum)mode, count, (GLenum)this->indexType, nullptr);
    glBindVertexArray(0);
}

void VertexArray::drawElements(PrimitiveType mode, glm::uvec2 size)
{
    this->drawElements(mode, glm::uvec2(0, 0), size);
}

GLuint VertexArray::getHandler() const
{
    return this->handler;
}
