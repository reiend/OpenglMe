
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void resizeRenderView(GLFWwindow* window, int width, int height);


int main(void)
{

	// Intialize GLFW 
	glfwInit();

	// Config
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create window
	GLFWwindow* window = glfwCreateWindow(1000, 800, "Reiend", NULL, NULL);

	if (window == NULL) {
		std::cout << "Creating GLFW window fail\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	// Initialize GLAD: Check OS
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD init: Failed\n";
		return -1;
	}

	// Render Window size
	// -1 to 1
	// 1000 : 800
	glViewport(0, 0, 1000, 800);


	//Resize render view according to window'size
	glfwSetFramebufferSizeCallback(window, resizeRenderView);


	// Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}


void resizeRenderView(GLFWwindow* window, int windowWidth, int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
}