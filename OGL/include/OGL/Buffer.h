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
class Buffer
{
public:
    Buffer();

    Buffer(Buffer&& buff);

    Buffer(const Buffer& buff);

    ~Buffer();

    Buffer& operator=(Buffer&& buff);

    Buffer& operator=(const Buffer& buff);

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
    void use(GLenum target);

    /**
     * @brief Map the buffer to memory for direct access.
     * 
     * Map the buffer object's data store into the client's address space. This allows for direct read/write access to the buffer's data without needing to use glBufferSubData or glGetBufferSubData.
     * 
     * @param access The access policy for the mapped buffer.
     * @return Pointer to the mapped memory. The pointer is valid until the buffer is unmapped using Buffer::unmap or the buffer is deleted. The behavior of accessing the mapped memory after unmapping or deleting the buffer is undefined.
     * @throw std::runtime_error if the buffer cannot be mapped.
     */
    void* map(Access access);

    /**
     * @brief Unmap the buffer from memory.
     * 
     * Release the mapping of the buffer object's data store from the client's address space. After this call, the pointer returned by Buffer::map is no longer valid and should not be accessed.
     * 
     * @throw std::runtime_error if the buffer cannot be unmapped (e.g., if the data store contents have become corrupt during the time it was mapped).
     */
    void unmap();

    /**
     * @brief Get the OpenGL handler of the buffer object.
     * @return The OpenGL handler of the buffer object.
     */
    GLuint getHandler() const;

    /**
     * @brief Get the size of the buffer object's data store in bytes.
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
    static void stopUse(GLenum target);
protected:
    GLuint handler = -1;
};

}
