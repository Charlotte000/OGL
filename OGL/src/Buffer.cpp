#include <assert.h>

#include "OGL/Buffer.h"

using namespace OGL;

template <GLenum Target>
Buffer<Target>::Buffer(GLenum usage)
    : usage(usage)
{
    glGenBuffers(1, &this->handler);
    glBindBuffer(Target, this->handler);
    glBindBuffer(Target, 0);
    
    this->write(nullptr, 0);
}

template <GLenum Target>
Buffer<Target>::Buffer(Buffer<Target>&& buff)
    : handler(buff.handler), size(buff.size), usage(buff.usage)
{
    buff.handler = -1;
}

template <GLenum Target>
Buffer<Target>::~Buffer()
{
    if (this->handler != -1)
    {
        glDeleteBuffers(1, &this->handler);
    }
}

template <GLenum Target>
void Buffer<Target>::write(const void* data, size_t offset, size_t size)
{
    assert(offset == 0 || offset + size <= this->size);

    glBindBuffer(Target, this->handler);
    {
        if (size > this->size)
        {
            // Resize (offset should be 0)
            this->size = size;
            glBufferData(Target, this->size, data, this->usage);
        }
        else
        {
            // Partial write
            glBufferSubData(Target, offset, size, data);
        }
    }
    glBindBuffer(Target, 0);

}

template <GLenum Target>
void Buffer<Target>::write(const void* data, size_t size)
{
    return this->write(data, 0, size);
}

template <GLenum Target>
void Buffer<Target>::read(size_t offset, size_t size, void* data) const
{
    assert(offset + size <= this->size);

    glBindBuffer(Target, this->handler);
    {
        glGetBufferSubData(Target, offset, size, data);
    }
    glBindBuffer(Target, 0);
}

template <GLenum Target>
void Buffer<Target>::read(size_t size, void* data) const
{
    return this->read(0, size, data);
}

template <GLenum Target>
void Buffer<Target>::bind(GLenum target, unsigned int binding)
{
    glBindBufferBase(target, binding, this->handler);
}

template <GLenum Target>
void Buffer<Target>::use()
{
    glBindBuffer(Target, this->handler);
}

template <GLenum Target>
GLuint Buffer<Target>::getHandler() const
{
    return this->handler;
}

template <GLenum Target>
void Buffer<Target>::stopUse()
{
    glBindBuffer(Target, 0);
}
