#pragma once
#include <vector>
#include <GL/glew.h>
#include <ctime>
#include <iostream>

class SeaRendering
{
public:
    SeaRendering();
    void GenerateWaves(int wavesCount, GLuint shaderProgram);
private:
    struct Wave {
        float wavelength;
        float amplitude;
        float speed;
        float angle;
    };

    void RenderWaves(int wavesCount);
    void WaveUniforms(GLuint shaderProgram);

    std::vector<Wave> waves;
};

