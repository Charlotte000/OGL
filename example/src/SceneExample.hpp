#pragma once

#include <OGL/Camera.h>
#include <OGL/Program.h>
#include <OGL/Context.h>
#include <OGL/FrameBuffer.h>
#include <OGL/VertexArray.h>

class SceneExample
{
public:
    SceneExample(glm::uvec2 size, const std::filesystem::path& shaderPath);
    void render(const OGL::Camera<float>& camera);
    OGL::Texture2D& output();
private:
    OGL::Program program;
    OGL::FrameBuffer frame;
    OGL::FrameBuffer shadowMap;
    OGL::VertexArray scene;
};

SceneExample::SceneExample(glm::uvec2 size, const std::filesystem::path& shaderPath)
    :
    program(
    {
        OGL::Shader(shaderPath / "scene" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "scene" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    }),
    frame(size),
    shadowMap({ { OGL::Attachment::DEPTH, OGL::Texture2D(size, OGL::ImageFormat::DEPTH32F) } }),
    scene({ { OGL::Type::FLOAT, 3 }, { OGL::Type::FLOAT, 3 }, { OGL::Type::FLOAT, 3 } })
{
    const float vertices[] =
    { //   x,    y,    z,  nx, ny, nz,  r, g, b
        -0.5, -0.5, -0.5,   0,  0, -1,  1, 0, 1,
         0.5,  0.5, -0.5,   0,  0, -1,  1, 0, 1,
         0.5, -0.5, -0.5,   0,  0, -1,  1, 0, 1,
         0.5,  0.5, -0.5,   0,  0, -1,  1, 0, 1,
        -0.5, -0.5, -0.5,   0,  0, -1,  1, 0, 1,
        -0.5,  0.5, -0.5,   0,  0, -1,  1, 0, 1,

        -0.5, -0.5,  0.5,   0,  0,  1,  1, 0, 1,
         0.5, -0.5,  0.5,   0,  0,  1,  1, 0, 1,
         0.5,  0.5,  0.5,   0,  0,  1,  1, 0, 1,
         0.5,  0.5,  0.5,   0,  0,  1,  1, 0, 1,
        -0.5,  0.5,  0.5,   0,  0,  1,  1, 0, 1,
        -0.5, -0.5,  0.5,   0,  0,  1,  1, 0, 1,

        -0.5,  0.5,  0.5,  -1,  0,  0,  1, 0, 1,
        -0.5,  0.5, -0.5,  -1,  0,  0,  1, 0, 1,
        -0.5, -0.5, -0.5,  -1,  0,  0,  1, 0, 1,
        -0.5, -0.5, -0.5,  -1,  0,  0,  1, 0, 1,
        -0.5, -0.5,  0.5,  -1,  0,  0,  1, 0, 1,
        -0.5,  0.5,  0.5,  -1,  0,  0,  1, 0, 1,

         0.5,  0.5,  0.5,   1,  0,  0,  1, 0, 1,
         0.5, -0.5, -0.5,   1,  0,  0,  1, 0, 1,
         0.5,  0.5, -0.5,   1,  0,  0,  1, 0, 1,
         0.5, -0.5, -0.5,   1,  0,  0,  1, 0, 1,
         0.5,  0.5,  0.5,   1,  0,  0,  1, 0, 1,
         0.5, -0.5,  0.5,   1,  0,  0,  1, 0, 1,

        -0.5, -0.5, -0.5,   0, -1,  0,  1, 0, 1,
         0.5, -0.5, -0.5,   0, -1,  0,  1, 0, 1,
         0.5, -0.5,  0.5,   0, -1,  0,  1, 0, 1,
         0.5, -0.5,  0.5,   0, -1,  0,  1, 0, 1,
        -0.5, -0.5,  0.5,   0, -1,  0,  1, 0, 1,
        -0.5, -0.5, -0.5,   0, -1,  0,  1, 0, 1,

        -0.5,  0.5, -0.5,   0,  1,  0,  1, 0, 1,
         0.5,  0.5,  0.5,   0,  1,  0,  1, 0, 1,
         0.5,  0.5, -0.5,   0,  1,  0,  1, 0, 1,
         0.5,  0.5,  0.5,   0,  1,  0,  1, 0, 1,
        -0.5,  0.5, -0.5,   0,  1,  0,  1, 0, 1,
        -0.5,  0.5,  0.5,   0,  1,  0,  1, 0, 1,

         -10,   -2,  -10,   0,  1,  0,  0, 1, 0,
          10,   -2,   10,   0,  1,  0,  0, 1, 0,
          10,   -2,  -10,   0,  1,  0,  0, 1, 0,
         -10,   -2,  -10,   0,  1,  0,  0, 1, 0,
         -10,   -2,   10,   0,  1,  0,  0, 1, 0,
          10,   -2,   10,   0,  1,  0,  0, 1, 0,
    };
    this->scene.vbo.write(vertices, sizeof(vertices));
}

void SceneExample::render(const OGL::Camera<float>& camera)
{
    this->program.use();

    const glm::vec2 size = this->frame.getSize();
    OGL::Context::Viewport::setBox(glm::uvec2(0, 0), size);
    OGL::Context::CullFace::setEnable(true);
    OGL::Context::Depth::setTest(true);

    const glm::vec3 lightPos(-2, 2, -1);

    const glm::mat4 lightPV =
        glm::ortho(-10.f, 10.f, -10.f, 10.f, 0.01f, 8.f) *
        glm::lookAt(lightPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    this->program.updateUniform("LightPV", lightPV);
    this->program.updateUniform("LightColor", glm::vec3(1, 1, 1));
    this->program.updateUniform("LightPos", lightPos);
    this->program.updateUniform("ViewPos", camera.pos);

    // Shadow
    this->shadowMap.use();
    {
        this->shadowMap.clear();

        this->program.updateUniform("PVM", lightPV);
        this->scene.drawArrays(OGL::PrimitiveType::TRIANGLES);
    }
    OGL::FrameBuffer::stopUse();

    // Render
    this->frame.use();
    {
        this->frame.clear();

        const glm::mat4 P = camera.createProjection(size, glm::vec2(0.01, 100));
        const glm::mat4 V = camera.createView();
        const glm::mat4 PV = P * V;

        this->program.updateUniform("PVM", PV);
        this->scene.drawArrays(OGL::PrimitiveType::TRIANGLES);
    }
    OGL::FrameBuffer::stopUse();

    OGL::Program::stopUse();
}

OGL::Texture2D& SceneExample::output()
{
    return this->frame.textures.at(OGL::Attachment::COLOR0);
}
