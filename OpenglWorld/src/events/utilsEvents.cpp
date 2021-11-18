
#include "./utilsEvents.h"
#include "../windows/windowUtils.h"

#include "../includes/includes.h"

void closeWindow(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, static_cast<bool>(WindowOption::Option::CLOSE));
	}
}