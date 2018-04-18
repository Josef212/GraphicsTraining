#ifndef __EDITOR_GEOMETRY_PANEL_H__
#define __EDITOR_GEOMETRY_PANEL_H__

#include "EditorPanel.h"

class Geometry;
class FrameBuffer;
class Shader;

class Editor_GeometryPanel : public EditorPanel
{
public:
	Editor_GeometryPanel(const char* name, bool startEnabled = false);
	virtual ~Editor_GeometryPanel();

	void OnInit() override;
	void Display() override;

private:
	void GeometryInfo(Geometry* geo);

public:

private:
	FrameBuffer * geoFrameBuffer = nullptr;
	Shader* simpleGeoShader = nullptr;

};

#endif // !__EDITOR_GEOMETRY_PANEL_H__