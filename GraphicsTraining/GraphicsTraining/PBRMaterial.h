#ifndef __PBR_MATERIAL_H__
#define __PBR_MATERIAL_H__

#include "Material.h"

#include <vector>
#include <glm/glm.hpp>

class Texture;

class PBRMaterial : public Material
{
public:
	PBRMaterial(const char* name);
	PBRMaterial(const char* name, Shader* sh);
	virtual ~PBRMaterial();

	void OnFree() override;

	void SendInfo(Scene* scene) const override;

public:
	glm::vec3 albedoColor;
	Texture* albedoMap = nullptr;

	float metallicValue;
	Texture* metallicMap = nullptr;
	
	float roughnessValue;
	Texture* roughnessMap = nullptr;
	
	float aoValue;
	Texture* aoMap = nullptr;

	Texture* normalMap = nullptr;

	glm::vec3* camPos = nullptr;

	std::vector<glm::vec3>* lightPositions;
	std::vector<glm::vec3>* lightColors;
	int* lightCount = nullptr;
	
};

#endif // !__PBR_MATERIAL_H__