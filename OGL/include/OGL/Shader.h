#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <filesystem>
#include <glm/glm.hpp>

namespace OGL
{

// TODO program pipeline
class Shader
{
public:
    Shader() = default;

    Shader(const std::filesystem::path& computePath);

    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);

    Shader(Shader&& shader);

    ~Shader();

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

    static const std::string load(const std::filesystem::path& path);
    static GLuint initShader(const std::filesystem::path& path, GLenum shaderType);
    static GLuint initProgram(const std::vector<GLuint>& handlers);
};

}
