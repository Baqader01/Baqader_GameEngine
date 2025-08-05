#version 330
out vec4 aColour;

in vec2 textureCoordinate;
in vec3 normal;
in vec3 colour;

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
	vec3 ambient = directionalLight.colour * directionalLight.ambientIntensity;

	//normalize all the vectors;
	float diff = max(dot( normalize(normal), normalize(-directionalLight.direction)), 0.0);
	vec3 diffuse = directionalLight.colour * diff * directionalLight.diffuseIntensity;

	aColour = vec4((ambient + diffuse) * colour, 1.0);
	//colour = texture(mainTexture, textureCoordinate) * ambientColour;
	
}