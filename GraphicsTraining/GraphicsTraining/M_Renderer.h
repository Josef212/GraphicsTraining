#ifndef __M_RENDERER_H__
#define __M_RENDERER_H__

#include "Module.h"
#include <SDL.h>

class M_Renderer : public Module
{
public:
	M_Renderer(const char* name, bool startEnabled = true);
	virtual ~M_Renderer();

	bool Init() override;
	UpdateReturn PreUpdate(float dt) override;
	UpdateReturn Update(float dt) override;
	UpdateReturn PostUpdate(float dt) override;
	bool CleanUp() override;

	void OnResize(uint w, uint h)override;

	// ================================

	bool GetVSync()const { return m_vsync; }
	void SetVSync(bool set);

private:

public:
	bool m_showGrid = true;

private:
	SDL_GLContext m_context;
	bool m_vsync;
};

#endif