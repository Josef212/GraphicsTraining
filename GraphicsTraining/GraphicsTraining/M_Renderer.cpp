#include "M_Renderer.h"

#include "App.h"
#include "M_Window.h"
#include "M_Editor.h"

#include "OpenGL.h"


M_Renderer::M_Renderer(const char* name, bool startEnabled) : Module(name, startEnabled)
{
	LOG_CREATION(name);

	vsync = false;

	configuration = M_INIT | M_START | M_PRE_UPDATE | M_POST_UPDATE | M_CLEAN_UP | M_SAVE_CONFIG | M_RESIZE_EVENT;
}


M_Renderer::~M_Renderer()
{
	LOG_DESTRUCTION(name.c_str());
}

bool M_Renderer::Init()
{
	LOG_INIT(name.c_str());
	bool ret = true;

	context = SDL_GL_CreateContext(app->window->GetWindow());

	if(context == nullptr)
	{
		LOG(LOG_ERROR, "OpenGL could not create context. SDL_Error: %s", SDL_GetError());
		ret = false;
	}
	else
	{
		glewExperimental = GL_TRUE;
		GLenum gl = glewInit();
		if(gl != GLEW_OK)
		{
			LOG(LOG_ERROR, "Glew lib could not init: %s", glewGetErrorString(gl));
			ret = false;
		}
		else
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
			{
				LOG(LOG_ERROR, "Could not init OpenGL! %s\n", glewGetErrorString(error));
				ret = false;
			}
		}

		if(ret)
		{
			LOG(LOG_INFO, "Vendor: %s", glGetString(GL_VENDOR));
			LOG(LOG_INFO, "Renderer: %s", glGetString(GL_RENDERER));
			LOG(LOG_INFO, "OpenGL version supported %s", glGetString(GL_VERSION));
			LOG(LOG_INFO, "GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

			SetVSync(vsync);

			glClearDepth(1.f);
			glClearColor(0.f, 0.f, 0.f, 1.f);

			glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
			glDepthFunc(GL_LESS);

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			OnResize(app->window->GetWinWidth(), app->window->GetWinHeight());
		}
	}

	return ret;
}

UpdateReturn M_Renderer::PreUpdate(float dt)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UpdateReturn::UPDT_CONTINUE;
}

UpdateReturn M_Renderer::Update(float dt)
{
	return UpdateReturn::UPDT_CONTINUE;
}

UpdateReturn M_Renderer::PostUpdate(float dt)
{


	if (app->debugDraw) app->DrawDebug();

	if (app->editor) app->editor->Render();

	SDL_GL_SwapWindow(app->window->GetWindow());

	return UpdateReturn::UPDT_CONTINUE;
}

bool M_Renderer::CleanUp()
{
	LOG_CLEANUP(name.c_str());

	SDL_GL_DeleteContext(context);

	return true;
}

void M_Renderer::OnResize(uint w, uint h)
{
	glViewport(0, 0, w, h);
}

void M_Renderer::SetVSync(bool set)
{
	if(set != vsync)
	{
		vsync = set;
		if (SDL_GL_SetSwapInterval(vsync ? 1 : 0) < 0)
			LOG(LOG_WARN, "Unable to set VSync. SDL_Error: %s", SDL_GetError());
	}
}
