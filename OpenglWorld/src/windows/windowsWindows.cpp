
#include "./windowsWindows.h"


#include "../includes/includes.h"

#include <string_view>




GLFWwindow* createWindow(int width, int height, std::string_view name) {

	GLFWwindow* window{ glfwCreateWindow(width, height, name.data(), nullptr, nullptr) };
	if (window == NULL) {
		glfwTerminate();
		return 0;
	}

	glfwMakeContextCurrent(window);
	return window;
}