#ifndef __EDITOR_MATERIAL_PANEL_H__
#define __EDITOR_MATERIAL_PANEL_H__

#include "EditorPanel.h"

class Material;
class ComplexMaterial;
class PhongMaterial;
class PBRMaterial;

class Editor_MaterialPanel : public EditorPanel
{
public:
	Editor_MaterialPanel(const char* name, bool startEnabled = false);
	virtual ~Editor_MaterialPanel();

	void OnInit() override;
	void Display() override;

private:
	void MaterialInfo(Material* mat);
	void CMaterialInfo(ComplexMaterial* cmat);
	void PhongMaterialInfo(PhongMaterial* phong);
	void PBRMaterialInfo(PBRMaterial* pbr);
	void EditMaterialWindow();

public:

private:
	ComplexMaterial * editingMaterial = nullptr;
	bool editingMat = false;
};

#endif // !__EDITOR_MATERIAL_PANEL_H__