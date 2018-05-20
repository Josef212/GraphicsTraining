#include "M_Editor.h"



M_Editor::M_Editor(const char* name, bool startEnabled) : Module(name, startEnabled)
{

	configuration = M_INIT | M_PRE_UPDATE | M_UPDATE;
}


M_Editor::~M_Editor()
{
}

bool M_Editor::Init()
{
	return true;
}

UpdateReturn M_Editor::PreUpdate(float dt)
{
	return UpdateReturn::UPDT_CONTINUE;
}

UpdateReturn M_Editor::Update(float dt)
{
	return UpdateReturn::UPDT_CONTINUE;
}

void M_Editor::Render()
{
	// TODO
}

void M_Editor::PassInput(SDL_Event* ev)
{
	// TODO
}
