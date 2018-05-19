#ifndef __M_WINDOW_H__
#define __M_WINDOW_H__

#include "Module.h"

class GLFWwindow;

class M_Window : public Module
{
public:
	M_Window(const char* name, bool startEnabled = true);
	virtual ~M_Window();

	bool Init() override;
	bool CleanUp() override;

private:

public:

private:
	uint width, height, scale;
	GLFWwindow* window = nullptr;
};

#endif