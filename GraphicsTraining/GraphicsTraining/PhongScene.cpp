#include "PhongScene.h"

#include "Geometry.h"
#include "Model.h"
#include "ComplexMaterial.h"
#include "Shader.h"
#include "ResourceManager.h"

#include "ModelLoader.h"

#include "Camera.h"

#include <glm/glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ImGui/imgui.h>

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

	light = new Model("Light", resourceManager->defaultResources.cubeGeo, resourceManager->defaultResources.simpleMat);
	
	std::string modelName("./Data/Models/Boat.fbx");
	Model* boat = ModelLoader::LoadModel(modelName, this);
	boat->SetMaterial(phong, 0);
	boat->modelMat = glm::scale(boat->modelMat, glm::vec3(0.05f));
}

void PhongScene::OnCleanUp()
{
	Resource* res[] = {
		light
	};

	resourceManager->RemoveResources(res, 1);
}

void PhongScene::OnRenderScene()
{
	light->modelMat = glm::mat4(1.f);
	light->modelMat = glm::translate(light->modelMat, lightPos);
	light->modelMat = glm::scale(light->modelMat, glm::vec3(0.3f, 0.3f, 0.3f));

	for (auto it : models)
	{
		it->Render(this);
	}

	light->Render(this);
}

void PhongScene::OnGui()
{
	ImGui::Separator();

	ImGui::ColorEdit3("Object color", &objectColor.r);
	ImGui::ColorEdit3("Light color", &lightColor.r);
	ImGui::DragFloat3("Light pos", &lightPos.x, 0.05f);

	ImGui::Separator();
}
