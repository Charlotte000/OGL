#pragma once

#include <GL/glew.h>

#include "OGL/Enums.h"

namespace OGL
{

// Mutable
template <GLenum Target>
class Buffer
{
public:
    Buffer();

    Buffer(Buffer<Target>&& buff);

    ~Buffer();

    void write(const void* data, size_t size, DataUsage usage = DataUsage::STATIC_COPY);

    void update(const void* data, size_t offset, size_t size);

    void read(void* data, size_t offset, size_t size) const;

    void read(void* data, size_t size) const;
    
    void bind(GLenum target, unsigned int binding);

    void use();

    GLuint getHandler() const;

    size_t getSize() const;

    DataUsage getUsage() const;

    static void stopUse();
protected:
    GLuint handler = -1;
};

template class Buffer<GL_ARRAY_BUFFER>;
template class Buffer<GL_ELEMENT_ARRAY_BUFFER>;
template class Buffer<GL_SHADER_STORAGE_BUFFER>;
template class Buffer<GL_UNIFORM_BUFFER>;

}
