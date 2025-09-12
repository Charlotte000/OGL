#include <iostream>
#include <stdexcept>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <OGL/Camera.h>
#include <OGL/Shader.h>
#include <OGL/VertexArray.h>
#include <OGL/FrameBuffer.h>
#include <OGL/UniformBuffer.h>

#include <unordered_map>
void initGLFW()
{
    if (glfwInit() == GL_FALSE)
    {
        throw std::runtime_error("GLFW Init Error");
    }
}

void initGLEW()
{
    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        throw std::runtime_error((const char*)glewGetErrorString(status));
    }
}

GLFWwindow* createWindow()
{
    GLFWwindow* window = glfwCreateWindow(600, 600, "Hello GLFW Template", nullptr, nullptr);
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
        OGL::ArrayBuffer(sizeof(float) * 4, { { GL_FLOAT, 2, 0 }, { GL_FLOAT, 2,  8 } }),
        OGL::ElementArrayBuffer()
    );

    {
        const float vertices[] =
        { // x,  y,    u, v
            -1, -1,    0, 0,
            -1,  1,    0, 1,
             1,  1,    1, 1,
            -1, -1,    0, 0,
             1,  1,    1, 1,
             1, -1,    1, 0,
        };
        quad.vbo.write(vertices, sizeof(vertices));

        const unsigned int indices[] =
        {
            0, 1, 2,
        };
        quad.ebo.write(indices, sizeof(indices));
    }

    OGL::Shader uvShader("../../example/shaders/uv/vertex.glsl", "../../example/shaders/uv/fragment.glsl");
    OGL::Shader viewShader("../../example/shaders/view/vertex.glsl", "../../example/shaders/view/fragment.glsl");
    OGL::Shader rayTracerShader("../../example/shaders/rayTracer/vertex.glsl", "../../example/shaders/rayTracer/fragment.glsl");

    OGL::FrameBuffer frameBuffer(glm::ivec2(5, 5), OGL::Texture(GL_RGBA32F, GL_NEAREST), OGL::Texture(GL_DEPTH_COMPONENT, GL_NEAREST));

    OGL::Camera camera(window);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        frameBuffer.use(); uvShader.use();
        {
            quad.drawArrays(GL_TRIANGLES, frameBuffer.getSize());
        }
        OGL::Shader::stopUse(); OGL::FrameBuffer::stopUse();

        camera.controlFree();

        rayTracerShader.use();
        {
            frameBuffer.colorTexture.bindSampler(0);
            rayTracerShader.updateUniform("cameraPos", camera.pos);
            rayTracerShader.updateUniform("cameraForward", camera.forward);
            rayTracerShader.updateUniform("cameraUp", camera.up);
            rayTracerShader.updateUniform("cameraFOV", camera.fov);
            rayTracerShader.updateUniform("aspectRatio", 1.f);
            quad.drawArrays(GL_TRIANGLES, glm::uvec2(600, 600));
        }
        OGL::Shader::stopUse();

        viewShader.use();
        {
            frameBuffer.colorTexture.bindSampler(0);
            quad.drawElements(GL_TRIANGLES, glm::uvec2(400, 400), glm::uvec2(200, 200));
        }
        OGL::Shader::stopUse();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}
