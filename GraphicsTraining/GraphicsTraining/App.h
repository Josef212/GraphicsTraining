#ifndef __APP_H__
#define __APP_H__

#include "Defs.h"
#include <memory>

#include <string>
#include <vector>

class Module;
class M_Window;

class App
{
public:
	App(int argc, char** argv);
	virtual ~App();

	bool Init();
	UpdateReturn Update();
	bool CleanUp();

private:


public:
	

private:


};
extern std::unique_ptr<App> app;

#endif