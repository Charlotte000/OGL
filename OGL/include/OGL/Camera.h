#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/constants.hpp>

namespace OGL
{

struct Camera
{
public:
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::vec3 forward = glm::vec3(0, 0, 1);
    glm::vec3 up = glm::vec3(0, 1, 0);
    float fov = glm::half_pi<float>();

    float rotationSpeed = 1;
    float movementSpeed = 5;

    Camera(GLFWwindow* window);

    void controlFree();

    void controlOrbit(glm::vec3 orbitOrigin, float orbitRadius);

    glm::mat4 createView() const;

    glm::mat4 createProjection(glm::vec2 size, glm::vec2 zClip) const;
private:
    GLFWwindow* window;
    float elapsedTime;
    glm::vec2 mouseDelta;

    void update();
};

}
