#include "Editor_ScenePanel.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Model.h"

#include "ImGui/imgui.h"

Editor_ScenePanel::Editor_ScenePanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_ScenePanel::~Editor_ScenePanel()
{
}

void Editor_ScenePanel::Display()
{
	ImGui::Begin(name.c_str(), &show);

	Scene* as = sceneManager->GetActiveScene();

	if(as)
	{
		ImGui::Text("Active scene: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), as->name.c_str());

		ImGui::ColorEdit4("Background color", &as->backgroundColor.r);

		ImGui::Separator();

		// Transformation

		for(auto model : as->models)
		{
			glm::vec3 t = model->GetTranslation();
			glm::vec3 e = model->GetEuler();
			glm::vec3 s = model->GetScale();

			if (ImGui::DragFloat3("Translation", &t.x, 0.1f)) model->SetTranslation(t);
			if (ImGui::DragFloat3("Rotation", &e.x, 0.1f, -360.f, 360.f)) model->SetEuler(e);
			if (ImGui::DragFloat3("Scale", &s.x, 0.01f)) model->SetScale(s);

			if(ImGui::Button("Reset transform"))
			{
				model->SetScale(glm::vec3(1.f));
				model->SetEuler(glm::vec3(0.f));
				model->SetTranslation(glm::vec3(0.f));
			}
		}

		ImGui::Separator();

		as->OnGui();

		if(ImGui::CollapsingHeader("Active camera"))
		{
			Camera* cam = as->GetActiveCamera();

			if(cam)
			{
				Camera_Type cType = cam->GetCameraType();
				ImGui::Text("Camera type: "); ImGui::SameLine();
				if (cType == Camera_Type::CAM_PERSPECTIVE)
				{
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "PERSPECTIVE");
					float f = cam->GetZFar();
					if (ImGui::DragFloat("Z Far", &f, 0.1f, 0.1f, 10000.f))
						cam->SetZFar(f);

					float n = cam->GetZNear();
					if (ImGui::DragFloat("Z Near", &n, 0.1f, 0.1f, 10000.f))
						cam->SetZNear(n);
				}
				else if (cType == Camera_Type::CAM_ORTHOGRAPHIC)
				{
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "ORTHOGRAPHICS");

					float s = cam->GetSize();
					if (ImGui::DragFloat("Size", &s, 0.1f))
						cam->SetSize(s);
				}
				else
				{
					ImGui::TextColored(ImVec4(1, 1, 0, 1), "UNDEFINED");
				}
			}
		}
	}

	static int sS = 0;
	for(int i = 0; i < sceneManager->scenes.size(); ++i)
	{
		Scene* sc = sceneManager->scenes[i];
		if(sc)
		{
			ImGuiTreeNodeFlags flags = 0;

			if (ImGui::TreeNodeEx(sc->name.c_str(), flags))
			{
				if (ImGui::IsItemClicked()) sS = i;
				//if (sS == i)
					SceneInfo(sc, i);

				ImGui::TreePop();
			}

			if (i < sceneManager->scenes.size() - 1) ImGui::Separator();
		}
	}

	ImGui::End();
}

void Editor_ScenePanel::SceneInfo(Scene * sc, int index)
{
	bool isActive = sc == sceneManager->GetActiveScene();

	if(isActive)
	{
		ImGui::TextColored(ImVec4(1, 0, 0, 1), "This is active scene");
	}

	ImGui::Text("Scene name: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), sc->name.c_str());

	if (ImGui::Button(isActive ? "Reload" : "Load")) sceneManager->SelectActiveScene(index);
}
