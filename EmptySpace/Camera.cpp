#include "Camera.h"


Camera::Camera(void)
{
}

void Camera::update()
{
	gluLookAt(pos.x, pos.y, pos.z,
		target.x, target.y, target.z,
		VECTOR_AXIS_Y.x, VECTOR_AXIS_Y.y, VECTOR_AXIS_Y.z);
}