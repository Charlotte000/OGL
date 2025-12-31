#include <assert.h>
#include <stdexcept>

#include "OGL/Image1D.h"

using namespace OGL;

Image3D::Image3D(glm::uvec3 size, const std::initializer_list<glm::vec4>& pixels)
    : size(size), pixels(pixels.size() != 0 ? pixels : std::vector<glm::vec4>(size.x * size.y * size.z, glm::vec4(0)))
{
    assert(this->size.x * this->size.y * this->size.z == this->pixels.size());
}

Image3D::Image3D(glm::uvec3 size, const void* data)
    : size(size), pixels(reinterpret_cast<const glm::vec4*>(data), reinterpret_cast<const glm::vec4*>(data) + size.x * size.y * size.z)
{
}

glm::vec4& Image3D::operator[](glm::uvec3 coords)
{
    assert(coords.x < this->size.x && coords.y < this->size.y && coords.z < this->size.z);
    const size_t index = coords.z * this->size.x * this->size.y + coords.y * this->size.x + coords.x;
    return this->pixels[index];
}

const glm::vec4& Image3D::operator[](glm::uvec3 coords) const
{
    assert(coords.x < this->size.x && coords.y < this->size.y && coords.z < this->size.z);
    const size_t index = coords.z * this->size.x * this->size.y + coords.y * this->size.x + coords.x;
    return this->pixels[index];
}
