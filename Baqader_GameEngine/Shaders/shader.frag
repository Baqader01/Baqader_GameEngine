#version 330
out vec4 colour;

in vec2 texCoord;

uniform sampler2D mainTexture; //GL_TEXTURE0

void main()
{
	//colour = texture(mainTexture, texCoord);
	colour = vec4(0.239, 0.953, 1, 1);
}