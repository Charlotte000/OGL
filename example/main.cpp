#include <iostream>
#include <stdexcept>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <GLFW/glfw3.h>

#include <OGL/Camera.h>
#include <OGL/Program.h>
#include <OGL/Context.h>
#include <OGL/VertexArray.h>
#include <OGL/FrameBuffer.h>
#include <OGL/UniformBuffer.h>

void initGLFW()
{
    if (glfwInit() == GL_FALSE)
    {
        throw std::runtime_error("GLFW Init Error");
    }
}

void initGLEW()
{
    if (GLenum status = glewInit(); status != GLEW_OK)
    {
        throw std::runtime_error((const char*)glewGetErrorString(status));
    }
}

GLFWwindow* createWindow()
{
    GLFWwindow* window = glfwCreateWindow(600, 600, "OLG Example", nullptr, nullptr);
    if (window == nullptr)
    {
        throw std::runtime_error("GLFW Create Window error");
    }

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode)
    {
        switch (action)
        {
            case GLFW_PRESS:
            {
                switch (key)
                {
                    case GLFW_KEY_ESCAPE:
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                        break;
                }

                break;
            }
        }
    });

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    return window;
}

int main()
{
    initGLFW();
    GLFWwindow* window = createWindow();
    initGLEW();

    OGL::VertexArray quad(
        { { OGL::Type::FLOAT, 2 }, { OGL::Type::FLOAT, 2 } }
    );
    {
        const float vertices[]
        { // x,  y,    u, v
            -1, -1,    0, 0, // 0
            -1,  1,    0, 1, // 1
             1,  1,    1, 1, // 2
            -1, -1,    0, 0, // 3
             1,  1,    1, 1, // 4
             1, -1,    1, 0, // 5
        };
        quad.vbo.write(vertices, sizeof(vertices));

        const unsigned int indices[]
        {
            0, 1, 2,
            0, 2, 5,
        };
        quad.ebo.write(indices, sizeof(indices));
    }

    OGL::VertexArray geometry({ { OGL::Type::FLOAT, 2 } });
    {
        const float vertices[]
        { //   x, y
            -0.8, 0,
            -0.4, 0,
               0, 0,
             0.4, 0,
             0.8, 0,
        };
        geometry.vbo.write(vertices, sizeof(vertices));

        const unsigned int indices[] { 0, 1, 2, 3, 4 };
        geometry.ebo.write(indices, sizeof(indices));
    }

    const std::filesystem::path shaderPath("../../example/shaders/");
    OGL::Program uvShader(
    {
        OGL::Shader(shaderPath / "uv"/ "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "uv" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    });
    OGL::Program viewShader(
    {
        OGL::Shader(shaderPath / "view" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "view" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    });
    OGL::Program rayTracerShader(
    {
        OGL::Shader(shaderPath / "rayTracer" / "main.glsl", OGL::ShaderType::COMPUTE)
    });
    OGL::Program geometryShader(
    {
        OGL::Shader(shaderPath / "geometry" / "vertex.glsl", OGL::ShaderType::VERTEX),
        OGL::Shader(shaderPath / "geometry" / "fragment.glsl", OGL::ShaderType::FRAGMENT),
    });

    OGL::FrameBuffer uvFrameBuffer(
        OGL::Texture2D(glm::uvec2(5, 5), OGL::ImageFormat::RGBA32F, OGL::Filter::NEAREST),
        OGL::Texture2D(glm::uvec2(5, 5), OGL::ImageFormat::DEPTH32, OGL::Filter::NEAREST)
    );
    OGL::Texture2D rayTracerTexture(glm::uvec2(300, 300), OGL::ImageFormat::RGBA32F);
    OGL::FrameBuffer geometryFrameBuffer(glm::uvec2(300, 300));

    OGL::Camera<float> camera;

    double time = glfwGetTime(), elapsedTime = 0;
    glm::vec2 mouseDelta;
    glfwSetCursorPos(window, 300, 300);
    while (!glfwWindowShouldClose(window))
    {
        // Update time
        {
            double newTime = glfwGetTime();
            elapsedTime = newTime - time;
            time = newTime;
        }

        // Update mouse
        {
            double mouseX, mouseY;
            glfwGetCursorPos(window, &mouseX, &mouseY);
            mouseDelta = glm::vec2(mouseX - 300, mouseY - 300);
            glfwSetCursorPos(window, 300, 300);
        }

        glfwPollEvents();

        // Control camera
        const float elapsedMove = 5 * elapsedTime;
        const float elapsedRotation = 1 * elapsedTime;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)               camera.pos += camera.forward * elapsedMove;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)               camera.pos += -camera.forward * elapsedMove;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)               camera.pos += -camera.right() * elapsedMove;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)               camera.pos += camera.right() * elapsedMove;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)      camera.pos += camera.up * elapsedMove;
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)    camera.pos += -camera.up * elapsedMove;
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)               camera.up = glm::rotate(camera.up, -elapsedRotation, camera.forward);
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)               camera.up = glm::rotate(camera.up, elapsedRotation, camera.forward);
        if (mouseDelta != glm::vec2(0))
        {
            const glm::vec3 right = camera.right();
            camera.forward = glm::rotate(camera.forward, -mouseDelta.y / 200, right);
            camera.up = glm::rotate(camera.up, -mouseDelta.y / 200, right);
            camera.forward = glm::rotate(camera.forward, -mouseDelta.x / 200, camera.up);
        }

        // Render uv
        uvFrameBuffer.use(); uvShader.use();
        {
            OGL::Context::Viewport::setBox(glm::uvec2(0, 0), uvFrameBuffer.getSize());
            quad.drawArrays(OGL::PrimitiveType::TRIANGLES);
        }
        OGL::Program::stopUse(); OGL::FrameBuffer::stopUse();

        // Render ray tracer
        rayTracerShader.use();
        {
            uvFrameBuffer.colorTexture.bindSampler(0);
            rayTracerTexture.bindImage(1, OGL::ImageUnitFormat::RGBA32F, OGL::Access::WRITE_ONLY);

            rayTracerShader.updateUniform("cameraPos", camera.pos);
            rayTracerShader.updateUniform("cameraForward", camera.forward);
            rayTracerShader.updateUniform("cameraUp", camera.up);
            rayTracerShader.updateUniform("cameraFOV", camera.fov);
            rayTracerShader.updateUniform("aspectRatio", 1.f);
            OGL::Program::dispatchCompute(glm::uvec3(500, 500, 1));
        }
        OGL::Program::stopUse();

        // Render geometry
        geometryFrameBuffer.use(); geometryShader.use();
        {
            OGL::Context::Viewport::setBox(glm::uvec2(0, 0), geometryFrameBuffer.getSize());
            OGL::Context::Point::setSize(10);
            geometry.drawElements(OGL::PrimitiveType::POINTS, -1, 0, 5, 0);
        }
        OGL::Program::stopUse(); OGL::FrameBuffer::stopUse();

        // Render framebuffer
        viewShader.use();
        {
            OGL::Context::Depth::setTest(false);

            rayTracerTexture.bindSampler(0);
            OGL::Context::Viewport::setBox(glm::uvec2(0, 0), glm::uvec2(300, 300));
            quad.drawElements(OGL::PrimitiveType::TRIANGLES);

            uvFrameBuffer.colorTexture.bindSampler(0);
            OGL::Context::Viewport::setBox(glm::uvec2(0, 300), glm::uvec2(300, 300));
            quad.drawElements(OGL::PrimitiveType::TRIANGLES, 3);

            geometryFrameBuffer.colorTexture.bindSampler(0);
            OGL::Context::Viewport::setBox(glm::uvec2(300, 300), glm::uvec2(300, 300));
            quad.drawElements(OGL::PrimitiveType::TRIANGLES);

            OGL::Context::Depth::setTest(true);
        }
        OGL::Program::stopUse();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
