#include <glm/gtx/rotate_vector.hpp>

#include "OGL/Camera.h"

using namespace OGL;

template <class T>
Camera<T>::Camera(GLFWwindow* window)
    : window(window)
{
    this->update();
}

template <class T>
void Camera<T>::controlFree()
{
    this->update();

    // Keyboard
    const T elapsedMove = this->movementSpeed * this->elapsedTime;
    const glm::vec<3, T> right = glm::normalize(glm::cross(this->forward, this->up));
    if (glfwGetKey(this->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        this->pos += this->forward * elapsedMove;
    }

    if (glfwGetKey(this->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        this->pos += -this->forward * elapsedMove;
    }

    if (glfwGetKey(this->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        this->pos += -right * elapsedMove;
    }

    if (glfwGetKey(this->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        this->pos += right * elapsedMove;
    }

    if (glfwGetKey(this->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        this->pos += this->up * elapsedMove;
    }

    if (glfwGetKey(this->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        this->pos += -this->up * elapsedMove;
    }

    if (glfwGetKey(this->window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        this->up = glm::rotate(this->up, -this->rotationSpeed * 2 * this->elapsedTime, this->forward);
    }

    if (glfwGetKey(this->window, GLFW_KEY_E) == GLFW_PRESS)
    {
        this->up = glm::rotate(this->up, this->rotationSpeed * 2 * this->elapsedTime, this->forward);
    }

    // Mouse
    if (this->mouseDelta != glm::vec2(0))
    {
        this->forward = glm::rotate(this->forward, -(T)this->mouseDelta.y, right);
        this->up = glm::rotate(this->up, -(T)this->mouseDelta.y, right);
        this->forward = glm::rotate(this->forward, -(T)this->mouseDelta.x, this->up);
    }
}

template <class T>
void Camera<T>::controlOrbit(glm::vec<3, T> orbitOrigin, T orbitRadius)
{
    this->update();

    // Mouse
    const glm::vec<3, T> right = glm::normalize(glm::cross(this->forward, this->up));
    if (glfwGetMouseButton(this->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        this->forward = glm::rotate(this->forward, -(T)this->mouseDelta.y, right);
        this->forward = glm::rotate(this->forward, -(T)this->mouseDelta.x, this->up);

        this->pos = orbitOrigin - this->forward * orbitRadius;
        const glm::vec<3, T> newRight = glm::normalize(glm::cross(this->forward, glm::vec<3, T>(0, 1, 0)));
        this->up = glm::normalize(glm::cross(newRight, this->forward));
    }
}

template <class T>
void Camera<T>::update()
{
    // Update time
    static double time = 0;
    double newTime = glfwGetTime();
    this->elapsedTime = newTime - time;
    time = newTime;

    // Update mouse
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    double newPosX, newPosY;
    glfwGetCursorPos(this->window, &newPosX, &newPosY);
    this->mouseDelta = glm::vec<2, T>(newPosX - width / 2, newPosY - height / 2) * this->rotationSpeed / (T)200;
    glfwSetCursorPos(this->window, width / 2, height / 2);
}

template <class T>
glm::mat<4, 4, T> Camera<T>::createProjection(glm::vec2 size, glm::vec2 zClip) const
{
    return glm::perspectiveFov(this->fov, (T)size.x, (T)size.y, (T)zClip.x, (T)zClip.y);
}

template <class T>
glm::mat<4, 4, T> Camera<T>::createView() const
{
    return glm::lookAt(this->pos, this->pos + this->forward, this->up);
}
