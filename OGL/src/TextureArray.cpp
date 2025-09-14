#include "OGL/TextureArray.h"

using namespace OGL;

TextureArray::TextureArray(Filter filter, Wrap wrap)
{
    glGenTextures(1, &this->handler);
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->handler);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, (GLint)filter);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, (GLint)filter);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, (GLint)wrap);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, (GLint)wrap);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

TextureArray::TextureArray(TextureArray&& tex)
    : handler(tex.handler)
{
    tex.handler = -1;
}

TextureArray::~TextureArray()
{
    if (this->handler != -1)
    {
        glDeleteTextures(1, &this->handler);
    }
}

void TextureArray::bindSampler(unsigned int binding)
{
    glBindTextureUnit(binding, this->handler);
}

void TextureArray::bindImage(unsigned int binding, Access access, GLenum format)
{
    glBindImageTexture(binding, this->handler, 0, GL_FALSE, 0, (GLenum)access, format);
}

void TextureArray::write(const void* pixels, glm::uvec3 size, GLenum format, Type type, GLint internalFormat)
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->handler);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, internalFormat, size.x, size.y, size.z, 0, format, (GLenum)type, pixels);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureArray::write(const std::vector<Image>& images, GLint internalFormat)
{
    // Find max image size
    glm::uvec2 maxImgSize(0, 0);
    for (const Image& img : images)
    {
        maxImgSize = glm::max(maxImgSize, img.size);
    }

    // Resize images to max image size
    const size_t count = maxImgSize.x * maxImgSize.y * 4;
    std::vector<float> data(count * images.size());
    for (size_t i = 0; i < images.size(); i++)
    {
        const Image resizedImg = images[i].resize(maxImgSize);
        data.insert(data.begin() + count * i, resizedImg.pixels.begin(), resizedImg.pixels.end());
    }

    this->write(data.data(), glm::uvec3(maxImgSize, images.size()), GL_RGBA, Type::FLOAT, internalFormat);
}

void TextureArray::update(const void* pixels, glm::uvec3 offset, glm::uvec3 size, GLenum format, Type type)
{
    assert(glm::all(glm::lessThanEqual(offset + size, this->getSize())));

    glBindTexture(GL_TEXTURE_2D_ARRAY, this->handler);
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, offset.x, offset.y, offset.z, size.x, size.y, 1, format, (GLenum)type, pixels);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void TextureArray::update(const Image& image, glm::uvec3 offset)
{
    this->update(image.pixels.data(), offset, glm::uvec3(image.size, 1), GL_RGBA, Type::FLOAT);
}

Image TextureArray::read(glm::uvec3 offset, glm::uvec2 size) const
{
    glm::uvec3 texSize = this->getSize();
    assert(glm::all(glm::lessThanEqual(offset + glm::uvec3(size, 1), texSize)));

    Image img(size);
    glGetTextureSubImage(this->handler, 0, offset.x, offset.y, offset.z, size.x, size.y, 1, GL_RGBA, GL_FLOAT, img.pixels.size() * sizeof(float), img.pixels.data());

    return img;
}

void TextureArray::clear()
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->handler);
    glClearTexImage(this->handler, 0, GL_RGBA, GL_FLOAT, nullptr);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

GLuint TextureArray::getHandler() const
{
    return this->handler;
}

glm::uvec3 TextureArray::getSize() const
{
    GLint width, height, depth;
 
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->handler);
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_HEIGHT, &height);
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_DEPTH, &depth);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    return glm::uvec3(width, height, depth);
}

GLint TextureArray::getInternalFormat() const
{
    GLint internalFormat;
 
    glBindTexture(GL_TEXTURE_2D_ARRAY, this->handler);
    glGetTexLevelParameteriv(GL_TEXTURE_2D_ARRAY, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    return internalFormat;
}
