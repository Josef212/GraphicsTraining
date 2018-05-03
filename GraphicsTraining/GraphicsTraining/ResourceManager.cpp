#include "ResourceManager.h"

#include <iostream>

#include "Defs.h"
#include "Resource.h"


ResourceManager::ResourceManager()
{
	std::cout << "\tRESOURCE MANAGER: Creation." << std::endl;
}


ResourceManager::~ResourceManager()
{
	std::cout << "\tRESOURCE MANAGER: Destruction." << std::endl;

	for(auto it : resources)
	{
		it->Free();
		RELEASE(it);
	}
}

void ResourceManager::AddResource(Resource * res)
{
	resources.push_back(res);
}

unsigned int ResourceManager::GatherResourceOfType(ResourceType type, std::vector<Resource*>& vec)
{
	vec.clear();

	for(auto it : resources)
	{
		if (it->GetType() == type)
			vec.push_back(it);
	}

	return vec.size();
}
