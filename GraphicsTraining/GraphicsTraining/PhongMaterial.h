#ifndef __PHONG_MATERIAL_H__
#define __PHONG_MATERIAL_H__

#include "Material.h"

#include <GLM/glm.hpp>

class Texture;

class PhongMaterial : public Material
{
public:
	PhongMaterial(const char* name);
	PhongMaterial(const char* name, Shader* sh);
	virtual ~PhongMaterial();

	void OnFree() override;

	void SendInfo(Scene* scene) const override;

public:
	Texture * colorTexture = nullptr;
	glm::vec3 color = glm::vec3(0.f);

	Texture * normalMap = nullptr;

	glm::vec3* lightColor = nullptr;
	glm::vec3* lightPos = nullptr;
	glm::vec3* viewPos = nullptr;

	bool blinn = false;
	bool useTexture = true;
	bool useNormalMap = true;

};

#endif // !__PHONG_MATERIAL_H__