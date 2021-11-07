


#ifndef  SHADER_C_H
#define  SHADER_C_H

#include "../includes/includes.h"
#include "../shaders/shader.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class ShaderC {
	
public:

	unsigned int ID;
	ShaderC(const char* vertexPath, const char* fragmentPath) {

		std::string vertex;
		std::string fragment;
		std::ifstream vertexShaderFile;
		std::ifstream fragmentShaderFile;

		// to ensure fstream throw exception
		vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		std::cout << "Hellow\n";
		std::cout << vertexPath << '\n';
		try {
			vertexShaderFile.open(vertexPath);
			fragmentShaderFile.open(fragmentPath);
			
			std::stringstream vs, fs;

			// read file into stream
			vs << vertexShaderFile.rdbuf();
			fs << fragmentShaderFile.rdbuf();

			// end file mod
			vertexShaderFile.close();
			fragmentShaderFile.close();

			// stream -> str
			vertex = vs.str();
			fragment = fs.str();
		}
		catch (std::ifstream::failure error) {
			std::cout << "Stream read: ERROR\n";
		}

		// c -> c++ str
		const char* vertexShaderSource{ vertex.c_str() };
		const char* fragmentShaderSource{ fragment.c_str() };
		std::cout << vertexShaderSource << '\n';

		ID = Shader::CreateShader(vertexShaderSource, fragmentShaderSource);
	}	

	void use() {
		glUseProgram(ID);
	}

	// Uniform
	void set(const std::string& name, bool value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
	}
	void set(const std::string& name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (value));
	}
	void set(const std::string& name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), (value));
	}

};



#endif