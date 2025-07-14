#include "Window.h"
#include <iostream>

Window::Window()
{
	height = 800;
	width = 600;
	window = NULL;

	bufferHeight = 800;
	bufferWidth = 600;

	mouseFirstMoved = true;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	changeX = 0.0f;
	changeY = 0.0f;
	lastX = 0.0f;
	lastY = 0.0f;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	height = windowHeight;
	width = windowWidth;
	window = NULL;

	bufferHeight = windowHeight;
	bufferWidth = windowWidth;

	mouseFirstMoved = true;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	changeX = 0.0f;
	changeY = 0.0f;
	lastX = 0.0f;
	lastY = 0.0f;
}

Window::~Window()
{
	glfwTerminate();
	glfwDestroyWindow(window);
}

int Window::init()
{
	if (!glfwInit())
	{
		printf("GLFW not initalised");
		return -1;
	}

	//opengl version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//no backward compatability
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//forward compatabilty
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//window creation
	window = glfwCreateWindow(width, height, "Test Window", NULL, NULL);

	if (!window)
	{
		printf("window not initalised");
		glfwTerminate();
		return -1;
	}
	//making window context current
	glfwMakeContextCurrent(window);

	//get buffer size
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//handle key + mouse inputs
	createCallbacks();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (glewInit() != GLEW_OK)
	{
		printf("glew initailsation failed");
		glfwTerminate();
		glfwDestroyWindow(window);
	}

	glEnable(GL_DEPTH_TEST);

	//allow modern extension features
	glewExperimental = GL_TRUE;

	//set viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(window, this);

	return 0;
}

GLfloat Window::getChangeX()
{
	GLfloat change = changeX;
	changeX = 0.0f;
	return change;
}

GLfloat Window::getChangeY()
{
	GLfloat change = changeY;
	changeY = 0.0f;
	return change;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(window, handleKeys);
	glfwSetCursorPosCallback(window, handleMouse); 
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//std::cout << "pressed: " << key << std::endl;
		}
		else if(action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//std::cout << "released: " << key << std::endl;
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;

		theWindow->mouseFirstMoved = false;
	}

	theWindow->changeX = xPos - theWindow->lastX;
	theWindow->changeY = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//std::cout << "x: " << theWindow->changeX << ", y:" << theWindow->changeY << std::endl;

}
