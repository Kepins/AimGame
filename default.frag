#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 color;
// Inputs the Normal from the Vertex Shader
in vec3 Normal;
// Inputs position from the Vertex Shader
in vec3 crntPos;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - crntPos);

	float diffuse = max(dot(normal, lightDirection), 0.0f);

	FragColor = vec4(color, 1.0f) * lightColor * diffuse;
}