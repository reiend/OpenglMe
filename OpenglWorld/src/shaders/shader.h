

#ifndef SHADER_H
#define SHADER_H

namespace Shader {
	unsigned int CompileShader(unsigned int shaderType, const char* shaderSource);
	unsigned int CreateShader(const char* vertexShaderSource, const char* fragmentShaderSource);
}

#endif