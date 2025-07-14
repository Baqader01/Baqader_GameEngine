#include <vector>

#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

//window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.1459265f / 180.0f;

GLuint uniformModel, uniformProjection;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

//vertex shader
static const char* vShader = "Shaders/shader.vert";

//fragment shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] =
	{
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2

	};

	GLfloat vertices[] =
	{	 //positions          //rgb
		 -1, -1,  0,		1, 0, 0, 
		  0, -1,  1,		1, 1, 1,
		  1, -1,  0,		0, 0, 1,
		  0,  1,  0,		0, 1, 0,
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 24, 12);
	meshList.push_back(obj1);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFile(vShader, fShader);
	shaderList.push_back(shader1);
}

int main()
{
	mainWindow = Window(800, 600);
	mainWindow.init();

	GLfloat bufferWidth = mainWindow.GetBufferWidth();
	GLfloat bufferHeight = mainWindow.GetBufferHeight();

	CreateObjects();
	CreateShaders();

	glm::mat4 projection = glm::perspective(45.0f, bufferWidth / bufferHeight, 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		//clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// color background
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

		//process + handle inputs
		glfwPollEvents();

		//shaders
		shaderList[0]->UseShader();

		//render
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0, 0.0f, -2.5f));
		model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1));

		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();

		//glUniform1f(uniformModel, triOffset);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		meshList[0]->RenderMesh();

		//swap buffers
		mainWindow.swapBuffers();

	}


	glfwTerminate();
	return 0;

}