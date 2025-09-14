#include "OGL/VertexArray.h"

using namespace OGL;

VertexArray::VertexArray(ArrayBuffer&& vbo, ElementArrayBuffer&& ebo)
    : vbo(std::move(vbo)), ebo(std::move(ebo))
{
    glGenVertexArrays(1, &this->handler);
    glBindVertexArray(this->handler);

    // VBO
    this->vbo.bindAttributes();
    this->vbo.use();

    // EBO
    this->ebo.use();

    glBindVertexArray(0);
}

VertexArray::VertexArray(VertexArray&& vao)
    : handler(handler), vbo(std::move(vao.vbo)), ebo(std::move(vao.ebo))
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
    const size_t count = this->vbo.getSize() / this->vbo.stride;

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
    const size_t count = this->ebo.getSize() / getTypeSize(this->ebo.type);

    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawElements((GLenum)mode, count, (GLenum)this->ebo.type, nullptr);
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
