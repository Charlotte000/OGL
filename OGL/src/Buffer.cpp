#include <assert.h>

#include "OGL/Buffer.h"

using namespace OGL;

Buffer::Buffer()
{
    glCreateBuffers(1, &this->handler);
}

Buffer::Buffer(Buffer&& buff)
    : handler(buff.handler)
{
    buff.handler = -1;
}

Buffer::~Buffer()
{
    if (this->handler != -1)
    {
        glDeleteBuffers(1, &this->handler);
    }
}

Buffer& Buffer::operator=(Buffer&& buff)
{
    if (this->handler != -1)
    {
        glDeleteBuffers(1, &this->handler);
    }

    this->handler = buff.handler;
    buff.handler = -1;
    return *this;
}

void Buffer::write(const void* data, size_t size, DataUsage usage)
{
    glNamedBufferData(this->handler, size, data, static_cast<GLenum>(usage));
}

void Buffer::update(const void* data, size_t offset, size_t size)
{
    assert(offset + size <= this->getSize());
    glNamedBufferSubData(this->handler, offset, size, data);
}

void Buffer::read(void* data, size_t offset, size_t size) const
{
    assert(offset + size <= this->getSize());
    glGetNamedBufferSubData(this->handler, offset, size, data);
}

void Buffer::read(void* data, size_t size) const
{
    return this->read(data, 0, size);
}

void Buffer::bind(GLenum target, unsigned int binding)
{
    glBindBufferBase(target, binding, this->handler);
}

void Buffer::use(GLenum target)
{
    glBindBuffer(target, this->handler);
}

GLuint Buffer::getHandler() const
{
    return this->handler;
}

size_t Buffer::getSize() const
{
    GLint size;
    glGetNamedBufferParameteriv(this->handler, GL_BUFFER_SIZE, &size);
    return size;
}

DataUsage Buffer::getUsage() const
{
    GLint usage;
    glGetNamedBufferParameteriv(this->handler, GL_BUFFER_USAGE, &usage);
    return static_cast<DataUsage>(usage);
}

void Buffer::stopUse(GLenum target)
{
    glBindBuffer(target, 0);
}
