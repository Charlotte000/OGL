#version 430 core
#pragma shader_stage(compute)

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

uniform vec3 cameraPos;
uniform vec3 cameraForward;
uniform vec3 cameraUp;
uniform float cameraFOV;
uniform float aspectRatio;
layout(rgba32f, binding=1) writeonly uniform image2D outImage;
layout(binding=0) uniform sampler2D environment;

ivec2 Size = imageSize(outImage);
ivec2 TexelCoord = ivec2(gl_GlobalInvocationID.xy);
vec2 UV = vec2(TexelCoord.x, TexelCoord.y) / Size;

vec3 Light = normalize(vec3(1, 1, -1));

struct Ray
{
    vec3 pos;
    vec3 dir;
};

struct Material
{
    vec3 color;
};

struct CollisionManifold
{
    vec3 pos;
    vec3 normal;
    float t;
    Material material;
};

struct Sphere
{
    vec3 pos;
    float radius;
    Material material;
};

Sphere spheres[] =
{
    Sphere(vec3(-3, 0, 0), 1, Material(vec3(1, .5, .5))),
    Sphere(vec3(0, 0, 0), 1, Material(vec3(.5, 1, .5))),
    Sphere(vec3(3, 0, 0), 1, Material(vec3(.5, .5, 1))),
};

bool raySphereCollide(in Ray ray, in Sphere sphere, inout CollisionManifold collisionManifold)
{
    float a = dot(ray.dir, ray.dir);
    vec3 deltaPos = ray.pos - sphere.pos;
    float b = 2 * dot(ray.dir, deltaPos);
    float c = dot(deltaPos, deltaPos) - (sphere.radius * sphere.radius);
    float d = b * b - 4 * a * c;

    if (d < 0)
    {
        return false;
    }

    float t = (-b - sqrt(d)) / (2 * a);
    if (t > collisionManifold.t || t < 0)
    {
        return false;
    }

    vec3 point = ray.pos + ray.dir * t;
    collisionManifold = CollisionManifold(point, normalize(point - sphere.pos), t, sphere.material);
    return true;
}

bool rayCollision(in Ray ray, out CollisionManifold collisionManifold)
{
    collisionManifold.t = 9999;

    for (uint i = 0; i < spheres.length(); i++)
    {
        raySphereCollide(ray, spheres[i], collisionManifold);
    }

    return collisionManifold.t < 9999;
}

void main()
{
    vec2 coord = (UV - .5) * 2 * vec2(1, aspectRatio) * tan(cameraFOV * .5);

    vec3 throughput = vec3(1);
    vec3 radiance = vec3(0);
    Ray ray = Ray(cameraPos, normalize(cameraForward + cross(cameraForward, cameraUp) * coord.x + cameraUp * coord.y));

    for (uint i = 0; i < 10; i++)
    {
        CollisionManifold collisionManifold;
        if (!rayCollision(ray, collisionManifold))
        {
            radiance += texture(environment, vec2(atan(ray.dir.z, ray.dir.x) * 0.15915494309189533 + 0.5, acos(ray.dir.y) * 0.31830988618379067)).rgb * throughput;
            break;
        }

        throughput *= collisionManifold.material.color;

        ray.pos = collisionManifold.pos;
        ray.dir = reflect(ray.dir, collisionManifold.normal);
    }

    imageStore(outImage, TexelCoord, vec4(radiance, 1));
}
