#include <glm/gtx/transform.hpp>

#include "OGL/Camera.h"

using namespace OGL;

template <class T>
glm::vec<3, T> Camera<T>::right() const
{
    return glm::normalize(glm::cross(this->forward, this->up));
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
