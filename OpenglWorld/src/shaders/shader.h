
#ifndef SHADER_H
#define SHADER_H

#include <GLAD/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

namespace MakeShader {
	unsigned int compileShader(unsigned int type, const char* source);
	unsigned int createShader(const char* vertexShader, const char* fragmentShader);
}

class Shader {
	
public:
	unsigned int ID;
	Shader(const char* vertexPath, const char* fragmentPath) {

		std::string vertexCode;
		std::string fragmentCode;
		std::fstream vertexFile;
		std::fstream fragmentFile;


		// Ensure to throw an error
		vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try {
			// Open file 
			vertexFile.open(vertexPath);
			fragmentFile.open(fragmentPath);

			std::stringstream vs, fs;

			// Read File
			vs << vertexFile.rdbuf();
			fs << fragmentFile.rdbuf();

			// Close File
			vertexFile.close();
			fragmentFile.close();

			// c to str
			vertexCode = vs.str();
			fragmentCode = fs.str();

		}
		catch (std::fstream::failure e) {
			std::cout << "Stream File: ERROR " << e.code() << '\n';
		}
		const char* vertex{ vertexCode.c_str() };
		const char* fragment{ fragmentCode.c_str() };
		std::cout << vertex << '\n';
		std::cout << fragment << '\n';

		ID = MakeShader::createShader(vertex, fragment);
	}
	void useProgram() {
		glUseProgram(ID);
	}

};


#endif