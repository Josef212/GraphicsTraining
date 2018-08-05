#ifndef __M_RESOURCE_MANAGER_H__
#define __M_RESOURCE_MANAGER_H__

#include "Module.h"
#include "Resource.h"

#include <map>
#include <vector>
#include <memory>

class M_ResourceManager : public Module
{
public:
	M_ResourceManager(const char* name, bool startEnabled = true);
	virtual ~M_ResourceManager();

	bool Init() override;
	bool CleanUp() override;

	std::shared_ptr<Resource> CreateResource(ResourceType type, const char* name, bool forceLoad = false);

	std::shared_ptr<Resource> GetResource(const char* resourceName);
	std::shared_ptr<Resource> GetResourceWithType(const char* resourceName, ResourceType type);

private:

public:

private:
	std::map<ResourceType, std::map<std::string, std::shared_ptr<Resource>>> m_resources;
};

#endif