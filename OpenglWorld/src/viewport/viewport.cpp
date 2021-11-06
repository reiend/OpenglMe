
#include "../includes/includes.h"

void setViewport(int width, int height, int xPos = 0, int yPos = 0) {
	glViewport(xPos, yPos, width, height);
}
void setViewport(GLFWwindow* window, int width, int height) {
	setViewport(width, height);
}

void resizeRenderView(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, setViewport);
}
