#version 430 core

layout (location = 0) in vec2 position;

out vec3 Color;

void main()
{
    gl_Position = vec4(position + vec2(0, gl_InstanceID / 5.0), 0, 1);
    Color = vec3((position.x + 0.8) / 1.6, gl_InstanceID / 10.0, 0);
}
