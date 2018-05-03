#ifndef __EDITOR_TEXTURE_PANEL_H__
#define __EDITOR_TEXTURE_PANEL_H__

#include "EditorPanel.h"

class Texture;

class Editor_TexturePanel : public EditorPanel
{
public:
	Editor_TexturePanel(const char* name, bool startEnabled = false);
	virtual ~Editor_TexturePanel();

	void Display() override;

private:
	//TMP
	Texture* t;
};

#endif // !__EDITOR_TEXTURE_PANEL_H__