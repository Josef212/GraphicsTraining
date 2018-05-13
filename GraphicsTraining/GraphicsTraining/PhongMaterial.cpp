#include "PhongMaterial.h"

#include "Texture.h"
#include "Shader.h"


PhongMaterial::PhongMaterial(const char* name) : Material(name)
{
}

PhongMaterial::PhongMaterial(const char* name, Shader* sh) : Material(name, sh)
{
}

PhongMaterial::~PhongMaterial()
{
	OnFree();
}

void PhongMaterial::OnFree()
{
}

void PhongMaterial::SendInfo(Scene * scene) const
{
	// Send color
	shader->SetVec3("objectColor", color);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, colorTexture->TextureID());
	shader->SetInt("colorTexture", 0);

	shader->SetBool("hasTexture", useTexture);

	// Normal map
	shader->SetBool("hasNormalMap", normalMap ? useNormalMap : false);

	if(normalMap != nullptr)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalMap->TextureID());
	}
	shader->SetInt("normalMap", 1);

	// Light color
	shader->SetVec3("lightColor", &lightColor->r);

	// Light pos
	shader->SetVec3("lightPos", &lightPos->x);

	// View pos
	shader->SetVec3("viewPos", &viewPos->x);

	// Blinn
	shader->SetBool("blinn", blinn);
}
