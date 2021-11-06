

extern const char* vertexShaderSource{
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec3 position;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		"}\n"
};
extern const char* fragmentShaderSource{
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		"\n"
		"void main()\n"
		"{\n"
		"  color = vec4(0.2f, 0.5f, 0.2f, 1.0f);\n"
		"}\n"
};
