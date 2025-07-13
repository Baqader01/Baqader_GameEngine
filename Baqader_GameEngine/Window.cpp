#include "Window.h"

Window::Window()
{
	height = 800;
	width = 600;
	window = NULL;

	bufferHeight = 800;
	bufferWidth = 600;
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	height = windowHeight;
	width = windowWidth;
	window = NULL;

	bufferHeight = windowHeight;
	bufferWidth = windowWidth;
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

	return 0;
}
