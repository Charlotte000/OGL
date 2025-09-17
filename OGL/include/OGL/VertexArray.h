#pragma once

#include <tuple>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "OGL/Enums.h"
#include "OGL/ArrayBuffer.h"
#include "OGL/ElementArrayBuffer.h"

namespace OGL
{

class VertexArray
{
public:
    ArrayBuffer vbo;
    ElementArrayBuffer ebo;

    VertexArray(size_t vertexStride, const std::vector<std::tuple<Type, size_t, size_t>>& vertexAttributes, TypeU indexType = TypeU::UNSIGNED_INT);

    VertexArray(const std::vector<std::tuple<Type, size_t>>& vertexAttributes, TypeU indexType = TypeU::UNSIGNED_INT);

    VertexArray(VertexArray&& vao);

    ~VertexArray();

    void drawArrays(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size);

    void drawArrays(PrimitiveType mode, glm::uvec2 size);

    void drawElements(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size);

    void drawElements(PrimitiveType mode, glm::uvec2 size);

    GLuint getHandler() const;
private:
    GLuint handler = -1;
    size_t vertexStride;
    TypeU indexType;
};

}
