#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation);

	~Light();

private:
	glm::vec3 m_colour;
	GLfloat m_ambientIntensity;
};

