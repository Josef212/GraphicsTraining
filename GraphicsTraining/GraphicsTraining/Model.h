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

	void AddMesh(Geometry* geometry, Material* material);
	void SetGeometry(Geometry* geometry, int index);
	void SetMaterial(Material* material, int index);

	std::pair<Geometry*, Material*> GetMesh(int index)const;
	Geometry* GetGeometry(int index)const;
	Material* GetMaterial(int index)const;

	void Render(Scene* scene);

public:
	glm::mat4 modelMat;
	std::string directory = "";

private:
	std::vector<std::pair<Geometry*, Material*>> meshes;
};

#endif // !__MODEL_H__