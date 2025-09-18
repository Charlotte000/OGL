#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace OGL
{

template <class T>
struct Camera
{
public:
    glm::vec<3, T> pos = glm::vec<3, T>(0, 0, 0);
    glm::vec<3, T> forward = glm::vec<3, T>(0, 0, 1);
    glm::vec<3, T> up = glm::vec<3, T>(0, 1, 0);
    T fov = glm::half_pi<T>();

    glm::vec<3, T> right() const;
    glm::mat<4, 4, T> createView() const;
    glm::mat<4, 4, T> createProjection(glm::vec2 size, glm::vec2 zClip) const;
};

template class Camera<float>;
template class Camera<double>;
template class Camera<long double>;

}
