
#include "../includes/includes.h"
#include "./windowsWindow.h"
#include <iostream>

GLFWwindow* createWindow(int windowWidth, int windowHeight, const char* title, 
	GLFWmonitor* monitor, GLFWwindow* share) {

	GLFWwindow* window{ glfwCreateWindow(windowWidth, windowHeight, title, monitor, share) };

	if (window == NULL) {
		std::cout << "Window creation: Error\n";
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	return window;
}