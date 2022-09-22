#include "Cube.h"

// Vertices coordinates
GLfloat Cube::vertices[] = { 
  //     COORDINATES      /        COLORS       //
	 1.0f,  1.0f,  1.0f,     0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, -1.0f,     0.0f, 0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f,     0.0f, 1.0f, 0.0f,
	 1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 1.0f,
	-1.0f,  1.0f,  1.0f,     1.0f, 0.0f, 0.0f,
	-1.0f,  1.0f, -1.0f,     1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f,  1.0f,     1.0f, 1.0f, 0.0f,
	-1.0f, -1.0f, -1.0f,     1.0f, 1.0f, 1.0f,
};

// Indices for vertices order
GLuint Cube::indices[] = {
	0, 1, 2,
	1, 2, 3,
	0, 1, 5,
	0, 4, 5,
	0, 2, 4,
	2, 4, 6,
	1, 3, 5,
	3, 5, 7,
	2, 3, 6,
	3, 6, 7,
	4, 5, 6,
	5, 6, 7
};



Cube::Cube(glm::vec3 position, float scale, Shader& shader)
	: Drawable(position, scale, 0.0f, 0.0f, 0.0f, shader)
{
	vao = VAO();
	vao.Bind();
	vbo = VBO(vertices, sizeof(vertices));
	ebo = EBO(indices, sizeof(indices));
	num_triangles = sizeof(indices) / sizeof(GLuint) / 3;

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

// Handles what should be done in delta time
void Cube::HandleTime(double dt) {
	double rot_Y = getRotation_Y();
	rot_Y += dt * rotation_around_Y_speed;
	while (rot_Y > glm::radians(360.0f)) {
		rot_Y -= glm::radians(360.0f);
	}
	while (rot_Y < 0) {
		rot_Y += glm::radians(360.0f);
	}
	setRotation(getRotation_X(), rot_Y, getRotation_Z());
	updateTransformMat();
}

