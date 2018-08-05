#include "M_ResourceManager.h"

#include "R_Geometry.h"


M_ResourceManager::M_ResourceManager(const char* name, bool startEnabled) : Module(name, startEnabled)
{
	LOG_CREATION(name);

	for(uint i = RES_NONE + 1; i < RES_ERROR; ++i)
	{
		m_resources.insert(std::pair<ResourceType, std::map<std::string, std::shared_ptr<Resource>>>((ResourceType)i, std::map<std::string, std::shared_ptr<Resource>>()));
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

bool M_ResourceManager::CleanUp()
{
	LOG_CLEANUP(name.c_str());

	for(auto it : m_resources)
	{
		for(auto t : it.second)
		{
			t.second->Free();
			t.second.reset();
		}

		it.second.clear();
	}

	return true;
}

std::shared_ptr<Resource> M_ResourceManager::CreateResource(ResourceType type, const char * name, bool forceLoad)
{
	std::shared_ptr<Resource> ret = nullptr;

	if(name && !GetResource(name))
	{ //TODO
		switch (type)
		{
		case ResourceType::RES_GEOMETRY:
			ret = std::make_shared<R_Geometry>(name);
			break;

		case ResourceType::RES_SHADER:

			break;

		case ResourceType::RES_TEXTURE:

			break;

		case ResourceType::RES_MATERIAL:

			break;

		case ResourceType::RES_MODEL:

			break;

		case ResourceType::RES_SCENE:

			break;

		default:
			LOG(LOG_ERROR, "Invalid resource type on creation.");
		}

		if (ret)
		{
			m_resources[type].insert(std::pair<std::string, std::shared_ptr<Resource>>(std::string(name), ret));

			if(forceLoad) ret->Load();
		}
	}
	else
	{
		LOG(LOG_ERROR, "Invalid resource name or resource already created.");
	}	

	return ret;
}

std::shared_ptr<Resource> M_ResourceManager::GetResource(const char * resourceName)
{
	if(resourceName)
	{
		for (uint i = RES_NONE + 1; i < RES_ERROR; ++i)
		{
			auto it = GetResourceWithType(resourceName, (ResourceType)i);
			if (it) return it;
		}
	}

	return nullptr;
}

std::shared_ptr<Resource> M_ResourceManager::GetResourceWithType(const char * resourceName, ResourceType type)
{
	if(resourceName)
	{
		auto it = m_resources.find(type);
		if (it != m_resources.end())
		{
			auto t = it->second.find(std::string(name));
			return t != it->second.end() ? t->second : nullptr;
		}
	}

	return nullptr;
}
