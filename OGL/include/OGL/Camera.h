/**
 * @file Camera.h
 */
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace OGL
{

/**
 * @brief Simple 3D camera structure that can create view and projection matrices.
 * @tparam T Numeric type (e.g., float, double, long double).
 */
template <class T>
struct Camera
{
public:
    /**
     * @brief Camera position in world space.
     */
    glm::vec<3, T> pos = glm::vec<3, T>(0, 0, 0);

    /**
     * @brief Camera forward direction (should be normalized).
     */
    glm::vec<3, T> forward = glm::vec<3, T>(0, 0, 1);

    /**
     * @brief Camera up direction (should be normalized and orthogonal to forward).
     */
    glm::vec<3, T> up = glm::vec<3, T>(0, 1, 0);

    /**
     * @brief Camera field of view in radians.
     */
    T fov = glm::half_pi<T>();

    /**
     * @brief Get the right direction vector of the camera (computed as cross product of forward and up).
     * @return Vector pointing to the right of the camera (orthogonal to both forward and up vectors and normalized).
     */
    glm::vec<3, T> right() const;

    /**
     * @brief Create a view matrix based on the camera's position and orientation.
     * 
     * The view matrix transforms world coordinates to camera (view) coordinates.

     * @return The view matrix as a 4x4 matrix.
     */
    glm::mat<4, 4, T> createView() const;

    /**
     * @brief Create a projection matrix based on the camera's field of view and clipping planes.
     * 
     * The projection matrix transforms camera coordinates to normalized device coordinates.
     * 
     * @param size Viewport size (width, height).
     * @param zClip Near and far clipping planes (zNear, zFar).
     * @return The projection matrix as a 4x4 matrix.
     */
    glm::mat<4, 4, T> createProjection(glm::vec2 size, glm::vec2 zClip) const;
};

template class Camera<float>;
template class Camera<double>;
template class Camera<long double>;

}
