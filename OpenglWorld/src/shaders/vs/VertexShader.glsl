#version 330 core
layout(location = 0) in vec3 position;
vec2 d2;
vec4 d4 = position.xyzz;
vec3 d3 = position.xyz;
vec2 d1 = d4.wy;
vec4 oneD = vec4(position.xyz, 1.0);

void main(){
	gl_Position = vec4(position.xyz, 1.0);
}

