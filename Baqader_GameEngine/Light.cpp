#include "Light.h"

Light::Light()
{
	m_colour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity)
{
	m_colour = glm::vec3(red, green, blue);
	m_ambientIntensity = ambientIntensity;
}

void Light::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation) const
{
	glUniform3f(ambientColourLocation, m_colour.x, m_colour.y, m_colour.z);
	glUniform1f(ambientIntensityLocation, m_ambientIntensity);
}

Light::~Light()
{
}
