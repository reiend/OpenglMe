

#include "./buffer.h"
#include "./vertices.h"
#include "../includes/includes.h"


#include <iostream>


unsigned int bufferObject;

Buffer::Buffer(BufferType type, unsigned int target, int count) {
	glGenBuffers(count, &bufferObject);
	Buffer::bufferConfigType(type, target);
}

unsigned int Buffer::getBufferObject() {
	return bufferObject;
}


void Buffer::bufferConfigType(BufferType type, unsigned int target) const
{
	switch (type) {
	case BufferType::vbo:
		Buffer::createBufferVBO(target);
		break;
	case BufferType::ebo:
		Buffer::createBufferEBO(target);
		break;
	default:
		std::cout << "Buffer init:: ERROR";
		return;
	}
}

void Buffer::createBufferVBO(unsigned int target) const {
	glBindBuffer(target, bufferObject);
	glBufferData(target, Vertices::vertexSize, Vertices::vertexPos, GL_STATIC_DRAW);
}

void Buffer::createBufferEBO(unsigned int target) const {
	glBindBuffer(target, bufferObject);
	glBufferData(target, Vertices::indexSize, Vertices::indexPos, GL_STATIC_DRAW);
}




