#ifndef __EDITOR_PANEL_H__
#define __EDITOR_PANEL_H__

#include <string>

class EditorPanel
{
public:
	EditorPanel(const char* name, bool startEnabled = false);
	virtual ~EditorPanel();

	virtual void Display() = 0;

	void Enable() { show = true; }
	void Disable() { show = false; }
	void SwapShow() { show ? Disable() : Enable(); }

	bool Visible() const { return show; }

private:

protected:

public:
	std::string name = "No name";

private:

protected:
	bool show = false;
};

#endif // !__EDITOR_PANEL_H__