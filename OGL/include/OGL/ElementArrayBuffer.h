/**
 * @file ElementArrayBuffer.h
 */
#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

/**
 * @brief Element array buffer (EBO/IBO) class for index data storage.
 * 
 * Element array buffers are used to store indices that define the order in which vertices are processed.
 * They are typically used in conjunction with vertex array buffers to optimize rendering by reusing vertex data.
 * Use VertexArray::drawElements to render using the indices stored in an ElementArrayBuffer.
 */
class ElementArrayBuffer : public Buffer<GL_ELEMENT_ARRAY_BUFFER>
{
};

}