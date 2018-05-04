#ifndef __DIRLIGHTSHADOW_H__
#define __DIRLIGHTSHADOW_H__

#include "Scene.h"

class DirLightShadowScene : public Scene
{
public:
	DirLightShadowScene(const char* name);
	virtual ~DirLightShadowScene();

	void OnInit() override;
	void OnCleanUp() override;

	void OnRenderScene() override;
};

#endif // !__DIRLIGHTSHADOW_H__