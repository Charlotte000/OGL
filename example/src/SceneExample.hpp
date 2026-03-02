#pragma once

#include <OGL/Camera.h>
#include <OGL/Program.h>
#include <OGL/Context.h>
#include <OGL/FrameBuffer.h>
#include <OGL/VertexArray.h>
#include <OGL/TextureCubeMap.h>

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

static inline OGL::Image3D parseSkybox(const std::filesystem::path& skyboxPath)
{
    OGL::Image2D src(skyboxPath);

    assert(src.size.x % 4 == 0 && src.size.y % 3 == 0 && src.size.x / 4 == src.size.y / 3);
    const unsigned int size = src.size.x / 4;

    OGL::Image3D result(glm::uvec3(size, size, 6));

    auto crop = [size, &src, &result](glm::uvec2 pos, unsigned int z)
    {
        for (size_t y = 0; y < size; y++)
        {
            const glm::uvec2 src_start = pos + glm::uvec2(0, y);
            const glm::uvec2 src_end = src_start + glm::uvec2(size - 1, 0);
            const glm::uvec3 dst_start(0, y, z);
            std::copy(&src[src_start], &src[src_end] + 1, &result[dst_start]);
        }
    };

    crop(glm::uvec2(2, 1) * size, 0); // Right
    crop(glm::uvec2(0, 1) * size, 1); // Left
    crop(glm::uvec2(1, 0) * size, 2); // Top
    crop(glm::uvec2(1, 2) * size, 3); // Bottom
    crop(glm::uvec2(1, 1) * size, 4); // Back
    crop(glm::uvec2(3, 1) * size, 5); // Front

    return result;
}

class SceneExample
{
public:
    glm::vec3 lightPos = glm::vec3(-2, 2, -1);

    SceneExample(glm::uvec2 size, const std::filesystem::path& shaderPath, const std::filesystem::path& imagesPath);
    void render(const OGL::Camera<float>& camera);
    OGL::Texture2D& output();
private:
    OGL::Program program;
    OGL::Program shadowMapProgram;
    OGL::Program skyBoxProgram;
    OGL::FrameBuffer frame;
    OGL::FrameBuffer shadowMap;
    OGL::TextureCubeMap skyBoxMap;
    OGL::VertexArray scene;
    OGL::VertexArray skyBox;

    glm::mat4 renderShadow();
    void renderSkyBox(const glm::mat4& PVM);
    void renderScene(const OGL::Camera<float>& camera, const glm::mat4& PVM, const glm::mat4& lightPV);
};

SceneExample::SceneExample(glm::uvec2 size, const std::filesystem::path& shaderPath, const std::filesystem::path& imagesPath)
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
    skyBoxProgram(
    {
        OGL::Shader(shaderPath / "scene" / "skyBox" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "scene" / "skyBox" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    }),
    skyBoxMap(glm::uvec2(1, 1), OGL::ImageFormat::RGBA32F),
    frame(size),
    shadowMap({ { OGL::Attachment::DEPTH, OGL::Texture2D(glm::uvec2(1024, 1024), OGL::ImageFormat::DEPTH32F) } }),
    scene({ { OGL::Type::FLOAT, 3 }, { OGL::Type::FLOAT, 3 }, { OGL::Type::FLOAT, 3 } }),
    skyBox({ { OGL::Type::FLOAT, 3 } })
{
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

    {
        const float vertices[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
        };
        this->skyBox.vbo.write(vertices, sizeof(vertices));
    }

    {
        OGL::Image3D map = parseSkybox(imagesPath / "skybox.png");
        this->skyBoxMap = OGL::TextureCubeMap(glm::uvec2(map.size), OGL::ImageFormat::RGBA32F);
        this->skyBoxMap.update(map, glm::uvec3(0));
    }
}

void SceneExample::render(const OGL::Camera<float>& camera)
{
    this->lightPos = glm::rotateY(this->lightPos, 1.0f * ImGui::GetIO().DeltaTime);

    const glm::mat4 P = camera.createProjection(this->frame.getSize(), glm::vec2(0.01, 100));
    const glm::mat4 V = camera.createView();
    const glm::mat4 PV = P * V;

    this->frame.clear();

    const glm::mat4 lightPV = this->renderShadow();
    this->renderSkyBox(P * glm::mat4(glm::mat3(V)));
    this->renderScene(camera, PV, lightPV);
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

    OGL::Context::reset();
    OGL::Context::Viewport::box(glm::uvec2(0, 0), this->shadowMap.getSize(OGL::Attachment::DEPTH));
    OGL::Context::CullFace::enable(true);
    OGL::Context::CullFace::mode(OGL::FaceMode::FRONT);
    OGL::Context::Depth::enable(true);

    this->shadowMap.use();
    this->shadowMapProgram.use();

    this->shadowMap.clear();

    this->shadowMapProgram.updateUniform("PVM", PV);
    this->scene.drawArrays(OGL::PrimitiveType::TRIANGLES);

    OGL::Program::stopUse();
    OGL::FrameBuffer::stopUse();

    return PV;
}

void SceneExample::renderSkyBox(const glm::mat4& PVM)
{
    OGL::Context::reset();
    OGL::Context::Viewport::box(glm::uvec2(0, 0), this->frame.getSize());
    OGL::Context::CullFace::enable(false);
    OGL::Context::Depth::enable(true);
    OGL::Context::Depth::func(OGL::Func::LEQUAL);
    OGL::Context::CubeMap::seamless(true);

    this->frame.use();
    this->skyBoxProgram.use();

    this->skyBoxMap.bindSampler(0);
    this->skyBoxProgram.updateUniform("PVM", PVM);
    this->skyBox.drawArrays(OGL::PrimitiveType::TRIANGLES);

    OGL::Program::stopUse();
    OGL::FrameBuffer::stopUse();
}

void SceneExample::renderScene(const OGL::Camera<float>& camera, const glm::mat4& PVM, const glm::mat4& lightPV)
{
    OGL::Context::reset();
    OGL::Context::Viewport::box(glm::uvec2(0, 0), this->frame.getSize());
    OGL::Context::CullFace::enable(true);
    OGL::Context::Depth::enable(true);

    this->frame.use();
    this->program.use();

    this->shadowMap.textures.at(OGL::Attachment::DEPTH).bindSampler(0);
    this->program.updateUniform("LightPV", lightPV);
    this->program.updateUniform("LightColor", glm::vec3(1, 1, 1));
    this->program.updateUniform("LightPos", this->lightPos);
    this->program.updateUniform("ViewPos", camera.pos);
    this->program.updateUniform("PVM", PVM);
    this->scene.drawArrays(OGL::PrimitiveType::TRIANGLES);

    OGL::Program::stopUse();
    OGL::FrameBuffer::stopUse();
}
