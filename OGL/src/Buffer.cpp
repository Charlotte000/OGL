#include <assert.h>
#include <stdexcept>

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

Buffer::Buffer(const Buffer& buff)
    : Buffer()
{
    glCopyNamedBufferSubData(buff.getHandler(), this->handler, 0, 0, buff.getSize());
}

Buffer::~Buffer()
{
    if (this->handler != -1)
    {
        glDeleteBuffers(1, &this->handler);
        this->handler = -1;
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

Buffer& Buffer::operator=(const Buffer& buff)
{
    if (this->handler != -1)
    {
        glDeleteBuffers(1, &this->handler);
    }

    glCreateBuffers(1, &this->handler);
    glCopyNamedBufferSubData(buff.getHandler(), this->handler, 0, 0, buff.getSize());
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

void Buffer::copy(size_t srcOffset, Buffer& dst, size_t dstOffset, size_t size) const
{
    assert(srcOffset + size <= this->getSize() && dstOffset + size <= dst.getSize());
    glCopyNamedBufferSubData(this->handler, dst.getHandler(), srcOffset, dstOffset, size);
}

void Buffer::bind(GLenum target, unsigned int binding)
{
    glBindBufferBase(target, binding, this->handler);
}

void Buffer::use(GLenum target)
{
    glBindBuffer(target, this->handler);
}

void* Buffer::map(Access access)
{
    void *ptr = glMapNamedBuffer(this->handler, static_cast<GLenum>(access));
    if (ptr == nullptr)
    {
        throw std::runtime_error("Failed to map buffer");
    }

    return ptr;
}

void Buffer::unmap()
{
    bool result = glUnmapNamedBuffer(this->handler);
    if (!result)
    {
        throw std::runtime_error("Failed to unmap buffer");
    }
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
