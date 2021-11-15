

#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H

#include "../includes/includes.h"

#include <string_view>

GLFWwindow* createWindow(int width, int height, std::string_view name);

#endif