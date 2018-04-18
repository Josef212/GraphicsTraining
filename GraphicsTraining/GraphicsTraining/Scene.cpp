#include "Scene.h"

#include <iostream>

#include <GL/glew.h>

#include "Defs.h"
#include "Camera.h"


Scene::Scene()
{
	std::cout << "\tSCENE: Creation." << std::endl;

	for (int i = 0; i < MAX_CAMERAS; ++i)
		cameras[i] = nullptr;
}


Scene::~Scene()
{
	std::cout << "\tSCENE: Destruction." << std::endl;
}

void Scene::Init()
{
	std::cout << "\tSCENE: Init." << std::endl;
}

void Scene::CleanUp()
{
	std::cout << "\tSCENE: Clean up." << std::endl;
}

void Scene::AddCamera(Camera * cam, int index, bool setAsActive)
{
	if(index >= 0 && index < MAX_CAMERAS)
	{
		cameras[index] = cam;
		if (setAsActive) activeCamera = cam;
	}
}

void Scene::RemoveCamera(int index)
{
	if (index >= 0 && index < MAX_CAMERAS)
	{
		cameras[index] = nullptr;
	}
}

void Scene::SetActiveCamera(int index)
{
	if (index >= 0 && index < MAX_CAMERAS)
	{
		if(cameras[index])
			activeCamera = cameras[index];
	}
}

void Scene::OnResize(int winW, int winH)
{
	viewportWidth = winW; viewportHeight = winH;

	for (int i = 0; i < MAX_CAMERAS; ++i)
		if (cameras[i]) cameras[i]->ResizeViewport(winW, winH);
}
