#ifndef __PBR_MATERIAL_H__
#define __PBR_MATERIAL_H__

#include "Material.h"

class PBRMaterial : public Material
{
public:
	PBRMaterial(const char* name);
	PBRMaterial(const char* name, Shader* sh);
	virtual ~PBRMaterial();

	void OnFree() override;

	void SendInfo(Scene* scene) const override;

public:
};

#endif // !__PBR_MATERIAL_H__