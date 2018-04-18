#pragma once

#include <GL/glew.h>

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(int width, int height);
	virtual ~FrameBuffer();

	void Create(int width, int height);
	void Destroy();
	void Resize(int width, int height);

	void Bind();
	void UnBind();

	GLuint FBO()const { return fbo; }
	GLuint ColorTexture()const { return colorTexture; }

	int Width() const { return width; }
	int Height() const { return height; }

private:
	GLuint fbo = 0;
	GLuint colorTexture = 0;

	int width, height;
};

