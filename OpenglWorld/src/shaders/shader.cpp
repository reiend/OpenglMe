

#include "../shaders/shader.h"

#include <GLAD/glad.h>
#include <iostream>

namespace MakeShader {
	unsigned int compileShader(unsigned int type, const char* source) {
		// Create Shader
		unsigned int shader{ glCreateShader(type) };
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);

		// Error handle
		int result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* message{ static_cast<char*>(_malloca(length * sizeof(float))) };
			glGetShaderInfoLog(shader, length, &length, message);

			std::cout << "Shader create: ERROR ";
			std::cout << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << '\n';
			std::cout << message << '\n';
			return 1;
		}
		else {
			std::cout << "Success\n";
		}

		return shader;
	}
	unsigned int createShader(const char* vertexShader, const char* fragmentShader) {

		unsigned int program{ glCreateProgram() };
		unsigned int vs{ compileShader(GL_VERTEX_SHADER, vertexShader) };
		unsigned int fs{ compileShader(GL_FRAGMENT_SHADER, fragmentShader) };

		// Combine to program
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		// Error Check
		int result;
		char infoLog[512];
		glGetProgramiv(program, GL_LINK_STATUS, &result);
		if (result == GL_FALSE) {
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			std::cout << "Shader Link: ERROR " << infoLog << '\n';
			return 2;
		}
		else {
			std::cout << "Success\n";
		}

		glDeleteShader(vs);
		glDeleteShader(fs);
		return program;
	}

}





