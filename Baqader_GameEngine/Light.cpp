#include "Light.h"

Light::Light()
{
	m_colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_ambientIntensity = 1.0f;

	m_direction = glm::vec3(0.0f, -1.0f, 0.0f);
	m_diffuseIntensity = 0.0f;
}


Light::Light(glm::vec3 colour, GLfloat ambientIntensity, glm::vec3 direction, GLfloat diffuseIntensity)
{
	m_colour = colour;
	m_ambientIntensity = ambientIntensity;

	m_direction = direction;
	m_diffuseIntensity = diffuseIntensity;
}

void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseDirectionLocation, GLuint diffuseIntensityLocation) const
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);

	glUniform3f(diffuseDirectionLocation, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(diffuseIntensityLocation, m_diffuseIntensity);
}

Light::~Light()
{
}
