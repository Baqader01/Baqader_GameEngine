#pragma once

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmentLocation);

	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation() const;
	GLuint GetModelLocation() const;
	GLuint GetViewLocation() const;
	GLuint GetAmbientColourLocation() const;
	GLuint GetAmbientIntenityLocation() const;
	GLuint GetDiffuseDirectionLocation() const;
	GLuint GetDiffuseIntensityLocation() const;

	void UseShader() const;
	void ClearShader();

private:
	GLuint shaderID,
		uniformModel, uniformProjection, uniformView, 
		uniformAmbientColour, uniformAmbientIntensity,
		uniformDiffuseDirection, uniformDiffuseIntensity;

	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint program, const char* shaderCode, GLenum type);
};

