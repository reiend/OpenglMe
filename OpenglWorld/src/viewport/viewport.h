

#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "../includes/includes.h"

void setViewport(int width, int height, int xPos = 0, int yPos = 0);
void setViewport(GLFWwindow* window, int width, int height);
void resizeRenderView(GLFWwindow* window);

#endif