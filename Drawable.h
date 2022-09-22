#ifndef DRAWABLE_CLASS_H
#define DRAWABLE_CLASS_H

#include <glad/glad.h>

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

class Drawable{
private:
	// Object specific fields

	// Object's position in 3D space
	glm::vec3 position;
	// Size of the object
	float scale;
	// Object's rotation around particular axis
	// Rotation around X axis
	float rot_X;
	// Rotation around Y axis
	float rot_Y;
	// Rotation around Z axis
	float rot_Z;

	// Matrices
	// Scaling matrix
	glm::mat4 scaleMat = glm::mat4(1.0f);
	// Rotation matrix
	glm::mat4 rotateMat = glm::mat4(1.0f);
	// Translate matrix
	glm::mat4 translateMat = glm::mat4(1.0f);

	// Transform matrix that is multiplication of matrices above
	glm::mat4 transformMat = glm::mat4(1.0f);

protected:
	// Vertex Array Object
	VAO vao;
	// Vertex Buffer Object
	VBO vbo;
	// Elements Buffer Object
	EBO ebo;
	int num_triangles;
	// Shader program
	Shader& shader;


public:
	void initStatic();

	Drawable(glm::vec3 position, float scale, float rot_X, float rot_Y, float rot_Z, Shader& shader);

	// Handles what should be done in delta time
	void HandleTime(double dt);

	// Draw object
	void Draw();

	// Deletes all Vertex buffers
	void Delete();

	//gettter and setter for position
	glm::vec3 getPosition() { return position; }
	void setPosition(glm::vec3 position);

	//gettter and setter for scale
	float getScale() { return scale; }
	void setScale(float scale);

	//gettter and setter for rotation
	float getRotation_X() { return rot_X; }
	float getRotation_Y() { return rot_Y; }
	float getRotation_Z() { return rot_Z; }
	void setRotation(float rot_X, float rot_Y, float rot_Z);

	// for setter to take effect this must be called
	void updateTransformMat();



	// AXIS
	static const glm::vec3 X_AXIS;
	static const glm::vec3 Y_AXIS;
	static const glm::vec3 Z_AXIS;
};


#endif