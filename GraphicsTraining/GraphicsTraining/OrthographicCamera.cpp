#include "OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>


OrthographicCamera::OrthographicCamera()
{
}


OrthographicCamera::~OrthographicCamera()
{
}

void OrthographicCamera::CalcProjection()
{
	projection = glm::ortho(-Size, Size, -Size, Size, 1.0f, 100.0f);
}

void OrthographicCamera::OnViewportResize()
{
}
