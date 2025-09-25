#include <glm/gtc/type_ptr.hpp>

#include "OGL/Program.h"

using namespace OGL;

Program::Program(const std::initializer_list<Shader>& shaders)
{
    // Create program
    this->handler = glCreateProgram();

    // Attach shaders
    for (const Shader& shader : shaders)
    {
        glAttachShader(this->handler, shader.getHandler());
    }

    glLinkProgram(this->handler);

    this->checkStatus();
}

Program::Program(Program&& program)
    : handler(program.handler)
{
    program.handler = -1;
}

Program::~Program()
{
    if (this->handler != -1)
    {
        glDeleteProgram(this->handler);
    }
}

void Program::use()
{
    glUseProgram(this->handler);
}

void Program::updateUniform(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(this->handler, name.c_str()), value);
}

void Program::updateUniform(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(this->handler, name.c_str()), value);
}

void Program::updateUniform(const std::string& name, glm::vec2 value)
{
    glUniform2f(glGetUniformLocation(this->handler, name.c_str()), value.x, value.y);
}

void Program::updateUniform(const std::string& name, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(this->handler, name.c_str()), value.x, value.y, value.z);
}

void Program::updateUniform(const std::string& name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->handler, name.c_str()), 1, false, glm::value_ptr(value));
}

GLuint Program::getHandler() const
{
    return this->handler;
}

void Program::applyCompute(glm::ivec3 groups)
{
    glDispatchCompute((GLuint)groups.x, (GLuint)groups.y, (GLuint)groups.z);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void Program::stopUse()
{
    glUseProgram(0);
}

void Program::checkStatus() const
{
    GLint status;
    glGetProgramiv(this->handler, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLint logSize;
        glGetProgramiv(this->handler, GL_INFO_LOG_LENGTH, &logSize);

        char* info = new char[logSize + 1];
        glGetShaderInfoLog(this->handler, logSize, nullptr, info);
        std::string msg(info);
        delete[] info;

        glDeleteProgram(this->handler);
        throw std::runtime_error(msg);
    }
}
