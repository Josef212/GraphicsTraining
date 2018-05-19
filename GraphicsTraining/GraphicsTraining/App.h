#ifndef __APP_H__
#define __APP_H__

#include "Defs.h"
#include <memory>

#include <string>
#include <vector>

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

	// ================================

	void Close() { shouldClose = true; };

private:
	void PrepareUpdate();
	void PostUpdate();

public:
	std::shared_ptr<M_Window>		window = nullptr;
	std::shared_ptr<M_Input>		input = nullptr;


	std::shared_ptr<M_Renderer>		renderer = nullptr;

private:
	std::vector<std::shared_ptr<Module>> modules;

	bool shouldClose;


};
extern std::unique_ptr<App> app;

#endif