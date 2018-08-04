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
class M_Editor;
class M_ResourceManager;

class App
{
public:
	App(int argc, char** argv);
	virtual ~App();

	bool Init();
	UpdateReturn Update();
	bool CleanUp();

	void OnResize(uint w, uint h);

	void DrawDebug();

	// ================================

	void Close() { shouldClose = true; };

	uint GetMaxFPS()const;
	void SetMaxFPS(uint _fps);

private:
	void PrepareUpdate();
	void FinishUpdate();

public:
	// Modules
	std::shared_ptr<M_Editor>				editor = nullptr;
	std::shared_ptr<M_Window>				window = nullptr;
	std::shared_ptr<M_Input>				input = nullptr;
	std::shared_ptr<M_ResourceManager>		resourceManager = nullptr;


	std::shared_ptr<M_Renderer>		renderer = nullptr;

	// Other public variables
	std::unique_ptr<GE::Clock>		clock = nullptr;

	bool debugDraw = false;

private:
	std::vector<std::shared_ptr<Module>> modules;

	bool shouldClose = false;

	uint32	cappedMs = 0;


};
extern std::unique_ptr<App> app;

#endif