#include "CubeMapFrameBuffer.h"
#include <cstddef>


CubeMapFrameBuffer::CubeMapFrameBuffer() : width(width), height(height)
{
}

CubeMapFrameBuffer::CubeMapFrameBuffer(int width, int height)
{
	Create(width, height);
}


CubeMapFrameBuffer::~CubeMapFrameBuffer()
{
	Destroy();
}

void CubeMapFrameBuffer::Create(int width, int height)
{
	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthCubeMap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
	for (unsigned int i = 0; i < 6; ++i)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindBuffer(GL_FRAMEBUFFER, 0);
}

void CubeMapFrameBuffer::Destroy()
{
	glDeleteFramebuffers(1, &depthMapFBO);
	glDeleteTextures(1, &depthCubeMap);
}

void CubeMapFrameBuffer::Resize(int width, int height)
{
	if(width != this->width || height != this->height)
	{
		Destroy();
		Create(width, height);
	}
}
