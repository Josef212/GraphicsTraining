#ifndef __M_EDITOR_H__
#define __M_EDITOR_H__

#include "Module.h"
#include <SDL.h>

class M_Editor : public Module
{
public:
	M_Editor(const char* name, bool startEnabled = true);
	virtual ~M_Editor();

	bool Init() override;
	UpdateReturn PreUpdate(float dt) override;
	UpdateReturn Update(float dt) override;

	void Render();
	void PassInput(SDL_Event* ev);

};

#endif