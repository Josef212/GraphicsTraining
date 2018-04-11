#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Shader.h"
#include "Geometry.h"
#include "GeometryDefs.h"
#include "RenderInfo.h"

#include "FrameBuffer.h"
#include "DepthFrameBuffer.h"


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
void RenderSceneFromDirectionalLight(RenderInfo& info);
void RenderFrameBuffer(RenderInfo& info);

void RenderIntoFrameBuffer(RenderInfo& info);

// -------------------------------------------------------------------------------

int winW = 1280;
int winH = 720;

float lastX = winW / 2.f;
float lastY = winH / 2.f;
bool firstMouse = true;

bool keys[1024];
bool buttons[7];

float dt = 0.f;
float lastFrame = 0.f;

Camera camera;
Camera camera2(glm::vec3(0.f, 2.f, 5.f));

// -------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit()) return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	std::string windowTitle = "Shadow mapping: ";
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

	glViewport(0, 0, winW, winH);

	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	//glfwMaximizeWindow(window);
	
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	// ==============================================
	// Init geometry, materials, cameras, shaders, scene, etc.

	FrameBuffer frameBuffer(winW, winH);

	Shader simpleSh("Simple shader", "./Data/Shaders/simple.vert", "./Data/Shaders/simple.frag");
	Shader framebufferRenderSh("Frame buffer render", "./Data/Shaders/render_framebuffer.vert", "./Data/Shaders/render_framebuffer.frag");

	Geometry simpleCube(cubeVerticesCount, cubeIndicesCount, cubeIndices, cubeVertices, cubeNormals, cubeTexCoords, cubeColors);
	Geometry simplePlane(planeVerticesCount, planeIndicesCount, planeIndices, planeVertices, planeNormals, planeTexCoords, planeColors);

	Geometry quadToShowTexture(quadVerticesCount, quadIndicesCount, quadIndices, quadVertices, quadNormals, quadTexCoords, quadColors);

	// ==============================================

	while(!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		dt = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// ---------------

		glfwPollEvents();
		ProcessInput(window);

		// ---------------

		frameBuffer.Bind();
		glClearColor(.3f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		// Render

		RenderInfo info;
		info.ResetModel();

		glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom), (float)winW / (float)winH, 0.1f, 100.f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.f);
		simpleSh.SetMat4("projection", proj);
		simpleSh.SetMat4("view", view);

		// Render plane -------------
		
		model = glm::scale(model, glm::vec3(3.f, 1.f, 3.f));

		info.SetMatrices(proj, view, model);
		info.shader = &simpleSh;
		info.geometry = &simplePlane;
		
		RenderSimpleGeometry(info);  

		// --------------------------

		// Render cube --------------

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.f, 0.5f, 0.f));

		info.SetMatrices(proj, view, model);
		info.shader = &simpleSh;
		info.geometry = &simpleCube;

		RenderSimpleGeometry(info);

		// -------------------

		frameBuffer.UnBind();
		glClearColor(.1f, .1f, .1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Render the quad ---------

		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(0.f, 2.f, -4.f));

		info.SetMatrices(proj, view, model);
		info.shader = &framebufferRenderSh;
		info.geometry = &quadToShowTexture;
		info.frameBuffer = &frameBuffer;

		RenderFrameBuffer(info);

		// -------------------------


		// ---------------------------

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}

// -------------------------------------------------------------------------------

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	winW = width; winH = height;
	glViewport(0, 0, width, height);
	
	std::string windowTitle = "Shadow mapping: ";
	windowTitle += (std::to_string(winW) + "x" + std::to_string(winH));
	glfwSetWindowTitle(window, windowTitle.c_str());
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
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
	
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		buttons[button] = true;
	else
		buttons[button] = false;
}

void ProcessInput(GLFWwindow* window)
{
	Camera* activeCamera = &camera;
	
	if (activeCamera)
	{
		if (keys[GLFW_KEY_W]) //w
			activeCamera->ProcessKeyboard(FORWARD, dt);
		if (keys[GLFW_KEY_S]) //s
			activeCamera->ProcessKeyboard(BACKWARD, dt);
		if (keys[GLFW_KEY_A]) //a
			activeCamera->ProcessKeyboard(LEFT, dt);
		if (keys[GLFW_KEY_D]) //d
			activeCamera->ProcessKeyboard(RIGHT, dt);
		if (keys[GLFW_KEY_Q]) //q
			activeCamera->ProcessKeyboard(UP, dt);
		if (keys[GLFW_KEY_E]) //e
			activeCamera->ProcessKeyboard(DOWN, dt);
	}
	
	//if (keys[GLFW_KEY_1])
	//	scene.SetActiveIndex(0);
	//if (keys[GLFW_KEY_2])
	//	scene.SetActiveIndex(1);
	//if (keys[GLFW_KEY_3])
	//	scene.SetActiveIndex(2);
	//if (keys[GLFW_KEY_4])
	//	scene.SetActiveIndex(3);
	//if (keys[GLFW_KEY_5])
	//	scene.SetActiveIndex(4);
	//if (keys[GLFW_KEY_6])
	//	scene.SetActiveIndex(5);
	//if (keys[GLFW_KEY_7])
	//	scene.SetActiveIndex(6);
	//if (keys[GLFW_KEY_8])
	//	scene.SetActiveIndex(7);
	//if (keys[GLFW_KEY_9])
	//	scene.SetActiveIndex(8);

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

void RenderSceneFromDirectionalLight(RenderInfo& info)
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