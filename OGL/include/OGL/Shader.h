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
     * @param src Source code of the shader.
     * @param type Shader stage.
     */
    Shader(const std::string& src, ShaderType type);

    /**
     * @brief Load a GLSL shader from a file.
     * @param path Path to the shader code.
     * @param type Shader stage.
     */
    Shader(const std::filesystem::path& path, ShaderType type);

    /**
     * @brief Load a SPIR-V shader from provided binary.
     * 
     * Standard, Portable Intermediate Representation - V (SPIR-V) is an intermediate language for defining shaders.
     * 
     * @param src Source binary.
     * @param srcSize Size of the source binary.
     * @param type Shader stage.
     */
    Shader(const unsigned char src[], size_t srcSize, ShaderType type);

    Shader(Shader&& shader);

    ~Shader();

    Shader& operator=(Shader&& shader);

    /**
     * @brief Get the OpenGL handler of the shader.
     * @return OpenGL handler.
     */
    GLuint getHandler() const;
private:
    GLuint handler = -1;

    void checkStatus() const;
};

}
