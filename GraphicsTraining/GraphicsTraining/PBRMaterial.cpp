#include "PBRMaterial.h"

#include "Shader.h"
#include "Texture.h"


PBRMaterial::PBRMaterial(const char* name) : Material(name)
{
}

PBRMaterial::PBRMaterial(const char* name, Shader* sh) : Material(name, sh)
{
}


PBRMaterial::~PBRMaterial()
{
}

void PBRMaterial::OnFree()
{
}

void PBRMaterial::SendInfo(Scene * scene) const
{
	shader->SetVec3("albedoValue", albedoColor);
	shader->SetFloat("metallicValue", metallicValue);
	shader->SetFloat("roughnessValue", roughnessValue);
	shader->SetFloat("aoValue", aoValue);

	shader->SetVec3("camPos", &camPos->x);

	int lC = *lightCount;
	for(int i = 0; i < lC; ++i)
	{
		std::string pos = "lightPositions[" + std::to_string(i) + "]";
		std::string col = "lightColors[" + std::to_string(i) + "]";

		glm::vec3 p = lightPositions->at(i);
		glm::vec3 c = lightColors->at(i);

		shader->SetVec3(pos.c_str(), p);
		shader->SetVec3(col.c_str(), c);
	}

	shader->SetBool("hasAlbedoTexture", albedoMap != nullptr);
	shader->SetBool("hasNormalMap", normalMap != nullptr);
	shader->SetBool("hasMetallicTexture", metallicMap != nullptr);
	shader->SetBool("hasRoughnessTexture", roughnessMap != nullptr);
	shader->SetBool("hasAOTexture", aoMap != nullptr);

	int texCount = 0;

	if(albedoMap)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, albedoMap->TextureID());
		shader->SetInt("albedoMap", texCount);
		++texCount;
	}

	if (normalMap)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, normalMap->TextureID());
		shader->SetInt("normalMap", texCount);
		++texCount;
	}

	if (metallicMap)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, metallicMap->TextureID());
		shader->SetInt("metallicMap", texCount);
		++texCount;
	}

	if (roughnessMap)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, roughnessMap->TextureID());
		shader->SetInt("roughnessMap", texCount);
		++texCount;
	}

	if (aoMap)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, aoMap->TextureID());
		shader->SetInt("aoMap", texCount);
		++texCount;
	}

	// --------------

	shader->SetFloat("opacityValue", opacityValue);
	shader->SetBool("hasOpacityTexture", opacityTexture != nullptr);

	if(opacityTexture)
	{
		glActiveTexture(GL_TEXTURE0 + texCount);
		glBindTexture(GL_TEXTURE_2D, opacityTexture->TextureID());
		shader->SetInt("opacityMap", texCount);
		++texCount;
	}
}
