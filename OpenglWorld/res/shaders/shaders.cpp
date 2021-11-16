
#include "./shaders.h"

#include "../../src/includes/includes.h"

#include <string_view>
#include <iostream>

// Rafactor Error Handling
namespace MakeShader {

	unsigned int compileShader(unsigned int type, std::string shaderSource) {

		unsigned int id{ glCreateShader(type) };
		const char* src{ shaderSource.c_str()};
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		// Error handling
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message{ static_cast<char*>(_malloca(length * sizeof(float))) };
			glGetShaderInfoLog(id, length, &length, message);

			std::cout << "Shader Compile: ERROR ";
			std::cout << ((type == GL_VERTEX_SHADER) ? "vertex" : "fragment") << '\n';
			std::cout << message << '\n';
			return 1;
		}
		return id;
	}

	unsigned int createShader(std::string vertexShader, std::string fragmentShader) {

		unsigned int program{ glCreateProgram() };
		unsigned int vs{compileShader(GL_VERTEX_SHADER, vertexShader)};
		unsigned int fs{compileShader(GL_FRAGMENT_SHADER, fragmentShader)};

		// Link, attach, 
		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);


		// Error Handling 
		int result;
		char message[512];
		glGetProgramiv(program, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {
			glGetProgramInfoLog(program, 512, nullptr, message);

			std::cout << "SHADER Create: ERROR ";
			std::cout << message << '\n';

			return 2;
		}
		glDeleteShader(vs);
		glDeleteShader(fs);
		return program;
	}
}









