#include "FrameBuffer.h"
#include <iostream>


FrameBuffer::FrameBuffer() : width(1024), height(1024)
{
}

FrameBuffer::FrameBuffer(int width, int height)
{
	Create(width, height);
}


FrameBuffer::~FrameBuffer()
{
}

void FrameBuffer::Create(int width, int height)
{
	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Texture attachments
	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	// TODO: Let add other textures.


	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Destroy();
		std::cout << "Could not create frame buffer." << std::endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Destroy()
{
	glDeleteFramebuffers(1, &fbo);
}

void FrameBuffer::Resize(int width, int height)
{
	if(width != this->width || height != this->height)
	{
		Destroy();
		Create(width, height);
	}
}

void FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
