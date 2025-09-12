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

void VertexArray::drawArrays(GLenum mode, glm::uvec2 pos, glm::uvec2 size)
{
    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawArrays(mode, 0, this->vbo.size / this->vbo.stride);
    glBindVertexArray(0);
}

void VertexArray::drawArrays(GLenum mode, glm::uvec2 size)
{
    this->drawArrays(mode, glm::uvec2(0, 0), size);
}

void VertexArray::drawElements(GLenum mode, glm::uvec2 pos, glm::uvec2 size)
{
    glBindVertexArray(this->handler);
    glViewport(pos.x, pos.y, size.x, size.y);
    glDrawElements(mode, this->ebo.size / this->ebo.stride, this->ebo.type, nullptr);
    glBindVertexArray(0);
}

void VertexArray::drawElements(GLenum mode, glm::uvec2 size)
{
    this->drawElements(mode, glm::uvec2(0, 0), size);
}

GLuint VertexArray::getHandler() const
{
    return this->handler;
}
