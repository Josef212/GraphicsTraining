#include "M_Window.h"

#include <GLFW/glfw3.h>


M_Window::M_Window(const char* name, bool startEnabled) : Module(name, startEnabled)
{
	LOG(LOG_INFO, "%s: Creation --------------", name);

	width = DEFAULT_WIN_WIDTH;
	height = DEFAULT_WIN_HEIGHT;
	scale = 1;
}

M_Window::~M_Window()
{
	LOG(LOG_INFO, "%s: Destruction --------------", name.c_str());
}

bool M_Window::Init()
{
	bool ret = false;

	if(glfwInit())
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

		window = glfwCreateWindow(width, height, "Graphics engine", NULL, NULL);

		if(!window)
		{
			LOG(LOG_ERROR, "Failed to create window.");
			glfwTerminate();
		}
		else
		{
			ret = true;
		}
	}

	return ret;
}

bool M_Window::CleanUp()
{
	glfwDestroyWindow(window);

	return true;
}
