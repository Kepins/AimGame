#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ShaderProgram.h"
#include "Cube.h"
#include "Sphere.h"
#include "Crosshair.h"
#include "Camera.h"
#include "Light.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float FOV = 60.0f;

int main() {
	// Initialize GLFW
	glfwInit();
	
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of WINDOW_WIDTH by WINDOW_HEIGHT pixels, naming it "AimGame"
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AimGame", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL) {
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();

	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = WINDOW_WIDTH, y = WINDOW_HEIGHT
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader uniColorShaderProg("uni_color.vert", "uni_color.frag");
	Shader hudShaderProg("hud.vert", "hud.frag");

	// Initialize static fields in drawable objects
	Sphere::initStatic(36, 18);
	Crosshair::initStatic(0.008f, 0.02f, 0.005f);

	// Initialize objetcs that will be used
	Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 0.0f));
	Light light(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 2.0f, -1.0f));
	Sphere sphere(glm::vec3(0.0f, 0.0f, -5.0f), 1.0f, glm::vec3(0.5f, 0.5f, 0.5f), uniColorShaderProg);
	Crosshair crosshair(hudShaderProg);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Variables to help handle time
	double prevTime = glfwGetTime();

	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double currTime = glfwGetTime();
		double dt = currTime - prevTime;
		prevTime = currTime;

		sphere.HandleTime(dt);

		camera.Inputs(window);
		uniColorShaderProg.Activate();
		camera.Matrix(FOV, 0.1f, 100.0f, uniColorShaderProg, "camMatrix");
		light.ExportUniforms(uniColorShaderProg, "lightColor", "lightPos");

		hudShaderProg.Activate();
		camera.OrthoMatrix(hudShaderProg, "orthoMatrix");

		// 3D objects
		sphere.Draw();

		// Hud elements
		crosshair.Draw();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}


	// Delete all the shaders that were created
	uniColorShaderProg.Delete();
	hudShaderProg.Delete();

	// Delete all the objects that were created
	sphere.Delete();
	crosshair.Delete();

	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}