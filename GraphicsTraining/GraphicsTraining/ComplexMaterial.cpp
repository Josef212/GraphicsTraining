#include "ComplexMaterial.h"

#include "Shader.h"
#include "Texture.h"
#include <GL/glew.h>


MatProperty::MatProperty(const char* name, int value) : propertyName(name), propertyType(MAT_INT)
{
	propertyValue._int = value;
}

MatProperty::MatProperty(const char* name, float value) : propertyName(name), propertyType(MAT_FLOAT)
{
	propertyValue._float = value;
}

MatProperty::MatProperty(const char* name, float* value, MatPropertyValueType type) : propertyName(name), propertyType(type)
{
	propertyValue._floatPtr = value;
}

MatProperty::MatProperty(const char * name, Texture * value) : propertyName(name), propertyType(MAT_TEXTURE)
{
	propertyValue._texture = value;
}

MatProperty::~MatProperty()
{
}

// --------------------------------------------------------------------------

ComplexMaterial::ComplexMaterial(const char * name) : Material(name)
{
}

ComplexMaterial::ComplexMaterial(const char * name, Shader * sh) : Material(name, sh)
{
}

ComplexMaterial::~ComplexMaterial()
{
	for (auto it = properties.begin(); it != properties.end();)
	{
		//RELEASE((*it));
		it = properties.erase(it);
	}
}

void ComplexMaterial::AddProperty(MatProperty * prop)
{
	if(prop) properties.push_back(prop);
}

void ComplexMaterial::RemoveProperty(MatProperty * prop)
{
	if(prop)
	{
		for (auto it = properties.begin(); it != properties.end();)
		{
			if ((*it) == prop)
			{
				it = properties.erase(it);
				RELEASE(*it);
			}
			else
			{
				++it;
			}
		}
	}
}

void ComplexMaterial::RemoveProperty(const char * name)
{
	if(name)
	{
		for (auto it = properties.begin(); it != properties.end();)
		{
			if ((*it)->propertyName == name)
			{
				it = properties.erase(it);
				RELEASE(*it);
			}
			else
			{
				++it;
			}
		}
	}
}

void ComplexMaterial::OnFree()
{
	for(auto it : properties)
	{
		RELEASE(it);
	}
}

void ComplexMaterial::SendInfo(Scene* scene) const
{
	int texturesCount = 0;

	for(auto it : properties)
	{
		if(it)
		{
			switch (it->propertyType)
			{
			case MatPropertyValueType::MAT_INT:
				shader->SetInt(it->propertyName.c_str(), it->propertyValue._int);
				break;

			case MatPropertyValueType::MAT_FLOAT:
				shader->SetFloat(it->propertyName.c_str(), it->propertyValue._float);
				break;

			case MatPropertyValueType::MAT_VEC2:
				shader->SetVec2(it->propertyName.c_str(), it->propertyValue._floatPtr);
				break;

			case MatPropertyValueType::MAT_VEC3:
				shader->SetVec3(it->propertyName.c_str(), it->propertyValue._floatPtr);
				break;

			case MatPropertyValueType::MAT_VEC4:
				shader->SetVec4(it->propertyName.c_str(), it->propertyValue._floatPtr);
				break;

			case MatPropertyValueType::MAT_MAT2:
				shader->SetMat2(it->propertyName.c_str(), it->propertyValue._floatPtr);
				break;

			case MatPropertyValueType::MAT_MAT3:
				shader->SetMat3(it->propertyName.c_str(), it->propertyValue._floatPtr);
				break;

			case MatPropertyValueType::MAT_MAT4:
				shader->SetMat4(it->propertyName.c_str(), it->propertyValue._floatPtr);
				break;

			case MatPropertyValueType::MAT_TEXTURE:
				glActiveTexture(GL_TEXTURE0 + texturesCount);
				glBindTexture(GL_TEXTURE_2D, it->propertyValue._texture->TextureID());
				shader->SetInt(it->propertyName.c_str(), texturesCount);
				++texturesCount;
				break;
			}
		}
	}
}
