#ifndef __PBR_SCENE_H__
#define __PBR_SCENE_H__

#include "Scene.h"

class PBRMaterial;
class Model;

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

	glm::vec3 rotationSpeed = glm::vec3(0.f, 5.f, 0.f);

private:
	PBRMaterial * pbr = nullptr;

	std::string modelName = "";
	Model* model = nullptr;

	//TMP
	
};

#endif // !__PBR_SCENE_H__