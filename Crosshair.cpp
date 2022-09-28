#include "Crosshair.h"

std::vector<GLfloat> Crosshair::vertices = {};
std::vector<GLuint>Crosshair::indices = {};

void Crosshair::initStatic(float gap, float length, float width) {
	vertices.clear();
	indices.clear();
	
	// left rect
	addVertexPos(-gap -length, -width / 2.0f);	// vert 0
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 0
	addVertexPos(-gap - length, width / 2.0f);	// vert 1
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 1
	addVertexPos(-gap , width / 2.0f);			// vert 2
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 2
	addVertexPos(-gap, -width / 2.0f);			// vert 3
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 3

	// top rect
	addVertexPos(-width / 2.0f, gap);			// vert 4
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 4
	addVertexPos(-width / 2.0f, gap + length);	// vert 5
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 5
	addVertexPos(width / 2.0f, gap + length);	// vert 6
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 6
	addVertexPos(width / 2.0f, gap );			// vert 7
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 7

	// right rect
	addVertexPos(gap + length, -width / 2.0f);	// vert 8
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 8
	addVertexPos(gap + length, width / 2.0f);	// vert 9
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 9
	addVertexPos(gap, width / 2.0f);			// vert 10
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 10
	addVertexPos(gap, -width / 2.0f);			// vert 11
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 11

	// bottom rect
	addVertexPos(-width / 2.0f, -gap);			// vert 12
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 12
	addVertexPos(-width / 2.0f, -gap - length);	// vert 13
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 13
	addVertexPos(width / 2.0f, -gap - length);	// vert 14
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 14
	addVertexPos(width / 2.0f, -gap);			// vert 15
	addVertexCol(0.0f, 1.0f, 0.0f);				// vert 15

	// add indices
	// left rect
	addInd(0, 1, 2);
	addInd(0, 2, 3);
	
	// top rect
	addInd(4, 5, 6);
	addInd(4, 6, 7);

	// right rect
	addInd(8, 9, 10);
	addInd(8, 10, 11);

	// bottom rect
	addInd(12, 13, 14);
	addInd(12, 14, 15);
}

void Crosshair::addVertexPos(GLfloat x, GLfloat y) {
	Crosshair::vertices.push_back(x);
	Crosshair::vertices.push_back(y);
}
void Crosshair::addVertexCol(GLfloat r, GLfloat g, GLfloat b) {
	Crosshair::vertices.push_back(r);
	Crosshair::vertices.push_back(g);
	Crosshair::vertices.push_back(b);
}
void Crosshair::addInd(GLuint vert1, GLuint vert2, GLuint vert3) {
	Crosshair::indices.push_back(vert1);
	Crosshair::indices.push_back(vert2);
	Crosshair::indices.push_back(vert3);
}

Crosshair::Crosshair(Shader& shader) : shader(shader)
{
	vao = VAO();
	vao.Bind();
	vbo = VBO(vertices.data(), vertices.size() * sizeof(GLfloat));
	ebo = EBO(indices.data(), indices.size() * sizeof(GLuint));
	num_triangles = indices.size() / 3;

	vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 5 * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Crosshair::Draw() {
	shader.Activate();

	vao.Bind();

	glDrawElements(GL_TRIANGLES, num_triangles * 3, GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

// Deletes all Vertex buffers 
void Crosshair::Delete() {
	// Frees memory
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
}