#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform mat4 PVM;
uniform mat4 LightPV;

out vec3 FragPos;
out vec4 FragLightPos;
out vec3 Normal;
out vec3 ObjColor;

void main()
{
    gl_Position = PVM * vec4(position, 1);
    FragPos = position;
    FragLightPos = LightPV * vec4(position, 1);
    Normal = normal;
    ObjColor = color;
}
