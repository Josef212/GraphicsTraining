#include "App.h"

#include "M_Window.h"


App::App(int argc, char** argv)
{
	LOG(LOG_INFO, "Creating modules.");

	window = std::make_shared<M_Window>("M_Window");



	modules.push_back(window);
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
	return UpdateReturn::UPDT_CONTINUE;
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
