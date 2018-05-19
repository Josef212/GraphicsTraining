#ifndef __M_WINDOW_H__
#define __M_WINDOW_H__

#include "Module.h"

struct SDL_Window;

class M_Window : public Module
{
public:
	M_Window(const char* name, bool startEnabled = true);
	virtual ~M_Window();

	bool Init() override;
	bool CleanUp() override;

	void OnResize(uint w, uint h) override;

	// ================================

	SDL_Window* GetWindow()const { return window; }

	int GetWidth()const { return width; }
	int GetHeight()const { return height; }
	int GetScale()const { return scale; }

private:

public:

private:
	uint width, height, scale;
	SDL_Window* window = nullptr;
};

#endif