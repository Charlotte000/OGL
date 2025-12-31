#include <assert.h>
#include <stdexcept>

#include "OGL/Image1D.h"

using namespace OGL;

Image1D::Image1D(glm::uvec1 size, const std::initializer_list<glm::vec4>& pixels)
    : size(size), pixels(pixels.size() != 0 ? pixels : std::vector<glm::vec4>(size.x, glm::vec4(0)))
{
    assert(this->size.x == this->pixels.size());
}

Image1D::Image1D(glm::uvec1 size, const void* data)
    : size(size), pixels(reinterpret_cast<const glm::vec4*>(data), reinterpret_cast<const glm::vec4*>(data) + size.x)
{
}

Image1D::operator Image2D() const
{
    Image2D img(glm::uvec2(this->size, 1));
    img.pixels = this->pixels;
    return img;
}

Image1D::operator Image3D() const
{
    Image3D img(glm::uvec3(this->size, 1, 1));
    img.pixels = this->pixels;
    return img;
}

glm::vec4& Image1D::operator[](glm::uvec1 coords)
{
    assert(coords.x < this->size.x);
    const size_t index = coords.x;
    return this->pixels[index];
}

const glm::vec4& Image1D::operator[](glm::uvec1 coords) const
{
    assert(coords.x < this->size.x);
    const size_t index = coords.x;
    return this->pixels[index];
}
