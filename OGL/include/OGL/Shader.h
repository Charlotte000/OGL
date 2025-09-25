#pragma once

#include <vector>
#include <string>
#include <filesystem>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "OGL/Enums.h"

namespace OGL
{

class Shader
{
public:
    Shader(const std::string& src, ShaderType type);

    Shader(const std::filesystem::path& path, ShaderType type);

    Shader(const unsigned char src[], size_t srcSize, ShaderType type);

    Shader(Shader&& shader);

    ~Shader();

    GLuint getHandler() const;
private:
    GLuint handler = -1;

    void checkStatus() const;
};

}
