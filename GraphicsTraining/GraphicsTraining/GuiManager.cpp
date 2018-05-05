#include "GuiManager.h"

#include "Defs.h"

#include "ThirdParty/ImGui/imgui_impl_glfw_gl3.h"
#include "ThirdParty/ImGui/imgui.h"

#include <iostream>

#include "EditorPanel.h"
#include "Editor_GeometryPanel.h"
#include "Editor_ShaderPanel.h"
#include "Editor_MaterialPanel.h"
#include "Editor_ModelPanel.h"
#include "Editor_TexturePanel.h"
#include "Editor_ScenePanel.h"

#include "Scene.h"
#include "SceneManager.h"


GuiManager::GuiManager()
{
	std::cout << "\tGUI MANAGER: Creation." << std::endl;

	panels.push_back(static_cast<EditorPanel*>(new Editor_GeometryPanel("Geometry")));
	panels.push_back(static_cast<EditorPanel*>(new Editor_ShaderPanel("Shader")));
	panels.push_back(static_cast<EditorPanel*>(new Editor_MaterialPanel("Material")));
	panels.push_back(static_cast<EditorPanel*>(new Editor_ModelPanel("Model")));
	panels.push_back(static_cast<EditorPanel*>(new Editor_TexturePanel("Texture")));
	panels.push_back(static_cast<EditorPanel*>(new Editor_ScenePanel("Scene", true)));
}


GuiManager::~GuiManager()
{
	std::cout << "\tGUI MANAGER: Destruction." << std::endl;
}

void GuiManager::Init(GLFWwindow * window)
{
	std::cout << "\tGUI MANAGER: Init." << std::endl;

	referenceWindow = window;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, false);
	ImGui::StyleColorsDark();

	for(auto it : panels)
	{
		it->OnInit();
	}
}

void GuiManager::StartFrame(bool & editorUseMouse, bool & editorUseKeyboard)
{
	ImGui_ImplGlfwGL3_NewFrame();

	ImGuiIO& io = ImGui::GetIO();
	editorUseMouse = io.WantCaptureMouse;
	editorUseKeyboard = io.WantCaptureKeyboard;
}

void GuiManager::Render()
{
	ImGui::BeginMainMenuBar();

	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("ImGui example", nullptr, showImGuiExmple)) showImGuiExmple = !showImGuiExmple;
		//if (ImGui::MenuItem("Exit")) glfwSetWindowShouldClose(referenceWindow, 1);

		ImGui::EndMenu();
	}

	if(ImGui::BeginMenu("Windows"))
	{
		for(auto it : panels)
		{
			if (ImGui::MenuItem(it->name.c_str(), nullptr, it->Visible())) it->SwapShow();
		}

		ImGui::EndMenu();
	}

	for (auto it : panels)
	{
		if (it->Visible()) it->Display();
	}

	ImGuiWindowFlags floatingWindowFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

	ImGui::SetNextWindowPos(ImVec2(5.f, 25.f));
	ImGui::Begin("Active scene", nullptr, floatingWindowFlags);
	{
		ImGui::Text("FPS: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d", sceneManager->fps);

		ImGui::SameLine();

		ImGui::Text("Dt: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.3f", sceneManager->dt);

		Scene* as = sceneManager->GetActiveScene();
		ImGui::Text("Active scene: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), as ? as->name.c_str() : "none");

		ImGui::Text("Number of models: "); ImGui::SameLine();
		ImGui::TextColored(ImVec4(1, 1, 0, 1), std::to_string(as ? as->models.size() : 0).c_str());

		ImGui::Separator();

		if (ImGui::Button("Reload")) 
			sceneManager->SelectActiveScene(as);

	}
	ImGui::End();

	ImGui::EndMainMenuBar();

	if (showImGuiExmple) ImGui::ShowDemoWindow(&showImGuiExmple);
}

void GuiManager::EndFrame()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::CleanUp()
{
	std::cout << "\tGUI MANAGER: Clean up." << std::endl;

	for(auto it : panels)
	{
		RELEASE(it);
	}

	ImGui_ImplGlfwGL3_Shutdown();
}
