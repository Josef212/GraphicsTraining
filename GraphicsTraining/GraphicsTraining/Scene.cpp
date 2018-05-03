#include "Scene.h"

#include <iostream>

#include <GL/glew.h>

#include "Defs.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "ComplexMaterial.h"
#include "Model.h"
#include "ModelLoader.h"


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

	defaultMaterial = new Material("Default material", new Shader("Defualt shader", "./Data/Shaders/simple.vert", "./Data/Shaders/simple.frag"));
}

void Scene::CleanUp()
{
	std::cout << "\tSCENE: Clean up." << std::endl;
}

void Scene::AddModel(Model * model)
{
	if (model) models.push_back(model);
}

void Scene::RemoveModel(const char * name)
{
	if(name)
	{
		for(auto it = models.begin(); it != models.end();)
		{
			if ((*it)->GetName() == name)
			{
				it = models.erase(it);
			}
			else
			{
				++it;
			}
		}
	}
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

Material * Scene::GetDefaultMaterial() const
{
	return defaultMaterial;
}

void Scene::RenderScene()
{
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(activeCamera)
	{
		for(auto it : models)
		{
			it->Render(this);
		}
	}
}
