#pragma once

#include <GL/glew.h>

#include "OGL/Shader.h"

namespace OGL
{

class Program
{
public:
    Program(const std::initializer_list<Shader>& shaders);

    Program(Program&& program);

    ~Program();

    void use();

    void updateUniform(const std::string& name, int value);

    void updateUniform(const std::string& name, float value);

    void updateUniform(const std::string& name, glm::vec2 value);

    void updateUniform(const std::string& name, glm::vec3 value);

    void updateUniform(const std::string& name, glm::mat4 value);

    GLuint getHandler() const;

    static void applyCompute(glm::ivec3 groups);

    static void stopUse();
private:
    GLuint handler = -1;

    void checkStatus() const;
};

}
