#include "AdvancedPhongScene.h"

#include "Geometry.h"
#include "Model.h"
#include "PhongMaterial.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"

#include "ModelLoader.h"

#include "Camera.h"

#include <glm/glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ImGui/imgui.h>


AdvancedPhongScene::AdvancedPhongScene(const char* name) : Scene(name)
{
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	lightPos = glm::vec3(1.2f, 1.f, 2.f);
	objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
}


AdvancedPhongScene::~AdvancedPhongScene()
{
}

void AdvancedPhongScene::OnInit()
{
	Texture* colorTexture = new Texture("Bricks");
	Texture* normalMapTexture = new Texture("Bricks normal");

	Texture* colorTexture2 = new Texture("Bricks2");
	Texture* normalMapTexture2 = new Texture("Bricks2 normal");

	colorTexture2->LoadTexture("./Data/Textures/bricks2.jpg");
	normalMapTexture2->LoadTexture("./Data/Textures/bricks2_normal.jpg");

	colorTexture->LoadTexture("./Data/Textures/brickwall.jpg");
	normalMapTexture->LoadTexture("./Data/Textures/brickwall_normal.jpg");

	phong = new PhongMaterial("Advanced phong", new Shader("Advanced phong shader", "./Data/Shaders/advanced-phong.vert", "./Data/Shaders/advanced-phong.frag"));

	phong->lightPos = &lightPos;
	phong->color = objectColor;
	phong->lightColor = &lightColor;

	phong->viewPos = &GetActiveCamera()->Position;

	phong->colorTexture = colorTexture;
	phong->normalMap = normalMapTexture;

	defaultMaterial = phong;

	light = new Model("Light", resourceManager->defaultResources.cubeGeo, resourceManager->defaultResources.simpleMat);

	Model* quad = new Model("Phong quad", resourceManager->defaultResources.quadGeo, phong);
	AddModel(quad);
	quad->SetEuler(glm::vec3(0.f, 180.f, 0.f));

}

void AdvancedPhongScene::OnCleanUp()
{
	Resource* res[] = {
		light
	};

	resourceManager->RemoveResources(res, 1);
}

void AdvancedPhongScene::OnActiveCameraChanged()
{
	if (!phong) return;

	phong->viewPos = &GetActiveCamera()->Position;
}

void AdvancedPhongScene::OnRenderScene()
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

void AdvancedPhongScene::OnGui()
{
	ImGui::Separator();

	ImGui::Checkbox("Use texture", &phong->useTexture); ImGui::SameLine();
	ImGui::Checkbox("Use normal map", &phong->useNormalMap); ImGui::SameLine();
	ImGui::Checkbox("Blinn", &phong->blinn);

	ImGui::ColorEdit3("Object color", &phong->color.r);
	ImGui::ColorEdit3("Light color", &lightColor.r);
	ImGui::DragFloat3("Light pos", &lightPos.x, 0.05f);

	ImGui::Separator();
}
