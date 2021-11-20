

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;


out vec3 color1;

void main() {

	gl_Position = vec4(position.xyz, 1.0f);
	color1 = color;
}