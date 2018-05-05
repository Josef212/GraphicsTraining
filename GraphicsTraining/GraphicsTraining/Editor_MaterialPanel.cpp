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

	if (editingMat) EditMaterialWindow();
}

void Editor_MaterialPanel::MaterialInfo(Material * mat)
{
	ImGui::Text("Shader: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), mat->GetShader() ? mat->GetShader()->GetNameCStr() : "none");

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
		}
	}

	if (ImGui::Button("Edit"))
	{
		editingMat = true;
		editingMaterial = cmat;
	}
}

void Editor_MaterialPanel::EditMaterialWindow()
{
	ImGui::Begin("Material editor", &editingMat);

	if(editingMaterial)
	{
		std::vector<MatProperty*> propertiesToRemove;

		for (auto it : editingMaterial->properties)
		{
			if (it)
			{
				ImGui::Text(it->propertyName.c_str());
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(0.7, 0.7, 0, 1), GetMatPropertyValueTypeStr(it->propertyType));

				ImGui::SameLine();

				if(ImGui::Button(("Remove " + it->propertyName).c_str()))
				{
					propertiesToRemove.push_back(it);
				}

				// Edit the property
				switch (it->propertyType)
				{
				case MAT_BOOL:
					ImGui::Checkbox(it->propertyName.c_str(), &it->propertyValue._bool);
					break;

				case MAT_INT:
					ImGui::DragInt(it->propertyName.c_str(), &it->propertyValue._int);
					break;

				case MAT_FLOAT:
					ImGui::DragFloat(it->propertyName.c_str(), &it->propertyValue._float);
					break;

				case MAT_VEC2:
					ImGui::DragFloat2(it->propertyName.c_str(), it->propertyValue._floatPtr);
					break;

				case MAT_VEC3:
					ImGui::DragFloat3(it->propertyName.c_str(), it->propertyValue._floatPtr);
					break;

				case MAT_VEC4:
					ImGui::DragFloat4(it->propertyName.c_str(), it->propertyValue._floatPtr);
					break;

					// TODO: Matrices & texture
				}

				if (it != (*(editingMaterial->properties.end() - 1))) ImGui::Separator();
			}
		}

		// TODO: Add properties
		/*static int selected = -1; const char* types[] = {
			"INT", "FLOAT", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "TEXTURE", "BOOL"
		};

		ImGui::TextColored(ImVec4(1, 0, 0, 1), selected == -1 ? "none" : types[selected]);

		if(ImGui::Button("Add property"))
		{
			selected = -1;
			ImGui::OpenPopup("prop type");
		}

		if(ImGui::BeginPopup("prop type"))
		{
			for(int i = 0; i < IM_ARRAYSIZE(types); ++i)
			{
				if(ImGui::Selectable(types[i]))
				{
					selected = i;
					editingMaterial->AddProperty(new MatProperty())
				}
			}



			ImGui::EndPopup();
		}*/

		for(auto it : propertiesToRemove)
		{
			editingMaterial->RemoveProperty(it);
		}
	}

	ImGui::End();
}
