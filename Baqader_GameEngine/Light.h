#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity);

	Light(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation) const;

	~Light();

private:
	glm::vec3 m_colour;
	GLfloat m_ambientIntensity;

	glm::vec3 m_direction;
	GLfloat m_DiffuseIntensity;
};

