


#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include "../includes/includes.h"
GLFWwindow* createWindow(int windowWidth, int windowHeight, const char* title,
	GLFWmonitor* monitor = NULL, GLFWwindow* share = NULL);

#endif