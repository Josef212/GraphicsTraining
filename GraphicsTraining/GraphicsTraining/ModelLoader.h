#ifndef __MODELLOADER_H__
#define __MODELLOADER_H__

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>	
#include <assimp/postprocess.h>

class Scene;
class Model;

class ModelLoader
{
public:
	ModelLoader(std::string& path, Scene* scene);
	virtual ~ModelLoader();

private:
	void LoadModel(std::string& path, Scene* scene);

	void ProcessNode(aiNode* node, const aiScene* aiScene, Model* model, Scene* scene);
	void ProcessMesh(aiMesh* mesh, Model* model, Scene* scene);
};

#endif // !__MODELLOADER_H__