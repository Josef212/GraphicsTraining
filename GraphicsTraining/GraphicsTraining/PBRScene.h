#ifndef __PBR_SCENE_H__
#define __PBR_SCENE_H__

#include "Scene.h"

class PBRMaterial;

class PBRScene : public Scene
{
public:
	PBRScene(const char* name);
	virtual ~PBRScene();

	void OnInit() override;
	void OnCleanUp() override;

	void OnActiveCameraChanged() override;

	void OnRenderScene() override;

	void OnGui() override;

public:
	int lightsCount = 4;
	std::vector<glm::vec3> lightPositions; //TODO: Light system
	std::vector<glm::vec3> lightColors;

private:
	PBRMaterial * pbr = nullptr;

	std::string modelName = "";
};

#endif // !__PBR_SCENE_H__