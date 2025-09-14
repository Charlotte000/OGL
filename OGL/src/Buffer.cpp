#include <assert.h>

#include "OGL/Buffer.h"

using namespace OGL;

template <GLenum Target>
Buffer<Target>::Buffer()
{
    glGenBuffers(1, &this->handler);
    glBindBuffer(Target, this->handler);
    glBindBuffer(Target, 0);
    
    this->write(nullptr, 0);
}

template <GLenum Target>
Buffer<Target>::Buffer(Buffer<Target>&& buff)
    : handler(buff.handler)
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
void Buffer<Target>::write(const void* data, size_t size, DataUsage usage)
{
    glBindBuffer(Target, this->handler);
    glBufferData(Target, size, data, (GLenum)usage);
    glBindBuffer(Target, 0);
}

template <GLenum Target>
void Buffer<Target>::update(const void* data, size_t offset, size_t size)
{
    assert(offset + size <= this->getSize());

    glBindBuffer(Target, this->handler);
    glBufferSubData(Target, offset, size, data);
    glBindBuffer(Target, 0);
}

template <GLenum Target>
void Buffer<Target>::read(void* data, size_t offset, size_t size) const
{
    assert(offset + size <= this->getSize());

    glBindBuffer(Target, this->handler);
    glGetBufferSubData(Target, offset, size, data);
    glBindBuffer(Target, 0);
}

template <GLenum Target>
void Buffer<Target>::read(void* data, size_t size) const
{
    return this->read(data, 0, size);
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
size_t Buffer<Target>::getSize() const
{
    GLint size;

    glBindBuffer(Target, this->handler);
    glGetBufferParameteriv(Target, GL_BUFFER_SIZE, &size);
    glBindBuffer(Target, 0);
    return size;
}

template <GLenum Target>
DataUsage Buffer<Target>::getUsage() const
{
    GLint usage;

    glBindBuffer(Target, this->handler);
    glGetBufferParameteriv(Target, GL_BUFFER_USAGE, &usage);
    glBindBuffer(Target, 0);
    return (DataUsage)usage;
}

template <GLenum Target>
void Buffer<Target>::stopUse()
{
    glBindBuffer(Target, 0);
}
