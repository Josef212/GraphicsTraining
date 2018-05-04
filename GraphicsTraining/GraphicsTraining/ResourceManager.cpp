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
