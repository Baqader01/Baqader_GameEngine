#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 color;

out vec3 vCol;
out vec2 textureCoordinate;
out vec3 Normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = color;
	//textureCoordinate = texture;

	Normal = mat3(transpose(inverse(model))) * normal;
	
}