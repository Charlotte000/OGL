#version 430 core

in vec3 FragPos;
in vec4 FragLightPos;
in vec3 Normal;
in vec3 ObjColor;
out vec4 FragColor;

uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;

vec3 LightDir = normalize(LightPos - FragPos);
vec3 ViewDir = normalize(ViewPos -FragPos);

vec3 ambient()
{
    return 0.1 * LightColor;
}

vec3 diffuse()
{
    return max(dot(Normal, LightDir), 0) * LightColor;
}

vec3 specular()
{
    vec3 reflectDir = reflect(-LightDir, Normal);
    float spec = pow(max(dot(ViewDir, reflectDir), 0.0), 32);
    return 0.5 * spec * LightColor;
}

void main()
{
    vec3 result = (ambient() + diffuse() + specular()) * ObjColor;
    FragColor = vec4(result, 1);
}
