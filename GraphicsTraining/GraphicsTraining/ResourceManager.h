#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <vector>

class Resource;
class Geometry;
class Shader;
class Model;
class Material;
class ComplexMaterial;

enum ResourceType;

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	void Init();

	virtual void OnScreenResize(int w, int h) {}

	void AddResource(Resource* res);

	unsigned int GatherResourceOfType(ResourceType type, std::vector<Resource*>& vec);

private:
	void SetDefaultResources();

public:
	struct DefaultResources
	{
		// Geometries
		Geometry* triangleGeo	= nullptr;
		Geometry* quadGeo		= nullptr;
		Geometry* cubeGeo		= nullptr;
		Geometry* planeGeo		= nullptr;

		// Shaders
		Shader* simpleSh		= nullptr;

		// Materials
		Material* simpleMat		= nullptr;

		// Models


	}defaultResources;

private:
	std::vector<Resource*> resources;
};
extern ResourceManager* resourceManager;

#endif // !__RESOURCE_MANAGER_H__