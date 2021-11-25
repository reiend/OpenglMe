

#ifndef SHADERS_H
#define SHADERS_H


#include "../../src/includes/includes.h"

#include <sstream>
#include <fstream>
#include <iostream>

namespace MakeShader {

	unsigned int compileShader(unsigned int type, std::string shaderSource);
	unsigned int createShader(std::string vertexShader, std::string fragmentShader);
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

		std::cout << vertexCode << '\n';
		std::cout << fragmentCode << '\n';

		ID = MakeShader::createShader(vertexCode, fragmentCode);
	}

	void useProgram() {
		glUseProgram(ID);
	}

	void setInt(const std::string& name, int value) const { // to use only const value and avoid modification
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
};



#endif