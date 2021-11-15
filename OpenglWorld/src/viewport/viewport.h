
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "../includes/includes.h"

void setViewport(const int width, const int height, const int xPos = 0, const int yPos = 0);
void setViewport(GLFWwindow* window, const int width, const int height);
void resizeViewport(GLFWwindow* window);

#endif