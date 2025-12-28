#pragma once

#include <OGL/Camera.h>
#include <OGL/Program.h>
#include <OGL/FrameBuffer.h>

class RayTracerExample
{
public:
    RayTracerExample(glm::uvec2 size, const std::filesystem::path& shaderPath);
    void render(const OGL::Camera<float>& camera);
    OGL::Texture2D& output();
private:
    OGL::Program program;
    OGL::Program backgroundProgram;
    OGL::FrameBuffer frame;
    OGL::Texture2D background;

    void renderBackground();
};

RayTracerExample::RayTracerExample(glm::uvec2 size, const std::filesystem::path& shaderPath)
    : 
    program({ OGL::Shader(shaderPath / "rayTracer" / "main.glsl", OGL::ShaderType::COMPUTE) }),
    backgroundProgram({ OGL::Shader(shaderPath / "rayTracer" / "background.glsl", OGL::ShaderType::COMPUTE) }),
    frame({ { OGL::Attachment::COLOR0, OGL::Texture2D(size, OGL::ImageFormat::RGBA32F) } }),
    background(glm::uvec2(1000, 1000), OGL::ImageFormat::RGBA32F)
{
    this->renderBackground();
}

void RayTracerExample::render(const OGL::Camera<float>& camera)
{
    this->program.use();

    this->background.bindSampler(0);
    this->frame.textures.at(OGL::Attachment::COLOR0).bindImage(1, OGL::ImageUnitFormat::RGBA32F, OGL::Access::WRITE_ONLY);

    this->program.updateUniform("cameraPos", camera.pos);
    this->program.updateUniform("cameraForward", camera.forward);
    this->program.updateUniform("cameraUp", camera.up);
    this->program.updateUniform("cameraFOV", camera.fov);
    this->program.updateUniform("aspectRatio", 1.f);
    OGL::Program::dispatchCompute(glm::uvec3(this->frame.getSize(), 1));

    OGL::Program::stopUse();
}

OGL::Texture2D& RayTracerExample::output()
{
    return this->frame.textures.at(OGL::Attachment::COLOR0);
}

void RayTracerExample::renderBackground()
{
    this->backgroundProgram.use();

    this->background.bindImage(0, OGL::ImageUnitFormat::RGBA32F, OGL::Access::WRITE_ONLY);
    OGL::Program::dispatchCompute(glm::uvec3(this->background.getSize(), 1));

    OGL::Program::stopUse();
}
