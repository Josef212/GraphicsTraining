#include "Editor_MaterialPanel.h"
#include "ImGui/imgui.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Material.h"
#include "ComplexMaterial.h"

#include "Shader.h"

#include "ImGui/imgui.h"


Editor_MaterialPanel::Editor_MaterialPanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_MaterialPanel::~Editor_MaterialPanel()
{
}

void Editor_MaterialPanel::OnInit()
{
}

void Editor_MaterialPanel::Display()
{
	ImGui::Begin(name.c_str(), &show);

	std::vector<Resource*> mats;
	resourceManager->GatherResourceOfType(ResourceType::RES_MATERIAL, mats);

	static int mI = -1;
	int i = 0;
	for (auto it : mats)
	{
		ImGuiTreeNodeFlags flags = 0; // ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
									  //if (gI == i) flags |= ImGuiTreeNodeFlags_Selected;
									  //else flags |=  ImGuiTreeNodeFlags_Leaf;

		Material* mat = static_cast<Material*>(it);
		if (mat)
		{
			if (ImGui::TreeNodeEx(mat->GetNameCStr(), flags))
			{
				if (ImGui::IsItemClicked())  mI = i;
				//if (gI == i)
				MaterialInfo(mat);

				ImGui::TreePop();
			}

			if (it != mats[mats.size() - 1]) ImGui::Separator();
		}

		++i;
	}

	ImGui::End();
}

void Editor_MaterialPanel::MaterialInfo(Material * mat)
{
	ImGui::Text("Shader: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), mat->GetShader()->GetNameCStr());

	ComplexMaterial* cm = dynamic_cast<ComplexMaterial*>(mat);
	if(cm)
	{
		CMaterialInfo(cm);
	}
}

void Editor_MaterialPanel::CMaterialInfo(ComplexMaterial* cmat)
{
	ImGui::Text("Num properties: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", cmat->properties.size());

	for(auto it : cmat->properties)
	{
		if(it)
		{
			ImGui::Text(("\t" + it->propertyName).c_str());
			ImGui::SameLine();
			if (it->propertyType == MAT_INT)
				ImGui::TextColored(ImVec4(0.7, 0.7, 0, 1), "%d", it->propertyValue._int);
			else if (it->propertyType == MAT_FLOAT)
				ImGui::TextColored(ImVec4(0.7, 0.7, 0, 1), "%f", it->propertyValue._float);
			else
				ImGui::TextColored(ImVec4(0.7, 0.7, 0, 1), "...");
		}
	}
}
