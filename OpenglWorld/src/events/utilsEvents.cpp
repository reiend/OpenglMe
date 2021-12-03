
#include "./utilsEvents.h"
#include "../windows/windowUtils.h"

#include "../includes/includes.h"
#include <iostream>

extern float opacityValue = 0.2f;

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
void opacityControl(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		opacityValue += 0.0001f;
		if (opacityValue >= 1.0f) {
			opacityValue = 1.0f;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		opacityValue -= 0.0001f;
		if (opacityValue <= 0.0f) {
			opacityValue = 0.0f;
		}
	}
}