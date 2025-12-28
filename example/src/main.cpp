#include <iostream>
#include <stdexcept>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <GLFW/glfw3.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "SceneExample.hpp"
#include "RayTracerExample.hpp"
#include "InstancedExample.hpp"

static inline void initGLFW()
{
    if (glfwInit() == GL_FALSE)
    {
        throw std::runtime_error("GLFW Init Error");
    }
}

static inline void initGLEW()
{
    if (GLenum status = glewInit(); status != GLEW_OK)
    {
        throw std::runtime_error((const char*)glewGetErrorString(status));
    }
}

static inline GLFWwindow* createWindow()
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

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    return window;
}

static inline std::tuple<ImVec2, ImVec2> drawFillImage(const OGL::Texture2D& texture, bool flipY = true)
{
    const float aspectRatio = (float)texture.getSize().x / texture.getSize().y;

    const ImVec2 dstSize = ImGui::GetContentRegionAvail();
    const float dstAspectRatio = dstSize.x / dstSize.y;

    const ImVec2 imageSize = dstSize * (aspectRatio > dstAspectRatio ? ImVec2(1, dstAspectRatio / aspectRatio) : ImVec2(aspectRatio / dstAspectRatio, 1));
    const ImVec2 imagePos = (ImGui::GetWindowSize() - imageSize) * 0.5f;

    ImGui::SetCursorPos(imagePos);
    const ImVec2 imageScreenPos = ImGui::GetCursorScreenPos();
    if (flipY)
    {
        ImGui::Image((ImTextureID)(intptr_t)texture.getHandler(), imageSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    else
    {
        ImGui::Image((ImTextureID)(intptr_t)texture.getHandler(), imageSize);
    }

    return { imageScreenPos, imageSize };
}

static inline void controlCamera(OGL::Camera<float>& camera)
{
    const ImGuiIO& io = ImGui::GetIO();

    const float deltaTime = io.DeltaTime;
    const float elapsedMove = 10 * deltaTime;

    // WASD
    if (ImGui::IsKeyDown(ImGuiKey_W)) camera.pos += camera.forward * elapsedMove;
    if (ImGui::IsKeyDown(ImGuiKey_S)) camera.pos -= camera.forward * elapsedMove;
    if (ImGui::IsKeyDown(ImGuiKey_D)) camera.pos += camera.right() * elapsedMove;
    if (ImGui::IsKeyDown(ImGuiKey_A)) camera.pos -= camera.right() * elapsedMove;

    // Up / down
    if (ImGui::IsKeyDown(ImGuiKey_LeftShift)) camera.pos += camera.up * elapsedMove;
    if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl))  camera.pos -= camera.up * elapsedMove;

    // Keyboard rotate
    if (ImGui::IsKeyDown(ImGuiKey_Q)) camera.up = glm::rotate(camera.up, -deltaTime * 1.5f, camera.forward);
    if (ImGui::IsKeyDown(ImGuiKey_E)) camera.up = glm::rotate(camera.up,  deltaTime * 1.5f, camera.forward);

    // Mouse rotate
    {
        const glm::vec3 right = camera.right();
        camera.forward = glm::rotate(camera.forward, -io.MouseDelta.y * camera.fov / 200.f, right);
        camera.up      = glm::rotate(camera.up,      -io.MouseDelta.y * camera.fov / 200.f, right);
        camera.forward = glm::rotate(camera.forward, -io.MouseDelta.x * camera.fov / 200.f, camera.up);
    }
}

int main()
{
    initGLFW();
    GLFWwindow* window = createWindow();
    initGLEW();

    const std::filesystem::path shaderPath("../../example/shaders/");
    RayTracerExample rayTracerExample(glm::uvec2(800, 800), shaderPath);
    InstancedExample instancedExample(glm::uvec2(300, 300), shaderPath);
    SceneExample sceneExample(glm::uvec2(800, 800), shaderPath);

    OGL::Camera<float> camera;
    camera.pos = glm::vec3(-1.5, 0, -5);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(0, nullptr, ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_PassthruCentralNode);

        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            controlCamera(camera);

            if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        }

        rayTracerExample.render(camera);
        instancedExample.render();
        sceneExample.render(camera);

        {
            ImGui::Begin("Scene Example");

            drawFillImage(sceneExample.output(), true);
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            ImGui::End();
        }

        {
            ImGui::Begin("Ray Tracer Example");

            drawFillImage(rayTracerExample.output(), true);
            if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }

            ImGui::End();
        }

        {
            ImGui::Begin("Instanced Example");

            drawFillImage(instancedExample.output(), true);

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
