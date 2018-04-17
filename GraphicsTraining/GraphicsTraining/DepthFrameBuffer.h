#include <GL/glew.h>

class DepthFrameBuffer
{
public:
	DepthFrameBuffer();
	DepthFrameBuffer(int width, int height);
	virtual ~DepthFrameBuffer();

	void Create(int width, int height);
	void Destroy();
	void Resize(int width, int height);

	void Bind();
	void UnBind();

	GLuint FBO()const { return depthMapFBO; }
	GLuint DepthMapTex()const { return depthMapTex; }
	int Width()const { return width; }
	int Height()const { return height; }

private:
	GLuint depthMapFBO = 0;
	GLuint depthMapTex = 0;

	int width, height;
};

