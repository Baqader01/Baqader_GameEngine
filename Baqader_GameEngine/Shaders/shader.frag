#version 330
out vec4 colour;

in vec3 vCol;
in vec2 textureCoordinate;

struct DirectionalLight
{
	vec3 colour;
	float ambientIntensity;
};

uniform sampler2D mainTexture; //GL_TEXTURE0
uniform DirectionalLight directionalLight;

void main()
{
	vec4 ambientColour = vec4(directionalLight.colour, 1.0f) * directionalLight.ambientIntensity;

	//colour = vec4(vCol, 1);
	colour = texture(mainTexture, textureCoordinate) * ambientColour;
	
}