#ifndef __SCENE_H__
#define __SCENE_H__

#include <vector>
#include <string>
#include <glm/glm.hpp>

class Camera;
class Model;
class Shader;
class Material;
enum Camera_Movement;

#define MAX_CAMERAS 9

class Scene
{
	friend class GuiManager;
public:
	Scene(const char* name);
	virtual ~Scene();

	void Init();
	void CleanUp();

	virtual void OnInit() {}
	virtual void OnCleanUp() {}

	virtual void OnActiveCameraChanged() {}

	void AddModel(Model* model);
	void RemoveModel(const char* name);

	void AddCamera(Camera* cam, int index, bool setAsActive = false);
	void RemoveCamera(int index);

	void SetActiveCamera(int index);
	Camera* GetActiveCamera() const { return activeCamera; }

	void OnResize(int winW, int winH);

	int Width()const { return viewportWidth; }
	int Height()const { return viewportHeight; }

	Material* GetDefaultMaterial()const;

	void RenderScene();
	virtual void OnRenderScene() = 0;

	void ProcessScroll(double yoffset);
	void ProcessMouseMovement(double xoffset, double yoffset);
	void ProcessInput(Camera_Movement movement, float dt);

	virtual void OnGui() {}

private:

public:
	glm::vec4 backgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.f);
	std::string name;

protected:
	Material * defaultMaterial = nullptr;
	std::vector<Model*> models;

private:
	Camera* cameras[MAX_CAMERAS];
	Camera* activeCamera = nullptr;

	int viewportWidth, viewportHeight;

};

#endif // !__SCENE_H__