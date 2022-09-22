#include "Drawable.h"


const glm::vec3 Drawable::X_AXIS = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 Drawable::Y_AXIS = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 Drawable::Z_AXIS = glm::vec3(0.0f, 0.0f, 1.0f);


Drawable::Drawable(glm::vec3 position, float scale, float rot_X, float rot_Y, float rot_Z, Shader& shader)
	: shader(shader)
{
	setPosition(position);
	setScale(scale);
	setRotation(rot_X, rot_Y, rot_Z);
	updateTransformMat();
}


void Drawable::HandleTime(double dt)
{}

void Drawable::Draw() {
	shader.Activate();

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "objMatrix"), 1, GL_FALSE, glm::value_ptr(transformMat));
	vao.Bind();

	glDrawElements(GL_TRIANGLES, num_triangles * 3, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

void Drawable::updateTransformMat() {
	transformMat = translateMat * rotateMat * scaleMat;
}

void Drawable::setPosition(glm::vec3 position)
{
	this->position = position;
	translateMat = glm::mat4(1.0f);
	translateMat = glm::translate(translateMat, position);
}

void Drawable::setScale(float scale)
{
	this->scale = scale;
	scaleMat = glm::mat4(1.0f);
	scaleMat = glm::scale(scaleMat, glm::vec3(scale, scale, scale));
}

void Drawable::setRotation(float rot_X, float rot_Y, float rot_Z)
{
	this->rot_X = rot_X;
	this->rot_Y = rot_Y;
	this->rot_Z = rot_Z;
	rotateMat = glm::mat4(1.0f);
	rotateMat = glm::rotate(rotateMat, rot_X, X_AXIS);
	rotateMat = glm::rotate(rotateMat, rot_Y, Y_AXIS);
	rotateMat = glm::rotate(rotateMat, rot_Z, Z_AXIS);
}

// Deletes all Vertex buffers 
void Drawable::Delete() {
	// Frees memory
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
}
