#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <OGL/Image1D.h>
#include <OGL/Image2D.h>
#include <OGL/Image3D.h>

#include <glm/glm.hpp>

#include <random>
#include <stdexcept>

struct Context
{
public:
    Context()
    {
        if (glfwInit() == GL_FALSE)
        {
            throw std::runtime_error("GLFW Init Error");
        }

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        this->window = glfwCreateWindow(1, 1, "Test", nullptr, nullptr);
        if (this->window == nullptr)
        {
            throw std::runtime_error("GLFW Create Window error");
        }

        glfwMakeContextCurrent(this->window);
        if (GLenum status = glewInit(); status != GLEW_OK)
        {
            throw std::runtime_error((const char*)glewGetErrorString(status));
        }
    }

    ~Context()
    {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }
private:
    GLFWwindow* window;
};

inline OGL::Image1D generateImage(glm::uvec1 size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);

    OGL::Image1D img(size);

    for (size_t i = 0; i < img.pixels.size(); i++)
        img.pixels[i] = glm::vec4(dis(gen), dis(gen), dis(gen), dis(gen));

    return img;
}

inline OGL::Image2D generateImage(glm::uvec2 size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);

    OGL::Image2D img(size);

    for (size_t i = 0; i < img.pixels.size(); i++)
        img.pixels[i] = glm::vec4(dis(gen), dis(gen), dis(gen), dis(gen));

    return img;
}

inline OGL::Image3D generateImage(glm::uvec3 size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);

    OGL::Image3D img(size);

    for (size_t i = 0; i < img.pixels.size(); i++)
        img.pixels[i] = glm::vec4(dis(gen), dis(gen), dis(gen), dis(gen));

    return img;
}

inline std::vector<float> generateData(size_t size)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(0, 1);

    std::vector<float> data(size);

    for (size_t i = 0; i < data.size(); i++)
        data[i] = dis(gen);

    return data;
}