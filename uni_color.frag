#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the Normal from the Vertex Shader
in vec3 Normal;
// Inputs position from the Vertex Shader
in vec3 crntPos;

// Uniform color
uniform vec3 color;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;

void main()
{
	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	FragColor = vec4(color, 1.0f) * lightColor * (diffuse + ambient);
}