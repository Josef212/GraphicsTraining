#include "DepthFrameBuffer.h"
#include <cstddef>


DepthFrameBuffer::DepthFrameBuffer() : width(1024), height(1024)
{
}

DepthFrameBuffer::DepthFrameBuffer(int width, int height)
{
	Create(width, height);
}


DepthFrameBuffer::~DepthFrameBuffer()
{
	Destroy();
}

void DepthFrameBuffer::Create(int width, int height)
{
	if(width != this->width || height != this->height)
	{
		this->width = width;
		this->height = height;

		// Create the frame buffer
		glGenFramebuffers(1, &depthMapFBO);
		// Crete the texture buffer and set parameters
		glGenTextures(1, &depthMapTex);
		glBindTexture(GL_TEXTURE_2D, depthMapTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->width, this->height, GL_DEPTH_COMPONENT, 0, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Attach the texture to the depth buffer
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTex, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void DepthFrameBuffer::Destroy()
{
	glDeleteFramebuffers(1, &depthMapFBO);
	glDeleteTextures(1, &depthMapTex);
}

void DepthFrameBuffer::Resize(int width, int height)
{
	if(this->width != width || this->height != height)
	{
		Destroy();
		Create(width, height);
	}
}

void DepthFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
}

void DepthFrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
