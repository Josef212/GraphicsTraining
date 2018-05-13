#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out VS_OUT
{
	vec3 WorldPos;
	vec3 Normal;
	vec2 TexCoord;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.WorldPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = mat3(model) * aNormal;
	vs_out.TexCoord = aTexCoord;

    gl_Position = projection * view * vec4(vs_out.WorldPos, 1.0);
}
