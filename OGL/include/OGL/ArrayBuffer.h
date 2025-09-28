/**
 * @file ArrayBuffer.h
 */
#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

/**
 * @brief Array buffer (VBO) class for vertex data storage.
 * 
 * Array buffers are used to store vertex attributes such as position, normal, color, texture coordinates, etc.
 * They are typically used in conjunction with vertex array objects (VAOs) to define the format and source of vertex data for rendering.
 * Use VertexArray::drawArrays or VertexArray::drawElements to render using the vertex data stored in an ArrayBuffer.
 */
class ArrayBuffer : public Buffer<GL_ARRAY_BUFFER>
{
};

}