#include "Model.h"

#include "Scene.h"

#include "Camera.h"
#include "PerspectiveCamera.h"
#include "OrthographicCamera.h"

#include "Shader.h"
#include "Geometry.h"
#include "Material.h"
#include "ComplexMaterial.h"


Model::Model(const char* name) : Resource(name, RES_MODEL)
{
	modelMat = glm::mat4(1.f);
}

Model::Model(const char * name, Geometry * geometry, Material * material) : Resource(name, RES_MODEL)
{
	modelMat = glm::mat4(1.f);

	AddMesh(geometry, material);
}


Model::~Model()
{
}

void Model::AddMesh(Geometry * geometry, Material * material)
{
	meshes.push_back(std::pair<Geometry*, Material*>(geometry, material));
}

void Model::SetGeometry(Geometry * geometry, int index)
{
	if(index>= 0 && index < meshes.size())
	{
		meshes[index].first = geometry;
	}
}

void Model::SetMaterial(Material * material, int index)
{
	if (index >= 0 && index < meshes.size())
	{
		meshes[index].second = material;
	}
}

std::pair<Geometry*, Material*> Model::GetMesh(int index) const
{
	if (index >= 0 && index < meshes.size())
	{
		return meshes[index];
	}

	return std::pair<Geometry*, Material*>(nullptr, nullptr);
}

Geometry * Model::GetGeometry(int index) const
{
	if (index >= 0 && index < meshes.size())
	{
		return meshes[index].first;
	}

	return nullptr;
}

Material * Model::GetMaterial(int index) const
{
	if (index >= 0 && index < meshes.size())
	{
		return meshes[index].second;
	}

	return nullptr;
}

void Model::Render(Scene * scene)
{
	for(auto it : meshes)
	{
		Geometry* geometry = it.first;
		Material* material = it.second;

		if(geometry)
		{
			if(!material) material = scene->GetDefaultMaterial();

			material->InitRender();

			material->GetShader()->SetMat4("model", modelMat);
			material->GetShader()->SetMat4("view", scene->GetActiveCamera()->GetViewMatrix());
			material->GetShader()->SetMat4("projection", scene->GetActiveCamera()->GetProjectionMatrix());

			material->SendInfo(scene);

			glBindVertexArray(geometry->EBO());

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->IdIndices());

			glDrawElements(GL_TRIANGLES, geometry->CountIndices(), GL_UNSIGNED_INT, NULL);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			material->EndRender();
		}
	}
}
