#include "PBRScene.h"

#include "Geometry.h"
#include "Model.h"
#include "PBRMaterial.h"
#include "Shader.h"
#include "Texture.h"
#include "ResourceManager.h"

#include "ModelLoader.h"

#include "Camera.h"

#include <glm/glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <ImGui/imgui.h>
#include "SceneManager.h"


PBRScene::PBRScene(const char* name) : Scene(name)
{
	lightPositions.push_back(glm::vec3(-10.f, 10.f, 10.f));
	lightPositions.push_back(glm::vec3(10.f, 10.f, 10.f));
	lightPositions.push_back(glm::vec3(-10.f, -10.f, 10.f));
	lightPositions.push_back(glm::vec3(10.f, -10.f, 10.f));

	lightColors.push_back(glm::vec3(300.f, 300.f, 300.f));
	lightColors.push_back(glm::vec3(300.f, 300.f, 300.f));
	lightColors.push_back(glm::vec3(300.f, 300.f, 300.f));
	lightColors.push_back(glm::vec3(300.f, 300.f, 300.f));

	modelName = "./Data/Models/Boat.fbx";
}


PBRScene::~PBRScene()
{
}

void PBRScene::OnInit()
{
	pbr = new PBRMaterial("PBR material", new Shader("PBR shader", "./Data/Shaders/pbr.vert", "./Data/Shaders/pbr.frag"));

	pbr->camPos = &GetActiveCamera()->Position;
	pbr->lightCount = &lightsCount;
	pbr->lightPositions = &lightPositions;
	pbr->lightColors = &lightColors;

	pbr->albedoColor = glm::vec3(0.5f, 0.0f, 0.0f);
	pbr->metallicValue = 0.5f;
	pbr->roughnessValue = 0.5f;
	pbr->aoValue = 1.0f;

	pbr->opacityValue = 1.f;

	Texture* albedo = new Texture("PBR albedo");
	Texture* normal = new Texture("PBR normal");
	Texture* metallic = new Texture("PBR metallic");
	Texture* roughness = new Texture("PBR roughness");
	Texture* ao = new Texture("PBR ao");
	Texture* opacity = new Texture("PBR opacity");

	//albedo->LoadTexture		("./Data/Textures/rusted_iron/albedo.png");
	//normal->LoadTexture		("./Data/Textures/rusted_iron/normal.png");
	//metallic->LoadTexture		("./Data/Textures/rusted_iron/metallic.png");
	//roughness->LoadTexture	("./Data/Textures/rusted_iron/roughness.png");
	//ao->LoadTexture			("./Data/Textures/rusted_iron/ao.png");

	albedo->LoadTexture		("./Data/Models/Lantern/textures/lantern_Base_Color.jpg");
	normal->LoadTexture		("./Data/Models/Lantern/textures/lantern_Normal_OpenGL.jpg");
	metallic->LoadTexture	("./Data/Models/Lantern/textures/lantern_Metallic.jpg");
	roughness->LoadTexture	("./Data/Models/Lantern/textures/lantern_Roughness.jpg");
	ao->LoadTexture			("./Data/Models/Lantern/textures/lantern_Mixed_AO.jpg");
	opacity->LoadTexture	("./Data/Models/Lantern/textures/lantern_Opacity.jpg");

	//albedo->LoadTexture		("./Data/Models/Dagger/Textures/Raw_Textures//DefaultMaterial_Base_Color.png");
	//normal->LoadTexture		("./Data/Models/Dagger/Textures/Raw_Textures///DefaultMaterial_Normal_DirectX.png");
	//metallic->LoadTexture("./Data/Models/Dagger/Textures/Raw_Textures/DefaultMaterial_Metallic.png");
	//roughness->LoadTexture("./Data/Models/Dagger/Textures/Raw_Textures/DefaultMaterial_Roughness.png");
	//ao->LoadTexture			("./Data/Models/Dagger/Textures/lantern_Mixed_AO.png");

	pbr->albedoMap = albedo;
	pbr->normalMap = normal;
	pbr->metallicMap = metallic;
	pbr->roughnessMap = roughness;
	pbr->aoMap = ao;

	pbr->opacityTexture = opacity;

	defaultMaterial = pbr;

	modelName = "./Data/Models/Lantern/lantern_obj.obj";
	//modelName = "./Data/Models/Dagger/Model/FBX(recommended)/Dagger.fbx";

	if (!modelName.empty())
	{
		model = ModelLoader::LoadModel(modelName, this);
		if(model) model->SetScale(glm::vec3(0.05f));
	}
}

void PBRScene::OnCleanUp()
{
}

void PBRScene::OnActiveCameraChanged()
{
	if (!pbr) return;

	pbr->camPos = &GetActiveCamera()->Position;
}

void PBRScene::OnRenderScene()
{
	glm::vec3 rot = model->GetEuler();
	rot += sceneManager->dt * rotationSpeed;
	rot.x = CLAMP_ROT_ROUND(rot.x);
	rot.y = CLAMP_ROT_ROUND(rot.y);
	rot.z = CLAMP_ROT_ROUND(rot.z);
	model->SetEuler(rot);

	for (auto it : models)
	{
		it->Render(this);
	}
}

void PBRScene::OnGui()
{
	ImGui::Separator();

	ImGui::DragFloat3("Rotation speed", &rotationSpeed.x);

	ImGui::Separator();
}
