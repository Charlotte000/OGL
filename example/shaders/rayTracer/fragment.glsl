#version 430 core

in vec2 TexCoords;
out vec4 FragColor;

uniform vec3 cameraPos;
uniform vec3 cameraForward;
uniform vec3 cameraUp;
uniform float cameraFOV;
uniform float aspectRatio;
layout(binding=0) uniform sampler2D environment;

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
    Sphere(vec3(0), 1, Material(vec3(1, 0, 1))),
    Sphere(vec3(-3, 0, 0), 1, Material(vec3(0, 1, 0))),
};
vec3 light = normalize(vec3(1, 1, -1));

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
    vec2 coord = (TexCoords - .5) * 2 * vec2(1, aspectRatio) * tan(cameraFOV * .5);
    Ray ray = Ray(cameraPos, normalize(cameraForward + cross(cameraForward, cameraUp) * coord.x + cameraUp * coord.y));

    for (uint i = 0; i < 10; i++)
    {
        CollisionManifold collisionManifold;
        if (!rayCollision(ray, collisionManifold))
        {
            FragColor = texture(environment, vec2(atan(ray.dir.z, ray.dir.x) * 0.15915494309189533 + 0.5, acos(ray.dir.y) * 0.31830988618379067));
            break;
        }

        FragColor = vec4(collisionManifold.material.color * dot(collisionManifold.normal, light), 1);
        ray.pos = collisionManifold.pos;
        ray.dir = reflect(ray.dir, collisionManifold.normal);
    }
}
