#include "Material.h"

#include "Shader.h"
#include <GL/glew.h>


Material::Material(const char* name) : Resource(name, RES_MATERIAL)
{
}

Material::Material(const char * name, Shader * sh) : Resource(name, RES_MATERIAL), shader(sh)
{
}


Material::~Material()
{
}

void Material::Load()
{
	OnLoad();
}

void Material::Free()
{
	OnFree();
}

void Material::InitRender() const
{
	if (shader) shader->Use();
}

void Material::EndRender() const
{
	glUseProgram(0);
}

void Material::SetShader(Shader * sh)
{
	shader = sh;
}

Shader * Material::GetShader() const
{
	return shader;
}

