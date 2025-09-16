#pragma once

#include <GL/glew.h>

namespace OGL
{

enum class DataUsage : GLenum
{
    STREAM_DRAW = GL_STREAM_DRAW,
    STREAM_READ = GL_STREAM_READ,
    STREAM_COPY = GL_STREAM_COPY,
    STATIC_DRAW = GL_STATIC_DRAW,
    STATIC_READ = GL_STATIC_READ,
    STATIC_COPY = GL_STATIC_COPY,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
    DYNAMIC_READ = GL_DYNAMIC_READ,
    DYNAMIC_COPY = GL_DYNAMIC_COPY,
};

enum class Filter : GLint
{
    NEAREST = GL_NEAREST,
    LINEAR = GL_LINEAR,
};

enum class Wrap : GLint
{
    CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
    CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
    MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
    REPEAT = GL_REPEAT,
    MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE,
};

enum class Access : GLenum
{
    READ_ONLY = GL_READ_ONLY,
    WRITE_ONLY = GL_WRITE_ONLY,
    READ_WRITE = GL_READ_WRITE,
};

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

enum class TypeU : GLenum
{
    UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
    UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
    UNSIGNED_INT = GL_UNSIGNED_INT,
};

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

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexStorage2D.xhtml
enum class InternalFormat : GLenum
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

// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindImageTexture.xhtml
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

enum class PixelFormat : GLenum
{
    RED = GL_RED,
    RG = GL_RG,
    RGB = GL_RGB,
    RGBA = GL_RGBA,
    DEPTH = GL_DEPTH_COMPONENT,
    STENCIL = GL_STENCIL_INDEX,
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

};