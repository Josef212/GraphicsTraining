#ifndef __MODULE_H__
#define __MODULE_H__

#include "Defs.h"

#include <string>

class Module
{
public:
	Module(const char* name, bool startEnabled) : name(name), enabled(startEnabled)
	{}
	virtual ~Module()
	{}

	// ======================================================

	virtual bool Init() { return true; }
	virtual bool Start() { return true; }
	virtual UpdateReturn PreUpdate(float dt) { return UpdateReturn::UPDT_CONTINUE; }
	virtual UpdateReturn Update(float dt) { return UpdateReturn::UPDT_CONTINUE; }
	virtual UpdateReturn PostUpdate(float dt) { return UpdateReturn::UPDT_CONTINUE; }
	virtual bool CleanUp() { return true; }

	virtual bool Save() { return true; }
	virtual bool Load() { return true; }

	virtual void DrawDebug() {}

	// ======================================================

	bool IsEnabled() const { return enabled; }

	bool Enable()
	{
		if(!enabled)
		{
			enabled = Start();
			return enabled;
		}

		return false;
	}

	bool Disable()
	{
		if(enabled)
		{
			enabled = !CleanUp();
			return enabled;
		}

		return false;
	}

	bool SetActive(const bool set)
	{
		if(set != enabled)
		{
			return set ? Enable() : Disable();
		}

		return false;
	}

public:
	std::string name;

private:
	bool enabled;
};

#endif