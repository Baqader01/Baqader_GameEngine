#pragma once
#include <glm/glm.hpp>
#include "FastNoiseLite.h"
#include <vector>
#include "Mesh.h"
#include <GL/glew.h>

class Chunk
{
public:
	//x and z positions
	Chunk(glm::vec2 position, Mesh* object, FastNoiseLite &noise);

	void Generate();
	void Render();

	glm::vec3 CubeHight(float worldX, float worldZ);

private:
	int width = 16;
	int depth = 16;
	int height = 256;

	float frequency = 1.0f;
	float amplitude = 150.0f;

	float cubeSize = 20;

	glm::vec3 m_position;
	Mesh* m_object;
	FastNoiseLite &m_noise;

	//100 positions
	std::vector<glm::vec3> translations;
	std::vector<glm::vec3> colours;

	GLuint instancePositionVBO = 0;
	GLuint instanceColourVBO = 0;
};