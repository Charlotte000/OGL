#pragma once

#include <vector>
#include <filesystem>

#include <glm/glm.hpp>

namespace OGL
{

struct Image
{
public:
    glm::uvec2 size;
    std::vector<float> pixels;

    Image(const std::filesystem::path& path);

    Image(glm::uvec2 size, const std::vector<float>& pixels = {});

    void saveToFile(const std::filesystem::path& path) const;

    Image resize(glm::uvec2 size) const;

    glm::vec4 get(glm::uvec2 coords) const;

    glm::vec4 get(size_t index) const;

    void set(glm::uvec2 coords, glm::vec4 value);

    void set(size_t index, glm::vec4 value);
};

}
