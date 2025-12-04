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
    this->checkStatus(GL_LINK_STATUS);
    
    glValidateProgram(this->handler);
    this->checkStatus(GL_VALIDATE_STATUS);
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

Program& Program::operator=(Program&& program)
{
    if (this->handler != -1)
    {
        glDeleteProgram(this->handler);
    }

    this->handler = program.handler;
    program.handler = -1;
    return *this;
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

void Program::dispatchCompute(glm::uvec3 groups)
{
    glDispatchCompute(groups.x, groups.y, groups.z);
}

void Program::stopUse()
{
    glUseProgram(0);
}

void Program::checkStatus(GLenum param) const
{
    GLint status;
    glGetProgramiv(this->handler, param, &status);
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
