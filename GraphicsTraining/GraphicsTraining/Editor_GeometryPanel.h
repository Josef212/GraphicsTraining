#ifndef __EDITOR_GEOMETRY_PANEL_H__
#define __EDITOR_GEOMETRY_PANEL_H__

#include "EditorPanel.h"

class Geometry;

class Editor_GeometryPanel : public EditorPanel
{
public:
	Editor_GeometryPanel(const char* name, bool startEnabled = false);
	virtual ~Editor_GeometryPanel();

	void Display() override;

private:
	void GeometryInfo(Geometry* geo);
};

#endif // !__EDITOR_GEOMETRY_PANEL_H__