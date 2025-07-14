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

	bool* getsKeys() { return keys; }
	GLfloat getChangeX();
	GLfloat getChangeY();
private:
	GLFWwindow* window;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	GLfloat lastX, lastY;
	GLfloat changeX, changeY;
	bool mouseFirstMoved;

	bool keys[1024];

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

