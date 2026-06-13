#include <fstream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

#include "OGL/Shader.h"

using namespace OGL;

static inline void attachCode(GLuint shaderHandler, const void* src, size_t srcSize, ShaderFormat format)
{
    switch (format)
    {
        case ShaderFormat::GLSL:
        {
            const GLchar* code = reinterpret_cast<const GLchar*>(src);
            const GLint size = srcSize == 0 ? -1 : srcSize;
            glShaderSource(shaderHandler, 1, &code, &size);
            glCompileShader(shaderHandler);
            break;
        }
        case ShaderFormat::SPIRV:
            glShaderBinary(1, &shaderHandler, GL_SHADER_BINARY_FORMAT_SPIR_V, src, srcSize);
            glSpecializeShader(shaderHandler, "main", 0, nullptr, nullptr);
            break;
        default:
            throw std::runtime_error("Unsupported shader format");
    }
}

Shader::Shader(ShaderType type, const void* src, size_t srcSize, ShaderFormat format)
{
    // Create shader
    this->handler = glCreateShader(static_cast<GLenum>(type));

    // Attach code
    attachCode(this->handler, src, srcSize, format);

    this->checkStatus(GL_COMPILE_STATUS);
}

Shader::Shader(ShaderType type, const std::filesystem::path& path, ShaderFormat format)
{
    // Create shader
    this->handler = glCreateShader(static_cast<GLenum>(type));

    // Open the file
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open())
        throw std::runtime_error("Shader source not found: " + path.string());

    // Get the file size
    std::streamsize srcSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file
    std::vector<uint8_t> buffer(srcSize);
    file.read(reinterpret_cast<char*>(buffer.data()), srcSize);
    file.close();

    // Attach code
    attachCode(this->handler, reinterpret_cast<const void*>(buffer.data()), srcSize, format);

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
        glDeleteShader(this->handler);

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
