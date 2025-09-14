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

    VertexArray(ArrayBuffer&& vbo, ElementArrayBuffer&& ebo);

    VertexArray(VertexArray&& vao);

    ~VertexArray();

    void drawArrays(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size);

    void drawArrays(PrimitiveType mode, glm::uvec2 size);

    void drawElements(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size);

    void drawElements(PrimitiveType mode, glm::uvec2 size);

    GLuint getHandler() const;
private:
    GLuint handler = -1;
};

}
