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


#endif // __DEFS_H__