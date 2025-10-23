#include <assert.h>

#include "OGL/Buffer.h"

using namespace OGL;

template <GLenum Target>
Buffer<Target>::Buffer()
{
    glCreateBuffers(1, &this->handler);
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
Buffer<Target>& Buffer<Target>::operator=(Buffer<Target>&& buff)
{
    if (this->handler != -1)
    {
        glDeleteBuffers(1, &this->handler);
    }

    this->handler = buff.handler;
    buff.handler = -1;
    return *this;
}

template <GLenum Target>
void Buffer<Target>::write(const void* data, size_t size, DataUsage usage)
{
    glNamedBufferData(this->handler, size, data, static_cast<GLenum>(usage));
}

template <GLenum Target>
void Buffer<Target>::update(const void* data, size_t offset, size_t size)
{
    assert(offset + size <= this->getSize());
    glNamedBufferSubData(this->handler, offset, size, data);
}

template <GLenum Target>
void Buffer<Target>::read(void* data, size_t offset, size_t size) const
{
    assert(offset + size <= this->getSize());
    glGetNamedBufferSubData(this->handler, offset, size, data);
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
    glGetNamedBufferParameteriv(this->handler, GL_BUFFER_SIZE, &size);
    return size;
}

template <GLenum Target>
DataUsage Buffer<Target>::getUsage() const
{
    GLint usage;
    glGetNamedBufferParameteriv(this->handler, GL_BUFFER_USAGE, &usage);
    return static_cast<DataUsage>(usage);
}

template <GLenum Target>
void Buffer<Target>::stopUse()
{
    glBindBuffer(Target, 0);
}
