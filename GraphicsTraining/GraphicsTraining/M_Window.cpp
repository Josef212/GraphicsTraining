#include "M_Window.h"



M_Window::M_Window(const char* name, bool startEnabled) : Module(name, startEnabled)
{
	LOG(LOG_INFO, "%s: Creation --------------", name);
}

M_Window::~M_Window()
{
	LOG(LOG_INFO, "%s: Destruction --------------", name.c_str());
}
