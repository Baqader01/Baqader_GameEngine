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
	std::vector<GLfloat> PlaneVertices(GLfloat width);

	void plane(glm::vec3 position, glm::vec2 uv, glm::vec3 direction, glm::vec3 colour);
	void calculateNormals(GLsizei vLength, GLsizei normalOffset);

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

	GLsizei indexCount;


};

