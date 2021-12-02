

#include "./bufferOld.h"
#include "./vertices.h"
#include "../includes/includes.h"

#include <iostream>

unsigned int bufferObject;

Buffer::Buffer(BufferType type, unsigned int target, int count) {

	switch (type) {
	case BufferType::VAO:
		glGenVertexArrays(count, &bufferObject);
		break;
	default:
		glGenBuffers(count, &bufferObject);
	}
	Buffer::bufferConfigType(type, target);
}

unsigned int Buffer::getBufferObject() {
	return bufferObject;
}

void Buffer::clearBuffer(BufferType type, int count) {
	switch (type) {
	case BufferType::VAO:
		glDeleteVertexArrays(count, &bufferObject);
		return;
	default:
		glDeleteBuffers(count, &bufferObject);
		return;
	}

}

void Buffer::bufferConfigType(BufferType type, unsigned int target) const
{
	switch (type) {
	case BufferType::VBO:
		Buffer::createBufferVBO(target);
		break;
	case BufferType::EBO:
		Buffer::createBufferEBO(target);
		break;
	case BufferType::VAO:
		Buffer::createBufferVAO();
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

void Buffer::createBufferVAO() const {
	glBindVertexArray(bufferObject);
}

void Buffer::setBufferLayout(GLuint index, GLint size, GLsizei stride, GLenum type, GLboolean normalized, const void* pointer) {
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}




