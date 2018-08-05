#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

enum ResourceType
{
	RES_NONE = 0,

	RES_GEOMETRY,
	RES_SHADER,
	RES_TEXTURE,
	RES_MATERIAL,
	RES_MODEL,
	RES_SCENE,

	RES_ERROR
};

class Resource
{
public:
	Resource(const char* name, ResourceType type) : m_resType(type)
	{
		this->m_resName = name;
	}

	Resource(std::string name, ResourceType type) : m_resType(type)
	{
		this->m_resName = name;
	}

public:
	virtual ~Resource() = default;

	virtual void Load() {}
	virtual void Free() {}

	ResourceType GetType()const { return m_resType; }
	std::string GetName()const { return m_resName; }
	const char* GetNameStr()const { return m_resName.c_str(); }


private:
	std::string m_resName = "Unmamed resource";
	ResourceType m_resType = RES_NONE;
};

#endif