#include <stdexcept>

#include "OGL/Image1D.h"

using namespace OGL;

Image3D::Image3D(glm::uvec3 size, const std::initializer_list<glm::vec4>& pixels)
    : size(size), pixels(pixels.size() != 0 ? pixels : std::vector<glm::vec4>(size.x * size.y * size.z, glm::vec4(0)))
{
    if (this->size.x * this->size.y * this->size.z != this->pixels.size())
        throw std::invalid_argument("Size of the image does not match the number of pixels provided");
}

Image3D::Image3D(glm::uvec3 size, const void* data)
    : size(size), pixels(reinterpret_cast<const glm::vec4*>(data), reinterpret_cast<const glm::vec4*>(data) + size.x * size.y * size.z)
{
}

glm::vec4& Image3D::operator[](glm::uvec3 coords)
{
    if (glm::any(glm::greaterThanEqual(coords, this->size)))
        throw std::out_of_range("Pixel coordinates are out of range");

    const size_t index = coords.z * this->size.x * this->size.y + coords.y * this->size.x + coords.x;
    return this->pixels[index];
}

const glm::vec4& Image3D::operator[](glm::uvec3 coords) const
{
    if (glm::any(glm::greaterThanEqual(coords, this->size)))
        throw std::out_of_range("Pixel coordinates are out of range");

    const size_t index = coords.z * this->size.x * this->size.y + coords.y * this->size.x + coords.x;
    return this->pixels[index];
}
