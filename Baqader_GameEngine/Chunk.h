#pragma once
#include <glm/glm.hpp>
#include "FastNoiseLite.h"
#include <vector>
#include "Mesh.h"
#include <GL/glew.h>

class Chunk
{
public:
	Chunk(glm::vec3 position, Mesh* object);

	void Generate(FastNoiseLite& noise);
	void Render();

private:
	const int WIDTH = 16;
	const int DEPTH = 12;
	const int HEIGHT = 256;

	glm::vec3 m_position;
	Mesh* m_object;

	//100 positions
	std::vector<glm::vec3> translations;
	std::vector<glm::vec3> colours;

	GLuint instancePositionVBO = 0;
	GLuint instanceColourVBO = 0;
};
