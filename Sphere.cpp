#include "Sphere.h"

#include <cmath>

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "ShaderProgram.h"

std::vector<GLfloat> Sphere::vertices = {};
std::vector<GLuint> Sphere::indices = {};

void Sphere::initStatic(int sectorCount, int stackCount) {
	const float PI = acos(-1);
	const float RADIUS = 1.0f;

	// Clear vectors of vertices and indices
	vertices.clear();	// Vercices x, y, z, r, g, b, norm_x, norm_y, norm_z
	indices.clear();	// Indices int vert1, int vert2, int vert 3

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;

	float lengthInv = 1.0f / RADIUS;

	// Adding Vertices
	for (int i = 0; i <= stackCount; i++) {
		float stackAngle = PI / 2 - i * stackStep; // from PI to -PI

		float z = RADIUS * sin(stackAngle);
		float cosStackAngle = cos(stackAngle);

		for (int j = 0; j <= sectorCount; j++) {
			float sectorAngle = j * sectorStep;	//from 0 to 2PI

			float x = RADIUS * cosStackAngle * cos(sectorAngle);
			float y = RADIUS * cosStackAngle * sin(sectorAngle);

			addVertexPos(x, y, z);
			addVertexNorm(x * lengthInv, y * lengthInv, z* lengthInv);
		}
	}
	// indices
	//  k1--k1+1
	//  |  / |
	//  | /  |
	//  k2--k2+1
	// Adding Indices
	for (int i = 0; i < stackCount; i++) {
		unsigned int k1 = i* (sectorCount+1);
		unsigned int k2 = k1 + sectorCount + 1;
		for (int j = 0; j < sectorCount; j++) {
			// 2 triangles per sector
			// 1 triangle per 1st and last sector
			if (i != 0) {
				// k1 != (k1 + 1)
				addInd(k1, k2, k1 + 1);
			}
			if (i != (stackCount - 1)) {
				// k2 != (k2 + 1)
				addInd(k1 + 1, k2, k2 + 1);
			}
			k1++;
			k2++;
		}
	}

}

void Sphere::addVertexPos(GLfloat x, GLfloat y, GLfloat z) {
	Sphere::vertices.push_back(x);
	Sphere::vertices.push_back(y);
	Sphere::vertices.push_back(z);
}
void Sphere::addVertexCol(GLfloat r, GLfloat g, GLfloat b) {
	Sphere::vertices.push_back(r);
	Sphere::vertices.push_back(g);
	Sphere::vertices.push_back(b);
}
void Sphere::addVertexNorm(GLfloat x, GLfloat y, GLfloat z) {
	Sphere::vertices.push_back(x);
	Sphere::vertices.push_back(y);
	Sphere::vertices.push_back(z);
}
void Sphere::addInd(GLuint vert1, GLuint vert2, GLuint vert3) {
	Sphere::indices.push_back(vert1);
	Sphere::indices.push_back(vert2);
	Sphere::indices.push_back(vert3);
}

Sphere::Sphere(glm::vec3 position, float scale, glm::vec3 color, Shader& shader)
	: Drawable(position, scale, 0.0f, 0.0f, 0.0f, shader), color(color)
{
	vao = VAO();
	vao.Bind();
	vbo = VBO(vertices.data(), vertices.size() * sizeof(GLfloat));
	ebo = EBO(indices.data(), indices.size() * sizeof(GLuint));
	num_triangles = indices.size() / 3;

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();
}

void Sphere::HandleTime(double dt) {

}

void Sphere::Draw() {
	shader.Activate();
	glUniform3f(glGetUniformLocation(shader.ID, "color"), color.x, color.y, color.z);
	Drawable::Draw();
}