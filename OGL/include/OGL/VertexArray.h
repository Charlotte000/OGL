/**
 * @file VertexArray.h
 */
#pragma once

#include <tuple>
#include <vector>

#include <glm/glm.hpp>

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

    VertexArray& operator=(VertexArray&& vao);

    /**
     * @brief Bind the vertex array to the OpenGL context.
     */
    void use();

    /**
     * @brief Renders vertex array from array data (VBO).
     * @param mode The type of primitives to render.
     * @param instanceCount The number of instances of indices to be rendered. Use gl_InstanceID from a vertex shader.
     */
    void drawArrays(PrimitiveType mode, size_t instanceCount = 1);

    /**
     * @brief Renders vertex array from array data (VBO) using indices (EBO).
     * @param mode The type of primitives to render.
     * @param instanceCount The number of instances of indices to be rendered. Use gl_InstanceID from a vertex shader.
     */
    void drawElements(PrimitiveType mode, size_t instanceCount = 1);

    /**
     * @brief Get the OpenGL handler of the vertex array.
     * @return OpenGL handler.
     */
    GLuint getHandler() const;

    /**
     * @brief Unbind any vertex array from the OpenGL context.
     */
    static void stopUse();
private:
    GLuint handler = -1;
    size_t vertexStride;
    TypeU indexType;
};

}
