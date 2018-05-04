#ifndef __EDITOR_SCENE_PANEL_H__
#define __EDITOR_SCENE_PANEL_H__

#include "EditorPanel.h"

class Scene;

class Editor_ScenePanel : public EditorPanel
{
public:
	Editor_ScenePanel(const char* name, bool startEnabled = false);
	virtual ~Editor_ScenePanel();

	void Display() override;

private:
	void SceneInfo(Scene* sc, int index);

};

#endif // !__EDITOR_SCENE_PANEL_H__