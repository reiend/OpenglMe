
#include "./viewport.h"

#include "../includes/includes.h"


void setViewport(const int width, const int height, const int xPos, const int yPos) {
	glViewport(xPos, yPos, width, height);
}

void setViewport(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

void resizeViewport(GLFWwindow* window) {
	glfwSetFramebufferSizeCallback(window, setViewport);
}