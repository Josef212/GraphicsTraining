#ifndef __COMPLEX_MATERIAL_H__
#define __COMPLEX_MATERIAL_H__

#include "Material.h"

#include "Defs.h"
#include <vector>

class MatProperty
{
public:
	MatProperty(const char* name, int value);
	MatProperty(const char* name, float value);
	MatProperty(const char* name, float* value, MatPropertyValueType type);
	~MatProperty();

public:
	union
	{
		int _int;
		float _float;
		float* _floatPtr;
	} propertyValue;

	std::string propertyName;
	MatPropertyValueType propertyType = MatPropertyValueType::MAT_NONE;
};

class ComplexMaterial : public Material
{
friend class Editor_MaterialPanel;

	public:
	ComplexMaterial(const char* name);
	ComplexMaterial(const char* name, Shader* sh);
	virtual ~ComplexMaterial();

	void AddProperty(MatProperty* prop);
	void RemoveProperty(MatProperty* prop);
	void RemoveProperty(const char*  name);

	void OnFree() override;

	void SendInfo(Scene* scene) const override;

protected:
	std::vector<MatProperty*> properties;
};

#endif // !__COMPLEX_MATERIAL_H__