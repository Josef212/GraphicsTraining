#ifndef __SIMPLE_SCENE_H__
#define __SIMPLE_SCENE_H__

#include "Scene.h"

class SimpleScene : public Scene
{
public:
	SimpleScene(const char* name);
	virtual ~SimpleScene();

	void OnInit() override;
	void OnCleanUp() override;

	void OnRenderScene() override;
};

#endif // !__SIMPLE_SCENE_H__