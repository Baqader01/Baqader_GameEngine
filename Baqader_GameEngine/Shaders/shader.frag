#version 330
out vec4 colour;

in vec3 vCol;
in vec2 textureCoordinate;
in vec3 Normal;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
	vec3 direction;
	float diffuseIntensity;
};

uniform sampler2D mainTexture; //GL_TEXTURE0
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;


	//A.B =	|A| |B| cos(angle)
	float diffuseFactor = max(dot(normalize(Normal), normalize(directionalLight.direction)), 0.0f);
	vec4 diffuseColour = vec4(directionalLight.colour, 1.0f) * directionalLight.diffuseIntensity * diffuseFactor;
	
	colour = vec4(vCol, 1) * (ambientColour + diffuseColour);

	//colour = texture(mainTexture, textureCoordinate) * (ambientColour + diffuseColour);
	
}