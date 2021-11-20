
#version 330 core

out vec4 color;
in vec3 color1;

void main() {

//	color = vec4(0.5f, 0.5f, 1.0f, 1.0f);
	color = vec4(color1, 1.0f);
}