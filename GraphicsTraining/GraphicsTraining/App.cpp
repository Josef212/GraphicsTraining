#include "App.h"

#include "M_Editor.h"
#include "M_Window.h"
#include "M_Input.h"
#include "M_ResourceManager.h"
#include "M_FileSystem.h"

#include "M_Renderer.h"


App::App(int argc, char** argv) : shouldClose(false)
{
	LOG(LOG_INFO, "Creating modules.");

	clock = std::make_unique<GE::Clock>();


	editor = std::make_shared<M_Editor>("M_Editor");
	fs = std::make_shared<M_FileSystem>("M_FileSustem");
	window = std::make_shared<M_Window>("M_Window");
	input = std::make_shared<M_Input>("M_Input");
	resourceManager = std::make_shared<M_ResourceManager>("M_ResourceManager");



	renderer = std::make_shared<M_Renderer>("M_Renderer");


	modules.push_back(editor);
	modules.push_back(fs);
	modules.push_back(window);
	modules.push_back(input);
	modules.push_back(resourceManager);



	modules.push_back(renderer);
}


App::~App()
{
	auto it = modules.rbegin();
	while (it != modules.rend())
	{
		(*it).reset();
		++it;
	}

	clock.release();
}

bool App::Init()
{
	bool ret = true;

	LOG(LOG_INFO, "Initing modules.");

	auto it = modules.begin();
	while(it != modules.end() && ret == true)
	{
		if((*it)->configuration & M_INIT)
			ret = (*it)->Init();
		++it;
	}

	if (!ret) return ret;

	LOG(LOG_INFO, "Starting modules.");

	it = modules.begin();
	while (it != modules.end() && ret == true)
	{
		if((*it)->configuration & M_START && (*it)->IsEnabled())
			ret = (*it)->Start();
		++it;
	}


	return ret;
}

UpdateReturn App::Update()
{
	UpdateReturn ret = UpdateReturn::UPDT_CONTINUE;

	PrepareUpdate();

	auto it = modules.begin();
	while (it != modules.end() && ret == UpdateReturn::UPDT_CONTINUE)
	{
		if ((*it)->configuration & M_PRE_UPDATE && (*it)->IsEnabled())
			ret = (*it)->PreUpdate(clock->Dt());
		++it;
	}

	if (ret == UpdateReturn::UPDT_ERROR)
		LOG(LOG_ERROR, "Exiting with error on preupdate!");

	it = modules.begin();
	while (it != modules.end() && ret == UpdateReturn::UPDT_CONTINUE)
	{
		if ((*it)->configuration & M_UPDATE && (*it)->IsEnabled())
			ret = (*it)->Update(clock->Dt());
		++it;
	}

	if (ret == UpdateReturn::UPDT_ERROR)
		LOG(LOG_ERROR, "Exiting with error on update!");

	it = modules.begin();
	while (it != modules.end() && ret == UpdateReturn::UPDT_CONTINUE)
	{
		if ((*it)->configuration & M_POST_UPDATE && (*it)->IsEnabled())
			ret = (*it)->PostUpdate(clock->Dt());
		++it;
	}

	if (ret == UpdateReturn::UPDT_ERROR)
		LOG(LOG_ERROR, "Exiting with error on postupdate!");

	FinishUpdate();

	if(shouldClose)
	{
		// TODO: What must be done on window close
		ret = UPDT_STOP;
	}

	return ret;
}

bool App::CleanUp()
{
	bool ret = true;

	LOG(LOG_INFO, "Cleaning modules.");

	auto it = modules.rbegin();
	while (it != modules.rend() && ret)
	{
		if((*it)->configuration & M_CLEAN_UP)
			ret = (*it)->CleanUp();
		++it;
	}

	return ret;
}

void App::OnResize(uint w, uint h)
{
	for(auto it = modules.begin(); it != modules.end(); ++it)
	{
		if((*it)->IsEnabled() && (*it)->configuration & M_RESIZE_EVENT)
		{
			(*it)->OnResize(w, h);
		}
	}
}

void App::DrawDebug()
{
	for (auto it = modules.begin(); it != modules.end(); ++it)
	{
		if ((*it)->IsEnabled() && (*it)->configuration & M_DRAW_DEBUG)
		{
			(*it)->DrawDebug();
		}
	}
}

// ===============================================================

/**
*	- GetMaxFPS: Return app max fps.
*/
uint App::GetMaxFPS() const
{
	if (cappedMs > 0)
		return (uint)((1.0f / (float)cappedMs) * 1000.0f);
	else
		return 0;
}

/**
*	- SetMaxFPS: Set app max fps.
*/
void App::SetMaxFPS(uint _fps)
{
	if (_fps > 0)
		cappedMs = 1000 / _fps;
	else
		cappedMs = 0;
}

// ===============================================================

void App::PrepareUpdate()
{
	clock->OnPrepareUpdate();
}

void App::FinishUpdate()
{
	clock->OnFinishUpdate();

	if (cappedMs > 0 && (clock->LastFrameMs() < cappedMs))
		SDL_Delay(cappedMs - clock->LastFrameMs());

	//if (editor) editor->LogFPS((float)clock->LastFPS(), (float)clock->LastFrameMs());
}
