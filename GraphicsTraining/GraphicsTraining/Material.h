#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Resource.h"

class Shader;
class Scene;

class Material : public Resource
{
public:
	Material(const char* name);
	Material(const char* name, Shader* sh);
	virtual ~Material();

	void Load() override;
	void Free() override;

	void InitRender()const;
	void EndRender()const;

	virtual void SendInfo(Scene* scene)const {}
	virtual void OnLoad() {}
	virtual void OnFree() {}

	void SetShader(Shader* sh);
	Shader* GetShader()const;

protected:
	Shader * shader = nullptr;
};

#endif // !__MATERIAL_H__