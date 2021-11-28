

#include "./buffers//bufferEntity.h"
#include "./buffers/vbo.h"
#include "./buffers/bufferOld.h"
#include "./events/utilsEvents.h"
#include "../res/shaders/shaders.h"
#include "./viewport/viewport.h"
#include "./windows/windowUtils.h"
#include "./inits/gladInit.h"
#include "./windows/windowsWindows.h"
#include "./inits/glfwInit.h"
#include "../res/imageLoader/stb_image.h"

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

	// Buffers
	Buffer* vao = new Buffer(BufferType::VAO);

	// vertex position - 1
	BufferEntity* vbo = new VBO(GL_ARRAY_BUFFER);

	Buffer* ebo = new Buffer(BufferType::EBO, GL_ELEMENT_ARRAY_BUFFER, 1);

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// textureBuffer
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Texture Wrapping - how to color things using a paper texture
	// S, T, R = X, Y, Z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Mipmaps	- paper coloring depends on distance
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	Shader customShader("shaders/shaderSource/vertexShader.glsl", "shaders/shaderSource/fragmentShader.glsl");
	// Image loader
	int width;
	int height;
	int channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* textureData{ stbi_load("assets/ropeFlat.png", &width, &height,&channels, 0) };

	if (textureData) {
		// Generate texture 
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture1 failed: ERROR\n";
	}

	stbi_image_free(textureData);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// Texture Wrapping - how to color things using a paper texture
	// S, T, R = X, Y, Z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Mipmaps	- paper coloring depends on distance
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	textureData = stbi_load("assets/SmilingPeace.png", &width, &height, &channels, 0) ;

	if (textureData) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture2 failed: ERROR\n";
	}


	stbi_image_free(textureData);

	customShader.useProgram();
	glUniform1i(glGetUniformLocation(customShader.ID, "textureSample1"), 0);
	customShader.setInt("textureSample2", 1);


	while (!glfwWindowShouldClose(window)) {


		// Exit Screen
		closeWindow(window);

		// Toggle Wireframe
		enableWireframe(window);

		// Clear screen using colors
		glClearColor(1.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		customShader.useProgram();
		glBindVertexArray(vao->getBufferObject());
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	
		// Swap buffers for smooth render
		glfwSwapBuffers(window);

		// Handle events
		glfwPollEvents();
	}


	// Freeing memory of Buffers
	glDeleteProgram(customShader.ID);
	ebo->clearBuffer(BufferType::EBO, 1);
	ebo->clearBuffer(BufferType::VBO, 1);
	ebo->clearBuffer(BufferType::VAO, 1);

	// Deallocating, returning memory from the heap
	delete vbo;
	delete ebo;
	delete vao;

	// No set nullptr == end
	glfwTerminate();


	return 0;
}