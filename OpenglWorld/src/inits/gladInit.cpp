
#include "../includes/includes.h"
#include "./gladInit.h"

#include <iostream>

int initGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD init: ERROR\n";
		glfwTerminate();
		return -1;
	}
	return 0;
}