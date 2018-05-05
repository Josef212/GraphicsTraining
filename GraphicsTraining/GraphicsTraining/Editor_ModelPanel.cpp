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

	// Transformation

	glm::vec3 t = model->GetTranslation();
	glm::vec3 e = model->GetEuler();
	glm::vec3 s = model->GetScale();

	if (ImGui::DragFloat3("Translation", &t.x, 0.1f)) model->SetTranslation(t);
	if (ImGui::DragFloat3("Rotation", &e.x, 0.1f, -360.f, 360.f)) model->SetEuler(e);
	if (ImGui::DragFloat3("Scale", &s.x, 0.01f)) model->SetScale(s);

	// -----------------------------

	if (ImGui::Button("Select material for all meshes"))
	{
		ImGui::OpenPopup("ChangeAllMaterials");
	}

	if(ImGui::BeginPopup("ChangeAllMaterials"))
	{
		std::vector<Resource*> materials;
		resourceManager->GatherResourceOfType(RES_MATERIAL, materials);

		for (auto it2 : materials)
		{
			if (ImGui::Selectable(it2->GetNameCStr()))
				model->SetMaterial(static_cast<Material*>(it2));
		}

		ImGui::EndPopup();
	}

	for(auto it = model->meshes.begin(); it != model->meshes.end(); ++it)
	{
		Geometry* geo = (*it).first;
		Material* mat = (*it).second;
		
		// Geometry

		ImGui::Text("Geometry: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (geo) ? geo->GetNameCStr() : "???");

		// Select geometry

		if (ImGui::Button("Change geometry"))
		{
			ImGui::OpenPopup("Select geometry");
		}

		// Material

		ImGui::Text("Material: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), (mat) ? mat->GetNameCStr() : "???");

		// Select material

		if(ImGui::Button("Change material"))
		{
			ImGui::OpenPopup("Select material");
		}

		// -----------------------------

		// Geometry popup

		if(ImGui::BeginPopup("Select geometry"))
		{
			std::vector<Resource*> geometries;
			resourceManager->GatherResourceOfType(RES_GEOMETRY, geometries);

			for(auto it2 : geometries)
			{
				if (ImGui::Selectable(it2->GetNameCStr()))
					(*it).first = static_cast<Geometry*>(it2);
			}

			ImGui::EndPopup();
		}

		// Material popup

		if (ImGui::BeginPopup("Select material"))
		{
			std::vector<Resource*> materials;
			resourceManager->GatherResourceOfType(RES_MATERIAL, materials);

			for (auto it2 : materials)
			{
				if (ImGui::Selectable(it2->GetNameCStr()))
					(*it).second = static_cast<Material*>(it2);
			}

			ImGui::EndPopup();
		}

		// --------------

		if (it != model->meshes.end() - 1) ImGui::Separator();
	}
}
