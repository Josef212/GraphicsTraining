#ifndef __APP_H__
#define __APP_H__

#include "Defs.h"
#include <memory>

#include <string>
#include <vector>
#include "Clock.h"

class Module;
class M_Window;
class M_Input;
class M_Renderer;

class App
{
public:
	App(int argc, char** argv);
	virtual ~App();

	bool Init();
	UpdateReturn Update();
	bool CleanUp();

	void OnResize(uint w, uint h);

	// ================================

	void Close() { shouldClose = true; };

	uint GetMaxFPS()const;
	void SetMaxFPS(uint _fps);

private:
	void PrepareUpdate();
	void FinishUpdate();

public:
	std::shared_ptr<M_Window>		window = nullptr;
	std::shared_ptr<M_Input>		input = nullptr;


	std::shared_ptr<M_Renderer>		renderer = nullptr;


	std::unique_ptr<GE::Clock>		clock = nullptr;

private:
	std::vector<std::shared_ptr<Module>> modules;

	bool shouldClose;

	uint32	cappedMs = 0;


};
extern std::unique_ptr<App> app;

#endif