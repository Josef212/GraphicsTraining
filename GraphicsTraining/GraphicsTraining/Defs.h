#ifndef __DEFS_H__
#define __DEFS_H__

#define RELEASE( x )\
	{\
		if(x != nullptr)\
		{\
			delete x;\
			x = nullptr;\
		}\
	}

#define RELEASE_ARRAY( x )\
	{\
		if(x != nullptr)\
		{\
			delete[] x;\
			x = nullptr;\
		}\
	}

#define DEFAULT_WIN_WIDTH 1280
#define DEFAULT_WIN_HEIGHT 720

#define DEBUG_LOG false

enum MatPropertyValueType
{
	MAT_INT,
	MAT_FLOAT,
	MAT_VEC2,
	MAT_VEC3,
	MAT_VEC4,
	MAT_MAT2,
	MAT_MAT3,
	MAT_MAT4,
	MAT_TEXTURE,
	MAT_BOOL,
	MAT_NONE
};

enum MatPropertyType
{
	MPVT_UNIFORM = 0,
	MPVT_LOCATION = 1
};

const char* GetMatPropertyValueTypeStr(MatPropertyValueType type);

#endif // __DEFS_H__