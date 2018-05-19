#include "App.h"



App::App(int argc, char** argv)
{
}


App::~App()
{
}

bool App::Init()
{
	return true;
}

UpdateReturn App::Update()
{
	return UpdateReturn::UPDT_STOP;
}

bool App::CleanUp()
{
	return true;
}
