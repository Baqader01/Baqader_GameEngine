#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseDirectionLocation, GLuint diffuseIntensityLocation) const;

	~Light();

private:
	glm::vec3 m_colour;
	GLfloat m_ambientIntensity;

	glm::vec3 m_direction;
	GLfloat m_diffuseIntensity;
	GLfloat m_DiffuseIntensity;
};

