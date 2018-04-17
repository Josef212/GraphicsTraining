#ifndef __EDITOR_SHADER_PANEL_H__
#define __EDITOR_SHADER_PANEL_H__

#include "EditorPanel.h"

class Shader;

class Editor_ShaderPanel : public EditorPanel
{
public:
	Editor_ShaderPanel(const char* name, bool startEnabled = false);
	virtual ~Editor_ShaderPanel();

	void Display() override;

private:
	void ShaderInfo(Shader* sh);
};

#endif // !__EDITOR_SHADER_PANEL_H__