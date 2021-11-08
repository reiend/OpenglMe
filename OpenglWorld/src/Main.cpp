



#include "shaders/shader.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

void resizeViewport(GLFWwindow* window, int width, int height);
void closeWindow(GLFWwindow* window);
void colorLife(float speed, unsigned int ID, const char* fragmentAttri);

constexpr int kWidth{ 1000 };
constexpr int kHeight{ 800 };



int main(void)
{

	// GLFW init
	glfwInit();

	// Config 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window 
	GLFWwindow* window{ glfwCreateWindow(kWidth, kHeight, "Reiend", NULL, NULL) };
	if (window == NULL) {
		std::cout << "Window create: ERROR\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD init: ERROR\n";
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, kWidth, kHeight);
	glfwSetFramebufferSizeCallback(window, resizeViewport);


	constexpr int size{ 3 };
	float vertexPosition[][size*3]{
		{
			-1.0f, -0.5f, 0.0f,
			-1.0f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
		},
		{
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			-1.0f,  0.5f, 0.0f,
		},
		{
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.0f, -0.5f, 0.0f,
		}

	};

	unsigned int vertexBufferObject[size];
	unsigned int vertexArrayObject[size];	

	glGenBuffers(size, vertexBufferObject);
	glGenVertexArrays(size, vertexArrayObject);

	for (int i{ 0 }; i < size; ++i) {
		glBindVertexArray(vertexArrayObject[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition[i]), vertexPosition[i], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

	}



	Shader shader("src/shaders/vertexShader/vertexShaderTest.glsl", "src/shaders/fragmentShader/fragmentShaderTest.glsl");
	Shader shader2("src/shaders/vertexShader/vertexShaderTest.glsl", "src/shaders/fragmentShader/fragmentShaderTest2.glsl");
	Shader shader3("src/shaders/vertexShader/vertexShaderTest.glsl", "src/shaders/fragmentShader/fragmentShaderTest3.glsl");

	shader.useProgram();
	while (!glfwWindowShouldClose(window))
	{

		closeWindow(window);

		// Clear Screen
		glClearColor(0.5f, 0.2f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.useProgram();
		glBindVertexArray(vertexArrayObject[0]);

		float timeElapsed{ static_cast<float>(glfwGetTime()) };
		shader.useProgram();
		colorLife(4.8f, shader.ID, "blinkColor");
		glDrawArrays(GL_TRIANGLES, 0, 3);


		shader2.useProgram();
		glBindVertexArray(vertexArrayObject[1]);
		float timeElapsed2{ static_cast<float>(glfwGetTime()) };
		colorLife(4.9f, shader2.ID, "blinkColor2");
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(vertexArrayObject[2]);
		shader3.useProgram();
		colorLife(5.0f, shader3.ID, "blinkColor3");
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		// Use Color
		glfwSwapBuffers(window);
		// Handle Events
		glfwPollEvents();


	}
	return 0;
}

void resizeViewport(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void closeWindow(GLFWwindow* window) {
	if ((glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)) {
		glfwSetWindowShouldClose(window, true);
	}
}
void colorLife(float speed, unsigned int ID, const char* fragmentAttri) {
	float timeElapsed{ static_cast<float>(glfwGetTime()) };
	float color{ sin(timeElapsed * speed) / 2.0f + 0.5f };
	int vertexColorLocation{ glGetUniformLocation(ID, fragmentAttri) };
	glUniform4f(vertexColorLocation, color, color, color, 1.0f);
}