#ifndef __MODEL_H__
#define __MODEL_H__

#include "Resource.h"

#include <vector>
#include <string>

#include <glm/glm.hpp>

class Geometry;
class Material;
class Scene;

class Model : public Resource
{
friend class Editor_ModelPanel;

public:
	Model(const char* name);
	Model(const char* name, Geometry* geometry, Material* material);
	virtual ~Model();

	void Free() override;

	void AddMesh(Geometry* geometry, Material* material);
	void SetGeometry(Geometry* geometry, int index);
	void SetMaterial(Material* material, int index);
	void SetMaterial(Material* material);

	std::pair<Geometry*, Material*> GetMesh(int index)const;
	Geometry* GetGeometry(int index)const;
	Material* GetMaterial(int index)const;

	void Render(Scene* scene);

	glm::vec3 GetTranslation()const;
	void SetTranslation(glm::vec3 pos);

	glm::vec3 GetEuler()const;
	void SetEuler(glm::vec3 euler);

	glm::vec3 GetScale()const;
	void SetScale(glm::vec3 scl);

private:
	void CalcModel();

public:
	glm::mat4 modelMat;
	std::string directory = "";

private:
	glm::vec3 translation = glm::vec3(0.f);
	glm::vec3 eulerRot = glm::vec3(0.f);
	glm::vec3 scale = glm::vec3(1.f);

	std::vector<std::pair<Geometry*, Material*>> meshes;
};

#endif // !__MODEL_H__