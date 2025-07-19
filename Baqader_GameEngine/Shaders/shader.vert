#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform float time;

float rand(float n) {
    return fract(n * 17.32394);
}


void main()
{
	vec3 newPos = pos;

	int waveCount = 5;
	for (int i = 0; i < waveCount; i++)
	{

		//wave parameters
		float waveLength = 2.0 + rand(float(i) * 12.34) * 4.0;		// from 2 to 6
		float amplitude  = 0.1 + rand(float(i) * 56.78) * 0.4;	    // from 0.1 to 0.5
        float speed      = 0.5 + rand(float(i) * 78.91) * 3.0;		// from 0.5 to 3.5
        float angle      =		 rand(float(i) * 91.92) * 6.2831;   // from 0 to 2 pie (360°)

		float frequency = 2.0 / waveLength;
		float dirX = cos(angle);
		float dirZ = sin(angle);

		float wavePhase = (newPos.x + model[3].x) * dirX + (newPos.z + model[3].z) * dirZ;

		newPos.y += amplitude * sin(wavePhase * frequency + time * speed);
	
	}

	gl_Position = projection * view * model * vec4(newPos, 1.0);
	texCoord = tex;

	//https://youtu.be/PH9q0HNBjT4?si=VmwQZg6KKlkNd16G
}