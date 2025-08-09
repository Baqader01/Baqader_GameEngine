#include "Chunk.h"
#include <iostream>

Chunk::Chunk(glm::vec3 position, Mesh* object)
{
	m_position = position;
	m_object = object;
}

void Chunk::Generate(FastNoiseLite &noise)
{
	int width = 16;
	int depth = 16;
	float frequency = 1.0f;
	float amplitude = 150.0f;

	float cubeSize = 20;

	// Setup noise generator
	noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	noise.SetFractalType(FastNoiseLite::FractalType::FractalType_Ridged);

	for (int z = 0; z < depth; ++z) {
		for (int x = 0; x < width; ++x) {
			float worldX = m_position.x + (x * cubeSize);
			float worldZ = m_position.z + (z * cubeSize);

			// Generate height using noise
			float rawHeight = noise.GetNoise(
				(worldX / cubeSize) * frequency,
				(worldZ / cubeSize) * frequency
			) * amplitude;

			float height = static_cast<int>(round(rawHeight / cubeSize) * cubeSize);

			//translations.push_back(glm::vec3(worldX, height, worldZ));
			for (float y = 0; y <= height; y += cubeSize)
			{
				translations.push_back(glm::vec3(worldX, y, worldZ));
			}

		}
	}

	for (int i = 0; i < translations.size(); i++)
	{
		colours.push_back(glm::vec3(
			static_cast<float>(rand()) / RAND_MAX,
			static_cast<float>(rand()) / RAND_MAX,
			static_cast<float>(rand()) / RAND_MAX
		));
	}

	//instance position vbo
	glGenBuffers(1, &instancePositionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instancePositionVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * translations.size(), translations.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// instance colour VBO
	glGenBuffers(1, &instanceColourVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceColourVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * colours.size(), colours.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Chunk::Render()
{

	m_object->BindVAO();

	// set instance data
	glBindBuffer(GL_ARRAY_BUFFER, instancePositionVBO);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(3, 1);

	glBindBuffer(GL_ARRAY_BUFFER, instanceColourVBO);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glVertexAttribDivisor(4, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//draw cubes
	m_object->BindIBO();
	glDrawElementsInstanced(GL_TRIANGLES, m_object->GetIndices().size(), GL_UNSIGNED_INT, 0, translations.size());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}


