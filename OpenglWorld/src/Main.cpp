

#include "../res/shaders/shaders.h"
#include "./viewport/viewport.h"
#include "./windows/windowUtils.h"
#include "./inits/gladInit.h"
#include "./windows/windowsWindows.h"
#include "./inits/glfwInit.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>




int main(void) {
	using namespace WindowInfo;


	// Use Window and dependencies
	initGlfw();
	GLFWwindow* window{ createWindow(WIDTH, HEIGHT, WINDOW_NAME)};
	initGlad();

	// Handle Viewport 
	setViewport(WIDTH, HEIGHT);
	resizeViewport(window);
	



	float vertexPos[]{
	   -0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
	   -0.5f,  0.5f, 0.0f,
	};
	
	unsigned int indexPos[]{
		0, 1, 2,
		2, 3, 0,
	};


	unsigned int vertexArrayObject;
	unsigned int vertexBufferObject;
	unsigned int elementBufferObject;

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &elementBufferObject);


	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexPos), indexPos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	Shader customShader("vertexShader.glsl", "fragmentShader.glsl");	

	while (!glfwWindowShouldClose(window)) {


		// Exit Screen


		// Clear screen using colors
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		customShader.useProgram();
		glBindVertexArray(vertexArrayObject);
	

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);


		// Swap buffers for smooth render
		glfwSwapBuffers(window);

		// Handle events
		glfwPollEvents();

	}

	glDeleteProgram(customShader.ID);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);

	return 0;
}