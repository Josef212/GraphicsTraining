#ifndef __PHONGSCENE_H__
#define __PHONGSCENE_H__

#include "Scene.h"

#include <glm/glm/glm.hpp>

class Model;
class ComplexMaterial;

class PhongScene : public Scene
{
public:
	PhongScene(const char* name);
	virtual ~PhongScene();

	void OnInit() override;
	void OnCleanUp() override;

	void OnRenderScene() override;

	void OnGui() override;

private:

public:
	glm::vec3 lightPos;
	glm::vec3 lightColor, objectColor;

private:
	Model* light = nullptr;
	ComplexMaterial* phong = nullptr;
};

#endif // !__PHONGSCENE_H__