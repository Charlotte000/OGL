#pragma once

#include <OGL/Program.h>
#include <OGL/Context.h>
#include <OGL/FrameBuffer.h>
#include <OGL/VertexArray.h>

class InstancedExample
{
public:
    InstancedExample(glm::uvec2 size, const std::filesystem::path& shaderPath);
    void render();
    OGL::Texture2D& output();
private:
    OGL::Program program;
    OGL::FrameBuffer frame;
    OGL::VertexArray points;
};

InstancedExample::InstancedExample(glm::uvec2 size, const std::filesystem::path& shaderPath)
    :
    program(
    {
        OGL::Shader(shaderPath / "instanced" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "instanced" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    }),
    frame({ { OGL::Attachment::COLOR0, OGL::Texture2D(size, OGL::ImageFormat::RGBA32F) } }),
    points({ { OGL::Type::FLOAT, 2 } })
{
    const float vertices[]
    { //   x, y
        -0.8, 0,
        -0.4, 0,
        0, 0,
        0.4, 0,
        0.8, 0,
    };
    this->points.vbo.write(vertices, sizeof(vertices));

    const unsigned int indices[] { 0, 1, 2, 3, 4 };
    this->points.ebo.write(indices, sizeof(indices));
}

void InstancedExample::render()
{
    OGL::Context::Viewport::setBox(glm::uvec2(0, 0), this->frame.getSize());
    OGL::Context::Point::setSize(10);
    OGL::Context::Depth::setTest(false);

    this->frame.use();
    this->program.use();

    this->points.drawElements(OGL::PrimitiveType::POINTS, -1, 0, 5, 0);

    OGL::Program::stopUse();
    OGL::FrameBuffer::stopUse();
}

OGL::Texture2D& InstancedExample::output()
{
    return this->frame.textures.at(OGL::Attachment::COLOR0);
}
