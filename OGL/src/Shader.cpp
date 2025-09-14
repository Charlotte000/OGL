#include <fstream>
#include <glm/gtc/type_ptr.hpp>

#include "OGL/Shader.h"

using namespace OGL;

Shader::Shader(const std::filesystem::path& computePath)
{
    // Create OpenGL shader
    const GLuint computeHandler = this->initShader(computePath, GL_COMPUTE_SHADER);

    // Create OpenGL program
    this->handler = this->initProgram({ computeHandler });

    // Clean OpenGL shader
    glDeleteShader(computeHandler);
}

Shader::Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath)
{
    // Create OpenGL shaders
    const GLuint vertexHandler = this->initShader(vertexPath, GL_VERTEX_SHADER);
    const GLuint fragmentHandler = this->initShader(fragmentPath, GL_FRAGMENT_SHADER);

    // Create OpenGL program
    this->handler = this->initProgram({ vertexHandler, fragmentHandler });

    // Clean OpenGL shaders
    glDeleteShader(vertexHandler);
    glDeleteShader(fragmentHandler);
}

Shader::Shader(Shader&& shader)
    : handler(shader.handler)
{
    shader.handler = -1;
}

Shader::~Shader()
{
    if (this->handler != -1)
    {
        glDeleteProgram(this->handler);
    }
}

void Shader::use()
{
    glUseProgram(this->handler);
}

void Shader::updateUniform(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(this->handler, name.c_str()), value);
}

void Shader::updateUniform(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(this->handler, name.c_str()), value);
}

void Shader::updateUniform(const std::string& name, glm::vec2 value)
{
    glUniform2f(glGetUniformLocation(this->handler, name.c_str()), value.x, value.y);
}

void Shader::updateUniform(const std::string& name, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(this->handler, name.c_str()), value.x, value.y, value.z);
}

void Shader::updateUniform(const std::string& name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->handler, name.c_str()), 1, false, glm::value_ptr(value));
}

GLuint Shader::getHandler() const
{
    return this->handler;
}

void Shader::applyCompute(glm::ivec3 groups)
{
    glDispatchCompute((GLuint)groups.x, (GLuint)groups.y, (GLuint)groups.z);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Shader::stopUse()
{
    glUseProgram(0);
}

GLuint Shader::initShader(const std::filesystem::path& main_path, GLenum shaderType)
{
    const std::string src = Shader::load(main_path);
    const GLchar* code = (const GLchar*)src.c_str();
    const GLuint handler = glCreateShader(shaderType);
    glShaderSource(handler, 1, &code, 0);
    glCompileShader(handler);

    GLint status = 0;
    glGetShaderiv(handler, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        std::string msg;
        GLint logSize = 0;
        glGetShaderiv(handler, GL_INFO_LOG_LENGTH, &logSize);
        char* info = new char[logSize + 1];
        glGetShaderInfoLog(handler, logSize, NULL, info);
        msg += info;
        delete[] info;
        glDeleteShader(handler);
        throw std::runtime_error(msg);
    }

    return handler;
}

GLuint Shader::initProgram(const std::vector<GLuint>& handlers)
{
    const GLuint handler = glCreateProgram();

    for (const GLuint shaderHandler : handlers)
    {
        glAttachShader(handler, shaderHandler);
    }

    glLinkProgram(handler);

    GLint success = 0;
    glGetProgramiv(handler, GL_LINK_STATUS, &success);
    if (success != GL_TRUE)
    {
        std::string msg;
        GLint logSize = 0;
        glGetProgramiv(handler, GL_INFO_LOG_LENGTH, &logSize);
        char* info = new char[logSize + 1];
        glGetShaderInfoLog(handler, logSize, NULL, info);
        msg += info;
        delete[] info;
        glDeleteProgram(handler);
        throw std::runtime_error(msg);
    }

    return handler;
}

const std::string Shader::load(const std::filesystem::path& path)
{
    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Shader source not found: " + path.string());
    }

    std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return source;
}
