#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aNormal;

out vec3 vCol;
out vec2 textureCoordinate;
out vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	vCol = aColor;
	normal = mat3(transpose(inverse(model))) * aNormal;
	//textureCoordinate = texture;
}