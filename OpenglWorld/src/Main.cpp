

#include "./events/utilsEvents.h"
#include "../res/shaders/shaders.h"
#include "./viewport/viewport.h"
#include "./windows/windowUtils.h"
#include "./inits/gladInit.h"
#include "./windows/windowsWindows.h"
#include "./inits/glfwInit.h"

#include <stb_image.h>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

int main(void) {
	using namespace WindowInfo;

	// Use Window and dependencies
	initGlfw();
	GLFWwindow* window{ createWindow(WIDTH, HEIGHT, WINDOW_NAME) };
	initGlad();

	// Handle Viewport 
	setViewport(WIDTH, HEIGHT);
	resizeViewport(window);


	//float vertexPos[]{
	//	0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
	//   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
	//	0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	//   //-0.5f,  0.5f, 0.0f,
	//};

	float vertexPos[]{
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};

	/*unsigned int indexPos[]{
		0, 1, 2,
		3, 2, 0,
	};*/

	float textureCoordinates[]{
		0.0f, 0.0f, // bottom left corner of image
		1.0f, 0.0f, // bottom right corner of image
		1.0f, 1.0f, // bottom left corner of image
	};

	
	// Texture Wrapping - how to color things using a paper texture
	// S, T, R = X, Y, Z
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// Texture Filtering - how coloring works on paper texture
	// 
	// GL_NEAREST - use closest pixel - pixelized edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);	
	// GL_LINEAR - use color between pixel - smoother edge
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

	// Mipmaps	- paper coloring depends on distance
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	// Image loader
	int width;
	int height;
	int channels;
	unsigned char* data{ stbi_load("assets/create.jpg", &width, &height,&channels, 0) };

	// textureBuffer
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// Generate texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);




	unsigned int vertexArrayObject;
	unsigned int vertexBufferObject;
	//unsigned int elementBufferObject;

	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexBufferObject);
	//glGenBuffers(1, &elementBufferObject);


	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos), vertexPos, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexPos), indexPos, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	Shader customShader("shaders/shaderSource/vertexShader.glsl", "shaders/shaderSource/fragmentShader.glsl");
	customShader.useProgram();


	while (!glfwWindowShouldClose(window)) {


		// Exit Screen
		closeWindow(window);

		// Toggle Wireframe
		enableWireframe(window);


		// Clear screen using colors
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		customShader.useProgram();
		glBindVertexArray(vertexArrayObject);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);



		// Swap buffers for smooth render
		glfwSwapBuffers(window);

		// Handle events
		glfwPollEvents();

	}

	glDeleteProgram(customShader.ID);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteVertexArrays(1, &vertexArrayObject);
	//glDeleteBuffers(1, &elementBufferObject);

	return 0;
}