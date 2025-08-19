#include "World.h"
#include <iostream>

World::World(Mesh* object, FastNoiseLite noise)
{
	m_object = object;
	m_noise = noise;
}

void World::Update()
{
	if (m_chunks.empty())
	{
		for (int x = -2; x < 4; x++)
		{
			for (int z = -2; z < 4; z++)
			{
				
				glm::vec2 chunkPosition = glm::vec2( x * 320, z * 320);
				Chunk chunk(chunkPosition, m_object, m_noise);

				chunk.Generate();

				if (x == 0 and z == 0)
				{
					m_playerPosition = chunk.CubeHight(0, 0);
				}

				// a pointer for the chunk
				m_chunks.push_back(chunk);

			}
		}
	}
}

void World::Render()
{
	for (auto& chunk : m_chunks)
	{
		chunk.Render();
	}
}

