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
     * @brief Create a shader from source code.
     * @param type Type of the shader.
     * @param src Source code of the shader.
     * @param srcSize Size of the source code in bytes. If the source code is a null-terminated GLSL code, this parameter can be set to 0.
     * @param format Format of the shader source code.
     * @throw std::runtime_error if the shader cannot be created.
     */
    Shader(ShaderType type, const void* src, size_t srcSize, ShaderFormat format = ShaderFormat::GLSL);

    /**
     * @brief Create a shader from a file.
     * @param type Type of the shader.
     * @param path Path to the shader file.
     * @param format Format of the shader source code.
     * @throw std::runtime_error if the shader cannot be created.
     */
    Shader(ShaderType type, const std::filesystem::path& path, ShaderFormat format = ShaderFormat::GLSL);

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
