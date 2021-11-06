
#include "../includes/includes.h"
#include "./util.h"

// Process window close event
void closeWindowEvent(GLFWwindow* window, int windowOption) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, static_cast<int>(windowOption));
	}
}


