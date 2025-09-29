/**
 * @file Enums.h
 */
#pragma once

#include <GL/glew.h>

namespace OGL
{

/**
 * @brief Data usage patterns for buffer objects.
 * 
 * These usage patterns provide hints to the OpenGL implementation about how the buffer will be used.
 */
enum class DataUsage : GLenum
{
    /**
     * @brief The data store contents will be modified once and used at most a few times.
     * 
     * The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
     */
    STREAM_DRAW = GL_STREAM_DRAW,

    /**
     * @brief The data store contents will be modified once and used at most a few times.
     * 
     * The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
     */
    STREAM_READ = GL_STREAM_READ,

    /**
     * @brief The data store contents will be modified once and used at most a few times.
     * 
     * The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
     */
    STREAM_COPY = GL_STREAM_COPY,

    /**
     * @brief The data store contents will be modified once and used many times.
     * 
     * The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
     */
    STATIC_DRAW = GL_STATIC_DRAW,

    /**
     * @brief The data store contents will be modified once and used many times.
     * 
     * The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
     * 
     */
    STATIC_READ = GL_STATIC_READ,

    /**
     * @brief The data store contents will be modified once and used many times.
     * 
     * The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
     */
    STATIC_COPY = GL_STATIC_COPY,

    /**
     * @brief The data store contents will be modified repeatedly and used many times.
     * 
     * The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
     */
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,

    /**
     * @brief The data store contents will be modified repeatedly and used many times.
     * 
     * The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
     */
    DYNAMIC_READ = GL_DYNAMIC_READ,

    /**
     * @brief The data store contents will be modified repeatedly and used many times.
     * 
     * The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
     */
    DYNAMIC_COPY = GL_DYNAMIC_COPY,
};

/**
 * @brief Texture filtering modes.
 */
enum class Filter : GLint
{
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR,
};

/**
 * @brief Texture wrapping modes.
 */
enum class Wrap : GLint
{
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    REPEAT = GL_REPEAT,
    MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
};

/**
 * @brief Buffer access types for mapping buffer objects.
 */
enum class Access : GLenum
{
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY,
    READ_WRITE = GL_READ_WRITE,
};

/**
 * @brief Primitive types for drawing commands.
 */
enum class PrimitiveType : GLenum
{
    POINTS = GL_POINTS,
    LINE_STRIP = GL_LINE_STRIP,
    LINE_LOOP = GL_LINE_LOOP,
    LINES = GL_LINES,
    LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
    LINES_ADJACENCY = GL_LINES_ADJACENCY,
    TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
    TRIANGLE_FAN = GL_TRIANGLE_FAN,
    TRIANGLES = GL_TRIANGLES,
    TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
    PATCHES = GL_PATCHES,
};

/**
 * @brief Unsigned data types for vertex attributes and indices.
 */
enum class TypeU : GLenum
{
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
};

/**
 * @brief Signed and floating-point data types for vertex attributes.
 */
enum class Type : GLenum
{
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    BYTE = GL_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    SHORT = GL_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
    INT = GL_INT,
    FLOAT = GL_FLOAT,
};

/**
 * @brief The format in which image data is stored in GPU memory.
 * 
 * See more formats at: https://www.khronos.org/opengl/wiki/Image_Format
 */
enum class ImageFormat : GLenum
{
    R16F = GL_R16F,
    RG16F = GL_RG16F,
    RGB16F = GL_RGB16F,
    RGBA16F = GL_RGBA16F,

    R32F = GL_R32F,
    RG32F = GL_RG32F,
    RGB32F = GL_RGB32F,
    RGBA32F = GL_RGBA32F,

    DEPTH16 = GL_DEPTH_COMPONENT16,
    DEPTH24 = GL_DEPTH_COMPONENT24,
    DEPTH32 = GL_DEPTH_COMPONENT32,
    DEPTH32F = GL_DEPTH_COMPONENT32F,

    DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
    DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,

    STENCIL8 = GL_STENCIL_INDEX8,
};

/**
 * @brief Image unit formats for image load/store operations.
 * 
 * These specify the format in which image data is accessed in shaders.
 * Must be compatible with the internal format of the texture bound to the image unit.
 * See more formats at: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindImageTexture.xhtml
 */
enum class ImageUnitFormat : GLenum
{
    R16F = GL_R16F,
    RG16F = GL_RG16F,
    RGB16F = GL_RGB16F,
    RGBA16F = GL_RGBA16F,

    R32F = GL_R32F,
    RG32F = GL_RG32F,
    RGB32F = GL_RGB32F,
    RGBA32F = GL_RGBA32F,
};

/**
 * @brief Pixel data formats for specifying texture data.
 * 
 * These specify the format of the pixel data provided to OpenGL when uploading texture data.
 */
enum class PixelFormat : GLenum
{
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,
    DEPTH = GL_DEPTH_COMPONENT,
    STENCIL = GL_STENCIL_INDEX,
};

/**
 * @brief Shader types.
 * 
 * These specify the type of shader being created or used.
 */
enum class ShaderType : GLenum
{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER,
    COMPUTE = GL_COMPUTE_SHADER,
    TESS_CONTROL = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER,
    GEOMETRY = GL_GEOMETRY_SHADER,
};

static size_t getTypeSize(TypeU type)
{
    switch (type)
    {
        case TypeU::UNSIGNED_BYTE:
            return sizeof(GLubyte);
        case TypeU::UNSIGNED_SHORT:
            return sizeof(GLushort);
        case TypeU::UNSIGNED_INT:
            return sizeof(GLuint);
    }

    return 0;
}

static size_t getTypeSize(Type type)
{
    switch (type)
    {
        case Type::UNSIGNED_BYTE:
            return sizeof(GLubyte);
        case Type::BYTE:
            return sizeof(GLbyte);
        case Type::UNSIGNED_SHORT:
            return sizeof(GLushort);
        case Type::SHORT:
            return sizeof(GLshort);
        case Type::UNSIGNED_INT:
            return sizeof(GLuint);
        case Type::INT:
            return sizeof(GLint);
        case Type::FLOAT:
            return sizeof(GLfloat);
    }

    return 0;
}

}
