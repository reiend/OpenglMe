
#include "./inits/glfwInit.h"
#include "./inits/gladInit.h"
#include "./window/windowsWindow.h"
#include "./window/windowUtils.h"
#include "./viewport/viewport.h"
#include "./buffers/buffer.h"
#include "./buffers/bufferConfig.h"
#include "./buffers/bufferLayout.h"
#include "./shaders/shader.h"
#include "./shaders/shaderTemp.h"
#include "./render/render.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

void closeWindowEvent(GLFWwindow* window);

enum class WindowOption {
	OPEN,
	CLOSE,
};



int main(void)
{
	// Temp
	using namespace WindowUtils;

	initGlfw();
	// Create window
	GLFWwindow* window{ createWindow(WIDTH, HEIGHT, TITLE) };
	
	initGlad();

	setViewport(HEIGHT, HEIGHT);

	resizeRenderView(window);

	// x,y coordinate discard z axis
	float vertexPos[]{
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
		 //0.5f, -0.5f, 0.0f,
	};

	//unsigned int indeces[]{
	//	0, 1, 2,	// First triangle 
	//	//0, 3, 2,	// second triangle
	//};

	
	unsigned int vertexBufferObject;		// Vertex Buffer Object
	unsigned int vertexArrayObject;			// Vertex Array object
	unsigned int elementBufferObject;		// Element Buffer Object


	setBuffers(1, vertexBufferObject, vertexArrayObject, elementBufferObject);

	configBuffer(GL_ARRAY_BUFFER, vertexBufferObject, sizeof(vertexPos), vertexPos, 
		GL_STATIC_DRAW);
	//configBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject, sizeof(indeces), indeces, GL_STATIC_DRAW);

	// Specify layout for opengl
	setBufferLayout(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0, 0);

	setBufferLayout(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)), 1);


	GLuint shaderProgram{ Shader::CreateShader(vertexShaderSource, fragmentShaderSource) };

	renderLoop(window, shaderProgram, vertexArrayObject);

	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteProgram(shaderProgram);

	std::cout << (GL_MAX_VERTEX_ATTRIBS) << '\n';
	return 0;
}

