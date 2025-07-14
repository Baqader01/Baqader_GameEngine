#version 330
out vec4 colour;

in vec3 vCol;

void main()
{
	colour = vec4(vCol, 1);
}