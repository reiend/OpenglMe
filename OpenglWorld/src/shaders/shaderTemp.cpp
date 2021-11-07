

extern const char* vertexShaderSource{
		"#version 330 core\n"
		"\n"
		"layout (location = 0) in vec3 position;\n"
		"layout (location = 1) in vec3 zaido;\n"
		"\n"
		//"out vec4 meColor;"
		"out vec3 zaidoColor;"
		"\n"
		"void main()\n"
		"{\n"
		"  gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
		//"  meColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);\n"
		"  zaidoColor = zaido;\n"
		"}\n"
};
extern const char* fragmentShaderSource{
		"#version 330 core\n"
		"\n"
		"out vec4 color;\n"
		//"in vec4 meColor;\n"
		"in vec3 zaidoColor;\n"
		//"uniform vec4 cpuColor;\n"
		"\n"
		"void main()\n"
		"{\n"
		//"  color = vec4(0.2f, 0.5f, 0.2f, 1.0f);\n"
		//"  color = meColor;\n"
		"  color = vec4(zaidoColor, 1.0f);\n"
		"}\n"
};
