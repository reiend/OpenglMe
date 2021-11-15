

#include "./gladInit.h"

#include "../includes/includes.h"

int initGlad() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}
	return 0;
}