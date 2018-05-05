#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include <vector>
#include "Camera.h"

class Scene;

class SceneManager
{
friend class Editor_ScenePanel;

public:
	SceneManager();
	virtual ~SceneManager();

	void CleanUp();

	void AddScene(Scene* sc, bool activate = false);
	void RemoveScene(Scene* sc);
	void RemoveScene(const char* name);

	void SelectActiveScene(int index);
	void SelectActiveScene(const char* name);
	void SelectActiveScene(Scene* sc);
	Scene* GetActiveScene()const;

	void OnResize(int w, int h);

	void ProcessScroll(double yoffset);
	void ProcessMouseMovement(double xoffset, double yoffset);
	void ProcessInput(Camera_Movement movement, float dt);
	void SelectCamera(int index);

	void RenderScene();

public:
	float dt = 0.f;
	int fps = 0;

private:
	std::vector<Scene*> scenes;
	Scene* activeScene = nullptr;
};
extern SceneManager* sceneManager;

#endif // !__SCENE_MANAGER_H__