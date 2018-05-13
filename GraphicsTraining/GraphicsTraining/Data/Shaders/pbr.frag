#version 330 core
out vec4 FragColor;

in VS_OUT
{
	vec3 WorldPos;
	vec3 Normal;
	vec2 TexCoord;
} fs_in;

// Material parameters
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// Material parameters samplers - TODO
/*uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;*/

// Lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

// Camera position
uniform vec3 camPos;

const float PI = 3.14159265359;

void main()
{

}
