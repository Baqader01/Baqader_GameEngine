#version 330
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexture;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 instanceOffset;
layout (location = 4) in vec3 instanceColour;

out vec2 textureCoordinate;
out vec3 normal;
out vec3 colour;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	vec3 worldPosition = aPos + instanceOffset;
	gl_Position = projection * view * model * vec4(worldPosition, 1.0);
	normal = mat3(transpose(inverse(model))) * aNormal;

	colour = instanceColour;
	//textureCoordinate = texture;

	Normal = mat3(transpose(inverse(model))) * normal;
	
}