#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh
{
public:

	Mesh();
	
	void CreateMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
	void ClearMesh();
	void RenderMesh();

	std::vector<float> CreatePlane(int div, float width);
	std::vector<GLuint> CreateIndices(int div);

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;


};

