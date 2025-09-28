/**
 * @file VertexArray.h
 */
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

/**
 * @brief Vertex array (VAO) class stores all of the state needed to supply vertex data (VBO and EBO).
 */
class VertexArray
{
public:
    /**
     * @brief Vertex buffer is used as a source for vertex array data.
     */
    ArrayBuffer vbo;

    /**
     * @brief Element array buffer is used as a source for index data.
     */
    ElementArrayBuffer ebo;

    /**
     * @brief Construct a new Vertex Array object (VAO)
     * @param vertexStride The distance between elements within the buffer.
     * @param vertexAttributes A collection of ( attribute type, attribute count, attribute offset ).
     * @param indexType The type of the EBO values.
     */
    VertexArray(size_t vertexStride, const std::vector<std::tuple<Type, size_t, size_t>>& vertexAttributes, TypeU indexType = TypeU::UNSIGNED_INT);

    /**
     * @brief Construct a new Vertex Array object (VAO)
     * @param vertexAttributes A collection of ( attribute type, attribute count ).
     * @param indexType The type of the EBO values.
     */
    VertexArray(const std::vector<std::tuple<Type, size_t>>& vertexAttributes, TypeU indexType = TypeU::UNSIGNED_INT);

    VertexArray(VertexArray&& vao);

    ~VertexArray();

    /**
     * @brief Renders vertex array from array data (VBO).
     * @param mode The type of primitives to render.
     * @param pos Coordinates of the viewport rectangle position where (0, 0) is the top-left corner.
     * @param size The size of the viewport rectangle.
     */
    void drawArrays(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size);

    /**
     * @brief Renders vertex array from array data (VBO) using indices (EBO).
     * @param mode The type of primitives to render.
     * @param pos Coordinates of the viewport rectangle position where (0, 0) is the top-left corner.
     * @param size The size of the viewport rectangle.
     */
    void drawElements(PrimitiveType mode, glm::uvec2 pos, glm::uvec2 size);

    /**
     * @brief Renders multiple instances of vertex array from array data (VBO).
     * @param mode The type of primitives to render.
     * @param instanceCount The number of instances of indices to be rendered. Use gl_InstanceID from a vertex shader.
     * @param pos Coordinates of the viewport rectangle position where (0, 0) is the top-left corner.
     * @param size The size of the viewport rectangle.
     */
    void drawArraysInstanced(PrimitiveType mode, size_t instanceCount, glm::uvec2 pos, glm::uvec2 size);

    /**
     * @brief Renders multiple instances of vertex array from array data (VBO) using indices (EBO).
     * @param mode The type of primitives to render.
     * @param instanceCount The number of instances of indices to be rendered. Use gl_InstanceID from a vertex shader.
     * @param pos Coordinates of the viewport rectangle position where (0, 0) is the top-left corner.
     * @param size The size of the viewport rectangle.
     */
    void drawElementsInstanced(PrimitiveType mode, size_t instanceCount, glm::uvec2 pos, glm::uvec2 size);

    /**
     * @brief Get the OpenGL handler of the vertex array.
     * @return OpenGL handler.
     */
    GLuint getHandler() const;
private:
    GLuint handler = -1;
    size_t vertexStride;
    TypeU indexType;
};

}
