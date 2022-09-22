#version 330 core

//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Normal
layout (location = 2) in vec3 aNormal;

// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the normal to the Fragment Shader
out vec3 Normal;
// Outputs current positon to the Fragment Shader
out vec3 crntPos;


// Camera matrix
uniform mat4 camMatrix;
// Object transform matrix
uniform mat4 objMatrix;
uniform mat4 rotateNormalMatrix;

void main()
{
	crntPos = vec3(objMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0));
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;

	// Assigns the rotated normal from the Vertex Data to "Normal"
	Normal = vec3(rotateNormalMatrix * vec4(aNormal, 1.0));
}