#pragma once

#include <gl/glew.h>

class CubeMapFrameBuffer
{
public:
	CubeMapFrameBuffer();
	CubeMapFrameBuffer(int width, int height);
	virtual ~CubeMapFrameBuffer();

	void Create(int width, int height);
	void Destroy();
	void Resize(int width, int height);


private:
	GLuint depthMapFBO = 0;
	GLuint depthCubeMap = 0; // Texture

	int width, height;

};

