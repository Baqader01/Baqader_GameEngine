#version 330
#define MAX_WAVES 10

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform float time;

//wave parameters
uniform int waveCount;
uniform float wavelength[MAX_WAVES];
uniform float amplitude[MAX_WAVES];
uniform float speed[MAX_WAVES];
uniform float angle[MAX_WAVES];

float rand(float n) {
    return fract(n * 17.32394);
}

void main()
{
	vec3 newPos = pos;
	int newCount = min(waveCount, MAX_WAVES);

	for (int i = 0; i < newCount; i++)
	{
		float frequency = 2.0 / wavelength[i];
		float dirX = cos(angle[i]);
		float dirZ = sin(angle[i]);

		float wavePhase = (newPos.x + model[3].x) * dirX + (newPos.z + model[3].z) * dirZ;
		newPos.y += amplitude[i] * sin(wavePhase * frequency + time * speed[i]);
	
	}

	gl_Position = projection * view * model * vec4(newPos, 1.0);
	texCoord = tex;

	//https://youtu.be/PH9q0HNBjT4?si=VmwQZg6KKlkNd16G
}