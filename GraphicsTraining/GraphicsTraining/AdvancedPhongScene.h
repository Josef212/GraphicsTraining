#ifndef __ADVANCED_PHONG_SCENE_H__
#define __ADVANCED_PHONG_SCENE_H__

#include "Scene.h"

#include <glm/glm.hpp>

class PhongMaterial;

class AdvancedPhongScene : public Scene
{
public:
	AdvancedPhongScene(const char* name);
	virtual ~AdvancedPhongScene();

	void OnInit() override;
	void OnCleanUp() override;

	void OnActiveCameraChanged() override;

	void OnRenderScene() override;

	void OnGui() override;

private:

public:
	glm::vec3 lightPos, objectColor, lightColor;


private:
	Model * light = nullptr;
	PhongMaterial* phong = nullptr;
	std::string modelName = "";
	
};

#endif // !__ADVANCED_PHONG_SCENE_H__