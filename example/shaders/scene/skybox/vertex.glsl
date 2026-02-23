#version 430 core

layout (location = 0) in vec3 position;

uniform mat4 PVM;

out vec3 FragPos;

void main()
{
    gl_Position = PVM * vec4(position, 1);
    gl_Position = gl_Position.xyww;

    FragPos = position;
}
