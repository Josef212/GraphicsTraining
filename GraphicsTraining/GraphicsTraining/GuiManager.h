#ifndef __GUI_MANAGER_H__
#define __GUI_MANAGER_H__

struct GLFWwindow;
class EditorPanel;
class MaterialCreator;

#include <vector>

class GuiManager
{
public:
	GuiManager();
	virtual ~GuiManager();

	void Init(GLFWwindow* window);
	void StartFrame(bool& editorUseMouse, bool& editorUseKeyboard);
	void Render();
	void EndFrame();
	void CleanUp();

private:
	GLFWwindow * referenceWindow = nullptr;

	bool showImGuiExmple = false;

	std::vector<EditorPanel*> panels;
	MaterialCreator* materialCreator = nullptr;

};
extern GuiManager* guiManager;

#endif // !__GUI_MANAGER_H__