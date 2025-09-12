#pragma once

#include <GL/glew.h>

namespace OGL
{

template <GLenum Target>
class Buffer
{
public:
    /**
     * @param usage { GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, GL_DYNAMIC_COPY }
     */
    Buffer(GLenum usage = GL_STATIC_COPY);

    Buffer(Buffer<Target>&& buff);

    ~Buffer();

    void write(const void* data, size_t offset, size_t size);

    void write(const void* data, size_t size);

    void read(size_t offset, size_t size, void* data) const;

    void read(size_t size, void* data) const;
    
    void bind(GLenum target, unsigned int binding);

    void use();

    GLuint getHandler() const;

    static void stopUse();
protected:
    GLenum usage;
    GLuint handler = -1;
    size_t size = 0;
};

template class Buffer<GL_ARRAY_BUFFER>;
template class Buffer<GL_ELEMENT_ARRAY_BUFFER>;
template class Buffer<GL_SHADER_STORAGE_BUFFER>;
template class Buffer<GL_UNIFORM_BUFFER>;

}
