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

	void RemoveResource(Resource* res, bool forceDefaults = false);
	void RemoveResources(Resource** res, int count, bool forceDefaults = false);
	void RemoveResources(std::vector<Resource*>& res, bool forceDefaults = false);
	void RemoveAllResources(bool forceDefaults = false);

	unsigned int GatherResourceOfType(ResourceType type, std::vector<Resource*>& vec);

	bool IsDefaultResource(Resource* res);

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