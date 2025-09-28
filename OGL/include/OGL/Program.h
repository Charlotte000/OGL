/**
 * @file Program.h
 */
#pragma once

#include <GL/glew.h>

#include "OGL/Shader.h"

namespace OGL
{

/**
 * @brief Program class that represents an OpenGL shader program.
 * 
 * A shader program is a combination of multiple shaders (e.g., vertex, fragment, compute) that are linked together to form a complete GPU program.
 */
class Program
{
public:
    Program(const std::initializer_list<Shader>& shaders);

    Program(Program&& program);

    ~Program();

    /**
     * @brief Bind the shader program to the OpenGL context for rendering or compute operations.
     */
    void use();

    /**
     * @brief Update the value of a uniform variable in the shader program.
     * 
     * The program must be in use (bound) before calling this function.
     * 
     * @param name Name of the uniform variable.
     * @param value New value of the uniform variable.
     */
    void updateUniform(const std::string& name, int value);

    /**
     * @brief Update the value of a uniform variable in the shader program.
     * 
     * The program must be in use (bound) before calling this function.
     * 
     * @param name Name of the uniform variable.
     * @param value New value of the uniform variable.
     */
    void updateUniform(const std::string& name, float value);

    /**
     * @brief Update the value of a uniform variable in the shader program.
     * 
     * The program must be in use (bound) before calling this function.
     * 
     * @param name Name of the uniform variable.
     * @param value New value of the uniform variable.
     */
    void updateUniform(const std::string& name, glm::vec2 value);

    /**
     * @brief Update the value of a uniform variable in the shader program.
     * 
     * The program must be in use (bound) before calling this function.
     * 
     * @param name Name of the uniform variable.
     * @param value New value of the uniform variable.
     */
    void updateUniform(const std::string& name, glm::vec3 value);

    /**
     * @brief Update the value of a uniform variable in the shader program.
     * 
     * The program must be in use (bound) before calling this function.
     * 
     * @param name Name of the uniform variable.
     * @param value New value of the uniform variable.
     */
    void updateUniform(const std::string& name, glm::mat4 value);

    /**
     * @brief Get the OpenGL handler of the shader program.
     * @return OpenGL handler.
     */
    GLuint getHandler() const;

    /**
     * @brief Apply a compute shader with the specified number of work groups.
     * @param groups
     */
    static void applyCompute(glm::ivec3 groups);

    /**
     * @brief Unbind any program from the OpenGL context.
     * 
     */
    static void stopUse();
private:
    GLuint handler = -1;

    void checkStatus() const;
};

}
