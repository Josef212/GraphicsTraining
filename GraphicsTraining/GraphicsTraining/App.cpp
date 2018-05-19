#include "App.h"

#include "M_Window.h"
#include "M_Input.h"

#include "M_Renderer.h"


App::App(int argc, char** argv) : shouldClose(false)
{
	LOG(LOG_INFO, "Creating modules.");

	window = std::make_shared<M_Window>("M_Window");
	input = std::make_shared<M_Input>("M_Input");


	renderer = std::make_shared<M_Renderer>("M_Renderer");


	modules.push_back(window);
	modules.push_back(input);



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
}

bool App::Init()
{
	bool ret = true;

	LOG(LOG_INFO, "Initing modules.");

	auto it = modules.begin();
	while(it != modules.end() && ret == true)
	{
		ret = (*it)->Init();
		++it;
	}

	if (!ret) return ret;

	LOG(LOG_INFO, "Starting modules.");

	it = modules.begin();
	while (it != modules.end() && ret == true)
	{
		if((*it)->IsEnabled())
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
		if ((*it)->IsEnabled())
			ret = (*it)->PreUpdate(0.f);
		++it;
	}

	if (ret == UpdateReturn::UPDT_ERROR)
		LOG(LOG_ERROR, "Exiting with error on preupdate!");

	it = modules.begin();
	while (it != modules.end() && ret == UpdateReturn::UPDT_CONTINUE)
	{
		if ((*it)->IsEnabled())
			ret = (*it)->Update(0.f);
		++it;
	}

	if (ret == UpdateReturn::UPDT_ERROR)
		LOG(LOG_ERROR, "Exiting with error on update!");

	it = modules.begin();
	while (it != modules.end() && ret == UpdateReturn::UPDT_CONTINUE)
	{
		if ((*it)->IsEnabled())
			ret = (*it)->PostUpdate(0.f);
		++it;
	}

	if (ret == UpdateReturn::UPDT_ERROR)
		LOG(LOG_ERROR, "Exiting with error on postupdate!");

	PostUpdate();

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
		ret = (*it)->CleanUp();
		++it;
	}

	return ret;
}

void App::PrepareUpdate()
{
}

void App::PostUpdate()
{
}
