#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Resource.h"

#include <string>

class Texture : public Resource
{
public:
	Texture(const char* name);
	virtual ~Texture();

	void Load() override;
	void Free() override;

	void LoadTexture(const char* path, bool flipY = false);

	bool Loaded()const { return textureID != 0; }

	unsigned int TextureID()const { return textureID; }

private:
	unsigned int textureID = 0;
	int width = 0, height = 0, nrChannels = 0;

	std::string path = "";
};

#endif // !__TEXTURE_H__