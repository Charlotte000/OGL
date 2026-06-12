/**
 * @file Shader.h
 */
#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <glm/glm.hpp>

#include "OGL/Enums.h"

namespace OGL
{

/**
 * @brief Shader class that represents an OpenGL shader object.
 * 
 * A Shader is a user-defined program designed to run on some stage of a graphics processor. Shaders provide the code for certain programmable stages of the rendering pipeline.
 */
class Shader
{
public:
    /**
     * @brief Load a GLSL shader from provided string.
     * @param type Shader stage.
     * @param src Source code of the shader.
     * @param srcSize The length of the source code. If less than 0, the source code is assumed to be null-terminated.
     * @throw std::runtime_error if the shader cannot be created.
     */
    Shader(ShaderType type, const char* src, int srcSize = -1);

    /**
     * @brief Load a GLSL shader from a file.
     * @param type Shader stage.
     * @param path Path to the shader code.
     * @throw std::runtime_error if the shader cannot be created.
     */
    Shader(ShaderType type, const std::filesystem::path& path);

    /**
     * @brief Load a SPIR-V shader from provided binary.
     * 
     * Standard, Portable Intermediate Representation - V (SPIR-V) is an intermediate language for defining shaders.
     * 
     * @param type Shader stage.
     * @param src Source binary.
     * @param srcSize Size of the source binary.
     * @throw std::runtime_error if the shader cannot be created.
     */
    Shader(ShaderType type, const void* src, size_t srcSize);

    Shader(Shader&& shader);

    ~Shader();

    Shader& operator=(Shader&& shader);

    /**
     * @brief Get the OpenGL handler of the shader.
     * @return OpenGL handler.
     */
    GLuint getHandler() const;

    ShaderType type() const;
private:
    GLuint handler = -1;

    void checkStatus(GLenum param) const;
};

}
