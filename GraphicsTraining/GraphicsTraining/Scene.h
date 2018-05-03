#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <glm/glm.hpp>

class Camera;
class Model;
class Shader;
class Material;

#define MAX_CAMERAS 9

class Scene
{
	friend class GuiManager;
public:
	Scene();
	virtual ~Scene();

	void Init();
	void CleanUp();

	void AddModel(Model* model);
	void RemoveModel(const char* name);

	void AddCamera(Camera* cam, int index, bool setAsActive = false);
	void RemoveCamera(int index);

	void SetActiveCamera(int index);
	Camera* GetActiveCamera() const { return activeCamera; }

	void OnResize(int winW, int winH);

	Material* GetDefaultMaterial()const;

	void RenderScene();

private:

public:
	glm::vec4 backgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.f);

private:
	Camera* cameras[MAX_CAMERAS];
	Camera* activeCamera = nullptr;

	int viewportWidth, viewportHeight;

	Material* defaultMaterial = nullptr;

	std::vector<Model*> models;

};
extern Scene* scene;

#endif // !__SCENE_H__