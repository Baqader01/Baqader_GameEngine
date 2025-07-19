#include "Mesh.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

void Mesh::CreateMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
{
	indexCount = indices.size();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

std::vector<float> Mesh::CreatePlane(int div, float width)
{
	std::vector <float> plane;
	float triangleSide = width / div;
	for (int row = 0; row < div + 1; row++)
	{
		for (int col = 0; col < div + 1; col++)
		{
			float x = col * triangleSide;
			float y = 0.0f;
			float z = row * -triangleSide;

			float u = static_cast<float>(col) / div;
			float v = static_cast<float>(row) / div;

			plane.push_back(x);
			plane.push_back(y);
			plane.push_back(z);
			plane.push_back(u);
			plane.push_back(v);
		}
	}

	return plane;
}

std::vector<GLuint> Mesh::CreateIndices(int div)
{
	std::vector<GLuint> indices;

	for (int row = 0; row < div; row++)
	{
		for (int col = 0; col < div; col++)
		{
			int index = row * (div + 1) + col;
			//Top triangle
			indices.push_back(index);
			indices.push_back(index + (div + 1) + 1);
			indices.push_back(index + (div + 1));
			//Bottom triangle
			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + (div + 1) + 1);
		}
	}
	//https://www.youtube.com/watch?v=FKLbihqDLsg&t=66s
	//https://youtu.be/FKLbihqDLsg?si=_17Q0t-dLSjNAl-W&t=103

	return indices;
}

void Mesh::ClearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}

Mesh::~Mesh()
{
	ClearMesh();
}
