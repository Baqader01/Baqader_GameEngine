#define STB_IMAGE_IMPLEMENTATION       // required exactly once in one .cpp file to compile stb.

#include <vector>
#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"
#include "SeaRendering.h";

//window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.1459265f / 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLuint uniformModel, uniformProjection, uniformView, uniformTime;

Window mainWindow;

Texture brickTexture;
Texture dirtTexture;

SeaRendering seaRend;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

//vertex shader
static const char* vShader = "Shaders/shader.vert";

//fragment shader
static const char* fShader = "Shaders/shader.frag";

void CreateObjects()
{
	Mesh* obj1 = new Mesh();

	std::vector<GLuint> indices = obj1->CreateIndices(150);
	std::vector<GLfloat> vertices = obj1->CreatePlane(150, 15);

	obj1->CreateMesh(vertices, indices);
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

	GLfloat bufferWidth  = (GLfloat) mainWindow.GetBufferWidth();
	GLfloat bufferHeight = (GLfloat) mainWindow.GetBufferHeight();

	CreateObjects();
	CreateShaders();

	camera = Camera(
		glm::vec3(0.0f, 0.0f, 0.0f),    // position
		glm::vec3(0.0f, 1.0f, 0.0f),    // up
		90.0f, 0.0f,                    // yaw, pitch
		5.0f, 0.5f                      // movementSpeed, turnSpeed
	);

	brickTexture = Texture("Textures/brick.png");
	//brickTexture.LoadTexture();
	dirtTexture = Texture("Textures/dirt.png");
	//dirtTexture.LoadTexture();

	seaRend = SeaRendering();

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), bufferWidth / bufferHeight, 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = (GLfloat) glfwGetTime();
		deltaTime   = now - lastTime;
		lastTime    = now;

		//clear window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// color background
		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);

		//process + handle inputs
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getChangeX(), mainWindow.getChangeY());

		//shaders
		shaderList[0]->UseShader();

		//render
		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::rotate(model, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4));

		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformModel	  = shaderList[0]->GetModelLocation();
		uniformView		  = shaderList[0]->GetViewLocation();
		uniformTime		  = shaderList[0]->GetTimeLocation();
		seaRend.GenerateWaves(5, shaderList[0]->GetShaderID());

		//glUniform1f(uniformModel, triOffset);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform1f(uniformTime, (GLfloat) glfwGetTime());

		//texture
		meshList[0]->RenderMesh();

		//swap buffers
		mainWindow.swapBuffers();

	}


	glfwTerminate();
	return 0;

}