#include "Editor_GeometryPanel.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Geometry.h"

#include "FrameBuffer.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ImGui/imgui.h"

Editor_GeometryPanel::Editor_GeometryPanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_GeometryPanel::~Editor_GeometryPanel()
{
}

void Editor_GeometryPanel::OnInit()
{
	//geoFrameBuffer = new FrameBuffer(512, 512);
	//simpleGeoShader = new Shader("Simple shader for geometry display", "./Data/Shaders/simple.vert", "./Data/Shaders/simple.frag");
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
		ImGuiTreeNodeFlags flags = 0; // ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		//if (gI == i) flags |= ImGuiTreeNodeFlags_Selected;
		//else flags |=  ImGuiTreeNodeFlags_Leaf;

		Geometry* geo = static_cast<Geometry*>(it);
		if(geo)
		{
			if (ImGui::TreeNodeEx(geo->GetNameCStr(), flags))
			{
				if (ImGui::IsItemClicked())  gI = i;
				//if (gI == i)
					GeometryInfo(geo);

				ImGui::TreePop();
			}

			if (it != geos[geos.size() - 1]) ImGui::Separator();
		}

		++i;
	}

	ImGui::End();
}

void Editor_GeometryPanel::GeometryInfo(Geometry * geo)
{
	//ImGui::BeginChild("geos", ImVec2(200, 170));

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
	/*
	ImGui::Separator();

	static glm::vec3 eye = glm::vec3(0.f, 0.f, -1.f);
	static glm::vec3 center = glm::vec3(0.f, 0.f, -1.f);

	ImGui::DragFloat3("Eye", value_ptr(eye));
	ImGui::DragFloat3("Center", value_ptr(center));

	geoFrameBuffer->Bind();

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// ---- Render

	glm::mat4 proj = glm::perspective(glm::radians(70.f), (float)16.f/(float)16.f, 0.1f, 50.f);
	glm::mat4 view = glm::lookAt(eye, center, glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 model = glm::mat4(1.f);

	simpleGeoShader->Use();

	simpleGeoShader->SetMat4("projection", proj);
	simpleGeoShader->SetMat4("view", view);
	simpleGeoShader->SetMat4("model", model);

	glBindVertexArray(geo->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo->IdIndices());
	glDrawElements(GL_TRIANGLES, geo->CountIndices(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	// ----


	geoFrameBuffer->UnBind();

	ImGui::Image(reinterpret_cast<ImTextureID*>(geoFrameBuffer->ColorTexture()), ImVec2(geoFrameBuffer->Width(), geoFrameBuffer->Height()));

	*/
	//ImGui::EndChild();
}
