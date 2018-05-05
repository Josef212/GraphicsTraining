#include <iostream>
#include <string>

#include "Defs.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "Geometry.h"
#include "Material.h"
#include "ComplexMaterial.h"
#include "Model.h"
#include "Texture.h"

#include "RenderInfo.h"

#include "ResourceManager.h"
#include "GuiManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SimpleScene.h"
#include "DirLightShadowScene.h"
#include "PhongScene.h"

#include "FrameBuffer.h"
#include "DepthFrameBuffer.h"

#include "ThirdParty/ImGui/imgui_impl_glfw_gl3.h"
#include "ComplexMaterial.h"
#include "ModelLoader.h"

// -------------------------------------------------------------------------------

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void ProcessInput(GLFWwindow* window);

static void ErrorCallback(int error, const char* description);

			//-----

void RenderSimpleGeometry(RenderInfo& info);
void RenderSimpleGeometryWithShadow(RenderInfo& info);
void RenderSceneFromDirectionalLight(RenderInfo& info);
void RenderFrameBuffer(RenderInfo& info);

void RenderIntoFrameBuffer(RenderInfo& info);

void DebugRenderFrmeBuffer(RenderInfo& info);

// -------------------------------------------------------------------------------

int winW = DEFAULT_WIN_WIDTH;
int winH = DEFAULT_WIN_HEIGHT;

float lastX = winW / 2.f;
float lastY = winH / 2.f;
bool firstMouse = true;

bool keys[1024];
bool buttons[7];

bool editorIsUsingMouse = false;
bool editorIsUsingKeyboard = false;

float dt = 0.f;
float lastFrame = 0.f;
int fps = 0;
int fpsCount = 0;
float msCount = 0.f;

ResourceManager* resourceManager = nullptr;
GuiManager* guiManager = nullptr; 
SceneManager* sceneManager = nullptr;

// -------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	glfwSetErrorCallback(ErrorCallback);

	resourceManager = new ResourceManager();
	sceneManager = new SceneManager();
	guiManager = new GuiManager();

	if (!glfwInit()) return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	std::string windowTitle = "OpenGL training: ";
	windowTitle += (std::to_string(winW)) + "x" + (std::to_string(winH));
	GLFWwindow* window = glfwCreateWindow(winW, winH, windowTitle.c_str(), NULL, NULL);
	if(!window)
	{
		std::cout << "Failed to create window." << std::endl;
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	GLenum error = glewInit();
	if(error != GLEW_OK)
	{
		std::cout << "Failed to init GLEW: " << glewGetErrorString(error) << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, winW, winH);

	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	glfwMaximizeWindow(window);
	
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	resourceManager->Init();
	guiManager->Init(window);


	// ==============================================
	// Init geometry, materials, cameras, shaders, scene, etc.

	FrameBuffer frameBuffer(winW, winH);
	DepthFrameBuffer shadowMapBuffer;
	shadowMapBuffer.Create(1024, 1024);

	SimpleScene* scene = new SimpleScene("simple");
	PerspectiveCamera camera;
	PerspectiveCamera camera2(glm::vec3(0.f, 2.f, 5.f));
	scene->AddCamera(&camera, 0, true);
	scene->AddCamera(&camera2, 1);

	DirLightShadowScene* dlsScene = new DirLightShadowScene("Directional light shadow scene");
	dlsScene->AddCamera(&camera, 0, true);
	dlsScene->AddCamera(&camera2, 1);

	PhongScene* phongScene = new PhongScene("Phong scene");
	phongScene->AddCamera(&camera, 0, true);
	phongScene->AddCamera(&camera2, 1);

	sceneManager->AddScene(scene, true);
	sceneManager->AddScene(dlsScene);
	sceneManager->AddScene(phongScene);

	/*Shader* simpleSh = new Shader("Simple shader", "./Data/Shaders/simple.vert", "./Data/Shaders/simple.frag");
	Shader* framebufferRenderSh = new Shader("Frame buffer render", "./Data/Shaders/render_framebuffer.vert", "./Data/Shaders/render_framebuffer.frag");
	Shader* renderDepthBufferSh = new Shader("Render depth buffer shader", "./Data/Shaders/render_depth.vert", "./Data/Shaders/render_depth.frag");
	Shader* simpleBillboardTextureSh = new Shader("Simple billboard texture shader", "./Data/Shaders/simple_billboard_texture.vert", "./Data/Shaders/simple_billboard_texture.frag");
	Shader* simpleShadowSceneSh = new Shader("Simple shadow scene shader", "./Data/Shaders/simple_shadow_scene.vert", "./Data/Shaders/simple_shadow_scene.frag");

	Geometry* simpleCube = new Geometry("Cube geometry", cubeVerticesCount, cubeIndicesCount, cubeIndices, cubeVertices, cubeNormals, cubeTexCoords, cubeColors);
	Geometry* simplePlane = new Geometry("Plane geometry", planeVerticesCount, planeIndicesCount, planeIndices, planeVertices, planeNormals, planeTexCoords, planeColors);

	Geometry* quadToShowTexture = new Geometry("Quad geometry", quadVerticesCount, quadIndicesCount, quadIndices, quadVertices, quadNormals, quadTexCoords, quadColors);
		*/
	// ==============================================

	while(!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		sceneManager->dt = dt;
		lastFrame = currentFrame;

		msCount += dt;
		++fpsCount;

		if(msCount >= 1.f)
		{
			msCount = 0.f;
			fps = fpsCount;
			sceneManager->fps = fps;
			fpsCount = 0;
		}

		// ---------------

		glfwPollEvents();
		guiManager->StartFrame(editorIsUsingMouse, editorIsUsingKeyboard);
		ProcessInput(window);

		// ---------------

		//frameBuffer.Bind();
		//glClearColor(.3f, .3f, .3f, 1.f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glEnable(GL_DEPTH_TEST);
		
		// Render
		/*
		RenderInfo info;
		info.ResetModel();

		Camera* cam = scene->GetActiveCamera();

		glm::mat4 proj = cam->GetProjectionMatrix();
		glm::mat4 view = cam->GetViewMatrix();
		glm::mat4 model = glm::mat4(1.f);


		// ==========================================================================
		// Calc shadows

		float nearPlane = 1.0f, farPlane = 20.0f;
		glm::vec3 lightPos = glm::vec3(-2.f, 4.f, -1.f);

		glm::mat4 lightProjection = glm::ortho(-15.f, 15.f, -15.f, 15.f, nearPlane, farPlane);
		
		glm::vec3 lPos = cam->Position + lightPos;
		glm::mat4 lightView = glm::lookAt(lPos,
			cam->Position,//glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 1.f, 0.f));

		glm::mat4 lightSpaceMatrix = lightProjection * lightView;

		info.lightSpaceMatrix = lightSpaceMatrix;
		info.lightPos = lightPos;

		info.depthFrameBuffer = &shadowMapBuffer;
		info.shader = renderDepthBufferSh;

		glViewport(0, 0, shadowMapBuffer.Width(), shadowMapBuffer.Height());
		shadowMapBuffer.Bind();
		glClear(GL_DEPTH_BUFFER_BIT);
		glCullFace(GL_FRONT);

		// Render plane -------------
		
		model = glm::scale(model, glm::vec3(10.f, 1.f, 10.f));

		info.model = model;
		info.geometry = simplePlane;
		
		RenderSceneFromDirectionalLight(info);

		// --------------------------

		// Render cubes --------------

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.f, 0.5f, 0.f));

		info.model = model;
		info.geometry = simpleCube;

		RenderSceneFromDirectionalLight(info);

		// ---

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.3f, 1.5f, -1.3f));

		info.model = model;

		RenderSceneFromDirectionalLight(info);

		// ---

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-6.0f, .5f, -7.0f));
		model = glm::scale(model, glm::vec3(0.7f, 1.f, 0.7f));

		info.model = model;

		RenderSceneFromDirectionalLight(info);

		// -------------------

		// ==========================================================================
		// Render the actual scene

		//frameBuffer.UnBind();
		//glClearColor(.1f, .1f, .1f, 1.f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glCullFace(GL_BACK);

		shadowMapBuffer.UnBind();
		glViewport(0, 0, winW, winH);

		// Render plane -------------

		model = glm::mat4(1.f);
		model = glm::scale(model, glm::vec3(10.f, 1.f, 10.f));

		info.SetMatrices(proj, view, model);
		info.shader = simpleShadowSceneSh;
		info.geometry = simplePlane;

		RenderSimpleGeometryWithShadow(info);

		// --------------------------

		// Render cube --------------

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.f, 0.5f, 0.f));

		info.model = model;
		info.geometry = simpleCube;

		RenderSimpleGeometryWithShadow(info);

		// ---

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.3f, 1.5f, -1.3f));

		info.model = model;

		RenderSimpleGeometryWithShadow(info);

		// ---

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-6.0f, .5f, -7.0f));
		model = glm::scale(model, glm::vec3(0.7f, 1.f, 0.7f));

		info.model = model;

		RenderSimpleGeometryWithShadow(info);

		// -------------------


		// Render the debug quad with shadow map --------- 

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.f, 3.f, 0.f));

		info.SetMatrices(proj, view, model);
		info.shader = simpleBillboardTextureSh;
		info.geometry = quadToShowTexture;
		info.depthFrameBuffer = &shadowMapBuffer;

		DebugRenderFrmeBuffer(info);
		*/
		// -------------------------

		sceneManager->RenderScene();
		guiManager->Render();

		// ---------------------------

		guiManager->EndFrame();

		glfwSwapBuffers(window);
	}

	guiManager->CleanUp();
	sceneManager->CleanUp();

	glfwTerminate();

	RELEASE(guiManager);
	RELEASE(sceneManager);
	RELEASE(resourceManager);

	if(DEBUG_LOG) system("PAUSE");

	return 0;
}

// -------------------------------------------------------------------------------

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	winW = width; winH = height;
	glViewport(0, 0, width, height);
	
	std::string windowTitle = "OpenGL training: ";
	windowTitle += (std::to_string(winW) + "x" + std::to_string(winH));
	glfwSetWindowTitle(window, windowTitle.c_str());


	sceneManager->OnResize(winW, winH);
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	if (action == GLFW_PRESS && !editorIsUsingKeyboard)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;

	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mode);
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (!editorIsUsingMouse)
		sceneManager->ProcessScroll(yoffset);

	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	
	lastX = xpos;
	lastY = ypos;
	
	if (buttons[GLFW_MOUSE_BUTTON_LEFT] && !editorIsUsingMouse)
		sceneManager->ProcessMouseMovement(xoffset, yoffset);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		buttons[button] = true;
	else
		buttons[button] = false;

	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void ProcessInput(GLFWwindow* window)
{
	if (sceneManager)
	{
		float _dt = keys[GLFW_KEY_LEFT_SHIFT] ? dt * 2.f : dt;

		if (keys[GLFW_KEY_W]) //w
			sceneManager->ProcessInput(FORWARD, _dt);
		if (keys[GLFW_KEY_S]) //s
			sceneManager->ProcessInput(BACKWARD, _dt);
		if (keys[GLFW_KEY_A]) //a
			sceneManager->ProcessInput(LEFT, _dt);
		if (keys[GLFW_KEY_D]) //d
			sceneManager->ProcessInput(RIGHT, _dt);
		if (keys[GLFW_KEY_Q]) //q
			sceneManager->ProcessInput(UP, _dt);
		if (keys[GLFW_KEY_E]) //e
			sceneManager->ProcessInput(DOWN, _dt);
	}
	
	if (keys[GLFW_KEY_1])
		sceneManager->SelectCamera(0);
	if (keys[GLFW_KEY_2])
		sceneManager->SelectCamera(1);
	if (keys[GLFW_KEY_3])
		sceneManager->SelectCamera(2);
	if (keys[GLFW_KEY_4])
		sceneManager->SelectCamera(3);
	if (keys[GLFW_KEY_5])
		sceneManager->SelectCamera(4);
	if (keys[GLFW_KEY_6])
		sceneManager->SelectCamera(5);
	if (keys[GLFW_KEY_7])
		sceneManager->SelectCamera(6);
	if (keys[GLFW_KEY_8])
		sceneManager->SelectCamera(7);
	if (keys[GLFW_KEY_9])
		sceneManager->SelectCamera(8);

}

static void ErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Error %d: %s\n", error, description);
}

		// -------------------------------

void RenderSimpleGeometry(RenderInfo& info)
{
	info.shader->Use();

	info.shader->SetMat4("projection", info.projection);
	info.shader->SetMat4("view", info.view);
	info.shader->SetMat4("model", info.model);

	glBindVertexArray(info.geometry->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.geometry->IdIndices());
	glDrawElements(GL_TRIANGLES, info.geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void RenderSimpleGeometryWithShadow(RenderInfo& info)
{
	info.shader->Use();

	info.shader->SetMat4("projection", info.projection);
	info.shader->SetMat4("view", info.view);
	info.shader->SetMat4("model", info.model);

	info.shader->SetVec3("viewPos", sceneManager->GetActiveScene()->GetActiveCamera()->Position);
	info.shader->SetVec3("lightPos", info.lightPos);
	info.shader->SetMat4("lightSpaceMatrix", info.lightSpaceMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, info.depthFrameBuffer->DepthMapTex());

	glBindVertexArray(info.geometry->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.geometry->IdIndices());
	glDrawElements(GL_TRIANGLES, info.geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

// Calcs the shadows by rendering the scene from light position
void RenderSceneFromDirectionalLight(RenderInfo& info)
{

	info.shader->Use();

	info.shader->SetMat4("lightSpaceMatrix", info.lightSpaceMatrix);
	info.shader->SetMat4("model", info.model);

	glBindVertexArray(info.geometry->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.geometry->IdIndices());
	glDrawElements(GL_TRIANGLES, info.geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

// Render the framebuffer for debugging purposes.
void RenderFrameBuffer(RenderInfo& info)
{
	info.shader->Use();

	//info.shader->SetMat4("projection", info.projection);
	//info.shader->SetMat4("view", info.view);
	//info.shader->SetMat4("model", info.model);

	info.shader->SetInt("screenTexture", 0);
	
	glBindVertexArray(info.geometry->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.geometry->IdIndices());

	glBindTexture(GL_TEXTURE_2D, info.frameBuffer->ColorTexture());

	glDrawElements(GL_TRIANGLES, info.geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void RenderIntoFrameBuffer(RenderInfo& info)
{
	info.shader->Use();

	info.shader->SetMat4("projection", info.projection);
	info.shader->SetMat4("view", info.view);
	info.shader->SetMat4("model", info.model);

	glBindVertexArray(info.geometry->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.geometry->IdIndices());
	glDrawElements(GL_TRIANGLES, info.geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

void DebugRenderFrmeBuffer(RenderInfo& info)
{
	info.shader->Use();

	glm::mat4 modelView = info.view * info.model;

	modelView[0][0] = 1.0;
	modelView[0][1] = 0.0;
	modelView[0][2] = 0.0;

	modelView[1][0] = 0.0;
	modelView[1][1] = 1.0;
	modelView[1][2] = 0.0;

	modelView[2][0] = 0.0;
	modelView[2][1] = 0.0;
	modelView[2][2] = 1.0;

	info.shader->SetMat4("projection", info.projection);
	info.shader->SetMat4("model_view", modelView);

	info.shader->SetInt("shadow_texture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, info.depthFrameBuffer->DepthMapTex());

	glBindVertexArray(info.geometry->EBO());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.geometry->IdIndices());
	glDrawElements(GL_TRIANGLES, info.geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

	glUseProgram(0);
}