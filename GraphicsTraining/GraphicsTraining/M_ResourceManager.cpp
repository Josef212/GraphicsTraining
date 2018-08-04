#include "M_ResourceManager.h"



M_ResourceManager::M_ResourceManager(const char* name, bool startEnabled) : Module(name, startEnabled)
{
	LOG_CREATION(name);

	for(uint i = RES_NONE + 1; i < RES_ERROR; ++i)
	{
		m_resources.insert(std::pair<ResourceType, std::vector<std::shared_ptr<Resource>>>((ResourceType)i, std::vector<std::shared_ptr<Resource>>()));
	}

	configuration = M_INIT | M_CLEAN_UP | M_SAVE_CONFIG | M_RESIZE_EVENT;
}


M_ResourceManager::~M_ResourceManager()
{
	LOG_DESTRUCTION(name.c_str());
}

bool M_ResourceManager::Init()
{
	LOG_INIT(name.c_str());

	return true;
}
