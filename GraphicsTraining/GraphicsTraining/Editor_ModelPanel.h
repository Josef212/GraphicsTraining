#ifndef __EDITOR_MODEL_PANEL_H__
#define __EDITOR_MODEL_PANEL_H__

#include "EditorPanel.h"

class Model;

class Editor_ModelPanel : public EditorPanel
{
public:
	Editor_ModelPanel(const char* name, bool startEnabled = false);
	virtual ~Editor_ModelPanel();

	void Display() override;

private:
	void ModelInfo(Model* model);
};

#endif // !__EDITOR_MODEL_PANEL_H__