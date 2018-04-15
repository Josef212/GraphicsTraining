#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D shadow_texture;

void main()
{
	float val = texture(shadow_texture, TexCoords).r;
	FragColor = vec4(vec3(val), 1.0);
}
