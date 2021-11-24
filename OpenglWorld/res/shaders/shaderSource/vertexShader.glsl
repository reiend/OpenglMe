

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texturePos;


out vec3 color1;
out vec2 textureCoord;

void main() {

	gl_Position = vec4(position.xyz, 1.0f);
	color1 = color;
	textureCoord = texturePos;
}