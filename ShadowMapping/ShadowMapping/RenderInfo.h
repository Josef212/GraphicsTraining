#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader;
class Geometry;
class FrameBuffer;
class DepthFrameBuffer;

struct RenderInfo
{
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

	Shader* shader;
	Geometry* geometry;

	FrameBuffer* frameBuffer;
	DepthFrameBuffer* depthFrameBuffer;


	// Texture
	// Other possible info
	
	void SetMatrices(glm::mat4& proj, glm::mat4& view, glm::mat4& model);

	void ResetModel();

};