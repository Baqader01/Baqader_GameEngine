#include "Mesh.h"

inline glm::vec3 position(float x, float y, float z) { return glm::vec3(x, y, z); }
inline glm::vec2 uv(float u, float v) { return glm::vec2(u, v); }
inline glm::vec3 colour(float red, float green, float blue) { return glm::vec3(red, green, blue); }
inline glm::vec3 direction(float nx, float ny, float nz) { return glm::vec3(nx, ny, nz); }

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Mesh::RenderMesh() const
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
	glUseProgram(0);
}

std::vector<GLuint> Mesh::CreateIndices(int squares)
{
	indices.reserve(6 * squares); // 6 indices per square (2 triangles)

	for (int i = 0; i < squares; i++)
	{
		int base = i * 4; // 4 vertices per quad

		//Top triangle
		indices.push_back(base);
		indices.push_back(base + 1);
		indices.push_back(base + 2);

		//Bottom triangle
		indices.push_back(base + 2);
		indices.push_back(base + 3);
		indices.push_back(base);
	}

	//https://www.youtube.com/watch?v=FKLbihqDLsg&t=66s
	//https://youtu.be/FKLbihqDLsg?si=_17Q0t-dLSjNAl-W&t=103

	return indices;
}

std::vector<GLfloat> Mesh::PlaneVertices(GLfloat width) //e.g. 5
{
	glm::vec3 red(1.0f, 0.f, 0.0f);
	glm::vec3 white(1.0f, 1.f, 1.0f);
	glm::vec3 blue(0.0f, 0.0f, 1.0f);
	glm::vec3 orange(1.0f, 0.5f, 0.0f);
	glm::vec3 green(0.0f, 1.0f, 0.0f);
	glm::vec3 yellow(1.0f, 1.0f, 0.0f);

	//front
	plane(position(-width,-width, 0.0f), uv(0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f) ,red);  // V0 - bottom left
	plane(position( width,-width, 0.0f), uv(1.0f, 0.0f), direction(0.0f, 0.0f, 0.0f) ,red);  // V1 - bottom right
	plane(position( width, width, 0.0f), uv(1.0f, 1.0f), direction(0.0f, 0.0f, 0.0f) ,red);  // V2 - top right
	plane(position(-width, width, 0.0f), uv(0.0f, 1.0f), direction(0.0f, 0.0f, 0.0f) ,red);  // V3 - top left

	//top
	plane(position(-width, width, 0.0f),	  uv(0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), white); // V4 - bottom left
	plane(position( width, width, 0.0f),	  uv(1.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), white); // V5 - bottom right
	plane(position( width, width, width * 2), uv(1.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), white); // V6 - top right
	plane(position(-width, width, width * 2), uv(0.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), white); // V7 - top left

	//right
	plane(position(-width, -width, 0.0f), uv(0.0f, 0.0f),      direction(0.0f, 0.0f, 0.0f), blue); // V8 - bottom left
	plane(position(-width, -width, width * 2), uv(1.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), blue); // V9 - bottom right
	plane(position(-width,  width, width * 2), uv(1.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), blue); // V10 - top right
	plane(position(-width,  width, 0.0f), uv(0.0f, 1.0f),	   direction(0.0f, 0.0f, 0.0f), blue); // V11 - top left

	//back
	plane(position(-width, -width, width * 2), uv(0.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), orange);  // V12 - bottom left
	plane(position( width, -width, width * 2), uv(1.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), orange);  // V13 - bottom right
	plane(position( width,  width, width * 2), uv(1.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), orange);  // V14 - top right
	plane(position(-width,  width, width * 2), uv(0.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), orange);  // V15 - top left

	//left
	plane(position(width, -width, 0.0f), uv(0.0f, 0.0f),	  direction(0.0f, 0.0f, 0.0f), green); // V16 - bottom left
	plane(position(width, -width, width * 2), uv(1.0f, 0.0f), direction(0.0f, 0.0f, 0.0f), green); // V17 - bottom right
	plane(position(width,  width, width * 2), uv(1.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), green); // V18 - top right
	plane(position(width,  width, 0.0f), uv(0.0f, 1.0f),	  direction(0.0f, 0.0f, 0.0f), green); // V19 - top left

	//bottom
	plane(position(-width, -width, 0.0f), uv(0.0f, 0.0f),	   direction(0.0f, 0.0f, 0.0f), yellow);  // V20 - bottom left
	plane(position( width, -width, 0.0f), uv(1.0f, 0.0f),	   direction(0.0f, 0.0f, 0.0f), yellow);  // V21 - bottom right
	plane(position( width, -width, width * 2), uv(1.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), yellow);  // V22 - top right
	plane(position(-width, -width, width * 2), uv(0.0f, 1.0f), direction(0.0f, 0.0f, 0.0f), yellow);  // V23 - top left

	//https://youtu.be/FKLbihqDLsg?si=SxWQxdszzjFUFJGP&t=206

	return vertices;
}

void Mesh::plane(glm::vec3 position, glm::vec2 uv, glm::vec3 direction, glm::vec3 colour)
{
	vertices.insert(vertices.end(), 
	{
		position.x, position.y, position.z,
		uv.x, uv.y,
		direction.x, direction.y, direction.z,
		colour.x, colour.y, colour.z,
	});
}

void Mesh::calculateNormals(GLsizei vLength, GLsizei normalOffset)
{
	for (size_t i = 0; i < indices.size(); i += 3)
	{
		GLuint in0 = indices[i] * vLength;
		GLuint in1 = indices[i + 1] * vLength;
		GLuint in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 + normalOffset; in1 + normalOffset; in2 + normalOffset;

		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < vertices.size() / vLength; i ++)
	{
		GLuint nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z; 
	}
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
