#pragma once

#include "OGL/Buffer.h"

namespace OGL
{

class StorageBuffer : public Buffer<GL_SHADER_STORAGE_BUFFER>
{
public:
    void bindBuffer(int binding);
};

}