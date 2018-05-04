#include "SimpleScene.h"

#include <iostream>

#include <GL/glew.h>

#include "Defs.h"
#include "Camera.h"
#include "Shader.h"
#include "Material.h"
#include "ComplexMaterial.h"
#include "Model.h"
#include "ModelLoader.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


SimpleScene::SimpleScene(const char* name) : Scene(name)
{
}


SimpleScene::~SimpleScene()
{
}

void SimpleScene::OnInit()
{;
	defaultMaterial = ResourceManager::defaultResources.simpleMat;

	std::string modelName = "./Data/Models/Boat.fbx";
	Model* m = ModelLoader::LoadModel(modelName, this);
	m->modelMat = glm::scale(m->modelMat, glm::vec3(0.05f));
}

void SimpleScene::OnCleanUp()
{
}

void SimpleScene::RenderScene()
{
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (GetActiveCamera())
	{
		for (auto it : models)
		{
			it->Render(this);
		}
	}
}
