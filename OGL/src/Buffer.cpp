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
    this->write(nullptr, buff.size(), buff.usage());
    buff.copy(0, *this, 0, buff.size());
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
    this->write(nullptr, buff.size(), buff.usage());
    buff.copy(0, *this, 0, buff.size());

    return *this;
}

void Buffer::write(const void* data, size_t size, DataUsage usage)
{
    glNamedBufferData(this->handler, size, data, static_cast<GLenum>(usage));
}

void Buffer::update(const void* data, size_t offset, size_t size)
{
    if (offset + size > this->size())
        throw std::out_of_range("offset + size is greater than the size of the buffer");

    glNamedBufferSubData(this->handler, offset, size, data);
}

void Buffer::read(void* data, size_t offset, size_t size) const
{
    if (offset + size > this->size())
        throw std::out_of_range("offset + size is greater than the size of the buffer");

    glGetNamedBufferSubData(this->handler, offset, size, data);
}

void Buffer::read(void* data, size_t size) const
{
    return this->read(data, 0, size);
}

void Buffer::copy(size_t srcOffset, Buffer& dst, size_t dstOffset, size_t size) const
{
    if (srcOffset + size > this->size())
        throw std::out_of_range("srcOffset + size is greater than the size of the srcBuffer");

    if (dstOffset + size > dst.size())
        throw std::out_of_range("dstOffset + size is greater than the size of the dstBuffer");

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
        throw std::runtime_error("Failed to map buffer");

    return ptr;
}

const void* Buffer::map() const
{
    void *ptr = glMapNamedBuffer(this->handler, static_cast<GLenum>(Access::READ_ONLY));
    if (ptr == nullptr)
        throw std::runtime_error("Failed to map buffer");

    return ptr;
}

void Buffer::unmap() const
{
    bool result = glUnmapNamedBuffer(this->handler);
    if (!result)
        throw std::runtime_error("Failed to unmap buffer");
}

GLuint Buffer::getHandler() const
{
    return this->handler;
}

size_t Buffer::size() const
{
    GLint size;
    glGetNamedBufferParameteriv(this->handler, GL_BUFFER_SIZE, &size);
    return size;
}

DataUsage Buffer::usage() const
{
    GLint usage;
    glGetNamedBufferParameteriv(this->handler, GL_BUFFER_USAGE, &usage);
    return static_cast<DataUsage>(usage);
}

void Buffer::stopUse(GLenum target)
{
    glBindBuffer(target, 0);
}
