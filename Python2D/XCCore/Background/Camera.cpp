#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../XCFrameInfo.h"
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(pos, target, up);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(fovy), (float)XCFrameInfo::ScreenWidth / XCFrameInfo::ScreenHeight, zNear, zFar);
}

void Camera::setPosition(glm::vec3 p)
{
	pos = p;
}

void Camera::setTarget(glm::vec3 t)
{
	target = t;
}

void Camera::setUp(glm::vec3 u)
{
	up = u;
}
