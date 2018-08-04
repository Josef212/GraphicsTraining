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

private:

public:

private:
	std::map<ResourceType, std::vector<std::shared_ptr<Resource>>> m_resources;
};

#endif