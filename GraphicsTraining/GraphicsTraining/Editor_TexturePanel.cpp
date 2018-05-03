#include "Editor_TexturePanel.h"

#include "ResourceManager.h"
#include "Resource.h"
#include "Texture.h"

#include "ImGui/imgui.h"


Editor_TexturePanel::Editor_TexturePanel(const char* name, bool startEnabled) : EditorPanel(name, startEnabled)
{
}


Editor_TexturePanel::~Editor_TexturePanel()
{
}

void Editor_TexturePanel::Display()
{
	ImGui::Begin(name.c_str(), &show);

	std::vector<Resource*> textures;
	resourceManager->GatherResourceOfType(RES_TEXTURE, textures);

	static int sT = 0;
	int i = 0;
	for(auto it : textures)
	{
		Texture* texture = static_cast<Texture*>(it);
		if(texture)
		{
			ImGuiTreeNodeFlags flags = 0;

			if(ImGui::TreeNodeEx(texture->GetNameCStr(), flags))
			{
				if (ImGui::IsItemClicked()) sT = i;
				//if (sT == i)
					TextureInfo(texture);

				ImGui::TreePop();
			}

			if (it != textures[textures.size() - 1]) ImGui::Separator();
		}

		++i;
	}		

	ImGui::End();
}

void Editor_TexturePanel::TextureInfo(Texture* tex)
{
	ImGui::Text("Path: "); ImGui::SameLine();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), tex->Path());

	ImGui::Text("Size: "); ImGui::Separator();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d x %d", tex->Width(), tex->Height());

	ImGui::Text("Num channels: "); ImGui::Separator();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", tex->NumChannels());

	ImGui::Text("Texture ID: "); ImGui::Separator();
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", tex->TextureID());

	ImGui::Image((ImTextureID)tex->TextureID(), ImVec2(200, 200));
}
