#include "Editor_GeometryPanel.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Geometry.h"

#include "ImGui/imgui.h"

Editor_GeometryPanel::Editor_GeometryPanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_GeometryPanel::~Editor_GeometryPanel()
{
}

void Editor_GeometryPanel::Display()
{
	ImGui::Begin(name.c_str(), &show);

	std::vector<Resource*> geos;
	resourceManager->GatherResourceOfType(ResourceType::RES_GEOMETRY, geos);

	static int gI = -1;

	int i = 0;
	for(auto it : geos)
	{
		ImGuiTreeNodeFlags flags = 0;
		if (gI == i) flags |= ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		else
			flags |= ImGuiTreeNodeFlags_Leaf;

		Geometry* geo = static_cast<Geometry*>(it);
		if(geo)
		{
			if (ImGui::TreeNodeEx(geo->GetNameCStr(), flags))
			{
				if (ImGui::IsItemClicked())  gI = i;
				if (gI == i) GeometryInfo(geo);

				ImGui::TreePop();
			}
		}

		++i;
	}

	ImGui::End();
}

void Editor_GeometryPanel::GeometryInfo(Geometry * geo)
{
	ImGui::BeginChild("geos", ImVec2(200, 170));

	ImGui::Text("Num vertices: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->CountVertices());

	ImGui::Text("Num indices: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->CountIndices());

	ImGui::Separator();

	// ----

	ImGui::Text("EBO: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->EBO());

	ImGui::Text("Id indices: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->IdIndices());

	ImGui::Text("Id vertices: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->IdVertices());

	ImGui::Text("Id normals: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->IdNormals());

	ImGui::Text("Id uvs: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->IdUvs());

	ImGui::Text("Id colors: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", geo->IdColors());

	// ----

	ImGui::EndChild();
}
