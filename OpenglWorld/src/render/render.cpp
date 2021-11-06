
#include "../includes/includes.h"
#include "../window/windowUtils.h"
#include "../events/util.h"
#include "render.h"


void renderLoop(GLFWwindow* window) {

	while (!glfwWindowShouldClose(window)) {

		// Press ESC to close the window
		closeWindowEvent(window, static_cast<int>(WindowUtils::WindowOption::CLOSE));

		// Clear Screen
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);




		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// Use color value for GLFW window
		glfwSwapBuffers(window);

		// Handle Events
		glfwPollEvents();
	}
}