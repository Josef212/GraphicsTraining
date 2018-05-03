#include "Editor_ModelPanel.h"

#include "Resource.h"
#include "ResourceManager.h"
#include "Model.h"
#include "Geometry.h"
#include "Material.h"

#include "ImGui/imgui.h"

Editor_ModelPanel::Editor_ModelPanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_ModelPanel::~Editor_ModelPanel()
{
}

void Editor_ModelPanel::Display()
{
	ImGui::Begin(name.c_str(), &show);

	std::vector<Resource*> models;
	resourceManager->GatherResourceOfType(ResourceType::RES_MODEL, models);

	static int sMo = 0;
	int i = 0;
	for(auto it : models)
	{
		Model* model = static_cast<Model*>(it);
		if(model)
		{
			ImGuiTreeNodeFlags flags = 0;

			if(ImGui::TreeNodeEx(model->GetNameCStr(), flags))
			{
				if (ImGui::IsItemClicked()) sMo = i;
				//if(sMo == i)
					ModelInfo(model);

				ImGui::TreePop();
			}

			if (it != models[models.size() - 1]) ImGui::Separator();
		}

		++i;
	}

	ImGui::End();
}

void Editor_ModelPanel::ModelInfo(Model * model)
{
	ImGui::Text("Directory: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), model->directory.c_str());

	// TODO: Model matrix

	for(auto it : model->meshes)
	{
		Geometry* geo = it.first;
		Material* mat = it.second;
		
		ImGui::Text("Geometry: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (geo) ? geo->GetNameCStr() : "???");

		ImGui::Text("Material: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (mat) ? mat->GetNameCStr() : "???");
	}
}
