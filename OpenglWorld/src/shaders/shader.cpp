
#include "../includes/includes.h"
#include "./shader.h"

#include <iostream>

//Todo's refactor this
namespace Shader{
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