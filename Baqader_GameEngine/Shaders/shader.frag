#version 330
out vec4 colour;

in vec3 vCol;
in vec2 textureCoordinate;

uniform sampler2D mainTexture; //GL_TEXTURE0

void main()
{
	//colour = vec4(vCol, 1);
	colour = texture(mainTexture, textureCoordinate);
	
}