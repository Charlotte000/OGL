#pragma once

#include <GL/glew.h>

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


namespace OGL::Context
{

namespace Viewport
{

OGL_PARAM_BOX(Box, GL_VIEWPORT, glViewport);

}

namespace Scissor
{

OGL_PARAM_BOX(Box, GL_SCISSOR_BOX, glScissor);

OGL_PARAM_BOOL_EN_DIS(Test, GL_SCISSOR_TEST);

}

namespace Depth
{

/**
 * @brief Whether depth testing of fragments is enabled.
 */
OGL_PARAM_BOOL_EN_DIS(Test, GL_DEPTH_TEST);

/**
 * @brief Whether to ignore near and far clipping plane.
 */
OGL_PARAM_BOOL_EN_DIS(Clamp, GL_DEPTH_CLAMP);

/**
 * @brief The depth comparison function
 */
OGL_PARAM_INT(Func, GL_DEPTH_FUNC, glDepthFunc, Func);

/**
 * @brief Mapping of depth values from normalized device coordinates to window coordinates.
 * 
 * First value specifies the mapping of the near clipping plane to window coordinates.
 * 
 * Second value specifies the mapping of the far clipping plane to window coordinates.
 */
OGL_PARAM_FLOAT2(Range, GL_DEPTH_RANGE, glDepthRange);

OGL_PARAM_BOOL(WriteMask, GL_DEPTH_WRITEMASK, glDepthMask);

}

}
