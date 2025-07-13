#pragma once

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	~Window();

	int init();

	GLint GetBufferWidth() const { return bufferWidth; }
	GLint GetBufferHeight() const { return bufferHeight; }

	bool getShouldClose() const { return glfwWindowShouldClose(window); }
	void swapBuffers() { glfwSwapBuffers(window); }
private:
	GLFWwindow* window;

	GLint width, height;
	GLint bufferWidth, bufferHeight;
};

