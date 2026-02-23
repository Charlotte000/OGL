#version 430 core

in vec3 FragPos;
out vec4 FragColor;

layout(binding=0) uniform samplerCube skyBox;

void main()
{
    FragColor = texture(skyBox, FragPos);
}
