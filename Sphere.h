#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include"Drawable.h"


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

#include <vector>

// Sphere with smooth shading
class Sphere : public Drawable {
private:
	// static fields common for all objects
	static const int DEFAULT_SECTOR_COUNT = 36;
	static const int DEFAULT_STACK_COUNT = 18;
	static std::vector<GLfloat> vertices;
	static std::vector<GLuint> indices;

	static void addVertexPos(GLfloat x, GLfloat y, GLfloat z);
	static void addVertexCol(GLfloat r, GLfloat g, GLfloat b);
	static void addVertexNorm(GLfloat x, GLfloat y, GLfloat z);
	static void addInd(GLuint vert1, GLuint vert2, GLuint vert3);

	// object specific 
	glm::vec3 color;

public:
	// Fills vectors with vertices and indices
	static void initStatic(int sector_count = DEFAULT_SECTOR_COUNT, int stack_count = DEFAULT_STACK_COUNT);

	Sphere(glm::vec3 position, float scale, glm::vec3 color, Shader& shader);

	// Handles what should be done in delta time
	void HandleTime(double dt);

	// Draw object
	void Draw();
};

#endif