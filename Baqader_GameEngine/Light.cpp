#include "Light.h"

Light::Light()
{
	m_colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_ambientIntensity = 1.0f;

	m_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	m_DiffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity)
{
	m_colour = glm::vec3(red, green, blue);
	m_ambientIntensity = ambientIntensity;

	m_direction = glm::vec3(xDir, yDir, zDir);
	m_DiffuseIntensity = diffuseIntensity;
}

Light::Light(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity)
{
	m_colour = glm::vec3(colour.x, colour.y, colour.z);
	m_ambientIntensity = ambientIntensity;

	m_direction = glm::vec3(direction.x, direction.y, direction.z);
	m_DiffuseIntensity = diffuseIntensity;
}

void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation) const
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);

	glUniform3f(ambientColourLocation, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(ambientIntensityLocation, m_DiffuseIntensity);
}

Light::~Light()
{
}
