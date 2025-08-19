#pragma once
#include <glm/glm.hpp>
#include "FastNoiseLite.h"
#include "Chunk.h"
#include <memory>

class World
{
public:
	World(Mesh *object, FastNoiseLite noise);

	void Update();
	glm::vec3 GetPlayerPosition() { return m_playerPosition; }
	void Render();

private:
	std::vector<Chunk> m_chunks;
	glm::vec3 m_playerPosition;
	FastNoiseLite m_noise;

	Mesh *m_object;

	int CHUNK_SIZE = 320;
};
