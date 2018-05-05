#include "Editor_ShaderPanel.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Shader.h"

#include "ImGui/imgui.h"

#define COMPILED_COLOR ImVec4(0, 1, 0, 1)
#define ERROR_COLOR ImVec4(1, 0, 0, 1)
#define PENDING_COLOR ImVec4(1, 1, 0, 1)


Editor_ShaderPanel::Editor_ShaderPanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_ShaderPanel::~Editor_ShaderPanel()
{
}

void Editor_ShaderPanel::Display()
{
	ImGui::Begin(name.c_str(), &show);

	std::vector<Resource*> shs;
	resourceManager->GatherResourceOfType(ResourceType::RES_SHADER, shs);

	static int sI = 0;

	int i = 0;
	for (auto it : shs)
	{
		Shader* sh = static_cast<Shader*>(it);
		if (sh)
		{
			ImGuiTreeNodeFlags flags = 0;
			//if (sI == i) flags |= ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow | //ImGuiTreeNodeFlags_OpenOnDoubleClick;
			//else
			//	flags |= ImGuiTreeNodeFlags_Leaf;
			
			if (ImGui::TreeNodeEx(sh->GetNameCStr(), flags))
			{
				if (ImGui::IsItemClicked())  sI = i;
				//if(sI == i) 
					ShaderInfo(sh);

				ImGui::TreePop();
			}

			if (it != shs[shs.size() - 1]) ImGui::Separator();
		}

		++i;
	}

	ImGui::End();
}

void Editor_ShaderPanel::ShaderInfo(Shader * sh)
{
	//ImGui::BeginChild("geos", ImVec2(400, 100));

	ImGui::Text("STATUS: "); ImGui::SameLine();
	switch (sh->GetStatus())
	{
	case Shader_Status::SH_COMPILED: ImGui::TextColored(COMPILED_COLOR, "COMPILED");
		break;
	case Shader_Status::SH_ERROR: ImGui::TextColored(ERROR_COLOR, "ERROR");
		break;
	case Shader_Status::SH_PENDING: ImGui::TextColored(PENDING_COLOR, "PENDING");
		break;
	}

	ImGui::Text("Program ID: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), "%d", sh->ID);

	ImGui::Separator();

	ImGui::Text("Vertex path: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), sh->vertPath.c_str());
	
	ImGui::Text("Fragment path: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), sh->fragPath.c_str());

	ImGui::Text("Geometry path: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.f, 1.f, 0.f, 1.f), sh->geoPath.c_str());

	if (ImGui::Button("Compile")) sh->ReloadShader();

	ImGui::SameLine();

	if (ImGui::Button("Log code")) sh->LogCode();

	//ImGui::EndChild();
}
