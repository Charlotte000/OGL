#version 430 core

in vec3 FragPos;
in vec4 FragLightPos;
in vec3 Normal;
in vec3 ObjColor;
out vec4 FragColor;

layout(binding=0) uniform sampler2D shadowMap;

uniform vec3 LightColor;
uniform vec3 LightPos;
uniform vec3 ViewPos;

vec3 LightDir = normalize(LightPos - FragPos);
vec3 ViewDir = normalize(ViewPos - FragPos);

vec3 ambient()
{
    return 0.15 * ObjColor;
}

vec3 diffuse()
{
    return max(dot(Normal, LightDir), 0) * LightColor;
}

vec3 specular()
{
    vec3 halfwayDir = normalize(LightDir + ViewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 64.0);
    return spec * LightColor;
}

vec3 shadow()
{
    float bias = max(0.05 * (1.0 - dot(Normal, LightDir)), 0.005);

    vec3 projCoords = FragLightPos.xyz / FragLightPos.w;
    projCoords = projCoords * 0.5 + 0.5;
    if (projCoords.z > 1) return vec3(0);

    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = 0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;

    return vec3(shadow);
}

void main()
{
    vec3 result = (ambient() + (1.0 - shadow()) * (diffuse() + specular())) * ObjColor;
    FragColor = vec4(result, 1);
}
