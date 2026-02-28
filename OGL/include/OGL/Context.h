/**
 * @file Context.h
 */
#pragma once

#include <glm/glm.hpp>

#include "OGL/Enums.h"

#define OGL_PARAM_BOOL_EN_DIS(name, glName) \
static inline bool get##name()              \
{                                           \
    GLboolean val;                          \
    glGetBooleanv(glName, &val);            \
    return val;                             \
}                                           \
static inline void set##name(bool val)      \
{                                           \
    if (val) glEnable(glName);              \
    else glDisable(glName);                 \
}

#define OGL_PARAM_BOOL(name, glGetName, glSetFunc)  \
static inline bool get##name()                      \
{                                                   \
    GLboolean val;                                  \
    glGetBooleanv(glGetName, &val);                 \
    return val;                                     \
}                                                   \
static inline void set##name(bool val)              \
{                                                   \
    glSetFunc(val);                                 \
}

#define OGL_PARAM_INT(name, glGetName, glSetFunc, type) \
static inline type get##name()                          \
{                                                       \
    GLint val;                                          \
    glGetIntegerv(glGetName, &val);                     \
    return static_cast<type>(val);                      \
}                                                       \
static inline void set##name(type val)                  \
{                                                       \
    glSetFunc(static_cast<GLenum>(val));                \
}

#define OGL_PARAM_FLOAT(name, glGetName, glSetFunc) \
static inline float get##name()                     \
{                                                   \
    GLfloat val;                                    \
    glGetFloatv(glGetName, &val);                   \
    return val;                                     \
}                                                   \
static inline void set##name(float val)             \
{                                                   \
    glSetFunc(val);                                 \
}

#define OGL_PARAM_FLOAT2(name, glGetName, glSetFunc)    \
static inline glm::vec2 get##name()                     \
{                                                       \
    GLfloat val[2];                                     \
    glGetFloatv(glGetName, val);                        \
    return glm::vec2(val[0], val[1]);                   \
}                                                       \
static inline void set##name(glm::vec2 val)             \
{                                                       \
    glSetFunc(val.x, val.y);                            \
}

#define OGL_PARAM_BOX(name, glGetName, glSetFunc)               \
static inline glm::uvec4 get##name()                            \
{                                                               \
    GLint val[4];                                               \
    glGetIntegerv(glGetName, val);                              \
    return glm::uvec4(val[0], val[1], val[2], val[3]);          \
}                                                               \
static inline void set##name(glm::uvec2 pos, glm::uvec2 size)   \
{                                                               \
    glSetFunc(pos.x, pos.y, size.x, size.y);                    \
}


/**
 * @brief The OGL context specifies the state of the OpenGL context.
 *
 * This class provides methods to set and get various parameters related to the viewport, scissor, depth test, blend mode, and more.
 */
namespace OGL::Context
{

/**
 * @brief The viewport is a rectangular area within the window where rendering takes place. It can be used to clip parts of the scene that are outside this rectangle.
 */
namespace Viewport
{

OGL_PARAM_BOX(Box, GL_VIEWPORT, glViewport);

}

/**
 * @brief Scissor clipping is used to restrict the rendering area within a rectangular region.
 */
namespace Scissor
{

OGL_PARAM_BOX(Box, GL_SCISSOR_BOX, glScissor);

OGL_PARAM_BOOL_EN_DIS(Test, GL_SCISSOR_TEST);

}

/**
 * @brief Depth testing is used to determine whether a pixel should be written or not.
 */
namespace Depth
{

OGL_PARAM_BOOL_EN_DIS(Enable, GL_DEPTH_TEST);

OGL_PARAM_BOOL_EN_DIS(Clamp, GL_DEPTH_CLAMP);

OGL_PARAM_INT(Func, GL_DEPTH_FUNC, glDepthFunc, Func);

OGL_PARAM_FLOAT2(Range, GL_DEPTH_RANGE, glDepthRange);

OGL_PARAM_BOOL(WriteMask, GL_DEPTH_WRITEMASK, glDepthMask);

}

/**
 * @brief Stencil testing is used mask out pixels based on their stencil value.
 */
namespace Stencil
{

OGL_PARAM_BOOL_EN_DIS(Enable, GL_STENCIL_TEST);

}

/**
 * @brief Blending specifies how colors are combined when blending occurs.
 */
namespace Blend
{

OGL_PARAM_BOOL_EN_DIS(Enable, GL_BLEND);

}

/**
 * @brief Point related parameters. These parameters control how points are drawn on the screen.
 */
namespace Point
{

OGL_PARAM_BOOL_EN_DIS(Smooth, GL_POINT_SMOOTH);

OGL_PARAM_FLOAT(Size, GL_POINT_SIZE, glPointSize);

OGL_PARAM_BOOL_EN_DIS(EnableProgramSize, GL_PROGRAM_POINT_SIZE);

}

/**
 * @brief Line related parameters. These parameters control how lines are drawn on the screen.
 */
namespace Line
{

OGL_PARAM_BOOL_EN_DIS(Smooth, GL_LINE_SMOOTH);

OGL_PARAM_FLOAT(Width, GL_LINE_WIDTH, glLineWidth);

}

/**
 * @brief Polygon related parameters. These parameters control how polygons are drawn on the screen.
 */
namespace Polygon
{

OGL_PARAM_BOOL_EN_DIS(Smooth, GL_POLYGON_SMOOTH);

}

/**
 * @brief Face culling is a feature that improves rendering perfomance by discarding triangles that face away from the viewer.
 */
namespace CullFace
{

OGL_PARAM_BOOL_EN_DIS(Enable, GL_CULL_FACE);

OGL_PARAM_INT(Mode, GL_CULL_FACE_MODE, glCullFace, FaceMode);

OGL_PARAM_INT(FrontFace, GL_FRONT_FACE, glFrontFace, WindingOrder);

}

/**
 * @brief Cube map related parameters. These parameters control how cube maps are drawn on the screen.
 */
namespace CubeMap
{

OGL_PARAM_BOOL_EN_DIS(Seamless, GL_TEXTURE_CUBE_MAP_SEAMLESS);

}

/**
 * @brief Checks for OpenGL errors and throws a runtime error if any error is found.
 * @throw std::runtime_error if an OpenGL error is detected.
 */
void checkError()
{
    GLenum code;
    while ((code = glGetError()) != GL_NO_ERROR)
    {
        switch (code)
        {
            case GL_NO_ERROR:
                break;
            case GL_INVALID_ENUM:
                throw std::runtime_error("GL_INVALID_ENUM: an unacceptable value is specified for an enumerated argument");
            case GL_INVALID_VALUE:
                throw std::runtime_error("GL_INVALID_VALUE: a numeric argument is out of range");
            case GL_INVALID_OPERATION:
                throw std::runtime_error("GL_INVALID_OPERATION: the specified operation is not allowed in the current state");
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                throw std::runtime_error("GL_INVALID_FRAMEBUFFER_OPERATION: the framebuffer object is not complete");
            case GL_OUT_OF_MEMORY:
                throw std::runtime_error("GL_OUT_OF_MEMORY: there is not enough memory left to execute the command");
            case GL_STACK_UNDERFLOW:
                throw std::runtime_error("GL_STACK_UNDERFLOW: an attempt has been made to perform an operation that would cause an internal stack to underflow");
            case GL_STACK_OVERFLOW:
                throw std::runtime_error("GL_STACK_OVERFLOW: an attempt has been made to perform an operation that would cause an internal stack to overflow");
            default:
                throw std::runtime_error("Unexpected error code: " + std::to_string(code));
        }
    }
}

}
