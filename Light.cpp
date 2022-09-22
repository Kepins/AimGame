#include "Light.h"


Light::Light(glm::vec4 color, glm::vec3 position)
	: color(color), position(position)
{}


void Light::ExportUniforms(Shader& shader, const char* colorUni, const char* positionUni) {
	glUniform4f(glGetUniformLocation(shader.ID, colorUni), color.x, color.y, color.z, color.w);
	glUniform3f(glGetUniformLocation(shader.ID, positionUni), position.x, position.y, position.z);
}