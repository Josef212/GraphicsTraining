#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <vector>

class Resource;
enum ResourceType;

class ResourceManager
{
public:
	ResourceManager();
	virtual ~ResourceManager();

	virtual void OnScreenResize(int w, int h) {}

	void AddResource(Resource* res);

	unsigned int GatherResourceOfType(ResourceType type, std::vector<Resource*>& vec);

private:
	std::vector<Resource*> resources;
};
extern ResourceManager* resourceManager;

#endif // !__RESOURCE_MANAGER_H__