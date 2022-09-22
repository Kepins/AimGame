#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include"Drawable.h"


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

class Cube: public Drawable{
private:
	// static fields common for all objects
	static GLfloat vertices[];
	static GLuint indices[];

	// object specific 
	float rotation_around_Y_speed = -glm::radians(45.0f);

public:
	Cube(glm::vec3 position, float scale, Shader& shader);

	// Handles what should be done in delta time
	void HandleTime(double dt);
};

#endif