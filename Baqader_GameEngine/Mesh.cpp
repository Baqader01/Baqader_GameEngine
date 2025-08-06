#include "Mesh.h"
#include <iostream>

inline glm::vec3 position(float x, float y, float z) { return glm::vec3(x, y, z); }
inline glm::vec2 uv(float u, float v) { return glm::vec2(u, v); }
inline glm::vec3 colour(float red, float green, float blue) { return glm::vec3(red, green, blue); }
inline glm::vec3 normal(float x, float y, float z) { return glm::vec3(x, y, z); }

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	instanceVBO = 0;
	instanceColourVBO = 0;

	//int rows = 50;
	//int columns = 100;
	//float spacing = 20.0f; // distance between cubes

	//for (int row = 0; row < rows; ++row)
	//{
	//	for (int col = 0; col < columns; ++col)
	//	{
	//		float x = col * spacing;
	//		float z = -row * spacing; // negative to go "behind"
	//		translations.push_back(glm::vec3(x, 0.0f, z));
	//	}
	//}
	
	int colourCount = 100000;
	for (int i = 0; i < colourCount; i++)
	{
		colours.push_back(glm::vec3(
			static_cast<float>(rand()) / RAND_MAX,
			static_cast<float>(rand()) / RAND_MAX,
			static_cast<float>(rand()) / RAND_MAX
		));
	}

	int width = 100;
	int depth = 100;
	float frequency = 1.0f;
	float amplitude = 150.0f;

	float spacing = 20;

	// Setup noise generator
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFractalType(FastNoiseLite::FractalType::FractalType_Ridged);

	for (int z = 0; z < depth; ++z) {
		for (int x = 0; x < width; ++x) {
			float worldX = x * spacing;
			float worldZ = z * spacing;

			// Generate height using noise
			float rawHeight = noise.GetNoise(x * frequency, z * frequency) * amplitude;
			float height = static_cast<int>(round(rawHeight / 20) * 20);

			//translations.push_back(glm::vec3(worldX, height, worldZ));
			for (float y = 0; y <= height; y += spacing)
			{
				translations.push_back(glm::vec3(worldX, y, worldZ));
			}
		}
	}
}

void Mesh::CreateMesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices)
{

	//vao vertex array
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//ibo vertex array
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);

	// vbo vertex array
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
	glEnableVertexAttribArray(2);

	//instance position vbo
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * translations.size(), translations.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// instance colour VBO
	glGenBuffers(1, &instanceColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), colours.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	 // also set instance data
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(3, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, instanceColourVBO);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(4, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::RenderMesh() const
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, translations.size());
		
	glBindVertexArray(0);
	glUseProgram(0);
}

std::vector<GLuint> Mesh::CreateIndices(int squares)
{
	indices.clear();

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

std::vector<GLfloat> Mesh::RenderCube(GLfloat width) //e.g. 5
{
	vertices.clear();

	glm::vec3 green (0.2f, 1.0f, 0.2f);

	/*glm::vec3 red(1.0f, 0.f, 0.0f);
	glm::vec3 blue(0.0f, 0.0f, 1.0f);
	glm::vec3 white(1.0f, 1.f, 1.0f);
	glm::vec3 green(0.0f, 1.0f, 0.0f);
	glm::vec3 orange(1.0f, 0.5f, 0.0f);
	glm::vec3 yellow(1.0f, 1.0f, 0.0f);*/
	
	//front
	plane(position(-width, -width, 0.0f), uv(0.0f, 0.0f), normal(0.0f, 0.0f, -1.0f)); // V0 - bottom left
	plane(position( width, -width, 0.0f), uv(1.0f, 0.0f), normal(0.0f, 0.0f, -1.0f));  // V1 - bottom right
	plane(position( width, width, 0.0f), uv(1.0f, 1.0f), normal(0.0f,  0.0f, -1.0f));   // V2 - top right
	plane(position(-width, width, 0.0f), uv(0.0f, 1.0f), normal(0.0f,  0.0f, -1.0f));  // V3 - top left

	//top
	plane(position(-width, width, 0.0f), uv(0.0f, 0.0f), normal(0.0f, 1.0f, 0.0f));	      // V4 - bottom left
	plane(position( width, width, 0.0f), uv(1.0f, 0.0f), normal(0.0f, 1.0f, 0.0f));		  // V5 - bottom right
	plane(position( width, width, width * 2), uv(1.0f, 1.0f), normal(0.0f, 1.0f, 0.0f));  // V6 - top right
	plane(position(-width, width, width * 2), uv(0.0f, 1.0f), normal(0.0f, 1.0f, 0.0f));  // V7 - top left

	//right
	plane(position(-width, -width, 0.0f), uv(0.0f, 0.0f), normal(-1.0f, 0.0f, 0.0f));      // V8 - bottom left
	plane(position(-width, -width, width * 2), uv(1.0f, 0.0f), normal(-1.0f, 0.0f, 0.0f)); // V9 - bottom right
	plane(position(-width, width, width * 2), uv(1.0f, 1.0f), normal(-1.0f, 0.0f, 0.0f));  // V10 - top right
	plane(position(-width, width, 0.0f), uv(0.0f, 1.0f), normal(-1.0f, 0.0f, 0.0f));		 // V11 - top left

	//back
	plane(position(-width, -width, width * 2), uv(0.0f, 0.0f), normal(0.0f, 0.0f, 1.0f));  // V12 - bottom left
	plane(position( width, -width, width * 2), uv(1.0f, 0.0f), normal(0.0f, 0.0f, 1.0f));  // V13 - bottom right
	plane(position( width,  width, width * 2), uv(1.0f, 1.0f), normal(0.0f, 0.0f, 1.0f));  // V14 - top right
	plane(position(-width,  width, width * 2), uv(0.0f, 1.0f), normal(0.0f, 0.0f, 1.0f));  // V15 - top left

	//left
	plane(position(width, -width, 0.0f), uv(0.0f, 0.0f), normal(1.0f, 0.0f, 0.0f));	    // V16 - bottom left
	plane(position(width, -width, width * 2), uv(1.0f, 0.0f), normal(1.0f, 0.0f, 0.0f)); // V17 - bottom right
	plane(position(width,  width, width * 2), uv(1.0f, 1.0f), normal(1.0f, 0.0f, 0.0f)); // V18 - top right
	plane(position(width,  width, 0.0f), uv(0.0f, 1.0f), normal(1.0f, 0.0f, 0.0f));	    // V19 - top left

	//bottom
	plane(position(-width, -width, 0.0f), uv(0.0f, 0.0f), normal(0.0f, -1.0f, 0.0f));      // V20 - bottom left
	plane(position( width, -width, 0.0f), uv(1.0f, 0.0f), normal(0.0f, -1.0f, 0.0f));       // V21 - bottom right
	plane(position( width, -width, width * 2), uv(1.0f, 1.0f), normal(0.0f, -1.0f, 0.0f));  // V22 - top right
	plane(position(-width, -width, width * 2), uv(0.0f, 1.0f), normal(0.0f, -1.0f, 0.0f)); // V23 - top left

	//https://youtu.be/FKLbihqDLsg?si=SxWQxdszzjFUFJGP&t=206

	return vertices;
}

void Mesh::plane(glm::vec3 position, glm::vec2 uv, glm::vec3 normal)
{
	vertices.insert(vertices.end(), 
	{
		position.x, position.y, position.z,
		uv.x, uv.y,
		normal.x, normal.y, normal.z
	});
}

void Mesh::ClearMesh()
{
	if (IBO != 0) glDeleteBuffers(1, &IBO); IBO = 0;
	if (VBO != 0) glDeleteBuffers(1, &VBO); VBO = 0;
	if (VAO != 0) glDeleteVertexArrays(1, &VAO); VAO = 0;
	if (instanceColourVBO != 0) glDeleteVertexArrays(1, &instanceColourVBO); instanceColourVBO = 0;
	if (instanceVBO != 0) glDeleteVertexArrays(1, &instanceVBO); instanceVBO = 0;
}

Mesh::~Mesh()
{
	ClearMesh();
}
