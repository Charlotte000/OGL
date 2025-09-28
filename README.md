# OGL
OGL is a lightweight OpenGL wrapper for C++ 17 and later. It provides a simple and modern interface for working with OpenGL in Objective Oriented Programming (OOP) style.

It is designed in OpenGL Direct State Access (DSA) style. This results in cleaner and more efficient code.

OGL uses CMake as its build system. It is cross-platform and can be used on Windows, Linux, and macOS.

## Supported OpenGL objects
- Array Buffers (VBO)
- Element Array Buffers (EBO)
- Vertex Array Objects (VAO)
- Textures (2D, 2D Array)
- Framebuffer Objects (FBO)
- Shaders
- Shader Programs
- Uniform Buffers (UBO)
- Shader Storage Buffers (SSBO)

## Additional features
- Image class for loading, saving and manipulation (using stb_image and stb_image_write)
- Camera class for easy 3D navigation (using GLM)

# Dependencies
- GLM (for mathematics)
- OpenGL 4.5 or later
- GLEW (for OpenGL function loading)
- stb_image and stb_image_write (for image loading and saving)

# Getting started
This repo contains a CMake example project in the `example` folder. You can use it as an showcase of how to use OGL in your own projects.
