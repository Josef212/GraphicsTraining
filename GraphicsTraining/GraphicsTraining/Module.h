#ifndef __MODULE_H__
#define __MODULE_H__

#include "Defs.h"

#include <string>

typedef enum
{
	M_NONE			= 0,
	M_INIT			= 1 << 0,
	M_START			= 1 << 1,
	M_PRE_UPDATE	= 1 << 2,
	M_UPDATE		= 1 << 3,
	M_POST_UPDATE	= 1 << 4,
	M_CLEAN_UP		= 1 << 5,
	M_SAVE_CONFIG	= 1 << 6,
	M_RESIZE_EVENT	= 1 << 7

} ModuleConfig;

#define MODULE_FULL_CONFIG\
	M_INIT | M_START |\
	M_PRE_UPDATE | M_UPDATE | M_POST_UPDATE |\
	M_CLEAN_UP |\
	M_SAVE_CONFIG |\
	M_RESIZE_EVENT


class Module
{
friend class App;
public:
	Module(const char* name, bool startEnabled) : name(name), enabled(startEnabled), configuration(0)
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

	virtual void OnResize(uint w, uint h) {}

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

protected:
	uint32 configuration;
};

#endif