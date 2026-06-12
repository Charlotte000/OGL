#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "OGL/Shader.h"

using namespace OGL;

Shader::Shader(ShaderType type, const char* src, int srcSize)
{
    // Create shader
    this->handler = glCreateShader(static_cast<GLenum>(type));

    // Attach code
    const GLchar* code = static_cast<const GLchar*>(src);
    const GLint size = static_cast<GLint>(srcSize);
    glShaderSource(this->handler, 1, &code, &size);

    glCompileShader(this->handler);

    this->checkStatus(GL_COMPILE_STATUS);
}

Shader::Shader(ShaderType type, const std::filesystem::path& path)
{
    // Create shader
    this->handler = glCreateShader(static_cast<GLenum>(type));

    // Attach code
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Shader source not found: " + path.string());

    std::string src((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    const GLchar* code = static_cast<const GLchar*>(src.c_str());
    glShaderSource(this->handler, 1, &code, 0);

    glCompileShader(this->handler);

    this->checkStatus(GL_COMPILE_STATUS);
}

Shader::Shader(ShaderType type, const void* src, size_t srcSize)
{
    // Create shader
    this->handler = glCreateShader(static_cast<GLenum>(type));

    // Attach code
    glShaderBinary(1, &this->handler, GL_SHADER_BINARY_FORMAT_SPIR_V, src, srcSize);
    glSpecializeShader(this->handler, "main", 0, nullptr, nullptr);

    this->checkStatus(GL_COMPILE_STATUS);
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
        glDeleteShader(this->handler);
        this->handler = -1;
    }
}

Shader& Shader::operator=(Shader&& shader)
{
    if (this->handler != -1)
    {
        glDeleteShader(this->handler);
    }

    this->handler = shader.handler;
    shader.handler = -1;
    return *this;
}

GLuint Shader::getHandler() const
{
    return this->handler;
}

ShaderType Shader::type() const
{
    GLint val;
    glGetShaderiv(this->handler, GL_SHADER_TYPE, &val);
    return static_cast<ShaderType>(val);
}

void Shader::checkStatus(GLenum param) const
{
    GLint status;
    glGetShaderiv(this->handler, param, &status);
    if (status != GL_TRUE)
    {
        GLint logSize;
        glGetShaderiv(this->handler, GL_INFO_LOG_LENGTH, &logSize);

        char* info = new char[logSize + 1];
        glGetShaderInfoLog(this->handler, logSize, nullptr, info);
        std::string msg(info);
        delete[] info;

        glDeleteShader(this->handler);
        throw std::runtime_error("Shader failed: " + msg);
    }
}
