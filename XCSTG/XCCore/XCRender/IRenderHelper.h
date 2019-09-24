#pragma once
#ifndef _IRENDER_MANAGER_H_
#define _IRENDER_MANAGER_H_
#include <glm/glm.hpp>
class IRenderHelper {
public:
	virtual void Render(glm::vec3 renderPos, glm::vec4 coverColor,
		glm::vec3 scaleSize = glm::vec3(1.0f, 1.0f, 1.0f), float *dataPointer = nullptr) = 0;
	virtual void Release() = 0;
};
#endif