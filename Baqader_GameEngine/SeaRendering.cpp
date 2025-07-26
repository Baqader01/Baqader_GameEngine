#include "SeaRendering.h"

SeaRendering::SeaRendering()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void SeaRendering::GenerateWaves(int wavesCount, GLuint shaderProgram)
{
    RenderWaves(wavesCount);
    WaveUniforms(shaderProgram);
}

void SeaRendering::RenderWaves(int wavesCount)
{
    for (int i = 0; i < wavesCount; i++)
    {
        //std::cout << "wave " << i << ":" << std::endl;

        float seed = static_cast<float>(i);
        float wavelength = 2.0f + fmod(seed * 12.34f, 1.0f) * 4.0f;
        float amplitude  = 0.1f + fmod(seed * 56.78f, 1.0f) * 0.4f;
        float speed      = 0.5f + fmod(seed * 78.91f, 1.0f) * 3.0f;
        float angle      =        fmod(seed * 91.92f, 1.0f) * 6.2831f;

        waves.push_back({ wavelength, amplitude, speed, angle});
        //std::cout << wavelength << ", " << amplitude << ", " << speed << ", " << angle << std::endl;

    }
}

void SeaRendering::WaveUniforms(GLuint shaderProgram)
{
    GLint uniformWaves = glGetUniformLocation(shaderProgram, "waveCount");
    glUniform1i(uniformWaves, waves.size());

    GLint uniformWavelength = glGetUniformLocation(shaderProgram, "wavelength");
    GLint uniformAmplitude  = glGetUniformLocation(shaderProgram, "amplitude");
    GLint uniformSpeed      = glGetUniformLocation(shaderProgram, "speed");
    GLint uniformAngle      = glGetUniformLocation(shaderProgram, "angle");

    std::vector<float> wavelengthArr, amplitudeArr, speedArr, angleArr;
    for (const auto& wave : waves) {
        wavelengthArr.push_back(wave.wavelength);
        amplitudeArr.push_back(wave.amplitude);
        speedArr.push_back(wave.speed);
        angleArr.push_back(wave.angle);
    }

    glUniform1fv(uniformWavelength, waves.size(), wavelengthArr.data());
    glUniform1fv(uniformAmplitude, waves.size(), amplitudeArr.data());
    glUniform1fv(uniformSpeed, waves.size(), speedArr.data());
    glUniform1fv(uniformAngle, waves.size(), angleArr.data());

}
