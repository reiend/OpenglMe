
#include "../includes/includes.h"
#include "../window/windowUtils.h"
#include "../events/util.h"
#include "render.h"

#include <cmath>
#include <iostream>



void renderLoop(GLFWwindow* window, GLuint program, GLuint vao) {

	while (!glfwWindowShouldClose(window)) {

		// Press ESC to close the window
		closeWindowEvent(window, static_cast<int>(WindowUtils::WindowOption::CLOSE));

		// Clear Screen
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//float timeValue{ static_cast<float>(glfwGetTime()) };
		//float genValue{ (sin(timeValue) / 2.0f) + 0.5f};
		////std::cout << timeValue << '\n';
		//int vertexColorLoc{ glGetUniformLocation(program, "cpuColor") };

		//glUniform4f(vertexColorLoc, 1.0f, genValue, 1.0f, 1.0f);
		glUseProgram(program);
		glBindVertexArray(vao);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Use color value for GLFW window
		glfwSwapBuffers(window);

		// Handle Events
		glfwPollEvents();
	}
}