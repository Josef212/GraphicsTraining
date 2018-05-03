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

	if(ImGui::Button("Load"))
	{
		if (t) delete t;

		t = new Texture("ss");
		t->LoadTexture("./Data/Textures/container.jpg");
	}

	if(t)
		ImGui::Image((ImTextureID)t->TextureID(), ImVec2(300, 300));

	ImGui::End();
}
