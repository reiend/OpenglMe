
#version 330 core

out vec4 color;
in vec3 color1;
in vec2 textureCoord;

uniform sampler2D textureSample1;
uniform sampler2D textureSample2;

void main() {

//	color = vec4(0.5f, 0.5f, 1.0f, 1.0f);
	
//	color = vec4(color1, 1.0f);
//	color = texture(textureSample, textureCoord) * vec4(color1, 1.0f) ;
	color = mix(texture(textureSample1, textureCoord), texture(textureSample2, textureCoord), 0.05);
}