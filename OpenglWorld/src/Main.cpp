
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>




void resizeRenderView(GLFWwindow* window, int width, int height);
void closeWindowEvent(GLFWwindow* window);


namespace {
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSource);
}

constexpr int WIDTH{ 1000 };
constexpr int HEIGHT{ 800 };

enum class WindowOption {
	OPEN,
	CLOSE,
};

int main(void)
{

	// GLFW init
	glfwInit();

	// Config
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window{ glfwCreateWindow(WIDTH, HEIGHT, "Reiend", NULL, NULL) };
	if (window == NULL) {
		std::cout << "GLFW window: ERROR\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLAD init
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD init: ERROR\n";
		glfwTerminate();
		return -1;
	}

	// Render viewport
	glViewport(0, 0, WIDTH, HEIGHT);

	// Resize render view relative to window
	glfwSetFramebufferSizeCallback(window, resizeRenderView);

	// x,y coordinate discard z axis
	float vertexPos[]{
		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	// Allocate memory for Vertex Buffer id
	unsigned int vertexBufferID;

	// Create A buffer
	glGenBuffers(1, &vertexBufferID);

	// Select buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	// Input data
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertexPos, GL_STATIC_DRAW);


	// Vertex Shader 
	const char* vertexShaderSource{
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec3 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_Position = vec4(position.x, position.y, position.z, 1.0f);\n"
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

	
	unsigned int vs{ CompileShader(GL_VERTEX_SHADER, vertexShaderSource) };
	unsigned int fs{ CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource) };


	while (!glfwWindowShouldClose(window)) {

		// Press ESC to close the window
		closeWindowEvent(window);

		// Clear Screen
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Use color value for GLFW window
		glfwSwapBuffers(window);

		// Handle Events
		glfwPollEvents();
	}


	return 0;
}


// Resize render view according to window's
void resizeRenderView(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}


// Process window close event
void closeWindowEvent(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, static_cast<int>(WindowOption::CLOSE));
	}
}

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
		}
		return shaderObject;
	}
}