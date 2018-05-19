// -------------------------------------------------------------------------------
// Includes

#include <iostream>
#include <string>

#include "Defs.h"

#include <GLFW/glfw3.h>

#include "App.h"

// -------------------------------------------------------------------------------
// Callbacks

static void ErrorCallback(int error, const char* description)
{
	LOG(CONSOLE_TEXT_RED, "Error %d: %s", error, description)
	fprintf(stderr, "Error %d: %s\n", error, description);
}

// -------------------------------------------------------------------------------
// Globals

enum MainState
{
	MAIN_CREATION = 0,
	MAIN_START = 1,
	MAIN_UPDATE = 2,
	MAIN_FINISH = 3,
	MAIN_EXIT = 4
};

std::unique_ptr<App> app = nullptr;

// -------------------------------------------------------------------------------

int main(int argc, char** argv)
{
	LOG(CONSOLE_TEXT_GREEN, "Starting graphics engine.")

	glfwSetErrorCallback(ErrorCallback);

	int ret = EXIT_FAILURE;
	MainState state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG(LOG_INFO, "==================== App creation =======================");
				
			app = std::make_unique<App>(argc, argv);
			state = MAIN_START;

			break;

		case MAIN_START:

			LOG(LOG_INFO, "==================== App Init =======================");
			
			if(app->Init())
			{
				state = MAIN_UPDATE;
				LOG(LOG_INFO, "==================== App update =======================");
			}
			else
			{
				LOG(LOG_ERROR, "App init error!");
				state = MAIN_EXIT;
			}

			break;

		case MAIN_UPDATE:
		{
			const auto tmp = app->Update();

			if (tmp == UpdateReturn::UPDT_ERROR)
			{
				LOG(LOG_ERROR, "App update error!");
				state = MAIN_EXIT;
			}

			if (tmp == UpdateReturn::UPDT_STOP) state = MAIN_FINISH;

			break;
		}

		case MAIN_FINISH:

			LOG(LOG_INFO, "==================== App clean up =======================");

			if (app->CleanUp())
				ret = EXIT_SUCCESS;
			else
				LOG(LOG_ERROR, "App clean up error.");

			state = MAIN_EXIT;

			break;
		}
	}

	app.release();

	LOG(LOG_INFO, "Exiting the engine.");

#ifdef _DEBUG	
	PAUSE
#else

#endif

	return ret;
}
