/**
 * @file Buffer.h
 */
#pragma once

#include "OGL/Enums.h"

namespace OGL
{

/**
 * @brief Generic buffer class.
 * 
 * Buffers are used to store various types of data such as vertex data, indices, uniform data, shader storage data, etc.
 * Buffer objects are mutable, meaning their size and usage pattern can be changed after creation.
 * 
 * @tparam Target OpenGL buffer target (e.g., GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, GL_UNIFORM_BUFFER, etc.).
 */
template <GLenum Target>
class Buffer
{
public:
    Buffer();

    Buffer(Buffer<Target>&& buff);

    ~Buffer();

    /**
     * @brief Allocate and initialize new data storage for the buffer object.
     * 
     * The previous data store, if any, is deleted.
     * 
     * @param data Pointer to the data that will be copied into the data store for initialization. Can be nullptr.
     * @param size Size in bytes of the data store.
     * @param usage Expected usage pattern of the data store.
     */
    void write(const void* data, size_t size, DataUsage usage = DataUsage::STATIC_COPY);

    /**
     * @brief Update a subset of the buffer object's data store.
     * @param data Pointer to the new data that will be copied into the data store.
     * @param offset Offset in bytes into the buffer object's data store where data replacement will begin.
     * @param size Size in bytes of the data to be copied from data to the data store.
     */
    void update(const void* data, size_t offset, size_t size);

    /**
     * @brief Read data from the buffer object's data store.
     * @param data Pointer to a memory location where the data will be copied.
     * @param offset Offset in bytes into the buffer object's data store from which data will be read.
     * @param size Size in bytes of the data to be read from the data store.
     */
    void read(void* data, size_t offset, size_t size) const;

    /**
     * @brief Read data from the beginning of the buffer object's data store.
     * 
     * This is a convenience method that reads data starting from offset 0.
     * 
     * @param data Pointer to a memory location where the data will be copied.
     * @param size Size in bytes of the data to be read from the data store.
     */
    void read(void* data, size_t size) const;

    /**
     * @brief Bind the buffer to a specified target and binding point.
     * 
     * This method binds the buffer to the specified target (e.g., GL_ARRAY_BUFFER) and binding point (for targets that support binding points, such as GL_UNIFORM_BUFFER).
     * 
     * @param target The target to which the buffer is bound.
     * @param binding The binding point index (used for targets like GL_UNIFORM_BUFFER).
     */
    void bind(GLenum target, unsigned int binding);

    /**
     * @brief Bind the buffer to the OpenGL context.
     */
    void use();

    /**
     * @brief Get the OpenGL handler of the buffer object.
     * @return The OpenGL handler of the buffer object.
     */
    GLuint getHandler() const;

    /**
     * @brief Get the size of the buffer object's data store in bytes.
     * 
     * @return Size in bytes of the buffer object's data store.
     */
    size_t getSize() const;

    /**
     * @brief Get the usage pattern of the buffer object's data store.
     * @return The usage pattern (DataUsage) of the buffer object's data store.
     */
    DataUsage getUsage() const;

    /**
     * @brief Unbind any buffer from the OpenGL context.
     */
    static void stopUse();
protected:
    GLuint handler = -1;
};

template class Buffer<GL_ARRAY_BUFFER>;
template class Buffer<GL_ELEMENT_ARRAY_BUFFER>;
template class Buffer<GL_SHADER_STORAGE_BUFFER>;
template class Buffer<GL_UNIFORM_BUFFER>;

}
