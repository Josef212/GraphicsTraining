#ifndef __MATERIALCREATOR_H__
#define __MATERIALCREATOR_H__

#include <string>
#include <vector>

class Shader;
class Texture;
class ComplexMaterial;
class MatProperty;

class MaterialCreator
{
public:
	MaterialCreator();
	virtual ~MaterialCreator();

	void OnOpen();
	void OnCancel();

	void Render();

	bool Show()const;
	void Open();
	void Close();

private:
	void CreateMaterial();

private:
	std::string tmpName = "";
	std::string tmpPropName = "";
	union
	{
		int _int;
		float _float;
		float* _floatPtr;
		Texture* _texture;
		bool _bool;
		bool* _boolPtr;
	} tmpPropValue;
	std::vector<MatProperty*> tmpMatProperties;
	Shader* tmpShader = nullptr;

	bool open = false;

};

#endif // !__MATERIALCREATOR_H__