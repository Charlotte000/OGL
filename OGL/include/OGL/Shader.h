#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace OGL
{

class Shader
{
public:
    Shader(const std::string& src, GLenum shaderType);

    Shader(const std::filesystem::path& path, GLenum shaderType);

    Shader(const unsigned char src[], size_t srcSize, GLenum shaderType);

    Shader(Shader&& shader);

    ~Shader();

    GLuint getHandler() const;
private:
    GLuint handler = -1;

    void checkStatus() const;
};

}
