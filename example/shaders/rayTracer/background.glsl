#version 430 core
#pragma shader_stage(compute)

layout (local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(rgba32f, binding=0) writeonly uniform image2D outImage;

ivec2 Size = imageSize(outImage);
ivec2 TexelCoord = ivec2(gl_GlobalInvocationID.xy);
vec2 UV = vec2(TexelCoord) / Size;

void main()
{
    float y = 1 - UV.y * 2;

    vec3 resultColor = mix(
        vec3(0.5, 0.5, 0.5),
        mix(vec3(1, 1, 1), vec3(0.5, 0.5, 1), pow(smoothstep(0.0, 0.4, y), 0.35)),
        smoothstep(-0.01, 0.0, y)
    );

    imageStore(outImage, TexelCoord, vec4(resultColor, 1));
}
