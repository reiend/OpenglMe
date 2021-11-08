
#version 330 core

out vec4 color;

uniform vec4 blinkColor;

void main() {

//	color = vec4(0.2f, 0.5f, 0.2f, 1.0f);
	color = blinkColor;

}