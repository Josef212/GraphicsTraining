#ifndef __R_GEOMETRY_H__
#define __R_GEOMETRY_H__

#include "Resource.h"

class R_Geometry : public Resource
{
public:
	R_Geometry(const char* name);
	R_Geometry(std::string name);
	virtual ~R_Geometry();
};

#endif