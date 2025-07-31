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
#include "Light.h"

//window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
const float toRadians = 3.1459265f / 180.0f;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0, 
	   uniformAmbientColour = 0, uniformAmbientIntensity = 0,
	   uniformDirection = 0,     uniformDiffuseIntensity = 0;

Window mainWindow;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

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

	std::vector <GLuint> indices = obj1->CreateIndices(6); 
	std::vector<GLfloat> vertices = obj1->PlaneVertices(0.25f);
	
	obj1->CreateMesh(vertices, indices);

	int vertexLength = 11, normalOffset = 5;
	obj1->calculateNormals(vertexLength, normalOffset);

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

	GLfloat bufferWidth =  (GLfloat) mainWindow.GetBufferWidth();
	GLfloat bufferHeight = (GLfloat) mainWindow.GetBufferHeight();

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

	mainLight = Light(1.0f, 1.0f, 1.0f, 1.0f, 2.0f,
		-1.0f, -2.0f, 1.0f);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), bufferWidth / bufferHeight, 0.1f, 100.0f);

	while (!mainWindow.getShouldClose())
	{
		GLfloat now = (GLfloat) glfwGetTime();
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
		//model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1));

		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();
		uniformAmbientColour = shaderList[0]->GetAmbientColourLocation();
		uniformAmbientIntensity = shaderList[0]->GetAmbientIntenityLocation();
		uniformDirection = shaderList[0]->GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();

		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);

		//glUniform1f(uniformModel, triOffset);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

		//texture
		meshList[0]->RenderMesh();

		//swap buffers
		mainWindow.swapBuffers();

	}


	glfwTerminate();
	return 0;

}