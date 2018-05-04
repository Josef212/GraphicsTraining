#include "ResourceManager.h"

#include <iostream>

#include "GeometryDefs.h"
#include "Defs.h"
#include "Resource.h"
#include "Geometry.h"
#include "Shader.h"
#include "Material.h"
#include "ComplexMaterial.h"
#include "Model.h"
#include "ModelLoader.h"


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

void ResourceManager::Init()
{
	std::cout << "\tRESOURCE MANAGER: Init." << std::endl;

	SetDefaultResources();
}

void ResourceManager::AddResource(Resource * res)
{
	resources.push_back(res);
}

void ResourceManager::RemoveResource(Resource* res, bool forceDefaults)
{
	auto it = std::find(resources.begin(), resources.end(), res);
	if(it != resources.end())
	{
		if (!IsDefaultResource(res) || forceDefaults)
		{
			res->Free();
			RELEASE(res);
			resources.erase(it);
		}
	}
}

void ResourceManager::RemoveResources(Resource** res, int count, bool forceDefaults)
{
	if(res)
	{
		for(int i = 0; i < count; ++i)
		{
			RemoveResource(res[i], forceDefaults);
		}
	}
}

void ResourceManager::RemoveResources(std::vector<Resource*>& res, bool forceDefaults)
{
	for(auto it = res.begin(); it != res.end();)
	{
		RemoveResource((*it), forceDefaults);
		it = res.erase(it);
	}
}

void ResourceManager::RemoveAllResources(bool forceDefaults)
{
	for(auto it = resources.begin(); it != resources.end();)
	{
		bool def = IsDefaultResource((*it));
		if((def && forceDefaults) || !def)
		{
			(*it)->Free();
			RELEASE((*it));
			it = resources.erase(it);
		}
		else
		{
			++it;
		}
	}
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

bool ResourceManager::IsDefaultResource(Resource* res)
{
	// TODO: Keep adding resources 
	if (res == defaultResources.triangleGeo || res == defaultResources.quadGeo || res == defaultResources.cubeGeo || res == defaultResources.planeGeo || res == defaultResources.simpleSh || res == defaultResources.simpleMat)
		return true;

	return false;
}

void ResourceManager::SetDefaultResources()
{
	// Geometries
	defaultResources.triangleGeo = new Geometry("Def triangle geo", triangleVerticesCount, triangleIndicesCount, triangleIndices, triangleVertices, triangleNormals, triangleTexCoords, triangleColors);
	defaultResources.quadGeo = new Geometry("Def quad geo", quadVerticesCount, quadIndicesCount, quadIndices, quadVertices, quadNormals, quadTexCoords, quadColors);
	defaultResources.cubeGeo = new Geometry("Def cube geo", cubeVerticesCount, cubeIndicesCount, cubeIndices, cubeVertices, cubeNormals, cubeTexCoords, cubeColors);
	defaultResources.planeGeo = new Geometry("Def plane geo", planeVerticesCount, planeIndicesCount, planeIndices, planeVertices, planeNormals, planeTexCoords, planeColors);

	// Shaders
	defaultResources.simpleSh = new Shader("Def simple shader", "./Data/Shaders/simple.vert", "./Data/Shaders/simple.frag");

	// Materials
	defaultResources.simpleMat = new Material("Def simple material", defaultResources.simpleSh);

	// Models
}
