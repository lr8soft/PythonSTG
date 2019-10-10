#pragma once
#ifndef _Camera_h_
#define _Camera_h_
#include <glm/glm.hpp>
class Camera {
private:
	glm::vec3 pos = glm::vec3(0.0f, 0.0f, 2.0f);
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float fovy = 45.0f;
	float zNear = 0.1f, zFar = 1000.0f;
public:
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

	void setPosition(glm::vec3 pos);
	void setTarget(glm::vec3 target);
	void setUp(glm::vec3 up);
};
#endif