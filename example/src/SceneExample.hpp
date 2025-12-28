#pragma once

#include <OGL/Camera.h>
#include <OGL/Program.h>
#include <OGL/Context.h>
#include <OGL/FrameBuffer.h>
#include <OGL/VertexArray.h>

static inline void createCube(glm::vec3 color, std::vector<float>& vertices)
{
    vertices.insert(
        vertices.end(),
        { //  x,    y,    z,  nx, ny, nz,  r, g, b
            -0.5, -0.5, -0.5,   0,  0, -1,  color.r, color.g, color.b,
             0.5,  0.5, -0.5,   0,  0, -1,  color.r, color.g, color.b,
             0.5, -0.5, -0.5,   0,  0, -1,  color.r, color.g, color.b,
             0.5,  0.5, -0.5,   0,  0, -1,  color.r, color.g, color.b,
            -0.5, -0.5, -0.5,   0,  0, -1,  color.r, color.g, color.b,
            -0.5,  0.5, -0.5,   0,  0, -1,  color.r, color.g, color.b,

            -0.5, -0.5,  0.5,   0,  0,  1,  color.r, color.g, color.b,
             0.5, -0.5,  0.5,   0,  0,  1,  color.r, color.g, color.b,
             0.5,  0.5,  0.5,   0,  0,  1,  color.r, color.g, color.b,
             0.5,  0.5,  0.5,   0,  0,  1,  color.r, color.g, color.b,
            -0.5,  0.5,  0.5,   0,  0,  1,  color.r, color.g, color.b,
            -0.5, -0.5,  0.5,   0,  0,  1,  color.r, color.g, color.b,

            -0.5,  0.5,  0.5,  -1,  0,  0,  color.r, color.g, color.b,
            -0.5,  0.5, -0.5,  -1,  0,  0,  color.r, color.g, color.b,
            -0.5, -0.5, -0.5,  -1,  0,  0,  color.r, color.g, color.b,
            -0.5, -0.5, -0.5,  -1,  0,  0,  color.r, color.g, color.b,
            -0.5, -0.5,  0.5,  -1,  0,  0,  color.r, color.g, color.b,
            -0.5,  0.5,  0.5,  -1,  0,  0,  color.r, color.g, color.b,

             0.5,  0.5,  0.5,   1,  0,  0,  color.r, color.g, color.b,
             0.5, -0.5, -0.5,   1,  0,  0,  color.r, color.g, color.b,
             0.5,  0.5, -0.5,   1,  0,  0,  color.r, color.g, color.b,
             0.5, -0.5, -0.5,   1,  0,  0,  color.r, color.g, color.b,
             0.5,  0.5,  0.5,   1,  0,  0,  color.r, color.g, color.b,
             0.5, -0.5,  0.5,   1,  0,  0,  color.r, color.g, color.b,

            -0.5, -0.5, -0.5,   0, -1,  0,  color.r, color.g, color.b,
             0.5, -0.5, -0.5,   0, -1,  0,  color.r, color.g, color.b,
             0.5, -0.5,  0.5,   0, -1,  0,  color.r, color.g, color.b,
             0.5, -0.5,  0.5,   0, -1,  0,  color.r, color.g, color.b,
            -0.5, -0.5,  0.5,   0, -1,  0,  color.r, color.g, color.b,
            -0.5, -0.5, -0.5,   0, -1,  0,  color.r, color.g, color.b,

            -0.5,  0.5, -0.5,   0,  1,  0,  color.r, color.g, color.b,
             0.5,  0.5,  0.5,   0,  1,  0,  color.r, color.g, color.b,
             0.5,  0.5, -0.5,   0,  1,  0,  color.r, color.g, color.b,
             0.5,  0.5,  0.5,   0,  1,  0,  color.r, color.g, color.b,
            -0.5,  0.5, -0.5,   0,  1,  0,  color.r, color.g, color.b,
            -0.5,  0.5,  0.5,   0,  1,  0,  color.r, color.g, color.b,
        }
    );
}

class SceneExample
{
public:
    glm::vec3 lightPos = glm::vec3(-2, 2, -1);

    SceneExample(glm::uvec2 size, const std::filesystem::path& shaderPath);
    void render(const OGL::Camera<float>& camera);
    OGL::Texture2D& output();
private:
    OGL::Program program;
    OGL::Program shadowMapProgram;
    OGL::FrameBuffer frame;
    OGL::FrameBuffer shadowMap;
    OGL::VertexArray scene;

    glm::mat4 renderShadow();
};

SceneExample::SceneExample(glm::uvec2 size, const std::filesystem::path& shaderPath)
    :
    program(
    {
        OGL::Shader(shaderPath / "scene" / "main" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "scene" / "main" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    }),
    shadowMapProgram(
    {
        OGL::Shader(shaderPath / "scene" / "shadow" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "scene" / "shadow" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    }),
    frame(size),
    shadowMap({ { OGL::Attachment::DEPTH, OGL::Texture2D(size, OGL::ImageFormat::DEPTH32F) } }),
    scene({ { OGL::Type::FLOAT, 3 }, { OGL::Type::FLOAT, 3 }, { OGL::Type::FLOAT, 3 } })
{
    std::vector<float> vertices;

    createCube(glm::vec3(1, 0, 1), vertices);
    vertices.insert(
        vertices.end(),
        { //  x,    y,    z,  nx, ny, nz,  r, g, b
            -10,   -2,  -10,   0,  1,  0,  0, 1, 0,
             10,   -2,   10,   0,  1,  0,  0, 1, 0,
             10,   -2,  -10,   0,  1,  0,  0, 1, 0,
            -10,   -2,  -10,   0,  1,  0,  0, 1, 0,
            -10,   -2,   10,   0,  1,  0,  0, 1, 0,
             10,   -2,   10,   0,  1,  0,  0, 1, 0,
        }
    );
    this->scene.vbo.write(vertices.data(), vertices.size() * sizeof(float));
}

void SceneExample::render(const OGL::Camera<float>& camera)
{
    this->lightPos = glm::rotateY(this->lightPos, 1.0f * ImGui::GetIO().DeltaTime);

    const glm::mat4 lightPV = this->renderShadow();

    const glm::mat4 P = camera.createProjection(this->frame.getSize(), glm::vec2(0.01, 100));
    const glm::mat4 V = camera.createView();
    const glm::mat4 PV = P * V;

    OGL::Context::Viewport::setBox(glm::uvec2(0, 0), this->frame.getSize());
    OGL::Context::CullFace::setEnable(true);
    OGL::Context::Depth::setTest(true);

    this->frame.use();
    this->program.use();

    this->frame.clear();

    this->shadowMap.textures.at(OGL::Attachment::DEPTH).bindSampler(0);
    this->program.updateUniform("LightPV", lightPV);
    this->program.updateUniform("LightColor", glm::vec3(1, 1, 1));
    this->program.updateUniform("LightPos", this->lightPos);
    this->program.updateUniform("ViewPos", camera.pos);
    this->program.updateUniform("PVM", PV);

    this->scene.drawArrays(OGL::PrimitiveType::TRIANGLES);

    OGL::Program::stopUse();
    OGL::FrameBuffer::stopUse();
}

OGL::Texture2D& SceneExample::output()
{
    return this->frame.textures.at(OGL::Attachment::COLOR0);
}

glm::mat4 SceneExample::renderShadow()
{
    const glm::mat4 P = glm::ortho(-20.f, 20.f, -20.f, 20.f, 0.01f, 8.f);
    const glm::mat4 V = glm::lookAt(this->lightPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    const glm::mat4 PV = P * V;

    OGL::Context::Viewport::setBox(glm::uvec2(0, 0), this->shadowMap.getSize(OGL::Attachment::DEPTH));
    OGL::Context::CullFace::setEnable(true);
    OGL::Context::CullFace::setMode(OGL::CullFaceMode::FRONT);
    OGL::Context::Depth::setTest(true);

    this->shadowMap.use();
    this->shadowMapProgram.use();

    this->shadowMap.clear();

    this->shadowMapProgram.updateUniform("PVM", PV);
    this->scene.drawArrays(OGL::PrimitiveType::TRIANGLES);

    OGL::Program::stopUse();
    OGL::FrameBuffer::stopUse();

    OGL::Context::CullFace::setMode(OGL::CullFaceMode::BACK);
    return PV;
}
