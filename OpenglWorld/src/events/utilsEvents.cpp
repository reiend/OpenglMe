
#include "./utilsEvents.h"
#include "../windows/windowUtils.h"

#include "../includes/includes.h"
#include <iostream>

void closeWindow(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, static_cast<bool>(WindowOption::Option::CLOSE));
	}
}

void enableWireframe(GLFWwindow* window) {
	

	if ((glfwGetKey(window, GLFW_KEY_W) && (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) == GLFW_PRESS)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if ((glfwGetKey(window, GLFW_KEY_F) && (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) == GLFW_PRESS)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}