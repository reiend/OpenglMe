
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>




void resizeRenderView(GLFWwindow* window, int width, int height);
void closeWindowEvent(GLFWwindow* window);

constexpr int WIDTH{ 1000 };
constexpr int HEIGHT{ 800 };

enum class WindowOption {
	OPEN = 0,
	CLOSE = 1
};

int main(void)
{


	// GLFW init
	glfwInit();


	// Config
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window{ glfwCreateWindow(WIDTH, HEIGHT, "Reiend", NULL, NULL) };
	if (window == NULL) {
		std::cout << "GLFW window: ERROR\n";
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

	// Render viewport
	glViewport(0, 0, WIDTH, HEIGHT);
	
	// Resize render view relative to window
	glfwSetFramebufferSizeCallback(window, resizeRenderView);


	while (!glfwWindowShouldClose(window)) {	

		// Press ESC to close the window
		closeWindowEvent(window);


		// Clear Screen
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use color value for GLFW window
		glfwSwapBuffers(window);

		// Handle Events
		glfwPollEvents();
	}


	return 0;
}


// Resize render view according to window's
void resizeRenderView(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


// Process window close event
void closeWindowEvent(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, static_cast<int>(WindowOption::CLOSE));
	}
}
