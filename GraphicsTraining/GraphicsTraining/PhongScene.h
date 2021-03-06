#ifndef __PHONGSCENE_H__
#define __PHONGSCENE_H__

#include "Scene.h"

#include <glm/glm/glm.hpp>

class Model;
class ComplexMaterial;

class PhongScene : public Scene
{
public:
	PhongScene(const char* name, const char* modelName);
	virtual ~PhongScene();

	void OnInit() override;
	void OnCleanUp() override;

	void OnActiveCameraChanged() override;

	void OnRenderScene() override;

	void OnGui() override;

private:

public:
	bool blinn = true;
	bool useTexture = true;
	glm::vec3 lightPos;
	glm::vec3 lightColor, objectColor;

private:
	Model* light = nullptr;
	ComplexMaterial* phong = nullptr;
	std::string modelName = "";
};

#endif // !__PHONGSCENE_H__