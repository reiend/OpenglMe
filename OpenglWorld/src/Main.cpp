
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

void resizeRenderView(GLFWwindow* window, int width, int height);
void closeWindowEvent(GLFWwindow* window);


namespace {
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSource);
	unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
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


	// Matrix for A
	float vervtexPos[][9]{

		// Letter A
		{
			-1.0f, -0.5f, 0.0f,
			-0.90f,-0.5f, 0.0f,
			-0.80f, 0.5f, 0.0f
		},

		{
			-0.80f, 0.5f, 0.0f,
			-0.70f, 0.5f, 0.0f,
			-0.90f,-0.5f, 0.0f,
		},

		{
			-0.80f, 0.5f, 0.0f,
			-0.60f, -0.5f, 0.0f,
			-0.50f, -0.5f, 0.0f,
		},

		{
			-0.50f, -0.5f, 0.0f,
			-0.80f, 0.5f, 0.0f,
			-0.70f, 0.5f, 0.0f
		},

		{
			-0.90f, -0.20f, 0.0f,
			-0.85f, -0.10f, 0.0f,
			-0.60f, -0.20f, 0.0f,
		},

		{
			-0.60f, -0.20f, 0.0f,
			-0.65f, -0.10f, 0.0f,
			-0.85f, -0.10f, 0.0f,
		},

		// Letter T
		{
			-0.25f,  0.5f, 0.0f,
			-0.25f,  0.4f, 0.0f,
			 0.25f,  0.5f, 0.0f,
		},

		{
			 0.25f,  0.5f, 0.0f,
			 0.25f,  0.4f, 0.0f,
			-0.25f,  0.4f, 0.0f,
		},

		{
			-0.05f,  0.4f, 0.0f,
			 0.05f,  0.4f, 0.0f,
			-0.05f, -0.5f, 0.0f,
		},

		{
			 0.05f,  0.4f, 0.0f,
			-0.05f, -0.5f, 0.0f,
			 0.05f, -0.5f, 0.0f,

		},


		// letter O
		{
			1.0f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, -0.4f, 0.0f,
		},

		{
			1.0f, -0.5f, 0.0f,
			1.0f, -0.4f, 0.0f,
			0.5f, -0.4f, 0.0f,
		},

		{
			1.0f, -0.5f, 0.0f,
			0.9f, -0.5f, 0.0f,
			1.0f,  0.5f, 0.0f,
		},

		{
			1.0f,  0.5f, 0.0f,
			0.9f,  0.5f, 0.0f,
			0.9f, -0.5f, 0.0f,
		},

		{
			1.0f,  0.5f, 0.0f,
			1.0f,  0.4f, 0.0f,
			0.5f,  0.5f, 0.0f
		},

		{
			0.5f,  0.5f, 0.0f,
			0.5f,  0.4f, 0.0f,
			1.0f,  0.4f, 0.0f,
		}, 

		{
			0.5f,  0.5f, 0.0f,
			0.6f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
		},

		{
			0.5f, -0.5f, 0.0f,
			0.6f, -0.5f, 0.0f,
			0.6f,  0.5f, 0.0f,
	    },

	};

	const int bufferCountK{ static_cast<int>(std::size(vervtexPos)) };

	// First triangle
	unsigned int vbo[bufferCountK];
	unsigned int vao[bufferCountK];

	glGenVertexArrays(bufferCountK, vao);
	glGenBuffers(bufferCountK, vbo);

	// Letter A
	for (int i{ 0 }; i < bufferCountK; ++i) {
		glBindVertexArray(vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vervtexPos[i]), vervtexPos[i], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(0));
		glEnableVertexAttribArray(0);
	}



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
		"  color = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
		"}\n"
	};

	const char* fragmentShaderSource2{
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  color = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
		"}\n"
	};	
	const char* fragmentShaderSource3{
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
		"}\n"
	};
	

	unsigned int shaderProgram1{ CreateShader(vertexShaderSource, fragmentShaderSource) };
	unsigned int shaderProgram2{ CreateShader(vertexShaderSource, fragmentShaderSource2) };
	unsigned int shaderProgram3{ CreateShader(vertexShaderSource, fragmentShaderSource3) };

	//glBindVertexArray(vertexArrayObject);

	while (!glfwWindowShouldClose(window)) {

		// Press ESC to close the window
		closeWindowEvent(window);

		// Clear Screen
		glClearColor(0.1f, 0.4f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram1);
		for (int i{ 0 }; i < 6; ++i) {
			glBindVertexArray(vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		glUseProgram(shaderProgram2);
		for (int i{ 6 }; i < 10; ++i) {
			glBindVertexArray(vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		glUseProgram(shaderProgram3);
		for (int i{ 10 }; i < bufferCountK; ++i) {
			glBindVertexArray(vao[i]);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}


		// Use color value for GLFW window
		glfwSwapBuffers(window);

		// Handle Events
		glfwPollEvents();
	}


	glDeleteVertexArrays(bufferCountK, vao);
	glDeleteBuffers(bufferCountK, vbo);

	glDeleteProgram(shaderProgram1);
	glDeleteProgram(shaderProgram2);


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