#pragma once

#include <tuple>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

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

    /**
     * @param mode { GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY, GL_PATCHES }
     */
    void drawArrays(GLenum mode, glm::uvec2 pos, glm::uvec2 size);

    void drawArrays(GLenum mode, glm::uvec2 size);

    void drawElements(GLenum mode, glm::uvec2 pos, glm::uvec2 size);

    void drawElements(GLenum mode, glm::uvec2 size);

    GLuint getHandler() const;
private:
    GLuint handler = -1;
};

}
