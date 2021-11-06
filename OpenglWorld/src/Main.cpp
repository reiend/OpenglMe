
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>


#include "./inits/glfwInit.h"
#include "./inits/gladInit.h"
#include "./window/windowsWindow.h"
#include "./viewport/viewport.h"


#include <iostream>
#include <string>

void closeWindowEvent(GLFWwindow* window);


namespace {
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSource);
	unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
}

constexpr int WIDTH{ 1000 };
constexpr int HEIGHT{ 800 };
const char* TITLE{ "Reiend" };


enum class WindowOption {
	OPEN,
	CLOSE,
};

int main(void)
{

	initGlfw();
	// Create window
	GLFWwindow* window{ createWindow(WIDTH, HEIGHT, TITLE) };
	
	initGlad();

	setViewport(WIDTH, HEIGHT);

	resizeRenderView(window);


	// x,y coordinate discard z axis
	float vertexPos[]{
		// First triangle
		-0.5f, -0.5f, 0.0f,        
		-0.5f,  0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
	};

	unsigned int indeces[]{
		0, 1, 2,	// First triangle 
		0, 3, 2,	// second triangle
	};

	// Vertex Buffer Object
	unsigned int vertexBufferObject;

	// Vertex Array object
	unsigned int vertexArrayObject;

	// Element Buffer Object
	unsigned int elementBufferObject;

	// Create A buffer
	glGenBuffers(1, &vertexBufferObject);
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &elementBufferObject);

	// Select buffer and inputs
	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertexPos, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indeces, GL_STATIC_DRAW);

	// Specify layout for opengl
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(0);

	// Vertex Shader 
	const char* vertexShaderSource{
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec3 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\n"
	};

	const char* fragmentShaderSource{
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  color = vec4(0.2f, 0.5f, 0.2f, 1.0f);\n"
		"}\n"
	};

	glUseProgram(CreateShader(vertexShaderSource, fragmentShaderSource));
	//glBindVertexArray(vertexArrayObject);

	while (!glfwWindowShouldClose(window)) {

		// Press ESC to close the window
		closeWindowEvent(window);

		// Clear Screen
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Primitives to draw
		//glDrawArrays(GL_TRIANGLES, 0, 3); // draw from vertex buffer
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	

		// Use color value for GLFW window
		glfwSwapBuffers(window);

		// Handle Events
		glfwPollEvents();
	}


	return 0;
}



// Process window close event
void closeWindowEvent(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, static_cast<int>(WindowOption::CLOSE));
	}
}



//Todo's refactor this
namespace {
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSource) {

		unsigned int shaderObject{ glCreateShader(shaderType) };

		// Attach shader source code to shader object
		glShaderSource(shaderObject, 1, &shaderSource, NULL);
		glCompileShader(shaderObject);

		// Error Check
		int result;
	
		glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);

			char* message{ static_cast<char*>(_malloca(length * sizeof(float))) };
			glGetShaderInfoLog(shaderObject, length, &length, message);
			std::cout << "Shader Compile: Error "
				<< (shaderType == GL_VERTEX_SHADER) ? "vertex" : "fragment\n";
			std::cout << message << '\n';
			glfwTerminate();
			return -1;
		}
		return shaderObject;
	}

	unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource) {

		unsigned int shaderProgramObject{ glCreateProgram() };

		std::cout << vertexShaderSource << '\n';
		std::cout << fragmentShaderSource << '\n';

		// Use Compiled shader
		unsigned int vertexShader{ CompileShader(GL_VERTEX_SHADER, vertexShaderSource) };
		unsigned int fragmentShader{ CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource) };

		// Attach and link shader
		glAttachShader(shaderProgramObject, vertexShader);
		glAttachShader(shaderProgramObject, fragmentShader);
		glLinkProgram(shaderProgramObject);

		// Error check
		// Experimenting error Check
		int result;
		char infoLog[512];
		glGetProgramiv(shaderProgramObject, GL_LINK_STATUS, &result);

		if (result == GL_FALSE) {
			glGetProgramInfoLog(shaderProgramObject, 512, NULL, infoLog);
			std::cout << "Shader Linking: Error " << infoLog << '\n';
			glfwTerminate();
			return -1;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return shaderProgramObject;
	}
}