#include "M_Window.h"

#include <SDL.h>
#include "App.h"


M_Window::M_Window(const char* name, bool startEnabled) : Module(name, startEnabled)
{
	LOG_CREATION(name);

	width = DEFAULT_WIN_WIDTH;
	height = DEFAULT_WIN_HEIGHT;
	scale = 1;
}

M_Window::~M_Window()
{
	LOG(LOG_INFO, "\t%s: Destruction --------------", name.c_str());
}

bool M_Window::Init()
{
	LOG_INIT(name.c_str());

	bool ret = false;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG(LOG_ERROR, "SDL_Video could not initialize. SDL_Error: %s", SDL_GetError());
	}
	else
	{
		// TODO: Get the config 

		uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;// | SDL_WINDOW_MAXIMIZED;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

		window = SDL_CreateWindow("Graphics engine.", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(!window)
		{
			LOG(LOG_ERROR, "Could not create window. SDL_Error: %s", SDL_GetError());
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
	LOG_CLEANUP(name.c_str());

	if (window) SDL_DestroyWindow(window);
	SDL_Quit();

	return true;
}
