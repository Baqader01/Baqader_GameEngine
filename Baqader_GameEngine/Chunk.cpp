#include "Chunk.h"
#include <iostream>
#include "World.h"

Chunk::Chunk(glm::vec2 position, Mesh* object, FastNoiseLite& noise) : m_noise(noise)
{
	//x and z positions
	m_position.x = position.x; m_position.y = 0; m_position.z = position.y;
	m_object = object;
}

void Chunk::Generate()
{
	// Setup noise generator
	m_noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	m_noise.SetFractalType(FastNoiseLite::FractalType::FractalType_Ridged);

	for (int z = 0; z < depth; ++z) {
		for (int x = 0; x < width; ++x) {
			float worldX = m_position.x + (x * cubeSize);
			float worldZ = m_position.z + (z * cubeSize);

			// Generate height using noise
			float rawHeight = m_noise.GetNoise(
				(worldX / cubeSize) * frequency,
				(worldZ / cubeSize) * frequency
			) * amplitude;

			float height = static_cast<int>(round(rawHeight / cubeSize) * cubeSize);
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

glm::vec3 Chunk::CubeHight(float worldX, float worldZ)
{
	// Generate height using noise
	float rawHeight = m_noise.GetNoise(
		(worldX / cubeSize) * frequency,
		(worldZ / cubeSize) * frequency
	) * amplitude;

	float height = static_cast<int>(round(rawHeight / cubeSize));
	return glm::vec3(worldX, height, worldZ);
	
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

