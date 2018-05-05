#include "MaterialCreator.h"

#include "ComplexMaterial.h"
#include "Shader.h"

#include "ResourceManager.h"

#include "ImGui/imgui.h"

#define AVAILABLE_SHADERS 64

MaterialCreator::MaterialCreator()
{
}


MaterialCreator::~MaterialCreator()
{
}

void MaterialCreator::OnOpen()
{
}

void MaterialCreator::OnCancel()
{
	tmpName = ""; tmpPropName = "";
	tmpShader = nullptr;

	for (int i = 0; i < tmpMatProperties.size(); ++i)
	{
		RELEASE(tmpMatProperties[i]);
	}

	tmpMatProperties.clear();
}

void MaterialCreator::Render()
{
	ImGui::Begin("Create material", &open);
	{
		// Material name
		static char name[128];
		strcpy_s(name, tmpName.c_str());
		if (ImGui::InputText("Material name", name, 128)) tmpName = name;

		// Material shader
		std::vector<Resource*> shs;
		resourceManager->GatherResourceOfType(RES_SHADER, shs);

		static int shSelected = 0;
		
		const char* shNames[AVAILABLE_SHADERS] = {};
		for(int i = 0; i < shs.size(); ++i)
		{
			if(i < AVAILABLE_SHADERS)
			{
				shNames[i] = shs[i]->GetNameCStr();
			}
		}
		
		if(ImGui::Combo("Shader", &shSelected, shNames, shs.size() <= AVAILABLE_SHADERS ? shs.size() : AVAILABLE_SHADERS))
		{
			tmpShader = static_cast<Shader*>(shs[shSelected]);
		}


		// Material properties

		ImGui::Separator();

		ImGui::TextColored(ImVec4(1, 1, 0, 1), "Material properties");

		static char propName[128];
		strcpy_s(propName, tmpPropName.c_str());
		if (ImGui::InputText("Property name", propName, 128)) tmpPropName = propName;

		ImGui::SameLine();

		static int tySelected = 0;
		const char* propTypeNames[MatPropertyValueType::MAT_NONE + 1] = {
			"INT", "FLOAT", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "TEXTURE", "BOOL", "BOOL_PTR", "NONE"
		};

		ImGui::Combo("Property type", &tySelected, propTypeNames, MatPropertyValueType::MAT_NONE + 1);

		MatPropertyValueType tmpPropType = static_cast<MatPropertyValueType>(tySelected);

		ImGui::Text("Value: "); ImGui::SameLine();

		switch (tmpPropType)
		{
		case MAT_BOOL:
			ImGui::Checkbox("", &tmpPropValue._bool);
			break;

		case MAT_INT:
			ImGui::DragInt("", &tmpPropValue._int);
			break;

		case MAT_FLOAT:
			ImGui::DragFloat("", &tmpPropValue._float);
			break;

			// TODO: Texture, vecs & mats
		}

		if(ImGui::Button("Add property"))
		{
			

			switch (tmpPropType)
			{
			case MAT_BOOL:
				tmpMatProperties.push_back(new MatProperty(tmpPropName.c_str(), tmpPropValue._bool));
				break;

			case MAT_INT:
				tmpMatProperties.push_back(new MatProperty(tmpPropName.c_str(), tmpPropValue._int));
				break;

			case MAT_FLOAT:
				tmpMatProperties.push_back(new MatProperty(tmpPropName.c_str(), tmpPropValue._float));
				break;

				// TODO: Texture, vecs & mats
			}

			tmpPropName = "";
		}

		ImGui::Separator();

		// Existing properties TODO:

		ImGui::Text("Num properties: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", tmpMatProperties.size());

		// Create or cancel

		ImGui::Separator();

		if(ImGui::Button("Create"))
		{
			CreateMaterial();
			open = false;
			shSelected = 0;
			tySelected = 0; 
			tmpName = ""; 
			tmpPropName = "";
			tmpShader = nullptr;
		}

		ImGui::SameLine();

		if(ImGui::Button("Cancel"))
		{
			OnCancel();
			open = false;
			shSelected = 0;
			tySelected = 0;
		}
		
		ImGui::End();
	}
}

bool MaterialCreator::Show() const
{
	return open;
}

void MaterialCreator::Open()
{
	open = true;
}

void MaterialCreator::Close()
{
	OnCancel();
	open = false;
}

void MaterialCreator::CreateMaterial()
{
	ComplexMaterial* mat = new ComplexMaterial(tmpName.c_str(), tmpShader);
	for(auto it : tmpMatProperties)
	{
		mat->AddProperty(it);
	}
	tmpMatProperties.clear();
}
