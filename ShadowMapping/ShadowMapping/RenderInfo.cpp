#include "RenderInfo.h"

#include "Shader.h"
#include "Geometry.h"
#include "DepthFrameBuffer.h"


void RenderInfo::SetMatrices(glm::mat4 & proj, glm::mat4 & view, glm::mat4 & model)
{
	this->projection = proj;
	this->view = view;
	this->model = model;
}

void RenderInfo::ResetModel()
{
	model = glm::mat4(1.0f);
}
