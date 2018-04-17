#include "GuiManager.h"

#include "ThirdParty/ImGui/imgui_impl_glfw_gl3.h"
#include "ThirdParty/ImGui/imgui.h"

#include <iostream>
#include <GLFW/glfw3.h>

#include "EditorPanel.h"
#include "Editor_GeometryPanel.h"
#include "Editor_ShaderPanel.h"


GuiManager::GuiManager()
{
	std::cout << "\tGUI MANAGER: Creation." << std::endl;

	panels.push_back(static_cast<EditorPanel*>(new Editor_GeometryPanel("Geometry")));
	panels.push_back(static_cast<EditorPanel*>(new Editor_ShaderPanel("Shader")));
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
		if (ImGui::MenuItem("Exit")) glfwSetWindowShouldClose(referenceWindow, 1);

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

	ImGui_ImplGlfwGL3_Shutdown();
}
