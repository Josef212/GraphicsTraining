#include "ModelLoader.h"

#include "Geometry.h"
#include "Scene.h"
#include "Material.h"
#include "ComplexMaterial.h"
#include "Model.h"

#include <iostream>


ModelLoader::ModelLoader()
{
}


ModelLoader::~ModelLoader()
{
}

Model* ModelLoader::LoadModel(std::string & path, Scene * scene)
{
	Assimp::Importer importer;
	const aiScene* aiscene = importer.ReadFile(
		path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!aiscene || aiscene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !aiscene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return nullptr;
	}

	std::cout << "Loading model: " << path << std::endl;

	int lastSeparator = path.find_last_of('/');
	int lastPoint = path.find_last_of('.');
	std::string name = path.substr(lastSeparator, lastPoint - lastSeparator);

	Model* model = new Model(name.c_str());
	model->directory = path.substr(0, lastSeparator);

	ProcessNode(aiscene->mRootNode, aiscene, model, scene);

	scene->AddModel(model);

	return model;
}

void ModelLoader::ProcessNode(aiNode * node, const aiScene * aiScene, Model * model, Scene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = aiScene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, model, scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], aiScene, model, scene);
	}
}

void ModelLoader::ProcessMesh(aiMesh * mesh, Model * model, Scene * scene)
{
	Geometry* geometry = new Geometry(mesh->mName.C_Str());

	geometry->numVertices = mesh->mNumVertices;
	geometry->vertices = new float[geometry->numVertices * 3];
	memcpy(geometry->vertices, mesh->mVertices, sizeof(float) * geometry->numVertices * 3);

	if (mesh->HasFaces())
	{
		geometry->numIndices = mesh->mNumFaces * 3;
		geometry->indices = new int[geometry->numIndices];
		for (int i = 0; i < mesh->mNumFaces; ++i)
		{
			if (mesh->mFaces[i].mNumIndices != 3)
				std::cout << "WARNING: geometry face with != 3 indices" << std::endl;
			memcpy(&geometry->indices[i * 3], mesh->mFaces[i].mIndices, 3 * sizeof(int));
		}
	}

	if (mesh->HasNormals())
	{
		geometry->normals = new float[geometry->numVertices * 3];
		memcpy(geometry->normals, mesh->mNormals, sizeof(float) * geometry->numVertices * 3);
	}

	if (mesh->HasTextureCoords(0))
	{
		geometry->texCoords = new float[geometry->numVertices * 2];
		aiVector3D* tmp = mesh->mTextureCoords[0];
		for (unsigned int i = 0; i < geometry->numVertices * 2; i += 2)
		{
			geometry->texCoords[i] = tmp->x;
			geometry->texCoords[i + 1] = tmp->y;
			++tmp;
		}
	}

	if (mesh->HasVertexColors(0))
	{
		geometry->colors = new float[geometry->numVertices * 3];
		memcpy(geometry->colors, mesh->mColors, sizeof(float) * geometry->numVertices * 3);
	}

	geometry->SendInfoToVRAM();

	// TODO: Should process material here

	model->AddMesh(geometry, scene->GetDefaultMaterial());
}
