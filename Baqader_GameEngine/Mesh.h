#pragma once
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();

	void CreateMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
	void ClearMesh();
	void RenderMesh() const;

	std::vector<GLuint> CreateIndices(int div);
	std::vector<GLfloat> RenderCube(GLfloat width);

	void plane(glm::vec3 position, glm::vec2 uv, glm::vec3 normal);

	~Mesh();

private:
	GLuint VAO, VBO, IBO, instanceVBO, instanceColourVBO;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	//100 positions
	std::vector<glm::vec3> translations;
	std::vector<glm::vec3> colours;
};

