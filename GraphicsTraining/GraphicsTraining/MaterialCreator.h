#ifndef __MATERIALCREATOR_H__
#define __MATERIALCREATOR_H__

#include <string>
#include <vector>

class ComplexMaterial;
class MatProperty;

class MaterialCreator
{
public:
	MaterialCreator();
	virtual ~MaterialCreator();

	void OnOpen();
	void OnClose();

	void Render();

private:
	std::string tmpName = "";
	std::vector<MatProperty*> tmpMatProperties;
};

#endif // !__MATERIALCREATOR_H__