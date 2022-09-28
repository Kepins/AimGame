#ifndef CROSSHAIR_CLASS_H
#define CROSSHAIR_CLASS_H


#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

#include <vector>

class Crosshair {

private:
	static std::vector<GLfloat> vertices;
	static std::vector<GLuint> indices;

	static void addVertexPos(GLfloat x, GLfloat y);
	static void addVertexCol(GLfloat r, GLfloat g, GLfloat b);
	static void addInd(GLuint vert1, GLuint vert2, GLuint vert3);

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
	// Fills vectors with vertices and indices
	static void initStatic(float gap, float length, float width);

	Crosshair(Shader& shader);

	// Draws object
	void Draw();

	// Deletes all Vertex buffers 
	void Delete();
};

#endif