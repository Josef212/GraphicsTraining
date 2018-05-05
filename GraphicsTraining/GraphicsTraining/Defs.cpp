#include "Defs.h"

const char* GetMatPropertyValueTypeStr(MatPropertyValueType type)
{
	static const char* rets[] = {
		"INT", "FLOAT", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "TEXTURE", "BOOL", "BOOL_PTR", "NONE"
	};

return rets[type];
}