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

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;


};

