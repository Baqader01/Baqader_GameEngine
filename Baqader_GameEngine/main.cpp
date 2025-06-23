#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

//window dimensions
GLuint WIDTH = 800, HEIGHT = 600;

int main()
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
	GLFWwindow* window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);

	if (!window)
	{
		printf("window not initalised");
		glfwTerminate();
		return -1;
	}
	//making window context current
	glfwMakeContextCurrent(window);

	//get buffer size
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	//allow modern extension features
	glewExperimental = GL_TRUE;

	if (!glewInit() != GLEW_OK)
	{
		printf("glew initailsation failed");
		glfwTerminate();
		glfwDestroyWindow(window);
	}

	//set viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	while (!glfwWindowShouldClose(window)) 
	{
		//clear window
		glClear(GL_COLOR_BUFFER_BIT);

		// color background
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
		
		//render

		//swap buffers
		glfwSwapBuffers(window);

		//process + handle inputs
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}