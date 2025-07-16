#define STB_IMAGE_IMPLEMENTATION

#include <vector>

#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

//window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.1459265f / 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLuint uniformModel, uniformProjection, uniformView;

Window mainWindow;

Texture brickTexture;
Texture dirtTexture;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

//vertex shader
static const char* vShader = "Shaders/shader.vert";

//fragment shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat vertices[] =
	{	 //positions			u     v			//rgb
		 -10.0f, 0.0f,-10.0f,   0.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // V0 - bottom left
		  10.0f, 0.0f,-10.0f,   1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   // V1 - bottom right
		  10.0f, 0.0f, 10.0f,   1.0f, 1.0f,   1.0f, 1.0f, 1.0f,   // V2 - top right
		 -10.0f, 0.0f, 10.0f,   0.0f, 1.0f,   0.0f, 1.0f, 0.0f    // V3 - top left
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, sizeof(vertices) / sizeof(vertices[0]), sizeof(indices) / sizeof(indices[0]));

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

	camera = Camera(
		glm::vec3(0.0f, 0.0f, 0.0f),    // position
		glm::vec3(0.0f, 1.0f, 0.0f),   // up
		90.0f, 0.0f,                     // yaw, pitch
		5.0f, 0.5f                      // movementSpeed, turnSpeed
	);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTexture();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), bufferWidth / bufferHeight, 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		//clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// color background
		glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

		//process + handle inputs
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getChangeX(), mainWindow.getChangeY());

		//shaders
		shaderList[0]->UseShader();

		//render
		glm::mat4 model(1.0f);
		//model = glm::translate(model, glm::vec3(0, 0.0f, -2.5f));
		//model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4));

		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();

		//glUniform1f(uniformModel, triOffset);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		//texture
		dirtTexture.UseTexture();
		meshList[0]->RenderMesh();

		//swap buffers
		mainWindow.swapBuffers();

	}


	glfwTerminate();
	return 0;

}