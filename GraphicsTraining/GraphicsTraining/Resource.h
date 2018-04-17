#ifndef __RESOURCE_H__
#define __RESOURCE_H__

#include <string>

class Resource
{
public:
	Resource(const char* _name)
	{
		name = _name;
	}

	Resource(std::string _name)
	{
		name = _name;
	}

	virtual ~Resource()
	{}

	virtual void Load() {}
	virtual void Free() {}

private:

public:
	std::string name = "Non named resource";

private:
};

#endif // !__RESOURCE_H__