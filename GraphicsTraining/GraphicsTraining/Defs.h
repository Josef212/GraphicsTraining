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

#define CLAMP(value, min, max) (value > max ? max : (value < min ? min : value))
#define CLAMP01(x) (CLAMP(x, 0.f, 1.f))
#define CLAMP_ROT(x) (CLAMP(x, 0.f, 360.f))
#define CLAMP_ROT_ROUND(x) (x > 360.f ? 0.f : (x < 0.f ? 360.f : x))
#define CLAMP_UP(value, max) (value > max ? max : value)
#define CLAMP_DOWN(value, min) (value < min ? min : value)

#define MAX (value, value2) value > value2 ? value : value2
#define MIN (value, value2) value < value2 ? value : value2

#define DEBUG_LOG false

enum MatPropertyValueType
{
	MAT_INT = 0,
	MAT_FLOAT,
	MAT_VEC2,
	MAT_VEC3,
	MAT_VEC4,
	MAT_MAT2,
	MAT_MAT3,
	MAT_MAT4,
	MAT_TEXTURE,
	MAT_BOOL,
	MAT_BOOL_PTR,
	MAT_NONE
};

enum MatPropertyType
{
	MPVT_UNIFORM = 0,
	MPVT_LOCATION = 1
};

const char* GetMatPropertyValueTypeStr(MatPropertyValueType type);

#endif // __DEFS_H__