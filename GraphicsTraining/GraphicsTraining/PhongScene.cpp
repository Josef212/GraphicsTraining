#include "PhongScene.h"

#include "Geometry.h"
#include "Model.h"
#include "ComplexMaterial.h"
#include "Shader.h"
#include "ResourceManager.h"

#include "Camera.h"

#include <glm/glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

PhongScene::PhongScene(const char * name) : Scene(name)
{
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
	lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
}

PhongScene::~PhongScene()
{
}

void PhongScene::OnInit()
{
	phong = new ComplexMaterial("Phong", new Shader("Phong shader", "./Data/Shaders/phong.vert", "./Data/Shaders/phong.frag"));

	phong->AddProperty(new MatProperty("objectColor", &objectColor.r, MAT_VEC3));
	phong->AddProperty(new MatProperty("lightColor", &lightColor.r, MAT_VEC3));
	phong->AddProperty(new MatProperty("lightPos", &lightPos.r, MAT_VEC3));
	phong->AddProperty(new MatProperty("viewPos", &GetActiveCamera()->Position.x, MAT_VEC3));

	plane = new Model("Plane", resourceManager->defaultResources.planeGeo, phong);
	cube = new Model("Cube", resourceManager->defaultResources.cubeGeo, phong);
	light = new Model("Light", resourceManager->defaultResources.cubeGeo, resourceManager->defaultResources.simpleMat);

	cube->modelMat = glm::translate(cube->modelMat, glm::vec3(0.f, 0.5f, 0.f));
	light->modelMat = glm::translate(light->modelMat, lightPos);
	light->modelMat = glm::scale(light->modelMat, glm::vec3(0.3f, 0.3f, 0.3f));
}

void PhongScene::OnCleanUp()
{
}

void PhongScene::OnRenderScene()
{
	plane->Render(this);
	cube->Render(this);

	light->Render(this);
}
