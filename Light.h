#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include<glm/glm.hpp>

#include<glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"

class Light {
private:
	glm::vec4 color;
	glm::vec3 position;
public:
	Light(glm::vec4 color, glm::vec3 position);

	void ExportUniforms(Shader& shader, const char* colorUni, const char* positionUni);
};


#endif