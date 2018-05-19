#ifndef __M_INPUT_H__
#define __M_INPUT_H__

#include "Module.h"

#define MAX_MOUSE_BUTTONS 5
#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class M_Input : public Module
{
public:
	M_Input(const char* name, bool startEnabled = true);
	virtual ~M_Input();

	bool Init()override;
	UpdateReturn PreUpdate(float dt)override;
	bool CleanUp()override;

	// ================================

private:

public:

private:
	KEY_STATE * keyboard = nullptr;
	KEY_STATE mouse[MAX_MOUSE_BUTTONS];
	int mouseX, mouseY, mouseMotionX, mouseMotionY, wheelY;
};

#endif