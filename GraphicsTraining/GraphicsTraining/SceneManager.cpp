#include "SceneManager.h"

#include <iostream>

#include "Defs.h"

#include "Scene.h"

SceneManager::SceneManager()
{
	std::cout << "\tSCENE MANAGER: Creation." << std::endl;
}


SceneManager::~SceneManager()
{
}

void SceneManager::AddScene(Scene * sc, bool activate)
{
	if (!sc) return;

	scenes.push_back(sc);
	if (activate)
	{
		if(activeScene) activeScene->CleanUp();
		activeScene = sc;
		activeScene->Init();
	}
}

void SceneManager::RemoveScene(Scene * sc)
{
	if (sc)
	{
		for (auto it = scenes.begin(); it != scenes.end();)
		{
			if ((*it) == sc)
			{
				(*it)->CleanUp();
				RELEASE((*it));
				it = scenes.erase(it);
			}
		}
	}
}

void SceneManager::RemoveScene(const char* name)
{
	if (name)
	{
		for (auto it = scenes.begin(); it != scenes.end();)
		{
			if ((*it)->name == name)
			{
				(*it)->CleanUp();
				RELEASE((*it));
				it = scenes.erase(it);
			}
		}
	}
}

void SceneManager::SelectActiveScene(int index)
{
	if(index >= 0 && index < scenes.size())
	{
		activeScene->CleanUp();
		activeScene = scenes[index];
		activeScene->Init();
	}
}

void SceneManager::SelectActiveScene(const char* name)
{
	if(name)
	{
		for(auto it : scenes)
		{
			if(it->name == name)
			{
				activeScene->CleanUp();
				activeScene = it;
				activeScene->Init();
			}
		}
	}
}

void SceneManager::SelectActiveScene(Scene * sc)
{
	auto it = std::find(scenes.begin(), scenes.end(), sc);
	if(it != scenes.end())
	{
		if (activeScene) activeScene->CleanUp();
		activeScene = sc;
		activeScene->Init();
	}
}

Scene * SceneManager::GetActiveScene() const
{
	return activeScene;
}

void SceneManager::OnResize(int w, int h)
{
	for(auto it : scenes)
	{
		it->OnResize(w, h);
	}
}

void SceneManager::ProcessScroll(double yoffset)
{
	if (activeScene) activeScene->ProcessScroll(yoffset);
}

void SceneManager::ProcessMouseMovement(double xoffset, double yoffset)
{
	if (activeScene) activeScene->ProcessMouseMovement(xoffset, yoffset);
}

void SceneManager::ProcessInput(Camera_Movement movement, float dt)
{
	if (activeScene) activeScene->ProcessInput(movement, dt);
}

void SceneManager::SelectCamera(int index)
{
	if (activeScene) activeScene->SetActiveCamera(index);
}

void SceneManager::RenderScene()
{
	if (activeScene) activeScene->RenderScene();
}
